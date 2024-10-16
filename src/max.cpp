#include <iostream>
#include <fstream>
#include <mpi.h>
#include <vector>
#include <algorithm> 
#include <cstdlib>  


int findMax(int elementsToProcess, const std::vector<int>& data) {
    int max = data[0];
    for (int i = 0; i < elementsToProcess; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  
    double time = MPI_Wtime();  
    
    int processorsNr;
    MPI_Comm_size(MPI_COMM_WORLD, &processorsNr);  
    int processId;
    MPI_Comm_rank(MPI_COMM_WORLD, &processId); 

    std::cout << "Before checking Core: " << processId << std::endl;

    int buff;  
    if (processId == 0) {
        int max = 0;  
        std::ifstream inputs("input.txt"); 
        int totalElements = 0;
        int elementsToEachProcess = 0;

        if (!inputs.is_open()) {
            std::cerr << "Input file not found" << std::endl;
            MPI_Finalize();
            return 0;
        }

        std::vector<int> data; 
        int num;
        while (inputs >> num) {
            data.push_back(num);  
            totalElements++;
        }
        inputs.close();

        std::cout << "File is read successfully!" << std::endl;

        
        elementsToEachProcess = totalElements / processorsNr;
        std::cout << "Elements that each core should process: " << elementsToEachProcess << std::endl;

        
        buff = elementsToEachProcess;

        for (int i = 1; i < processorsNr; i++) {
            std::cout << "Sending data from master to process " << i << std::endl;
            MPI_Send(&buff, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(data.data() + i * elementsToEachProcess, elementsToEachProcess, MPI_INT, i, 2, MPI_COMM_WORLD);
        }

        
        std::cout << "Finding max of master data" << std::endl;
        max = findMax(elementsToEachProcess, data);

        int theMax;
        
        std::cout << "Receiving max values from other processors" << std::endl;
        for (int i = 1; i < processorsNr; i++) {
            MPI_Recv(&theMax, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (theMax > max) {
                max = theMax;
            }
        }

        std::cout << "Global maximum is " << max << std::endl;
        time = MPI_Wtime() - time;
        std::cout << "Time elapsed: " << time << " seconds" << std::endl;
    }
    
    else {
        std::cout << "Process " << processId << " waiting for data from master" << std::endl;

        MPI_Recv(&buff, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::vector<int> dataToProcess(buff);  
        MPI_Recv(dataToProcess.data(), buff, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        
        int theMax = findMax(buff, dataToProcess);

        
        MPI_Send(&theMax, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
