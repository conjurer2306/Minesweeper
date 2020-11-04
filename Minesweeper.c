#include<stdio.h>
#include <stdbool.h>
#define MAXEDGE 25 
#define MAXMINES 99 
#define MOVESIZE 526
#define BEGINNER 1 
#define INTERMEDIATE 2 
#define ADVANCED 3  

int EDGE ; 
int MINES ; 

bool Valid(int row, int column) 
{  
	return (column < EDGE)	&& (column >= 0) && (row < EDGE) && (row >= 0); 
} 
 
bool MinePresent (int row, int column, char board[][MAXEDGE]) 
{ 
	if (board[row][column] == '*') 
		return (true); 
	else
		return (false); 
} 

void UserMakeMove (int *x, int *y, int gamemove[][2], int IndexOfCurrentMove) 
{ 
	*x = gamemove[IndexOfCurrentMove][0]; 
	*y = gamemove[IndexOfCurrentMove][1]; 
	scanf("%d %d", x, y); 
	return; 
} 

void AssignUserMoves (int gamemove[][2], int gamemoveLeft) 
{ 
	bool mark[MAXEDGE*MAXEDGE]; 

	memset(mark, false, sizeof(mark)); 

	int i;
	for (i=0; i<gamemoveLeft; ) 
	{ 
		int random = rand() % (EDGE*EDGE); 
		int x = random / EDGE; 
		int y = random % EDGE; 

		if (mark[random] == false) 
		{ 
		
			gamemove[i][0]= x; 
			
			gamemove[i][1] = y; 

			mark[random] = true; 
			i++; 
		} 
	} 

	return; 
} 

void DisplayBoard(char UserBoard[][MAXEDGE]) 
{ 
	int i,j; 

	printf (" "); 

	for (i=0; i<EDGE; i++) 
		printf ("%d ", i); 

	printf ("\n\n"); 

	for (i=0; i<EDGE; i++) 
	{ 
		printf ("%d ", i); 

		for (j=0; j<EDGE; j++) 
			printf ("%c ", UserBoard[i][j]); 
		printf ("\n"); 
	} 
	return; 
} 


int AdjacentMinesCount(int row ,int column ,int mines[][2], char OriginalBoard[][MAXEDGE]) 
{ 

	int i; 
	int count = 0; 
	
		if (Valid (row-1, column) == true) 
		{ 
			if (MinePresent (row-1, column, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row+1, column) == true) 
		{ 
			if (MinePresent (row+1, column, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row, column+1) == true) 
		{ 
			if (MinePresent (row, column+1, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row, column-1) == true) 
		{ 
			if (MinePresent (row, column-1, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row-1, column+1) == true) 
		{ 
			if (MinePresent (row-1, column+1, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row-1, column-1) == true) 
		{ 
			if (MinePresent (row-1, column-1, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row+1, column+1) == true) 
		{ 
			if (MinePresent (row+1, column+1, OriginalBoard) == true) 
			count++; 
		} 

		if (Valid (row+1, column-1) == true) 
		{ 
			if (MinePresent (row+1, column-1, OriginalBoard) == true) 
			count++; 
		} 

	return (count); 
} 

bool MinesweeperUtil(char UserBoard[][MAXEDGE], char OriginalBoard[][MAXEDGE], 
			int mines[][2], int row, int column, int *gamemoveLeft) 
{ 

	if (UserBoard[row][column]!='-') 
		return (false); 

	int i, j; 

	if (OriginalBoard[row][column] == '*') 
	{ 
		UserBoard[row][column]='*'; 

		for (i=0; i<MINES; i++) 
			UserBoard[mines[i][0]][mines[i][1]]='*'; 

		DisplayBoard (UserBoard); 
		printf ("\n THE END! YOU LOST THE GAME :(\n"); 
		return (true) ; 
	} 

	else
	{ 

		int count = AdjacentMinesCount(row, column, mines, OriginalBoard); 
		(*gamemoveLeft)--; 

		UserBoard[row][column] = count + '0'; 

		if (!count) 
		{ 
			
			if (Valid (row-1, column) == true) 
			{ 
				if (MinePresent (row-1, column, OriginalBoard) == false) 
				MinesweeperUtil(UserBoard, OriginalBoard, mines, row-1, column, gamemoveLeft); 
			} 

			if (Valid (row+1, column) == true) 
			{ 
				if (MinePresent (row+1, column, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row+1, column, gamemoveLeft); 
			} 
 
			if (Valid (row, column+1) == true) 
			{ 
				if (MinePresent (row, column+1, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row, column+1, gamemoveLeft); 
			} 

			if (Valid (row, column-1) == true) 
			{ 
				if (MinePresent (row, column-1, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row, column-1, gamemoveLeft); 
			} 

			if (Valid (row-1, column+1) == true) 
			{ 
				if (MinePresent (row-1, column+1, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row-1, column+1, gamemoveLeft); 
			} 

			if (Valid (row-1, column-1) == true) 
			{ 
				if (MinePresent (row-1, column-1, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row-1, column-1, gamemoveLeft); 
			} 

			if (Valid (row+1, column+1) == true) 
			{ 
				if (MinePresent (row+1, column+1, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row+1, column+1, gamemoveLeft); 
			} 

			if (Valid (row+1, column-1) == true) 
			{ 
				if (MinePresent (row+1, column-1, OriginalBoard) == false) 
					MinesweeperUtil(UserBoard, OriginalBoard, mines, row+1, column-1, gamemoveLeft); 
			} 
		} 

		return (false); 
	} 
} 
void PlantMineBombs(int mines[][2], char OriginalBoard[][MAXEDGE]) 
{ 
	bool mark[MAXEDGE*MAXEDGE]; 

	memset (mark, false, sizeof (mark)); 
	int i;

	for (i=0; i<MINES; ) 
	{ 
		int random = rand() % (EDGE*EDGE); 
		int x = random / EDGE; 
		int y = random % EDGE; 

		if (mark[random] == false) 
		{  
			mines[i][0]= x; 
			
			mines[i][1] = y; 

			OriginalBoard[mines[i][0]][mines[i][1]] = '*'; 
			mark[random] = true; 
			i++; 
		} 
	} 

	return; 
} 

void Initialize (char OriginalBoard[][MAXEDGE], char UserBoard[][MAXEDGE]) 
{ 
	srand (time (NULL)); 
int i;
	for (i=0; i<EDGE; i++) 
	{ int j;
		for (j=0; j<EDGE; j++) 
		{ 
			UserBoard[i][j] = OriginalBoard[i][j] = '-'; 
		} 
	} 

	return; 
} 
void ReplaceTheMines (int row, int column, char board[][MAXEDGE]) 
{ int i,j;
	for (i=0; i<EDGE; i++) 
	{ 
		for (j=0; j<EDGE; j++) 
			{ 
				if (board[i][j] != '*') 
				{ 
					board[i][j] = '*'; 
					board[row][column] = '-'; 
					return; 
				} 
			} 
	} 
	return; 
} 
void PlayMinesweeper () 
{  
	bool gameOver = false; 
	char OriginalBoard[MAXEDGE][MAXEDGE], UserBoard[MAXEDGE][MAXEDGE]; 

	int gamemoveLeft = EDGE * EDGE - MINES, x, y; 
	int mines[MAXMINES][2]; 
	int gamemove[MOVESIZE][2];

	Initialize (OriginalBoard, UserBoard); 

	PlantMineBombs (mines, OriginalBoard); 

	AssignUserMoves (gamemove, gamemoveLeft); 

	int IndexOfCurrentMove = 0; 
	while (gameOver == false) 
	{ 
		printf ("Board's Current Status: \n"); 
		DisplayBoard (UserBoard); 

		UserMakeMove (&x, &y, gamemove, IndexOfCurrentMove); 

		if (IndexOfCurrentMove == 0) 
		{ 
			if (MinePresent (x, y, OriginalBoard) == true) 
				ReplaceTheMines (x, y, OriginalBoard); 
		} 

		IndexOfCurrentMove ++; 

		gameOver = MinesweeperUtil (UserBoard, OriginalBoard, mines, x, y, &gamemoveLeft); 

		if ((gameOver == false) && (gamemoveLeft == 0)) 
		{ 
			printf ("\n YAYYY!!! YOU WON THE GAME :) \n"); 
			gameOver = true; 
		} 
	} 

	return; 
} 

void LevelOfDifficulty () 
{ 
	int Level; 
  
    printf ("Choose Difficulty Level\n"); 
    printf ("BEGINNER: Press 1 (10 Mines and 9 * 9 Cells)\n"); 
    printf ("INTERMEDIATE: Press 2 (40 Mines and 16 * 16 Cells)\n"); 
    printf ("ADVANCED: Press 3 (99 Mines and 24 * 24 Cells)\n"); 
  
    scanf ("%d", &Level); 

	if (Level == BEGINNER) 
	{ 
		EDGE = 9; 
		MINES = 10; 
	} 

	if (Level == INTERMEDIATE) 
	{ 
		EDGE = 16; 
		MINES = 40; 
	} 

	if (Level == ADVANCED) 
	{ 
		EDGE = 24; 
		MINES = 99; 
	} 

	return; 
} 

int main() 
{ 	
	LevelOfDifficulty (); 
	PlayMinesweeper (); 
	return (0); 
}

