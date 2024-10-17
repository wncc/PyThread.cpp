
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
#include <random>
#include <omp.h>

using namespace std;

vector<int> parallel_sort(vector<int> Vec);
vector<int> merge(vector<int> v1, vector<int> v2);


vector<int> merge(vector<int> v1, vector<int> v2)
{
    int i = 0;
    int j = 0;
    int k = 0;

    vector<int> c(v1.size() + v2.size());
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] > v2[j]) {
            c[k] = v2[j];
            j++;
        }
        else {
            c[k] = v1[i];
            i++;
        }
        k++;

    }

    while (j < v2.size()) {
        c[k] = v2[j];
        k++;
        j++;
    }
    while (i < v1.size()) {
        c[k] = v1[i];
        k++; 
        i++;
    }

    return c;

}


vector<int> parallel_sort(vector<int> Vec)
{
    if (Vec.size() == 1) {
        return Vec;
    }

    vector<int> vec2(Vec.size() / 2);
    for (int i = 0; i < Vec.size() / 2; i++) {
        vec2[i] = Vec[Vec.size() - Vec.size() / 2 + i];
    }
    Vec.resize(Vec.size() - Vec.size() / 2);

    vector<int> firstV, secondV;

    

    // using sections
    #pragma omp parallel sections shared(firstV, secondV) nowait
    {
        #pragma omp section
        {
            firstV = parallel_sort(Vec);
        }

        #pragma omp section
        {
            secondV = parallel_sort(vec2);
        }

    }

    return merge(firstV, secondV);

}



int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 20000);

    vector<int> V1;
    vector<int> V2;
    for (int i = 0; i < 200000; i++) {
        V1.push_back(dist(gen));
    }
    
    /////////////
    // Sorting using parallel programming and calculating time

    float result1 = 0;
    for (int i = 0; i < 5; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        V2 = parallel_sort(V1);

        auto end = std::chrono::high_resolution_clock::now();
        float time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

        result1 += time_took;
    }
    
    //////////////
    // sorting using inbuilt function and calculating time

    float result2 = 0;
    for (int i = 0; i < 5; i++) {
        auto start2 = std::chrono::high_resolution_clock::now();

        vector<int> V3 = V1;
        
        sort( V3.begin(), V3.end() );

        auto end2 = std::chrono::high_resolution_clock::now();
        float time_took2 = std::chrono::duration_cast<std::chrono::duration<float>>(end2 - start2).count();

        result2 += time_took2;
    }
    
    cout<<"Time consistent for parallel sort "<< result1/5 <<"\n";
    cout<<"Time consistent for inbuilt sort "<< result2/5 <<"\n";

}

