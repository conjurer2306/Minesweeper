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


//mousepress function
//We don't want the first click to be a mine
boolean firstClick=true;
void mousePressed() {
  int x=int(mouseX/cellSize);
  int y=int(mouseY/cellSize);
  //Right-click is flagging or de-flagging a square
  if (mouseButton==RIGHT) {
    flags[x][y]=!flags[x][y];
    return;
  } else {//left-click
    //Avoid making the first click a mine
    if (firstClick) {
      firstClick=false;
      do {
        clearMines();
        placeMines();
      } while (calcNear(x,y)!=0);
    }
    //Check for game loss
    if (mines[x][y]!=0) {
      println("Dang!");
      exit();
    } else {//If game not lost, reveal starting from that square
      reveal(x, y);
    }
  }
}
void draw() {
  background(0);
  //For each cell
  for (int x=0; x<gridW; x++) {
    for (int y=0; y<gridH; y++) {
      //The colors alternate for texture
      color col1=color(2*255/5);
      color col2=color(3*255/5);
      color txtColor=color(0);
      int near=calcNear(x, y);
      if (flags[x][y]) {
        col1=color(255, 0, 0);
        col2=color(4*255/5, 255/5, 255/5);
      } else if (revealed[x][y]) {
        col1=color(255/2);
        col2=color(255/2);
      }
      if (near==1)txtColor=color(255*1/4, 255*1/4, 255*3/4);
      if (near==2)txtColor=color(255*1/4, 255*3/4, 155*1/4);
      if (near==3)txtColor=color(255, 0, 0);
      if (near==4)txtColor=color(0, 0, 255);
      if (near==5)txtColor=color(255, 0, 0);
      boolean alternate=(x+y)%2==0;
      if (alternate) {
        fill(col2);
        stroke(col2);
      } else {
        fill(col1);
        stroke(col1);
      }
      //if(mines[x][y]>0){
      //fill(0,255,0);
      //stroke(0,255,0);
      //}
      rect(x*cellSize, y*cellSize, cellSize, cellSize);
      //If there is a mine near this spot and it is revealed
      if (near>0&&revealed[x][y]) {
        fill(txtColor);
        noStroke();
        textAlign(LEFT, TOP);
        textSize(cellSize);
        text(""+near, x*cellSize, y*cellSize);
      }
    }
  }
}
