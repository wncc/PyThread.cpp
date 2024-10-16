#include<omp.h>
#include<stdio.h>

int a[int(1e7)],sum=0;
#define ARR_SIZE 10000000
int main(int argc,char *argv[])
{
    int i,tid,numt,sum=0;
    double t1,t2;
    for(int i=0;i<ARR_SIZE;i++)
    {
        a[i]=1;
    }
    t1=omp_get_wtime();
    #pragma omp parrallel default(shared) private(i,tid)
    {
        int from ,to, psum=0;
        tid=omp_get_thread_num();
        numt=omp_get_num_threads();
        from=(ARR_SIZE/numt)*tid;
        to=(ARR_SIZE/numt)*(tid+1)-1;
        for(int i=from;i<=to;i++)
        {
            psum+=a[i];
        }
        #pragma omp critical
        {
            sum+=psum;
        }
    }
    printf("Sum=%d\n",sum);
    t2=omp_get_wtime();
    printf("Time taken=%f\n",t2-t1);
    return 0;
}