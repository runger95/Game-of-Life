#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <unistd.h>
#include <string.h>


/*
Main Function, with main loop
Don't need to worry about thr
Generates initial state
handles I/O, 
updates board
prints board
*/

//defines for Board Size (includes border)
//R3.000
#define MAX_ROW 12
#define MAX_COL 12

//board
char boardArray[MAX_ROW][MAX_COL];


void initializeBoard(){
/*
function which creates board
R9
*/
   for (int i = 0; i < MAX_ROW; i++){
      for (int j = 0; j < MAX_COL; j++){
         if ((i == 0 || i == MAX_ROW-1) && (j == 0 || j == MAX_COL-1 )){
            boardArray[i][j] = '+';
         }
         else if (i == 0 || i == MAX_ROW-1) {
            boardArray[i][j] = '-';
         }
         else if (j == 0 || j == MAX_COL-1 ){
            boardArray[i][j] = '|';
         }
         else{
            boardArray[i][j] = ' ';
         }
      }        
   }

   //extra definition for testing
   //blinker
   boardArray[1][3] = '*';
   boardArray[2][3] = '*';
   boardArray[3][3] = '*';

   //toad
   boardArray[7][4] = '*';
   boardArray[7][5] = '*';
   boardArray[7][6] = '*';
   boardArray[6][5] = '*';
   boardArray[6][6] = '*';
   boardArray[6][7] = '*';

}


void printBoard(){
/*
Is called to print the board
is given the board and then loops to print it
*/
   for (int i = 0; i < MAX_ROW; i++){
      for (int j = 0; j < MAX_COL; j++){
         printf("%c ",boardArray[i][j]);
      }
      printf("\n");
   }
}


int checkGameOver(){
/*
Check if no live cells - returns gameOver
R11
*/
   for (int i = 1; i < MAX_ROW-1; i++){
      for (int j = 1; j < MAX_COL-1; j++){
         if (boardArray[i][j] == '*'){
            return 0;
         }
      }      
   }
   printf("Game Ended Early\n");
   return 1;
}



#if 0
Dont want this because easier to have in the other function

void updateBoardMath(int count){
/*
Given count, places either the " " or "*"
*/

}
#endif


void updateBoard(){
   /*
   R4.000
   R7
   R8
   R5
   R6
   Creates a copy of the board with which to do math.
   Then iterates through cells to determine alive/dead
   If has 3 neighbours, then it should be alive (alive stays alive, dead becomes alive)
   If it has 2 neighbours but is alive, then it stays alive   
   */
   char oldBoard[MAX_ROW][MAX_COL]; //old state, we update the new
   int countNeighbours; //number of alive Neighbours


   //populate the old state with the current board, pre-time step. Need to do it this way because can't assign an array to another array :(
   for (int i = 0; i < MAX_ROW; i++){
      for (int j = 0; j < MAX_COL; j++){
         oldBoard[i][j] = boardArray[i][j];
      }
   } 
   
   //loop x/y, ignoring borders cause edges are just dead in this definition
   for (int x = 1; x < MAX_ROW-1; x++){
      for (int y = 1; y < MAX_COL-1; y++){
         countNeighbours = 0;
         
         //loop grid around the cell
         for (int a = x-1; a <= x+1; a++){
            for (int b = y-1; b <= y+1; b++){
               if ( a == x && b == y){
                  //do nothing since we are the cell
               }
               else if (oldBoard[a][b] == '*'){
                  countNeighbours += 1;
               }
            }
         }
         
         // logic to determine if cell is alive next pass
         if (countNeighbours == 3 || (countNeighbours == 2 && oldBoard[x][y] =='*')){
            boardArray[x][y] = '*';
         }
         else {
            boardArray[x][y] = ' ';
         }
         
      }
   }
}


void playerPlaceAlive(){
//R2.000
//looks for keystroke and places alive cells based on x/y
//takes "add" for alive, "del" for delete (deaden) or "end"
//if out of range, then throw error message
//ends when "end" is sent
   char inputCode[] = "Run";
   int inputX = 3;
   int inputY = 3;

   //strcmp returns 0 if both are the same
   while (0 != strcmp(inputCode, "end")){
      printf("Enter Action (add, del, ent)\n");
      scanf("%s", inputCode);
      
      //not sure if I need this if case...
      if(0 == strcmp(inputCode, "ent")){
         printf("User input terminated\n");
         break; //get out of the whole loop.
      }
      else if (0 == strcmp(inputCode, "add") || 0 == strcmp(inputCode, "del")){
         printf("Enter Row: ");
         scanf("%d", &inputX);
         printf("Enter Col: ");
         scanf("%d", &inputY);

         if (inputX < 1 || inputX > MAX_ROW -1 || inputY <1 || inputY > MAX_COL -1){
            //invalid cell input
            printf("Cell Input our of range, try again\n");
            continue;
         }
         else{
            boardArray[inputX][inputY] = '*'; 
         } 
      } 
      else{
         printf("Invalid action!\n");
         continue; //skip to give user another try
      }

   }

   printf("GameTime\n"); //test print
}



int main() {
   /*
   Main function for the Game.
   Creates the Board, then allows the player to place certain cells
   Loops 10 times
   */

   int gameOver = 10; //R10.000: drives 10 loop Game.
      
   printf("Conway's Game Of Life that I am making to learn C/Git\n");
   

   initializeBoard(); //create Board
   playerPlaceAlive(); //get player to place initial stuff
   
   // Main Loop, which runs 10 times or until game is over.
   while ( 0 != gameOver){
      printBoard();
      updateBoard();
      gameOver -= 1;
      sleep(1);
      //gameOver = checkGameOver(); dont like this because it sets it to 1 if over so it runs another loop, see below which is more clear. 
      if (checkGameOver()){
         gameOver = 0;
      }
   }
   
   printBoard();    //prints for a final time
   printf("Game Completed");

   return 0;
}