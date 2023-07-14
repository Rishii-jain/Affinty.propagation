#include <iostream>
#include <vector>
#include <cmath>
#include<bits/stdc++.h>
using namespace std;

const int n = 5; // Number of students
double similarityMatrix[n][n] = {0};

// Calculate similarity matrix
void SimilarityMatrix() {
    vector<vector<double>> students = {
        {3, 4, 3, 2, 1}, // Alice
        {4, 3, 5, 1, 1}, // Bob
        {3, 5, 3, 3, 3}, // Charlie         //input
        {2, 1, 3, 3, 2}, // David
        {1, 1, 3, 2, 3}  // Emily
    };

    double lowestValue = 10000; // Initialize with highest possible value 

    // Find the lowest value in the similarity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double sumOfSquares = 0.0;
                for (int dim = 0; dim < students[i].size(); dim++) {
                    double diff = students[i][dim] - students[j][dim];
                    sumOfSquares += diff * diff;
                }
                similarityMatrix[i][j] = -sumOfSquares;
                lowestValue = min(lowestValue, similarityMatrix[i][j]);
            } else {
                similarityMatrix[i][j] = lowestValue;
            }
        }
    }

    // Update the diagonal elements with the lowest value
    for (int i = 0; i < n; i++) {
        similarityMatrix[i][i] = lowestValue;
    }
}

// Calculate responsibility martix
// Convert similarity matrix to responsibility matrix
double responsibilityMatrix[n][n] = {0};

void  ResponsibilityMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double  Resp = -10000;
            for (int r = 0; r < n; r++) {
                if (r != j && similarityMatrix[i][r] >  Resp) {
                     Resp = similarityMatrix[i][r];
                }
            }
            responsibilityMatrix[i][j] = similarityMatrix[i][j] -  Resp;
        }
    }
}


// Calculate availability matrix
double availabilityMatrix[n][n] = {0};

void AvailabilityMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                double sum = 0.0;
                for (int p = 0; p < n; p++) {
                    if (p != i && responsibilityMatrix[p][j] > 0) {
                        sum += responsibilityMatrix[p][j];
                    }
                }
                availabilityMatrix[i][j] = sum;
            } else {
                double sum = 0.0;
                int maxik = max(i, j);
                int minik = min(i, j);
                for (int p = 0; p < minik; p++) {
                    if (responsibilityMatrix[p][j] > 0) {
                        sum += responsibilityMatrix[p][j];
                    }
                }
                for (int a = minik + 1; a < maxik; a++) {
                    if (responsibilityMatrix[a][j] > 0) {
                        sum += responsibilityMatrix[a][j];
                    }
                }
                for (int a = maxik + 1; a < n; a++) {
                    if (responsibilityMatrix[a][j] > 0) {
                        sum += responsibilityMatrix[a][j];
                    }
                }
                availabilityMatrix[i][j] = min(0.0, responsibilityMatrix[j][j] + sum);
            }
        }
    }
}

// Calculate criterion matrix
double criterionMatrix[n][n] = {0};

void CriterionMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            criterionMatrix[i][j] = responsibilityMatrix[i][j] + availabilityMatrix[i][j];
        }
    }
}


int main() {
    // Calculate similarity matrix
    SimilarityMatrix();

    // Display the similarity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << similarityMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Convert similarity matrix to responsibility matrix
     ResponsibilityMatrix();

    // Display the responsibility matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << responsibilityMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    // Calculate availability matrix
    AvailabilityMatrix();

    // Display the availability matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << availabilityMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    // Calculate criterion matrix
    CriterionMatrix();

    // Display the criterion matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << criterionMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}