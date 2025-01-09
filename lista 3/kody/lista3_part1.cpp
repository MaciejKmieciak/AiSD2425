#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <chrono>
#include <fstream>

using namespace std;

int minInt = numeric_limits<int>::min();

int cutRod(int p[], int n);
int memorizedCutRod(int p[], int r[], int n);
pair<vector<int>, vector<int>> extBotUpCutRod(int p[], int n);
void printSolution(int p[], int n);

int main() {
    ofstream csvFile("cut_rod_execution_times.csv");
    csvFile << "DataSize,RecursiveTime(us),MemorizedTime(us),BottomUpTime(us)" << endl;

    const int maxSize = 2500;

    srand(time(0));

    for (int n = 1; n <= maxSize; ++n) {
        vector<int> prices(n);
        
        for (int i = 0; i < n; ++i) {
            prices[i] = rand() % maxSize + 1;
        }

        long long recursiveTime = -1;
        if (n <= 25) { 
            auto start = chrono::high_resolution_clock::now();
            cutRod(prices.data(), n);
            auto end = chrono::high_resolution_clock::now();
            recursiveTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
        }

        vector<int> r(n + 1, -1);
        auto startMem = chrono::high_resolution_clock::now();
        memorizedCutRod(prices.data(), r.data(), n);
        auto endMem = chrono::high_resolution_clock::now();
        long long memorizedTime = chrono::duration_cast<chrono::microseconds>(endMem - startMem).count();


        auto startBU = chrono::high_resolution_clock::now();
        extBotUpCutRod(prices.data(), n);
        auto endBU = chrono::high_resolution_clock::now();
        long long bottomUpTime = chrono::duration_cast<chrono::microseconds>(endBU - startBU).count();

        csvFile << n << "," << recursiveTime << "," << memorizedTime << "," << bottomUpTime << endl;

        cout << "Data Size: " << n
            << ", Recursive: " << recursiveTime << " us"
            << ", Memorized: " << memorizedTime << " us"
            << ", Bottom-Up: " << bottomUpTime << " us" << endl;
    }

    csvFile.close();
    cout << "Done" << endl;
    return 0;
}

int cutRod(int p[], int n) {
    if (n == 0) {
        return 0;
    }

    int q = minInt;
    for (int i = 0; i < n; ++i) {
        q = max(q, p[i] + cutRod(p, n - i - 1));
    }

    return q;
}

int memorizedCutRod(int p[], int r[], int n) {
    if (r[n] >= 0) {
        return r[n];
    }

    int q = minInt;
    if (n == 0) {
        q = 0;
    }
    else {
        for (int i = 0; i < n; ++i) {
            q = max(q, p[i] + memorizedCutRod(p, r, n - i - 1));
        }
    }

    r[n] = q;
    return q;
}

pair<vector<int>, vector<int>> extBotUpCutRod(int p[], int n) {
    vector<int> r(n + 1, 0);
    vector<int> s(n + 1, 0);

    for (int j = 1; j <= n; ++j) {
        int q = minInt;

        for (int i = 1; i <= j; ++i) {
            if (q < p[i - 1] + r[j - i]) {
                q = p[i - 1] + r[j - i];
                s[j] = i;
            }
        }

        r[j] = q;
    }

    return { r, s };
}

void printSolution(int p[], int n) {
    pair<vector<int>, vector<int>> myPair = extBotUpCutRod(p, n);
    while (n > 0) {
        int cut = myPair.second[n];
        cout << cut << " ";
        n -= cut;
    }
    cout << endl;
}
