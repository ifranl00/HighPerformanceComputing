#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

int find(int array[], int element, int size); // find if there an element in a specific row or 1d array


int main(){

  int a,i,j,k,l; 

  srand(time(NULL)); //seed for generating differnt sequence of random numbers

  printf("Insert the number of rows of the sparse matrix:\n"); //ask by console to insert number of rows of matrix to make square matrix of selected dimensions
  scanf("%d", &a); // saved the values entered by console
  int matrix[a][a]; //matrix for part 1

  /********************************  PART 1: fill the main diagonal of the matrix in the range 1-2 and others in range 0-1 ********************************/

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

  /******************************** PART 3: Record created matrix in CRS (Compressed row storage) ********************************/

      struct csrFormat { // use of a struct which will consist the structure of a sparse matrix in CRS fotmat to record the matrix
        int *indexColumn; // column indexs of the non-zero elements of the matrix
        int *indexRow; // locations in val vector that starts a row
        int *val; // non-zero elements of the matrix
      };

      struct csrFormat m; // create an struct with CRS format called m
      int c = 0; // to know the index of current non-zero element in the loops below

      m.indexColumn = calloc(a*k, sizeof(m.indexColumn[0])); // allocate memory for save the colums which belong to a non-zero element index (num of elements non-zero per row (k) * num of rows (a))
      m.indexRow = calloc(a, sizeof(m.indexRow[0])); // allocate memory for save the locations in val vector which start a row
      m.val = calloc(a*k, sizeof(m.val[0])); // allocate memory for save non-zero elements (num of elements non-zero per row (k) * num of rows (a))

    for (int i = 0; i < a; i++) //iterate over rows
      {
        for (int j = 0; j < a; j++) //iterate over columns
        {
          if(matrix2[i][j]!= 0){ // if the current element is non-zero one
            m.indexColumn[c] = j+1; // save its column index
            m.val[c] = matrix2[i][j]; // save the element
            c++; // increase the counter of elements
          }
        }
        m.indexRow[i] = c; //each value of c when a row is finished saved for store in row_ptr vector of CRS format 
      }

      // print the sparse matrix in CSR format
      printf("\n ---- CSR FORMAT -----");
      printf("\n Val: ");

      for (int i = 0; i < a*k; i++)
      {
        printf("%d ",m.val[i]);
      }

      printf("\n col_in: ");

      for (int i = 0; i < a*k; i++)
      {
        printf("%d ",m.indexColumn[i]);
      }

      printf("\n row_ptr: ");

      for (int i = 0; i < a; i++)
      {
        printf("%d ",m.indexRow[i]);
      }

      /******************************** FINAL PART: Validation of results ********************************/
    printf("\n");

      // Let's get the standard format of the matrix from the CRS format created before, and check if the matrixs are equal.
      int matrixFromCRS[a][a]; // save in this variable the matrix generated form CRS format
      int numNonZeros = 0; // number of non-zero elements

      for (int i = 0; i < a; i++) //iterate over rows
      {
        int nonzeroPerRowIndex[k]; // index non-zero elements per row
        int p = 0; // count of non-zero elements 
          for(int x = k*i;x<k*i+k;x++){ // to loop from k elements ecah time to obtain the k non-zero values that belongs to current row
            nonzeroPerRowIndex[p] = m.indexColumn[x]; // get the index non-zero per row from the csr struct parameter named indexColum
            p++; // increase counter
          }

          for (int j = 0; j < a; j++) //iterate over columns
          {
              
            if(find(nonzeroPerRowIndex,j+1,k)==1) { // if is a non-zero element to be set
              matrixFromCRS[i][j] = m.val[numNonZeros]; // assign its value from values of the struct
              numNonZeros++; // increase counter
            }else{
              matrixFromCRS[i][j] = 0; // if its index is not in indexColumn, is a zero value
            }
          }
      }

       //print sparse matrix generated from CRS format

      printf("\nThe sparse matrix generated from CRS format is:\n");

      for (int i = 0; i < a; i++)
      {
        for (int j = 0; j < a; j++)
        {
          printf("%d ",matrixFromCRS[i][j]);
        }
        printf("\n");
      }

      // Test if both matrix, standard generated one (matrix2) is equal to the generated from CRS format (matrixFromCRS)

      printf("Validating if the standard matrix generated and the one generated from CRS are equals...\n");

      for(int i = 0; i<a;i++){
        for(int j = 0;j<a;j++){
          if(matrix2[i][j]!=matrixFromCRS[i][j]){ //this element is different
            printf(" TEST FAILED-------> The matrix are not equals!\n");
            return 0;
          }
        }
      } printf(" TEST OK-------> The matrix are equals!\n");
      return 0;
}


/*********** functions ***********/

int find(int array[], int element, int size) { // RETURNS 1 if the element is in the array or 0 if not
  
  int i = -1;

  for (i = 0; i < size; i++)
  {
    if(array[i] == element){
      return 1; // element is found 
    }
  }
  return 0; // is not found
}