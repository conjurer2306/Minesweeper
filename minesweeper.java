int gridW; // grid width
int gridH; // grid height
int numMines; // number of mines on the board
int[][] mines; // entry is 1 for having a mine and 0 for not
boolean[][] flags; // entry is true if you have flagged that spot
boolean[][] revealed; // entry is true if that spot is revealed
int calcNear(int x, int y) {
  int i=0;
  for (int offsetX=-1; offsetX<=1; offsetX++) {
    for (int offsetY=-1; offsetY<=1; offsetY++) {
      i+=mines[offsetX+x][offsetY+y];
    }
  }
  return i;
}
boolean outBounds(int x,int y){
  return x<0||y<0||x>=gridW||y>=gridH;
}
int calcNear(int x, int y) {
  if(outBounds(x,y))return 0;
  int i=0;
  for (int offsetX=-1; offsetX<=1; offsetX++) {
    for (int offsetY=-1; offsetY<=1; offsetY++) {
      if (outBounds(offsetX+x, offsetY+y))continue;
      i+=mines[offsetX+x][offsetY+y];
    }
  }
  return i;
}
void reveal(int x, int y){
  if(outBounds(x,y))return;
  if(revealed[x][y])return;
  revealed[x][y]=true;
  if(calcNear(x,y)!=0)return;
  reveal(x-1,y-1);
  reveal(x-1,y+1);
  reveal(x+1,y-1);
  reveal(x+1,y+1);
  reveal(x-1,y);
  reveal(x+1,y);
  reveal(x,y-1);
  reveal(x,y+1);
}
void settings(){
  size(gridW*cellSize, gridH*cellSize);
}
void setup(){
  //initialize and clear the arrays
  mines=new int[gridW][gridH];
  flags=new boolean[gridW][gridH];
  revealed=new boolean[gridW][gridH];
  for(int x=0;x<gridW;x++){
    for(int y=0;y<gridH;y++){
      mines[x][y]=0;
      flags[x][y]=false;
      revealed[x][y]=false;
    }
  }
}
//Place numMines mines on the grid
void placeMines(){
  int i=0;
  while(i<numMines){//We don't want mines to overlap, so while loop
    int x=int(random(gridW));
    int y=int(random(gridH));
    if(mines[x][y]==1)continue;
    mines[x][y]=1;
    i++;
  }
}
//Clear the mines
void clearMines() {
  for (int x=0; x<gridW; x++) {
    for (int y=0; y<gridH; y++) {
      mines[x][y]=0;
    }
  }
}
