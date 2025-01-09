#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

pair<vector<vector<int>>, vector<vector<string>>> LCS_Iterative(const vector<int>& X, const vector<int>& Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    vector<vector<string>> b(m + 1, vector<string>(n + 1, ""));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = "DIAGONAL";
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = "UP";
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = "LEFT";
            }
        }
    }

    return { c, b };
}

void Print_Solution_Iterative(const vector<vector<string>>& b, const vector<int>& X, int i, int j) {
    if (i == 0 || j == 0) return;
    if (b[i][j] == "DIAGONAL") {
        Print_Solution_Iterative(b, X, i - 1, j - 1);
        cout << X[i - 1] << " ";
    }
    else if (b[i][j] == "UP") {
        Print_Solution_Iterative(b, X, i - 1, j);
    }
    else {
        Print_Solution_Iterative(b, X, i, j - 1);
    }
}

int LCS_Recursive_Helper(const vector<int>& X, const vector<int>& Y, int i, int j, vector<vector<int>>& memo, vector<vector<string>>& b) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    if (X[i - 1] == Y[j - 1]) {
        memo[i][j] = LCS_Recursive_Helper(X, Y, i - 1, j - 1, memo, b) + 1;
        b[i][j] = "DIAGONAL";
    }
    else {
        int up = LCS_Recursive_Helper(X, Y, i - 1, j, memo, b);
        int left = LCS_Recursive_Helper(X, Y, i, j - 1, memo, b);

        if (up >= left) {
            memo[i][j] = up;
            b[i][j] = "UP";
        }
        else {
            memo[i][j] = left;
            b[i][j] = "LEFT";
        }
    }

    return memo[i][j];
}

pair<vector<vector<int>>, vector<vector<string>>> LCS_Recursive(const vector<int>& X, const vector<int>& Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    vector<vector<string>> b(m + 1, vector<string>(n + 1, ""));

    LCS_Recursive_Helper(X, Y, m, n, memo, b);
    return { memo, b };
}

void Print_Solution_Recursive(const vector<vector<string>>& b, const vector<int>& X, int i, int j) {
    if (i == 0 || j == 0) return;
    if (b[i][j] == "DIAGONAL") {
        Print_Solution_Recursive(b, X, i - 1, j - 1);
        cout << X[i - 1] << " ";
    }
    else if (b[i][j] == "UP") {
        Print_Solution_Recursive(b, X, i - 1, j);
    }
    else {
        Print_Solution_Recursive(b, X, i, j - 1);
    }
}

int main() {
    srand(time(0));
    ofstream csv_file("lcs_comparison.csv");
    csv_file << "Sequence Size,Iterative Time (ms),Recursive Time (ms)\n";

    for (int size = 10; size <= 1500; size += 1) {
        vector<int> X(size), Y(size);
        for (int& x : X) x = rand() % 1500;
        for (int& y : Y) y = rand() % 1500;

        auto start_iterative = chrono::high_resolution_clock::now();
        auto iterative_result = LCS_Iterative(X, Y);
        auto end_iterative = chrono::high_resolution_clock::now();
        auto iterative_duration = chrono::duration_cast<chrono::milliseconds>(end_iterative - start_iterative).count();

        auto start_recursive = chrono::high_resolution_clock::now();
        auto recursive_result = LCS_Recursive(X, Y);
        auto end_recursive = chrono::high_resolution_clock::now();
        auto recursive_duration = chrono::duration_cast<chrono::milliseconds>(end_recursive - start_recursive).count();

        csv_file << size << "," << iterative_duration << "," << recursive_duration << "\n";
        cout << "Size: " << size << " Iterative Time: " << iterative_duration << " ms Recursive Time: " << recursive_duration << " ms" << endl;
    }

    csv_file.close();
    return 0;
}
