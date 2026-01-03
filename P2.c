#include <stdio.h>
#include <stdbool.h>

// Configuration for the problem size
#define P 5  // Number of Processes
#define R 4  // Number of Resources

// Global structures to hold the system state
int available[R];
int max[P][R];
int allocation[P][R];
int need[P][R];

// Function to calculate the Need Matrix
void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafeState(int current_avail[], int safeSeq[]) {
    int work[R];
    bool finish[P];
    
    // Initialize Work and Finish
    for (int i = 0; i < R; i++) work[i] = current_avail[i];
    for (int i = 0; i < P; i++) finish[i] = false;

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                // Check if Need <= Work for all resources
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j])
                        break;
                }

                // If all resources satisfied
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[p][k];
                    
                    safeSeq[count++] = p + 1; // Storing as P1, P2...
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) return false; // System is not safe
    }
    return true;
}

// Function to handle a resource request
void requestResources(int pid, int request[]) {
    int p_index = pid - 1; // Convert P1 -> index 0

    printf("\n--- Processing Request for P%d: [ %d %d %d %d ] ---\n", 
           pid, request[0], request[1], request[2], request[3]);

    // Step 1: Check if Request <= Need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[p_index][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    // Step 2: Check if Request <= Available
    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("Result: Request cannot be granted immediately. Resources unavailable (Wait).\n");
            return;
        }
    }

    // Step 3: Pretend to allocate resources
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[p_index][i] += request[i];
        need[p_index][i] -= request[i];
    }

    // Step 4: Check if this new state is safe
    int safeSeq[P];
    if (isSafeState(available, safeSeq)) {
        printf("Result: Request Granted. System is in SAFE State.\n");
        printf("Safe Sequence: < ");
        for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
        printf(">\n");
    } else {
        printf("Result: Request Denied. Allocation would result in UNSAFE state.\n");
        // Rollback
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[p_index][i] -= request[i];
            need[p_index][i] += request[i];
        }
    }
}

int main() {
    // --- 1. Initialization (Data from Image) ---
    
    // Total Existing Resources: R1=6, R2=7, R3=12, R4=12
    int total_resources[R] = {6, 7, 12, 12};
    
    // Allocation Matrix
    int alloc_init[P][R] = {
        {0, 0, 1, 2}, // P1
        {2, 0, 0, 0}, // P2
        {0, 0, 3, 4}, // P3
        {2, 3, 5, 4}, // P4
        {0, 3, 3, 2}  // P5
    };

    // Max Matrix
    int max_init[P][R] = {
        {0, 0, 1, 2}, // P1
        {2, 7, 5, 0}, // P2
        {6, 6, 5, 6}, // P3
        {4, 3, 5, 6}, // P4
        {0, 6, 5, 2}  // P5
    };

    // Copy to global variables and Calculate Available
    int alloc_sum[R] = {0, 0, 0, 0};
    for(int i=0; i<P; i++) {
        for(int j=0; j<R; j++) {
            allocation[i][j] = alloc_init[i][j];
            max[i][j] = max_init[i][j];
            alloc_sum[j] += allocation[i][j];
        }
    }

    for(int i=0; i<R; i++) {
        available[i] = total_resources[i] - alloc_sum[i];
    }

    // --- Part (a): Find Content of Need Matrix ---
    calculateNeed();
    printf("a) Need Matrix:\n");
    printf("    R1 R2 R3 R4\n");
    for (int i = 0; i < P; i++) {
        printf("P%d: ", i + 1);
        for (int j = 0; j < R; j++) {
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }

    // --- Part (b): Is System Safe? ---
    int safeSeq[P];
    printf("\nb) Checking Safety of Initial State:\n");
    if (isSafeState(available, safeSeq)) {
        printf("System is in a SAFE state.\n");
        printf("Safe Sequence: < ");
        for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
        printf(">\n");
    } else {
        printf("System is in an UNSAFE state.\n");
    }

    // --- Part (c): Request for P3 ---
    // Request: 1 instance of R2 and R4. Vector: [0, 1, 0, 1]
    int requestP3[R] = {0, 1, 0, 1};
    printf("\nc) Checking Request for P3:\n");
    requestResources(3, requestP3);

    return 0;
}
