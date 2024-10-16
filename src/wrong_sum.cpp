#include<stdio.h>
#include<omp.h>
#include<iostream>
#include<ostream>
int main(int argc, char *argv[]){
    int i,sum=0;
    #define ARR_SIZE 600
    #define STEP_SIZE 100
    int a[ARR_SIZE];
    for(int i=0;i<ARR_SIZE;i++){
        a[i]=1;
    }
    #pragma omp parallel
    {
        #pragma omp for nowait
        for(int i=0;i<ARR_SIZE;i+=STEP_SIZE){
            int j,start=i,end=i+STEP_SIZE-1;
            std::cout<<"Thread computing Sum("<<start<<","<<end<<") from "<<omp_get_thread_num()<<" of "<<omp_get_num_threads()<<std::endl;
            #pragma omp task
            {
                int psum=0;
                std::cout<<"Task computing Sum("<<start<<","<<end<<") from "<<omp_get_thread_num()<<" of "<<omp_get_num_threads()<<std::endl;
                for(int j=start;j<=end;j++){
                    psum+=a[j];
                }
                #pragma omp critical
                sum+=psum;
            }
        }
    }
    printf("Sum=%d\n",sum);
    return 0;
}