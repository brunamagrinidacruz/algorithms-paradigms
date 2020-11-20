//2020-10-16

#include <iostream>
using namespace std;
#include <vector>

int merge(vector<int> *dataset, int left, int middle, int right) {
    int inversoes = 0;
    int size_temporary_left = middle - left + 1; 
    int size_temporary_right = right - middle; 
    
    vector<int> temporary_left;
    vector<int> temporary_right;

    for(int i = 0; i < size_temporary_left; i++) 
        temporary_left.push_back((*dataset)[left + i]);
    for(int i = 0; i < size_temporary_right; i++)
        temporary_right.push_back((*dataset)[middle + 1 + i]);
    
    int index_left = 0, index_right = 0, index_dataset = left;
    for(int i = left; i < right+1; i++) {
        if(index_left >= size_temporary_left) {
            (*dataset)[index_dataset] = temporary_right[index_right];
            index_right++;
        } else if(index_right >= size_temporary_right) {
            (*dataset)[index_dataset] = temporary_left[index_left];
            index_left++;
        } else if(temporary_left[index_left] < temporary_right[index_right]) {
            (*dataset)[index_dataset] = temporary_left[index_left];
            index_left++;
        } else {
            (*dataset)[index_dataset] = temporary_right[index_right];
            index_right++;
            inversoes += (middle - (index_left+left) + 1);
        }
        index_dataset++;
    }

    return inversoes;
}

int merge_sort(vector<int> *dataset, int left, int right) {
    if(left < right) {
        int middle = (left+right)/2;
        int inversoes_left, inversoes_right, inversoes_merge;
        inversoes_left = merge_sort(dataset, left, middle);
        inversoes_right = merge_sort(dataset, middle+1, right);
        inversoes_merge = merge(dataset, left, middle, right);
        return inversoes_merge + inversoes_left + inversoes_right;
    } else {
        return 0;
    }
}

void inversoes() {
    vector<int> dataset;
    int size_of_vector;

    cin >> size_of_vector;
    int value;
    for(int i = 0; i < size_of_vector; i++) {
        cin >> value;
        dataset.push_back(value);
    }

    cout << merge_sort(&dataset, 0, size_of_vector-1) << endl;
}

int main(void) {
    int number_of_test_cases;
    cin >> number_of_test_cases;

    for(int i = 0; i < number_of_test_cases; i++) inversoes();

    return 0;
}