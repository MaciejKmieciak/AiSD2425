#include <iostream>
#include <fstream>

using namespace std;

const int n_limit = 10000;
int n = 2, high = 2;

unsigned long long assignment_counter;
unsigned long long comparison_counter;

struct Node {
	float data;
	Node* next;

	Node(float val) : data(val), next(nullptr) {}
};

class List {
private:
	Node* head;

	void insert(Node** sorted, Node* newNode) {
		++comparison_counter;
		if (!*sorted || (*sorted)->data >= newNode->data) {
			newNode->next = *sorted;
			*sorted = newNode;
			assignment_counter += 2;
		}
		else {
			Node* current = *sorted;
			++assignment_counter;

			++comparison_counter;
			while (current->next && current->next->data < newNode->data) {
				++comparison_counter;
				current = current->next;
				++assignment_counter;
			}
			newNode->next = current->next;
			current->next = newNode;
			assignment_counter += 2;
		}
	}

public:
	List() : head(nullptr) {}

	int getSize() {
		if (!head) return 0;
		
		int size = 1;

		Node* current = head;

		while (current->next) {
			++size;
			current = current->next;
		}

		return size;
	}

	float getElement(int n) {
		Node* current = head;
		int i = 0;

		while (current) {
			if (i == n) {
				return current->data;
			}
			current = current->next;
			++i;
		}
	}

	void append(float value) {
		Node* newNode = new Node(value);
		if (!head) {
			head = newNode;
			return;
		}

		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
	}

	/* void display() {
		Node* temp = head;
		while (temp) {
			cout << temp->data << " -> ";
			temp = temp->next;
		}
		cout << "nullptr" << endl;
	} */

	void insertionSort() {
		if (!head || !head->next) return;

		Node* sorted = nullptr;
		Node* current = head;

		while (current) {
			Node* next = current->next;
			insert(&sorted, current);
			current = next;
		}

		head = sorted;
	}

	
};

float* bucket(const float* unsorted);
float* bucket_mod(const float* unsorted);

int main() {
	srand(time(0));
	ofstream MyFile("BucketSort.csv");

	cout << "n;b1_a;b1_c;b2_a;b2_c" << endl;
	MyFile << "n;b1_a;b1_c;b2_a;b2_c" << endl;

	while(n <= n_limit) {
		cout << n << ";";
		MyFile << n << ";";

		float* unsorted = new float[n];

		for (int i = 0; i < n; ++i) {
			int x = rand() % high;
			unsorted[i] = (float)x / high;
		}

		float* bucket_result = bucket(unsorted);

		//for (int i = 0; i < n; ++i) {
		//	cout << bucket_result[i] << " ";
		//} cout << endl;

		delete[] bucket_result;
		delete[] unsorted;

		cout << assignment_counter << ";" << comparison_counter << ";";
		MyFile << assignment_counter << ";" << comparison_counter << ";";

		float* unsorted2 = new float[n];

		for (int i = 0; i < n; ++i) {
			unsorted2[i] = rand() % high;
		}

		float* bucket_mod_result = bucket_mod(unsorted2);

		//for (int i = 0; i < n; ++i) {
		//	cout << bucket_mod_result[i] << " ";
		//} cout << endl;

		delete[] bucket_mod_result;
		delete[] unsorted2;

		cout << assignment_counter << ";" << comparison_counter << ";" << endl;
		MyFile << assignment_counter << ";" << comparison_counter << ";" << endl;

		++n;
		high = n;
	}

	MyFile.close();
	return 0;
}

float* bucket(const float* unsorted) {
	float* A = new float[n];

	for (int i = 0; i < n; ++i) {
		A[i] = unsorted[i];
	}

	assignment_counter = 0;
	comparison_counter = 0;

	List* B = new List[n];
	for (int j = 0; j < n; ++j) {
		B[j] = List();
	}

	for (int i = 0; i < n; ++i) {
		B[(int)floor(n * A[i])].append(A[i]);
		++assignment_counter;
	}

	for (int j = 0; j < n; ++j) {
		B[j].insertionSort();
	}

	int i = 0;
	for (int j = 0; j < n; ++j) {
		for (int k = 0; k < B[j].getSize(); ++k) {
			A[i] = B[j].getElement(k);
			++i;
			if (i >= n) break;
		}
	}

	return A;
}

float* bucket_mod(const float* unsorted) {
	float* A = new float[n];

	for (int i = 0; i < n; ++i) {
		A[i] = unsorted[i];
	}

	assignment_counter = 0;
	comparison_counter = 0;

	float min_val = A[0], max_val = A[0];
	for (int i = 1; i < n; ++i) {
		comparison_counter += 2;
		if (A[i] < min_val) {
			min_val = A[i];
			++assignment_counter;
		}
		
		if (A[i] > max_val) {
			max_val = A[i];
			++assignment_counter;
		}
	}

	float range = max_val - min_val;

	List* B = new List[n];
	for (int j = 0; j < n; ++j) {
		B[j] = List();
	}

	for (int i = 0; i < n;++i) {
		int bucket_idx = (int)floor(n * (A[i] - min_val) / range);
		if (bucket_idx == n) bucket_idx = n - 1;
		B[bucket_idx].append(A[i]);
		++assignment_counter;
	}

	for (int j = 0; j < n; ++j) {
		B[j].insertionSort();
	}

	int i = 0;
	for (int j = 0; j < n; ++j) {
		for (int k = 0; k < B[j].getSize(); ++k) {
			A[i] = B[j].getElement(k);
			++i;
			if (i >= n) break;
		}
	}

	return A;
}