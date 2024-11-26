#include <iostream>
#include <fstream>

using namespace std;

int n = 10000;

unsigned long long comparison_counter;
unsigned long long assignment_counter;

int* radix_init(const int* unsorted, int d);
void radix(int A[], int d);
void counting(int A[], int digit_place, int d);

int main()
{
    srand(time(0));

    int* unsorted = new int[n];

    for (int i = 0; i < n; ++i) {
        unsorted[i] = rand() % n;
    }

    int max_d = 1000;

    ofstream MyFile("RadixSort.csv");
    cout << "d;a;c" << endl;
    MyFile << "d;a;c" << endl;

    for (int d = 2; d <= max_d; ++d) {
        int* radix_result = radix_init(unsorted, d);
        cout << d << ";" << assignment_counter << ";" << comparison_counter << ";" << endl;
        MyFile << d << ";" << assignment_counter << ";" << comparison_counter << ";" << endl;
        delete[] radix_result;
    }

    delete[] unsorted;
    MyFile.close();
    
    return 0;
}

int* radix_init(const int* unsorted, int d) {
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }

    assignment_counter = 0;
    comparison_counter = 0;

    radix(A, d);
    return A;
}

void radix(int A[], int d) {
    int max_val = A[0];
    
    ++assignment_counter;
    for (int i = 1; i < n; ++i) {
        
        ++comparison_counter;
        if (A[i] > max_val) {
            max_val = A[i];
            ++assignment_counter;
        }
    }

    int num_digits = log(max_val) / log(d) + 1;

    int digit_place = 1;
    for (int i = 0; i < num_digits; ++i) {
        counting(A, digit_place, d);
        digit_place *= d;
    }
}

void counting(int A[], int digit_place, int d) {
    int* C = new int[d]();
    int* B = new int[n];   

    for (int i = 0; i < n; ++i) {
        assignment_counter += 2;
        int digit = (A[i] / digit_place) % d;
        ++C[digit];
    }

    for (int j = 1; j < d; ++j) {
        ++assignment_counter;
        C[j] += C[j - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        assignment_counter += 3;
        int digit = (A[i] / digit_place) % d;
        B[C[digit] - 1] = A[i];
        --C[digit];
    }

    for (int i = 0; i < n; ++i) {
        A[i] = B[i];
    }

    delete[] C;
    delete[] B;
}