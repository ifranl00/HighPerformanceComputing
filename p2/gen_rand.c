#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

//const int commands = 4; //number of commands to set the title and plot both int and double random numbers vs sequence numbers (2 plots)



int find(int array[], int element, int size); // find if there an element in a specific row

int main(){

  int a,i,j,k,l; 

  srand(time(NULL)); //seed for generating differnt sequence of random numbers

  printf("Insert the number of rows of the sparse matrix:\n"); //ask by console to insert number of rows of matrix to make square matrix of selected dimensions
  scanf("%d", &a); // saved the values entered by console
  int matrix[a][a];

  /***********  PART 1: fill the main diagonal of the matrix in the range 1-2 and others in range 0-1 ***********/

    for (i = 0; i < a; i++)
    {
      for (j = 0; j < a; j++)
      {
        if(i == j){ // main diagonal of the matrix

          matrix[i][j] = rand() % (2 + 1 - 1) + 1; // rand between 2 and 1

        }else{
          matrix[i][j] = rand() % (1 + 1); // rand between 1 and 0
        }
      }

    }
    //print sparse matrix generated

    printf("\nThe sparse matrix generated:\n");

    for (int i = 0; i < a; i++)
    {
      for (int j = 0; j < a; j++)
      {
        
        printf("%d ",matrix[i][j]);
      }
      printf("\n");
    }


 /*********** PART 2: fill the new sparse matrix with the condition of a parameter that has been set to control how many elemnets are non-zero per row (k) ***********/

    do{
      printf("\nNow please enter the number of non-zero elements in each row:\n"); //ask by console to insert number of rows of matrix to make square matrix of selected dimensions
      scanf("%d", &k); // saved the values entered by console
     
      if(k<1 || k>a){
        printf("Error evaluating the matrix. The parameter entered must be between 1 and %d\n",a);
      }
    }while(k<1 || k>a);
    
       int matrix2[a][a];
      int guard[a][k-1]; // guard is a variable of how many elements of echa row are set to be non-zero without counting the elememt which belongs to the main diagonal
      int pos = -1;
      for (i = 0; i < a; i++) // for each row 
      {
        for (j = 0; j < k-1; j++) //save the positions where non-zero elements are random located
        {
          do{
            pos = rand() % (((a) + 1) - 1) + 1; // rand between k-1 and 1

          }while(i+1 == pos || find(guard[i],pos,k-1) == 1); // while the random position generated is equals to the current row to avoid de diagonal that is set from previous exercise to non be zero or this pos already has been generated
          guard[i][j] = pos;
        }
      }

      for (i = 0; i < a; i++)
      {
        for (j = 0; j < a; j++)
        {
          if(i == j){ // main diagonal of the matrix

            matrix2[i][j] = rand() % (2 + 1 - 1) + 1; // rand between 2 and 1

          }else{ // the value of non main diagonal elements will be 0 or 1 

            if(find(guard[i],j+1,k-1) == 1){ // if current column is in the random selected to be a non-zero
              matrix2[i][j] = 1; // non-zero

            }else{
              matrix2[i][j] = 0; // zero
            }
          }
        }
      }

      //print sparse matrix generated
      printf("\nThe sparse matrix with %d non-zero elements pero row is generated:\n",k);

      for (int i = 0; i < a; i++)
      {
        for (int j = 0; j < a; j++)
        {
          printf("%d ",matrix2[i][j]);
        }
        printf("\n");
      }
}

int find(int array[], int element, int size) {

  int i = 0;
  
  for (i = 0; i < size; i++)
  {
    if(array[i] == element){
      return 1; // element is found
    }
  }
  return 0; // is not found
}

