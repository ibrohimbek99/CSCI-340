/*
Ibrahim Pulatov
Professor Haque
CSCI-340
KNIGHT TOUR PROBLEM
*/
// C program for Knight Tour problem 
//Remember it might not generate any output since it is taking too long for larger values of N
#include <stdio.h> 
#define N 6



int solveKTUtil(int x, int y, int movei, int sol[N][N], 
				int xMove[], int yMove[]); 

/* A utility function to check if i,j are valid indexes 
for N*N chessboard */
int isSafe(int x, int y, int sol[N][N]) 
{ 
 if ((x >= 0) && (y >= 0) && (x < N) && (y < N) && (sol[x][y] == -1)){
   return 1;
 }
 return 0;
} 

/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N]) 
{ 
  int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d\t",sol[i][j]);
        }
        printf("\n\n");
    }
} 

/* This function solves the Knight Tour problem using 
Backtracking. This function mainly uses solveKTUtil() 
to solve the problem. It prints "Solutions doesn't exist" if
no complete tour is possible, otherwise prints the 
tour. */
void solveKT() 
{ 
  int sol[N][N];
  for(int i = 0 ; i < N; i++){
    for(int j = 0; j < N; j++){
      sol[i][j] = -1;
    }
  }

  int xMove[8]={-2, -1, 1, 2, 2, 1, -1, -2};
  int yMove[8]={1, 2, 2, 1, -1, -2, -2, -1};

  sol[0][0] = 0;
  if(solveKTUtil(0,0,1,sol,xMove,yMove)){
    printSolution(sol);
  }
  else{
    printf("no solution\n");
  }
} 

/* A recursive utility function to solve Knight Tour problem */
int solveKTUtil(int x, int y, int movei, int sol[N][N], int xMove[N], int yMove[N]) 
{ 
  int newx, newy;
  if(movei == N*N)
    return true;

  for(int i = 0; i < 8; i++){
      newx= x + xMove[i];
      newy= y + yMove[i];

      if(isSafe(newx, newy,sol)){
        sol[newx][newy] = movei;
        if(solveKTUtil(newx, newy, movei + 1, sol, xMove, yMove) == 1){
          return 1;
        }
        
          sol[newx][newy] = -1;
        
      }
  }
  return 0;
} 

/* Driver program to test above functions */
int main() 
{ 
	solveKT(); 
	return 0; 
} 
