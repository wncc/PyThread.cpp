#include<omp.h>
#include<stdio.h>
//for setting chunk size there is no need to consider cache as it only depends when ur data is continuous and 
//getting used again and again so that it can be stored in cache
// Cache size does not matter but depends on cache line size

int main(int argc, char* argv[]){
    int A[1000],B[1000];
    int dot=0;
    for(int i=0;i<1000;i++){
        A[i]=1;
        B[i]=1;
    }
    #pragma omp parallel for schedule(dynamic,100) reduction(+:dot)
    for(int i=0;i<1000;i++){
        dot+=A[i]*B[i];
    }
    printf("Dot product=%d\n",dot);
}