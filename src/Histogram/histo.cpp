#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <omp.h>
#include <mpi.h>
using namespace std;

int NumberOfPoints = 0;
int max_value = -1;
int *p;
int arr[100];
int *ReadFromFile()
{
    int *points;
    FILE *file;
    int index = 0;
    char line[10];
    file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    while (fgets(line, sizeof(line), file))
        NumberOfPoints++;
    fclose(file);
    int size = NumberOfPoints;
    points = (int *)malloc(size* sizeof(int));
    if (points == NULL) {
        perror("Error allocating memory");
        return NULL;
    }

    file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        free(points);
        return NULL;
    }
    while (fgets(line, sizeof(line), file)) {
        points[index++] = atoi(line);
    }
    fclose(file);
    return points;
}

int main(int argc, char **argv)
{
    int indexx = 0;
    int *points, Bars, np, Range, tmp_Range = 0,
                                  Points_per_process;
    int size;
    int *irecv;
    int *AllCount, *count;
    int rank, NumberOfprocess, i, l, j;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &NumberOfprocess);

#pragma omp parallel
    {
        np = omp_get_num_threads();
    }

    if (rank == 0)
    {
        cout << "Enter the number of bars" << endl;
        cin >> Bars;


        points = ReadFromFile();
        Points_per_process = ((double)NumberOfPoints / (NumberOfprocess)) + 0.5;

        size = Points_per_process * NumberOfprocess;
        if (size < NumberOfPoints)
            size = NumberOfPoints;

        p = (int*)malloc(size * sizeof(int)); 
                                        
        for (i = 0; i < size; i++)
        {
            if (i < NumberOfPoints)
                p[i] = points[i];
            else
                p[i] = -1;
        }
        Range = max_value / Bars;
        if (max_value % Bars != 0)
        {
            Range++;
        }
        free(points);
    }

    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&Bars, 1, MPI_INT, 0, MPI_COMM_WORLD);

    irecv = (int*)malloc(size * sizeof(int *));
    count = (int*)malloc(Bars * sizeof(int *));

    MPI_Bcast(&Range, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&Points_per_process, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(p, Points_per_process, MPI_INT, irecv, Points_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    for (l = 0; l < Bars; l++)
    {
        count[l] = 0;
    }

#pragma omp parallel shared(AllCount)
    {
#pragma omp for schedule(static)
        for (i = 0; i < Points_per_process; i++)
        {
            for (l = 0; l < Bars; l++)
            {
                if (irecv[i] <= l * Range + Range && irecv[i] != -1)
                {
                    count[l]++;
                    arr[indexx++] = l;
                    break;
                }
            }
        }
    }
    free(irecv);
    AllCount = (int*)malloc(NumberOfPoints * sizeof(int));
    MPI_Gather(arr, indexx, MPI_INT, AllCount, indexx, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        // count = malloc(Bars * sizeof(int));
        for (l = 0; l < Bars; l++)
        {
            count[l] = 0;
        }

        for (i = 0; i < Bars; i++)
        {
            for (j = 0; j < NumberOfPoints; j++)
            {
                if (AllCount[j] == i && AllCount[j] != -1)
                {
                    count[i]++;
                }
            }
        }

        for (i = 0; i < Bars; i++)
        {
            cout << "Bar " << i << " has " << count[i] << " points" << endl;
        }
        
    }
    MPI_Finalize();
    

    return 0;
}