#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

vector<int> DPActivitySelector(const vector<int>& s, const vector<int>& f) {
    int n = s.size() - 1;
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1));
    for (int i = n; i >= 0; --i) {
        for (int j = i + 1; j <= n; ++j) {
            int m = i + 1;
            while (m <= j && s[m] < f[i]) {
                m++;
            }
            vector<int> exclude = dp[i + 1][j];
            vector<int> include = (i > 0) ? vector<int>{i} : vector<int>{};
            if (m <= j) {
                include.insert(include.end(), dp[m][j].begin(), dp[m][j].end());
            }
            dp[i][j] = (include.size() > exclude.size()) ? include : exclude;
        }
    }
    vector<int> result = dp[0][n];
    if (!result.empty() && result[0] == 0) {
        result.erase(result.begin());
    }
    return result;
}

void generateLargeActivityList(int maxSize, vector<int>& s, vector<int>& f) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> startDist(1, 1000000);
    uniform_int_distribution<> finishDist(1, 1000000);

    s.resize(maxSize + 1);
    f.resize(maxSize + 1);
    s[0] = -numeric_limits<int>::max();
    f[0] = -numeric_limits<int>::max();

    for (int i = 1; i <= maxSize; ++i) {
        s[i] = startDist(gen);
        f[i] = finishDist(gen);
    }

    vector<pair<int, int>> activities(maxSize);
    for (int i = 1; i <= maxSize; ++i) {
        activities[i - 1] = { s[i], f[i] };
    }
    sort(activities.begin(), activities.end());

    for (int i = 1; i <= maxSize; ++i) {
        s[i] = activities[i - 1].first;
        f[i] = activities[i - 1].second;
    }

    cout << "Generated Activities (Start, Finish):\n";
    for (int i = 1; i <= maxSize; ++i) {
        cout << "(" << s[i] << ", " << f[i] << ") ";
    }
    cout << endl;
}

int main() {
    const int maxSize = 10000; 
    vector<int> s, f;
    generateLargeActivityList(maxSize, s, f);

    ofstream csvFile("dp_activity_selection_comparison.csv");
    csvFile << "InputSize,DPTime(ms)" << endl;

    for (int n = 10; n <= maxSize; n += 10) { 
        vector<int> sSubset(s.begin(), s.begin() + n + 1);
        vector<int> fSubset(f.begin(), f.begin() + n + 1);

        auto start = chrono::high_resolution_clock::now();
        vector<int> result = DPActivitySelector(sSubset, fSubset);
        
        /*
        cout << "Selected Activities: ";
        for (int idx : result) {
            cout << "(" << sSubset[idx] << ", " << fSubset[idx] << ") ";
        }
        cout << endl;
        */
        
        auto end = chrono::high_resolution_clock::now();
        auto dpTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        csvFile << n << "," << dpTime << endl;

        cout << "Input Size: " << n << ", DP: " << dpTime << " ms" << endl;
    }

    csvFile.close();
    cout << "Results saved to dp_activity_selection_comparison.csv" << endl;
    return 0;
}
