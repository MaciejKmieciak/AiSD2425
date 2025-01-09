#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

vector<int> RecursiveActivitySelector(const vector<int>& s, const vector<int>& f, int k) {
    int n = s.size() - 1;
    int m = k + 1;
    while (m <= n && s[m] < f[k]) {
        m++;
    }
    if (m > n) {
        return {};
    }
    vector<int> result = { m };
    vector<int> next = RecursiveActivitySelector(s, f, m);
    result.insert(result.end(), next.begin(), next.end());
    return result;
}

vector<int> IterativeActivitySelector(const vector<int>& s, const vector<int>& f) {
    int n = s.size() - 1;
    vector<int> A = { 1 };
    int k = 1;
    for (int m = 2; m <= n; ++m) {
        if (s[m] >= f[k]) {
            A.push_back(m);
            k = m;
        }
    }
    return A;
}

void generateLargeActivityList(int maxSize, vector<int>& s, vector<int>& f) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> startDist(1, maxSize);
    uniform_int_distribution<> durationDist(1, maxSize / 10);

    s.resize(maxSize + 1);
    f.resize(maxSize + 1);
    s[0] = -numeric_limits<int>::max();
    f[0] = -numeric_limits<int>::max();

    for (int i = 1; i <= maxSize; ++i) {
        s[i] = startDist(gen);
        f[i] = s[i] + durationDist(gen);
    }

    vector<pair<int, int>> activities(maxSize);
    for (int i = 1; i <= maxSize; ++i) {
        activities[i - 1] = { f[i], s[i] };
    }
    sort(activities.begin(), activities.end());

    for (int i = 1; i <= maxSize; ++i) {
        f[i] = activities[i - 1].first;
        s[i] = activities[i - 1].second;
    }

    /*
    cout << "Generated Activities (Start, Finish):\n";
    for (int i = 1; i <= maxSize; ++i) {
        cout << "(" << s[i] << ", " << f[i] << ") ";
    }
    cout << endl;
    */
}

int main() {
    const int maxSize = 1000000; 
    vector<int> s, f;
    generateLargeActivityList(maxSize, s, f);

    ofstream csvFile("activity_selection_comparison.csv");
    csvFile << "InputSize,RecursiveTime(us),IterativeTime(us)" << endl;

    for (int n = 10; n <= maxSize; n += 10) { 
        vector<int> sSubset(s.begin(), s.begin() + n + 1);
        vector<int> fSubset(f.begin(), f.begin() + n + 1);

        auto start1 = chrono::high_resolution_clock::now();
        vector<int> recursiveResult = RecursiveActivitySelector(sSubset, fSubset, 0);
        auto end1 = chrono::high_resolution_clock::now();
        auto recursiveTime = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();

        auto start2 = chrono::high_resolution_clock::now();
        vector<int> iterativeResult = IterativeActivitySelector(sSubset, fSubset);
        auto end2 = chrono::high_resolution_clock::now();
        auto iterativeTime = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();

        csvFile << n << "," << recursiveTime << "," << iterativeTime << endl;

        cout << "Input Size: " << n << ", Recursive: " << recursiveTime
            << " us, Iterative: " << iterativeTime << " us" << endl;

        /*
        cout << "Recursive Selected Activities: ";
        for (int idx : recursiveResult) {
            cout << "(" << sSubset[idx] << ", " << fSubset[idx] << ") ";
        }
        cout << endl;

        cout << "Iterative Selected Activities: ";
        for (int idx : iterativeResult) {
            cout << "(" << sSubset[idx] << ", " << fSubset[idx] << ") ";
        }
        cout << endl;
        */
    }

    csvFile.close();
    cout << "Done" << endl;
    return 0;
}
