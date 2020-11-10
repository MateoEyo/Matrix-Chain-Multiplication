/*
Matrix Chain multiplication problem solved using a recursive approach
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
using namespace std;

// Functions
int matrixChain(int dim[], int i, int j);
void matrixChainTabular(int dim[], int size);
void printResults(int size);
void resetMatrices(int size);

// Matrices to be modifed
int costMatrix[20][20];
int splitMatrix[20][20];
const int probOneSize = 5;
const int probTwoSize = 9;

// Begin the program
int main() {

    cout << "*** Welcome to Matrix Chain Multiplication solved by recursion! ***" << endl;

    // Predefined dimensions and random length dimension vector
    int probOne[probOneSize] = { 30, 1, 40, 10, 25 };
    int probTwo[probTwoSize] = { 80, 96, 66, 4, 85, 94, 68, 76, 75 };
    int minCost = -1;

    // Perform MCM on problem 1 and print out both matrices; calculate time
    cout << "\n*** Problem 1 - {30, 1, 40, 10, 25} ***" << endl;

    auto begOneRec = chrono::high_resolution_clock::now();
    minCost = matrixChain(probOne, 1, probOneSize - 1);
    auto endOneRec = chrono::high_resolution_clock::now();
    auto totOneRec = chrono::duration_cast<chrono::microseconds>(endOneRec - begOneRec);

    printResults(probOneSize - 1);
    cout << "Minimum cost is " + to_string(minCost) + " and ";
    resetMatrices(probOneSize - 1);

    // Perform MCM on problem 2 and print out both matrices
    cout << "\n\n*** Problem 2 - {80, 96, 66, 4, 85, 94, 68, 76, 75} ***" << endl;

    auto begTwoRec = chrono::high_resolution_clock::now();
    minCost = matrixChain(probTwo, 1, probTwoSize - 1);
    auto endTwoRec = chrono::high_resolution_clock::now();
    auto totTwoRec = chrono::duration_cast<chrono::microseconds>(endTwoRec - begTwoRec);

    printResults(probTwoSize - 1);
    resetMatrices(probTwoSize - 1);

    // Perform MCM on problem 1 with tabular and print out both matrices
    cout << "\n*** Problem 1 (Tabular) - {30, 1, 40, 10, 25} ***" << endl;

    auto begOneTab = chrono::high_resolution_clock::now();
    matrixChainTabular(probOne, probOneSize - 1);
    auto endOneTab = chrono::high_resolution_clock::now();
    auto totOneTab = chrono::duration_cast<chrono::microseconds>(endOneTab - begOneTab);

    printResults(probOneSize - 1);
    resetMatrices(probOneSize - 1);

    // Perform MCM on problem 2 with tabular and print out both matrices
    cout << "\n*** Problem 2 (Tabular) - {80, 96, 66, 4, 85, 94, 68, 76, 75} ***" << endl;

    auto begTwoTab = chrono::high_resolution_clock::now();
    matrixChainTabular(probTwo, probTwoSize - 1);
    auto endTwoTab = chrono::high_resolution_clock::now();
    auto totTwoTab = chrono::duration_cast<chrono::microseconds>(endTwoTab - begTwoTab);

    printResults(probTwoSize - 1);
    resetMatrices(probTwoSize - 1);

    // Print out execution time for each problem and each problems algorithm
    cout << "\nExecution time for Problem 1 Recursive is " + to_string(totOneRec.count()) + " microseconds or " +
        to_string(totOneRec.count() / 1000000) << +" seconds." << endl;

    cout << "\nExecution time for Problem 2 Recursive is " + to_string(totTwoRec.count()) + " microseconds or " +
        to_string(totTwoRec.count() / 1000000) << +" seconds." << endl;

    cout << "\nExecution time for Problem 1 Tabular is " + to_string(totOneTab.count()) + " microseconds or " +
        to_string(totOneTab.count() / 1000000) << +" seconds." << endl;

    cout << "\nExecution time for Problem 1 Recursive is " + to_string(totTwoTab.count()) + " microseconds or " +
        to_string(totTwoTab.count() / 1000000) << +" seconds." << endl;
}

/*
Populate Matrices recursively
*/
int matrixChain(int dim[], int i, int j) {

    // If only one matrix, no multiplication is necessary
    if (i == j) { return 0; }

    int minimum = INT_MAX;
    int count;

    // Recurse 
    for (int k = i; k < j; k++) {
        count = matrixChain(dim, i, k) + matrixChain(dim, k + 1, j) + dim[i - 1] * dim[k] * dim[j];

        if (count < minimum) {
            minimum = count;
            costMatrix[i - 1][j - 1] = minimum;
            splitMatrix[i - 1][j - 1] = k;
        }
    }
    return minimum;
}

/*
Populate Matrices with tabular method
*/
void matrixChainTabular(int dim[], int size) {

    int j;
    int count;
    int minimum;
    int split;

    for (int l = 0; l < size; l++) {
        for (int i = 0; i < size - l; i++) {
            j = i + l;
            minimum = INT_MAX;
            split = INT_MAX;
            for (int k = i; k < j; k++) {
                count = costMatrix[i][k] + costMatrix[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
                if (count < minimum) {
                    minimum = count;
                    split = k+1;
                    costMatrix[i][j] = minimum;
                    splitMatrix[i][j] = split;
                }
            }

        }
    }
}

/*
Print out results
*/
void printResults(int size) {
    cout << "Minimum cost table" << endl;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            cout << left << setw(10) << setfill(' ') << costMatrix[x][y];
        }
        cout << endl;
    }
    cout << "Split table" << endl;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            cout << left << setw(10) << setfill(' ') << splitMatrix[x][y];
        }
        cout << endl;
    }
}

/*
Reset matrices to all 0's
*/
void resetMatrices(int size) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            costMatrix[x][y] = 0;
            splitMatrix[x][y] = 0;
        }
    }
}