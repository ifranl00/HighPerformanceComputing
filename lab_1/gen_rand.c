#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>


const int number = 20; // this number specify how many random numbers of int and double are going to be generated
const int commands = 4; //number of commands to set the title and plot both int and double random numbers vs sequence numbers (2 plots)

int main(){

  double a, b, c; // (a,b) numbers that are the interval to generate double random numbers. c is will be used to store the current random double generated
  int i,j,k,l; // (j,k) numbers that are the interval to generate random int. i is used as iterator for the loops. l will be used to store the current random int generated
  int axis_x[number]; // int array with sequence numbers

  for(i = 0;i<number;i++){
    axis_x[i] = i; // create sequence numbers to use them as horizontal axis of the plots
  }

  srand(time(NULL)); //seed for generating differnt sequence of random numbers


  //////-------------------------------------- RANDOM DOUBLE--------------------------------------------//////

  printf("Insert two real numbers:\n"); //ask by console to insert 2 real numbers
  scanf("%lf %lf", &a, &b); // saved the values entered by console
  printf("\nRandom numbers from interval: %lf - %lf\n", a, b); //info about the interval generated printed by console
  
  /* Elaboration of the commands to set horizontal lines given a interval */
    char string_a[64];
    sprintf(string_a,"%lf",a); // string value of a 

    char commandArrowA[150] = "set arrow from graph 0,first "; // first part to set an arrow with gnuplot
    strcat(commandArrowA,string_a); // concat multiple times
    strcat(commandArrowA," to graph 1,first ");
    strcat(commandArrowA,string_a);
    strcat(commandArrowA," nohead"); // finally we have "set arrow from graph 0,first a to graph 1,first a nohead"


    char string_b[64];
    sprintf(string_b,"%lf",b); // string value of b

    char commandArrowB[150] = "set arrow from graph 0,first "; // first part to set an arrow with gnuplot
    strcat(commandArrowB,string_b); //concat multiple times
    strcat(commandArrowB," to graph 1,first ");
    strcat(commandArrowB,string_b);
    strcat(commandArrowB," nohead"); // finally we have "set arrow from graph 0,first b to graph 1,first b nohead"

    char * autognuplot[4];// char array to execute gnuplot commands to plot first plot with the data of the random doubles.
    autognuplot[0] = "set title \"Generating random double numbers\"";
    autognuplot[1] = commandArrowA;
    autognuplot[2] = commandArrowB;
    autognuplot[3] = "plot 'randomDouble.temp'";

      /* end of the elaboration of the commands to set horizontal lines of the interval a,b given */



  FILE *f = fopen("randomDouble.temp", "w");// Creation of the pointer to the file where the double random numbers are saved in colums
  FILE * plot = popen ("gnuplot -persistent", "w"); // To create the first plot

  if (f == NULL) { // exit the program if an error occured while creating the file
    printf("Cannot create the file\n"); // message to info
    exit(1);
  }

  if (plot == NULL) { // exit the program if an error occured while creating the plot
    printf("Cannot create the plot\n"); // message to info
    exit(1);
  }

  for(i=0;i<number;i++){ // loop to generate a double random number each iteration as the value of the const number (20)

    c = (double)rand() * (b - a) / (double)RAND_MAX + a; //rand() * ( high - low ) ) / (double)RAND_MAX + low
    printf("%lf ",c);

    fprintf(f, "%d %lf \n",axis_x[i],c); //Write the data to the file data.temp
    fflush(plot);

#ifdef DEBUG // error debug
    if(c<a || c>b) { /
      printf("Generation error %lf\n", c); exit(0); // if each number generated is not in the interval an error occurs
    }
#endif

  }

  //////-------------------------------------- RANDOM INT--------------------------------------------//////
  
  printf("\nInsert two integer numbers:\n");//ask by console to insert 2 integer numbers
  scanf("%d %d", &j, &k);// saved the values entered by console
  printf("\nRandom numbers from interval: %d - %d\n", j, k);//info about the interval generated printed by console
  
  /* Elaboration of the commands to set horizontal lines given a interval */
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


  for (i=0; i < commands; i++){ //First plot of Double random numbers
    printf("Executing %d of 3 commands: %s\n",i,autognuplot[i]);
    fprintf(plot, "%s \n", autognuplot[i]); //Send commands to gnuplot one by one.
  }

  for (i=0; i < commands; i++){ //Second plot of Int random numbers
    printf("Executing %d of 3 commands: %s\n",i,autognuplot2[i]);
    fprintf(plot2, "%s \n", autognuplot2[i]); //Send commands to gnuplot one by one.
  }

}
