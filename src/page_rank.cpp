#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Parameters for PageRank
const int NUM_PAGES = 5;        // Number of pages (nodes)
const int MAX_ITERATIONS = 100; // Maximum number of iterations
const double DAMPING_FACTOR = 0.85;
const double EPSILON = 1e-6;    // Convergence criterion

// Example graph as an adjacency matrix (edges represent links between pages)
vector<vector<int>> graph = {
    {0, 1, 1, 0, 0},  // Page 0 links to pages 1 and 2
    {0, 0, 1, 1, 0},  // Page 1 links to pages 2 and 3
    {0, 0, 0, 1, 1},  // Page 2 links to pages 3 and 4
    {0, 0, 0, 0, 1},  // Page 3 links to page 4
    {1, 0, 0, 0, 0}   // Page 4 links to page 0
};

// Function to perform PageRank using OpenMP
void pageRank() {
    vector<double> rank(NUM_PAGES, 1.0 / NUM_PAGES); // Initialize rank values
    vector<double> new_rank(NUM_PAGES, 0.0);

    bool converged = false;

    // Iteration loop
    for (int iter = 0; iter < MAX_ITERATIONS && !converged; iter++) {
        converged = true;

        // Parallelize the rank computation using OpenMP
        #pragma omp parallel for shared(rank, new_rank)
        for (int i = 0; i < NUM_PAGES; i++) {
            double incoming_rank_sum = 0.0;

            // Calculate the sum of ranks from incoming links
            for (int j = 0; j < NUM_PAGES; j++) {
                if (graph[j][i] == 1) {
                    int outgoing_links = 0;

                    // Count the number of outgoing links from page j
                    for (int k = 0; k < NUM_PAGES; k++) {
                        outgoing_links += graph[j][k];
                    }

                    if (outgoing_links > 0) {
                        incoming_rank_sum += rank[j] / outgoing_links;
                    }
                }
            }

            // Update the new rank with damping factor
            new_rank[i] = (1.0 - DAMPING_FACTOR) / NUM_PAGES + DAMPING_FACTOR * incoming_rank_sum;
        }

        // Check for convergence (difference between old and new ranks)
        converged = true;
        #pragma omp parallel for shared(rank, new_rank) reduction(&& : converged)
        for (int i = 0; i < NUM_PAGES; i++) {
            if (abs(new_rank[i] - rank[i]) > EPSILON) {
                converged = false;
            }
            rank[i] = new_rank[i]; // Update rank for next iteration
        }

        // Print the ranks after each iteration
        cout << "Iteration " << iter + 1 << ": ";
        for (double r : rank) {
            cout << r << " ";
        }
        cout << endl;
    }
}

int main() {
    // Run the PageRank algorithm
    pageRank();
    return 0;
}
