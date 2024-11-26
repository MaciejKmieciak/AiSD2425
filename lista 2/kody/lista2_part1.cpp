#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>

using namespace std;

const int n_limit = 10000;
int n = 2;
int low = -2, high = 2;

unsigned long long comparison_counter;
unsigned long long assignment_counter;

int* quick_init(const int* unsorted);
void quick(int A[], int p, int k);
int partition(int A[], int p, int k);

int* quick_mod_init(const int* unsorted);
void quick_mod(int A[], int p, int k);
array<int, 2> partition_mod(int A[], int p, int k);

int main()
{
    srand(time(0));
    ofstream MyFile("QuickSort.csv");

    cout << "Lista 2" << endl;
    cout << "Maciej Kmieciak 277516" << endl;
    cout << "Quick Sort" << endl;
    cout << "Maksymalny n: " << n_limit << endl;
    cout << endl << "------------------------------------------------------" << endl << endl;

    cout << "n;q1_a;q1_c;q2_a;q2_c" << endl;
    MyFile << "n;q1_a;q1_c;q2_a;q2_c" << endl;

    while (n <= n_limit) {
        cout << n << ";";
        MyFile << n << ";";

        int* unsorted = new int[n];

        // cout << "Wypelniam tablice losowymi liczbami... ";
        for (int i = 0; i < n; ++i) {
            unsorted[i] = low + rand() % (high - low + 1);
            //cout << unsorted[i] << " ";
        } //cout << endl;

        // cout << endl;

        // cout << "Sortuje zwyklym Quick Sort... ";
        int* quick_result = quick_init(unsorted);
        //for (int i = 0;i < n; ++i) {
        //    cout << quick_result[i] << " ";
        //} cout << endl;
        delete[] quick_result;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "Sortuje mod Quick Sort... ";
        int* quick_mod_result = quick_mod_init(unsorted);
        //for (int i = 0;i < n; ++i) {
        //    cout << quick_mod_result[i] << " ";
        //} cout << endl;
        delete[] quick_mod_result;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "----------------------------------------------------------------" << endl << endl;

        cout << endl;
        MyFile << endl;

        delete[] unsorted;

        ++n;
        high = n;
        low = -n;
    }

    MyFile.close();
    return 0;
}

// -----------QUICK_SORT - ZWYKŁY----------------------------------
// ----------------------------------------------------------------

int* quick_init(const int* unsorted) {
    assignment_counter = 0;
    comparison_counter = 0;
    
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }
    quick(A, 0, n - 1);
    return A;
}

void quick(int A[], int p, int k) {
    if (p < k) {
        int s = partition(A, p, k);
        quick(A, p, s - 1);
        quick(A, s + 1, k);
    }
}

int partition(int A[], int p, int k) {
    int x = A[k];
    int i = p - 1;
    assignment_counter += 2;

    for (int j = p; j <= k - 1; ++j) {
        
        ++comparison_counter;
        if (A[j] <= x) {
            ++i;
            swap(A[i], A[j]);
            assignment_counter += 4;
        }
    }
    swap(A[i + 1], A[k]);
    assignment_counter += 3;
    return i + 1;
}

// -----------QUICK_SORT - MODYFIKACJA-----------------------------
// ----------------------------------------------------------------

int* quick_mod_init(const int* unsorted) {
    assignment_counter = 0;
    comparison_counter = 0;
    
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }
    quick_mod(A, 0, n - 1);
    return A;
}

void quick_mod(int A[], int p, int k) {
    if (p < k) {
        auto S = partition_mod(A, p, k);
        quick_mod(A, p, S[0] - 1);
        quick_mod(A, S[0] + 1, S[1] - 1);
        quick_mod(A, S[1] + 1, k);
    }
}

array<int, 2> partition_mod(int A[], int p, int k) {
    if (A[p] > A[k]) {
        swap(A[p], A[k]);
        assignment_counter += 3;
    }
    int leftPivot = A[p];
    int rightPivot = A[k];

    int i = p + 1,
        j = p + 1,
        g = k - 1;
    assignment_counter += 5;

    while (j <= g) {
        ++comparison_counter;

        ++comparison_counter;
        if (A[j] < leftPivot) {
            swap(A[i], A[j]);
            ++i;
            assignment_counter += 4;
        }
        else if (A[j] > rightPivot) {

            ++comparison_counter;
            while (A[g] > rightPivot && j < g) {
                comparison_counter += 2;
                --g;
                ++assignment_counter;
            }
            
            swap(A[j], A[g]);
            --g;
            assignment_counter += 4;
           
            ++comparison_counter;
            if (A[j] < leftPivot) {
                swap(A[i], A[j]);
                ++i;
                assignment_counter += 4;
            }
        }
        ++comparison_counter;
        ++j;
        ++assignment_counter;
    }
    
    --i;
    ++g;
    swap(A[p], A[i]);
    swap(A[k], A[g]);
    comparison_counter += 8;

    return { i, g };
}