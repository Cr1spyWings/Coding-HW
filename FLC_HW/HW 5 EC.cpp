#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define MAX 40

using namespace std;

// Function to initialize the matrix with reflexive, symmetric and transitive properties
void generateRandomEquivalenceRelation(int R[MAX][MAX], int size) {
    // Ensure reflexivity (set diagonal elements to 1)
    for (int i = 0; i < size; i++) {
        R[i][i] = 1;
    }

    // Initialize random pairs and ensure symmetry
    srand(time(0));  // Seed for randomness
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {5
            // Randomly decide if there should be a relation between i and j
            if (rand() % 2 == 1) {   // 50% chance to create a relation
                R[i][j] = 1;
                R[j][i] = 1;         // Enforce symmetry
            }
        }
    }

    // Ensure transitivity only when necessary
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (R[i][k] == 1 && R[k][j] == 1) {
                    R[i][j] = 1;  // If i is related to k, and k to j, ensure i is related to j
                }
            }
        }
    }
}

// Function to write the matrix to a binary file
void writeMatrixToFile(int R[MAX][MAX], int size, const char* filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Error: Could not open file for writing.\n";
        exit(1);
    }

    // Write the size of the matrix
    char size_char = static_cast<char>(size);
    fout.write(&size_char, 1);

    // Write the matrix elements
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char val = static_cast<char>(R[i][j]);
            fout.write(&val, 1);
        }
    }

    fout.close();
    cout << "Matrix written to " << filename << endl;
}

int main() {
    int size;
    cout << "Enter the size of the relation matrix (up to " << MAX << "): ";
    cin >> size;

    if (size > MAX || size <= 0) {
        cerr << "Invalid size. Please enter a value between 1 and " << MAX << "." << endl;
        return 1;
    }

    int R[MAX][MAX] = {0};  // Initialize the matrix with all elements as 0

    // Generate the random equivalence relation
    generateRandomEquivalenceRelation(R, size);

    // Write the matrix to a binary file
    const char* filename = "random_equiv_relation.bin";
    writeMatrixToFile(R, size, filename);

    return 0;
}
