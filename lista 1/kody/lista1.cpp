/*

1. (4 pkt) Zaimplementuj algorytm INSERTION_SORT oraz jego modyfikację polegającą na wsta -
wianiu na raz dwóch kolejnych elementów tablicy (uprzednio je porównawszy).

2. (4 pkt) Zaimplementuj algorytm MERGE_SORT oraz jego modyfikację polegająca na dzieleniu na
trzy części zamiast dwóch.

3. (4 pkt) Zaimplementuj algorytm HEAP_SORT oraz jego modyfikację używającą zamiast kopców
binarnych kopce ternarne.

4. W kazdym z algorytmów dodaj zmienne liczące porównania i przypisania.

5. Dokonaj testów, dzięki którym mozna porównać zaimplementowane algorytmy

*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n_limit = 10000;
int n = 2;
int low = -2, high = 2;
const bool display_array = true;

unsigned long long comparison_counter;
unsigned long long assignment_counter;

int* ins_sort(const int* unsorted);

int* ins_sort_mod(const int* unsorted);

int* merge_sort_init(const int* unsorted);
void merge_sort(int A[], int p, int k);
void merge(int A[], int p, int s, int k);

int* merge_sort_mod_init(const int* unsorted);
void merge_sort_mod(int A[], int p, int k);
void merge_mod(int A[], int p, int part1, int part2, int k);

int* heap_sort_init(const int* unsorted);
void heap_sort(int A[], int n);
void build_heap(int A[], int n);
void heapify(int A[], int i, int n);

int* heap_sort_mod_init(const int* unsorted);
void heap_sort_mod(int A[]);
void build_heap_mod(int A[]);
void heapify_mod(int A[], int i, int size);

int main()
{
    srand(time(0));
    ofstream MyFile("sorting_alg_comparison.csv");

    cout << "Lista 1" << endl;
    cout << "Maciej Kmieciak 277516" << endl;
    cout << "Maksymalny n: " << n_limit << endl;
    // cout << "Wyswietlanie zawartosci tablic: "; 
    // if (display_array) cout << "tak"; else cout << "nie";
    cout << endl << "------------------------------------------------------" << endl << endl;

    cout << "n;ins1_a;ins1_c;ins2_a;ins2_c;mer1_a;mer1_c;mer2_a;mer2_c;heap1_a;heap1_c;heap2_a;heap2_c" << endl;
    MyFile << "n;ins1_a;ins1_c;ins2_a;ins2_c;mer1_a;mer1_c;mer2_a;mer2_c;heap1_a;heap1_c;heap2_a;heap2_c" << endl;
    
    while (n <= n_limit) {
        cout << n << ";";
        MyFile << n << ";";

        int* unsorted = new int[n];

        // cout << "Wypelniam tablice losowymi liczbami... ";
        for (int i = 0; i < n; ++i) {
            unsorted[i] = low + rand() % (high - low + 1);
            // if (display_array) cout << unsorted[i] << " ";
        } // cout << endl;

        // cout << endl;

        // cout << "Sortuje zwyklym INSERTION... ";
        int* ins_sort_result = ins_sort(unsorted);
        // if (display_array) for (int i = 0;i < n; ++i) {
        //     cout << ins_sort_result[i] << " ";
        // } cout << endl;
        delete[] ins_sort_result;
        // cout << "Przypisan: " << assignment_counter << ". ";
        // cout << "Porownan: " << comparison_counter << ". " << endl;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "Sortuje zmodyfikowanym INSERTION... ";
        int* ins_sort_mod_result = ins_sort_mod(unsorted);
        // if (display_array) for (int i = 0;i < n; ++i) {
        //     cout << ins_sort_mod_result[i] << " ";
        // } cout << endl;
        delete[] ins_sort_mod_result;
        // cout << "Przypisan: " << assignment_counter << ". ";
        // cout << "Porownan: " << comparison_counter << ". " << endl;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "Sortuje zwyklym MERGE... ";
        int* merge_sort_result = merge_sort_init(unsorted);
        // if (display_array) for (int i = 0;i < n; ++i) {
        //     cout << merge_sort_result[i] << " ";
        // } cout << endl;
        delete[] merge_sort_result;
        // cout << "Przypisan: " << assignment_counter << ". ";
        // cout << "Porownan: " << comparison_counter << ". " << endl;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "Sortuje zmodyfikowanym MERGE... ";
        int* merge_sort_mod_result = merge_sort_mod_init(unsorted);
        // if (display_array) for (int i = 0;i < n; ++i) {
        //     cout << merge_sort_mod_result[i] << " ";
        // } cout << endl;
        delete[] merge_sort_mod_result;
        // cout << "Przypisan: " << assignment_counter << ". ";
        // cout << "Porownan: " << comparison_counter << ". " << endl;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "Sortuje zwyklym HEAP... ";
        int* heap_sort_result = heap_sort_init(unsorted);
        // if (display_array) for (int i = 0;i < n; ++i) {
        //     cout << heap_sort_result[i] << " ";
        // } cout << endl;
        delete[] heap_sort_result;
        // cout << "Przypisan: " << assignment_counter << ". ";
        // cout << "Porownan: " << comparison_counter << ". " << endl;
        cout << assignment_counter << ";" << comparison_counter << ";";
        MyFile << assignment_counter << ";" << comparison_counter << ";";

        // cout << endl;

        // cout << "Sortuje zmodyfikowanym HEAP... ";
        int* heap_sort_mod_result = heap_sort_mod_init(unsorted);
        // if (display_array) for (int i = 0;i < n; ++i) {
        //     cout << heap_sort_mod_result[i] << " ";
        // } cout << endl;
        delete[] heap_sort_mod_result;
        // cout << "Przypisan: " << assignment_counter << ". ";
        // cout << "Porownan: " << comparison_counter << ". " << endl;
        cout << assignment_counter << ";" << comparison_counter << endl;
        MyFile << assignment_counter << ";" << comparison_counter << endl;

        delete[] unsorted;

        ++n;
        low = -n;
        high = n;
    }
    
    MyFile.close();
    return 0;
}

// ------------------------------------------------------
// INSERTION SORT - ZWYKLY

int* ins_sort(const int* unsorted) {
    int* A = new int[n];

    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }

    assignment_counter = 0;
    comparison_counter = 0;

    for (int i = 1; i < n; ++i) {

        int x = A[i];
        ++assignment_counter;
        int j = i - 1;
        ++assignment_counter;


        while (j >= 0 && A[j] > x) {
            comparison_counter += 1;

            A[j + 1] = A[j];
            --j;
            assignment_counter += 2;
        }
        comparison_counter += 1;

        A[j + 1] = x;
        assignment_counter += 1;
    }


    return A;
}

// ------------------------------------------------------
// INSERTION SORT - MODYFIKACJA

int* ins_sort_mod(const int* unsorted) {
    int* A = new int[n];

    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }

    assignment_counter = 0;
    comparison_counter = 0;

    for (int i = 1; i + 1 < n; i += 2) {
        // Porównanie A[i] z A[i + 1]
        ++comparison_counter;
        if (A[i] > A[i + 1]) {
            swap(A[i], A[i + 1]);
            assignment_counter += 3; // Swap wykonuje 3 przypisania
        }

        int x = A[i], y = A[i + 1];
        assignment_counter += 2;

        int j = i - 1;
        int k = i;
        assignment_counter += 1;

        
        while (j >= 0) {

            ++comparison_counter;
            if (A[j] > y) {
                A[k + 1] = A[j];
                --j;
                --k;
                assignment_counter += 3;
                continue;
            }
            
            ++comparison_counter;
            if (A[j] > x) {
                A[j + 1] = A[j];
                --j;
                assignment_counter += 2;
            }

            else {
                break;
            }
        }

        A[j + 1] = x;
        A[k + 1] = y;
        assignment_counter += 2;
    }

    // Jeśli n jest parzyste, został ostatni, pojedynczy element
    // Wstawiamy go, jak w zwykłym INSERTION
    if (n % 2 == 0) {
        int x = A[n - 1];
        int j = n - 2;
        assignment_counter += 2;

        while (j >= 0 && A[j] > x) {
            ++comparison_counter;

            A[j + 1] = A[j];
            --j;
            assignment_counter += 2;
        }
        ++comparison_counter;

        A[j + 1] = x;
        ++assignment_counter;
    }

    return A;
}


// ------------------------------------------------------
// MERGE SORT - ZWYKLY

int* merge_sort_init(const int* unsorted) {
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }
    assignment_counter = 0;
    comparison_counter = 0;
    merge_sort(A, 0, n - 1);
    return A;
}

void merge_sort(int A[], int p, int k) {
    ++comparison_counter;
    if (p < k) {
        int s = (p + k) / 2;
        ++assignment_counter;
        merge_sort(A, p, s);
        merge_sort(A, s + 1, k);
        merge(A, p, s, k);
    }
}

void merge(int A[], int p, int s, int k) {
    int n1 = s - p + 1;
    int n2 = k - s;
    assignment_counter += 2;

    int* L = new int[n1 + 1];
    int* R = new int[n2 + 1];
    
    L[n1] = high + 1; // (high + 1) pełni tu funkcję nieskończoności
    R[n2] = high + 1;
    assignment_counter += 2; // (być może tego nie powinno się liczyć)

    for (int i = 0; i < n1; ++i) {
        L[i] = A[p + i];
        ++assignment_counter;
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = A[s + 1 + j];
        ++assignment_counter;
    }

    int i = 0, j = 0;
    assignment_counter += 2;

    for (int l = p; l <= k; ++l) {
        
        ++comparison_counter;
        if (L[i] <= R[j]) {
            A[l] = L[i];
            ++i;
            assignment_counter += 2;
        }
        else {
            A[l] = R[j];
            ++j;
            assignment_counter += 2;
        }
    }

    delete[] L;
    delete[] R;
}


// ------------------------------------------------------
// MERGE SORT - MODYFIKACJA

int* merge_sort_mod_init(const int* unsorted) {
    int* A = new int[n];

    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }

    assignment_counter = 0;
    comparison_counter = 0;

    merge_sort_mod(A, 0, n - 1);

    return A;
}

void merge_sort_mod(int A[], int p, int k) {
    ++comparison_counter;
    if (p < k) {
        int part1 = p + (k - p) / 3;
        int part2 = p + 2 * (k - p) / 3;
        assignment_counter += 2;

        merge_sort_mod(A, p, part1);
        merge_sort_mod(A, part1 + 1, part2);
        merge_sort_mod(A, part2 + 1, k);

        merge_mod(A, p, part1, part2, k);
    }
}

void merge_mod(int A[], int p, int part1, int part2, int k) {
    int n1 = part1 - p + 1;
    int n2 = part2 - part1;
    int n3 = k - part2;
    assignment_counter += 3;

    int* L = new int[n1 + 1];
    int* M = new int[n2 + 1];
    int* R = new int[n3 + 1];

    L[n1] = high + 1;
    M[n2] = high + 1;
    R[n3] = high + 1;
    assignment_counter += 3;

    for (int i = 0; i < n1; ++i) {
        L[i] = A[p + i];
        ++assignment_counter;
    }
    for (int j = 0; j < n2; ++j) {
        M[j] = A[part1 + 1 + j];
        ++assignment_counter;
    }
    for (int l = 0; l < n3; ++l) {
        R[l] = A[part2 + 1 + l];
        ++assignment_counter;
    }

    int i = 0, j = 0, l = 0;
    assignment_counter += 3;

    for (int m = p; m <= k; ++m) {

        // Uwaga: liczba porównań zależy od tego, czy druga część AND musiała być sprawdzona
        if (L[i] <= M[j] && L[i] <= R[l]) {
            comparison_counter += 2;

            A[m] = L[i];
            i++;
            assignment_counter += 2;
        }
        else if (M[j] <= L[i] && M[j] <= R[l]) {
            if (L[i] <= M[j]) comparison_counter += 4;
            else comparison_counter += 3;
            
            A[m] = M[j];
            j++;
            assignment_counter += 2;
        }
        else {
            comparison_counter += 2;
            if (L[i] <= M[j]) ++comparison_counter;
            if (M[j] <= L[i]) ++comparison_counter;

            
            A[m] = R[l];
            l++;
            assignment_counter += 2;
        }
    }

    delete[] L;
    delete[] M;
    delete[] R;
}

// ------------------------------------------------------
// HEAP SORT - ZWYKLY

int* heap_sort_init(const int* unsorted) {
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }
    assignment_counter = 0;
    comparison_counter = 0;
    heap_sort(A, n);
    return A;
}

void heap_sort(int A[], int n) {
    build_heap(A, n);
    for (int i = n - 1; i > 0; --i) {
        swap(A[0], A[i]);
        assignment_counter += 3;

        heapify(A, 0, i);
    }
}


void build_heap(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(A, i, n);
    }
}

void heapify(int A[], int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    assignment_counter += 3;

    comparison_counter += 3; // Po 1 za każdy if

    if (left < n && A[left] > A[largest]) {
        largest = left;
        ++assignment_counter;
        ++comparison_counter; // Druga część AND
    }

    if (right < n && A[right] > A[largest]) {
        largest = right;
        ++assignment_counter;
        ++comparison_counter; // Druga część AND
    }

    if (largest != i) {
        swap(A[i], A[largest]);
        assignment_counter += 3;

        heapify(A, largest, n);
    }
}

// ------------------------------------------------------
// HEAP SORT - MODYFIKACJA

int* heap_sort_mod_init(const int* unsorted) {
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = unsorted[i];
    }
    assignment_counter = 0;
    comparison_counter = 0;
    heap_sort_mod(A);
    return A;
}

void heap_sort_mod(int A[]) {
    build_heap_mod(A);
    for (int i = n - 1; i > 0; --i) {
        swap(A[0], A[i]);
        assignment_counter += 3;

        heapify_mod(A, 0, i);
    }
}

void build_heap_mod(int A[]) {
    for (int i = n / 3 - 1; i >= 0; --i) {
        heapify_mod(A, i, n);
    }
}

void heapify_mod(int A[], int i, int size) {
    int largest = i;
    int left = 3 * i + 1;
    int middle = 3 * i + 2;
    int right = 3 * i + 3;
    assignment_counter += 4;

    comparison_counter += 4;

    if (left < size && A[left] > A[largest]) {
        largest = left;
        ++assignment_counter;
        ++comparison_counter;
    }

    if (middle < size && A[middle] > A[largest]) {
        largest = middle;
        ++assignment_counter;
        ++comparison_counter;
    }

    if (right < size && A[right] > A[largest]) {
        largest = right;
        ++assignment_counter;
        ++comparison_counter;
    }

    if (largest != i) {
        swap(A[i], A[largest]);
        assignment_counter += 3;

        heapify_mod(A, largest, size);
    }
}