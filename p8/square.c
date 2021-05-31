#include<stdio.h>
#include<omp.h>

#define N 500

int main()
{
    int square=0, number, i;
    double time1 = 0.0;
    double time2 = 0.0;

    printf("Insert number:\n");
    scanf("%d",&number);
    //how to parallelize it with good final result?
    time1 = omp_get_wtime(); //For measuring execution times
#pragma omp parallel for reduction(+:square)
    for(i=0;i<N;i++)
    {
        square+=number*number;
    }
    time2 = omp_get_wtime();
    printf("Square=%d\n",square);
    printf("Execution time: %lf\n",time2-time1);
}

/*
 With parallization:
		Insert number:
			5
			Square=12500
			Execution time: 0.000010

Without parallization:

		Insert number:
			5
			Square=12500
			Execution time: 0.000002
 */