#include<iostream>
#include<omp.h>
int main(int argc,char *argv[]){
    int A[1000][1000],B[1000];
    int y[1000];
    for(int i=0;i<1000;i++){
        for(int j=0;j<1000;j++){
            A[i][j]=1;
        }
    }
    for(int i=0;i<1000;i++){
        B[i]=1;
    }
    #pragma omp parallel for schedule(dynamic,16)
    for(int i=0;i<1000;i++){
        for(int j=0;j<1000;j++){
            y[i]+=A[i][j]*B[j];
        }
    }
    for(int i=0;i<1000;i++){
        std::cout<<y[i]<<std::endl;
    }
    return 0;
}