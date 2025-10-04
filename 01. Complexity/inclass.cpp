#include <iostream>
#include <vector>

int *alloc1(int n) {
  return new int(n);
}

int *alloc2(int n) {
  return new int[n];
}

int *alloc3(int n) {
  return new int[n]{};
}

int sumN(int n) {
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += i;
  }
  return sum;
}

int sum(int n) {
  int s = 0;
  for (int i = 0; i < 2000000; ++i)
    s += n;
  return s;
}

// TODO: push_back

// binary search - )(log(n))
int binarySearch(std::vector<int> const &v, int target) {
  int left = 0, right = v.size()-1, mid;
  while (left >= right) {
    mid = left + (right - left) / 2;
    if (v[mid] == target)     return mid;
    else if (v[mid] < target) left = mid+1;
    else                      right = mid-1;
  }
  return -1;
}

// selection sort - O(n^2)
void selectionSort(std::vector<int> &v) {
  for (int i = 0; i < v.size()-1 ; ++i) {
    int minIdx = i;
    for (int j = i+1; j < v.size(); ++j) {
      if (v[minIdx] > v[j])
        minIdx = j;
    }
    std::swap(v[minIdx], v[i]);
  }
}

// bubble sort - O(n^2)
void bubbleSort(std::vector<int> &v) {
  for (int i = 0; i < v.size()-1; ++i) {
    bool swapped = false;
    for (int j = v.size()-1; j > i; --j) {
      if (v[j] < v[j-1]) {
        std::swap(v[j], v[j-1]);
        swapped = true;
      }
    }
    if (!swapped) break;
  }
}

// insertion sort - O(n^2)
void insertionSort(std::vector<int> &v) {
  for (int i = 1; i < v.size(); ++i) {
    int j = i - 1;
    int key = v[i];

    while (j >= 0 && v[j] > key) {
      v[j+1] = v[j];
      j--;
    }
    v[j+1] = key;
  }
}

// quick sort - O(n*log(n))
int partition(std::vector<int> &v, int low, int high) {
  int pivot = v[high];
  int i = low;

  for (int j = low; j < high; ++j) {
    if (v[j] <= pivot) {
      std::swap(v[i], v[j]);
      i++;
    }
  }
  std::swap(v[i], v[high]);
  return i;
}

void quicksort(std::vector<int> &v, int low, int high) {
  if (low >= high) return;

  int pi = partition(v, low, high);
  quicksort(v, low, pi-1);
  quicksort(v, pi+1, high);
}

void quicksort(std::vector<int> &v) {
  quicksort(v, 0, v.size()-1);
}

// TODO: merge sort

int main() {

  std::vector<int> v{4,3,1,2};
  bubbleSort(v);

  for (int el : v)
    std::cout << el << ' ';
  std::cout << std::endl;

  return 0;
}
