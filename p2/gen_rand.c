#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

//const int commands = 4; //number of commands to set the title and plot both int and double random numbers vs sequence numbers (2 plots)

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
      int matrix2[a][a];

      if(k<1 || k>a){
        printf("Error evaluating the matrix. The parameter entered must be between 1 and %d\n",a);
      }


      int guard = k -1; // guard is a variable of how many elements of echa row are set to be non-zero without counting the elememt which belongs to the main diagonal

      for (i = 0; i < a; i++)
      {
        for (j = 0; j < a; j++)
        {
          if(i == j){ // main diagonal of the matrix

            matrix2[i][j] = rand() % (2 + 1 - 1) + 1; // rand between 2 and 1

          }else{ // the value of non main diagonal elements will be 0 or 1 

            if(guard > 0){ // till the set of total non-zero erlements is reached

              matrix2[i][j] = 1; // non-zero for a total of k elements per row
              guard--; // decrease because one non-zero element has been set
            }else{
              matrix2[i][j] = 0; // zero for the rest per row
            }
          }
            
        } guard = k-1; // reset the guard to its original for each row
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

    }while(k<1 || k>a);
      

  //////-------------------------------------- RANDOM INT--------------------------------------------//////
  
  /* Elaboration of the commands to set horizontal lines given a interval */
  /*
    char string_j[64];
    sprintf(string_j,"%d",j); // string value of j 

    char commandArrowJ[150] = "set arrow from graph 0,first "; // first part to set an arrow with gnuplot
    strcat(commandArrowJ,string_j); // concat multiple times
    strcat(commandArrowJ," to graph 1,first ");
    strcat(commandArrowJ,string_j);
    strcat(commandArrowJ," nohead"); // finally we have "set arrow from graph 0,first j to graph 1,first j nohead"


    char string_k[64];
    sprintf(string_k,"%d",k); // string value of k

    char commandArrowK[150] = "set arrow from graph 0,first "; // first part to set an arrow with gnuplot
    strcat(commandArrowK,string_k); //concat multiple times
    strcat(commandArrowK," to graph 1,first ");
    strcat(commandArrowK,string_k);
    strcat(commandArrowK," nohead"); // finally we have "set arrow from graph 0,first k to graph 1,first k nohead"

    char * autognuplot2[4];// char array to execute gnuplot commands to plot second plot with the data of the random int.
    autognuplot2[0] = "set title \"Generating random int numbers\"";
    autognuplot2[1] = commandArrowJ;
    autognuplot2[2] = commandArrowK;
    autognuplot2[3] = "plot 'randomInt.temp'";

    /* end of the elaboration of the commands to set horizontal lines of the interval j,k given */


/*

  FILE *f2 = fopen("randomInt.temp", "w");// Creation of the pointer to the file where the int random numbers are saved in colums
  FILE * plot2 = popen ("gnuplot -persistent", "w"); // To craete second plot

  if (f2 == NULL) { // exit the program if an error occured while creating the file
        printf("Cannot create the file\n"); // message to info
        exit(1);
  }

  if (plot2 == NULL) { // exit the program if an error occured while creating the plot
        printf("Cannot create the plot\n"); // message to info
        exit(1);
  }

  for(i=0;i<number;i++){  // loop to generate a int random number each iteration as the value of the const number (20)

    if (k<j){ 
      l= rand() % (j + 1 - k) + k;
    }else{
      l= rand() % (k + 1 - j) + j;
    }
   

    printf("%d ",l);

    fprintf(f2, "%d %d \n",axis_x[i],l); //Write the data to the file data.temp
    fflush(plot2);

#ifdef DEBUG //error debug
    if(l<j || l>k) {
      printf("Generation error %d\n", l); exit(0); // if each number generated is not in the interval an error occurs
    }
#endif
  }


  //////-------------------------------------- GNUPLOT--------------------------------------------//////

  for (i=0; i < commands; i++){ //Second plot of Int random numbers
    printf("Executing %d of 3 commands: %s\n",i,autognuplot2[i]);
    fprintf(plot2, "%s \n", autognuplot2[i]); //Send commands to gnuplot one by one.
  }
  */

}
