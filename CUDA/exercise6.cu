//Parallelization - several blocks - several threads + balance
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#define N 100000
#define M 8 //Threads per block

__global__ void add(int *a, int *b, int *c, int n)
{
        int index = threadIdx.x + blockIdx.x * blockDim.x;
        if(index<n)
                c[index] = a[index] + b[index];
}

void random (int *tab, int wym )
{
        int i;
        for(i=0;i<wym;i++)
                tab[i]=rand()%101;
}


int main(void) {
        int *a, *b, *c; // host copies of a, b, c
        int *d_a, *d_b, *d_c; // device copies of a, b, c
        int size = N * sizeof(int);
        int i;
        srand(time(NULL));
        // Allocate space for device copies of a, b, c
        cudaMalloc((void **)&d_a, size);
        cudaMalloc((void **)&d_b, size);
        cudaMalloc((void **)&d_c, size);
        // Alloc space for host copies of a, b, c and setup input values
        a = (int *)malloc(size);
        long cputime,seconds,temp;
        struct timeval start2,end2;
        gettimeofday(&start2,NULL);
         random(a, N);
        b = (int *)malloc(size);
         random(b, N);
        gettimeofday(&end2,NULL);
        seconds = end2.tv_sec - start2.tv_sec;
        temp = end2.tv_usec - start2.tv_usec;
        cputime = ((seconds)*1000 + temp/1000.0)+0.5;
        printf("cpu time: %ld ms\n",cputime);
        c = (int *)malloc(size);
        // Copy inputs to device
        cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
        // Launch add() kernel on GPU
        float gputime=0;
        cudaEvent_t start,stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start,0);
        add<<<(N+M-1)/M,M>>>(d_a, d_b, d_c, N);
        cudaEventRecord(stop,0);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&gputime,start,stop);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        printf("GPU time: %.4f ms\n",gputime);
        // Copy result back to host
        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

        for(i=0;i<N;i++)
        {
                //printf("a[%d](%d) + b[%d](%d) = c[%d](%d)\n",i,a[i],i,b[i],i,c[i]);
        }
        // Cleanup
        //printf("%d+%d=%d\n",a,b,c);
        free(a); free(b); free(c);
        cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
        printf("Total time: %lf ms\n",cputime+gputime);
        return 0;
}
