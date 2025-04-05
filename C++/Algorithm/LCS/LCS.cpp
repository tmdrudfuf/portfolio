#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Takes two strings, X and Y, as input.
// Returns a pair:
//   - First element: 2D vector (c) representing the LCS lengths.
//   - Second element: 2D vector (b) representing the traceback directions.
pair<vector<vector<int>>, vector<vector<char>>> LCS_LENGTH(const string& X, const string& Y) {
    int m = X.length(); // Length of string X.
    int n = Y.length(); // Length of string Y.

    // Initialize 2D vectors 'c' and 'b' with appropriate sizes.
    // 'c' stores the lengths of LCS for substrings of X and Y.
    // 'b' stores the directions for traceback (used to reconstruct the LCS).
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    vector<vector<char>> b(m + 1, vector<char>(n + 1, ' '));

    // Initialize the first column of 'c' to 0.
    for (int i = 1; i <= m; ++i) {
        c[i][0] = 0;
    }
    // Initialize the first row of 'c' to 0.
    for (int j = 0; j <= n; ++j) {
        c[0][j] = 0;
    }

    // Populate the 'c' and 'b' tables.
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // If characters match, increment the LCS length and set traceback direction to diagonal.
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\'; // Diagonal (match).
            }
            // If characters don't match, choose the direction with the larger LCS length.
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '^'; // Up.
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '<'; // Left.
            }
        }
    }

    // Return the 'c' and 'b' tables.
    return make_pair(c, b);
}

// Function to print the Longest Common Subsequence 
// Takes the traceback matrix 'b', the string X, and the current indices i and j as input.
void PRINT_LCS(const vector<vector<char>>& b, const string& X, int i, int j) {
    // Base case: If either index is 0, return (end of traceback).
    if (i == 0 || j == 0) {
        return;
    }
    // If traceback direction is diagonal, print the character and move diagonally.
    if (b[i][j] == '\\') {
        PRINT_LCS(b, X, i - 1, j - 1);
        cout << X[i - 1]; // Print the matching character.
    }
    // If traceback direction is up, move up.
    else if (b[i][j] == '^') {
        PRINT_LCS(b, X, i - 1, j);
    }
    // If traceback direction is left, move left.
    else {
        PRINT_LCS(b, X, i, j - 1);
    }
}

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1; // Return error code 1.
    }

    string filename = argv[1];
    ifstream inputFile(filename);

    // Check if the file opened successfully.
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        return 1; // Return error code 1.
    }

    // Read the two input strings from the file.
    string X, Y;
    if (!getline(inputFile, X) || !getline(inputFile, Y)) {
        cerr << "Error: Invalid file format. File should contain two lines." << endl;
        return 1; // Return error code 1.
    }

    // Close the input file.
    inputFile.close();

    // Print the input strings.
    cout << "String X: " << X << endl;
    cout << "String Y: " << Y << endl;

    // Calculate the LCS length and traceback matrix.
    pair<vector<vector<int>>, vector<vector<char>>> result = LCS_LENGTH(X, Y);
    vector<vector<char>> b = result.second;

    // Print the LCS.
    cout << "LCS: ";
    PRINT_LCS(b, X, X.length(), Y.length());
    cout << endl;

    // Return 0 to indicate successful execution.
    return 0;
}