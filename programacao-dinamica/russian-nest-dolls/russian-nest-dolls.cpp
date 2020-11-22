#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define DEBUG 0
#define FLAG -1000

int lis(int arr[], int n) 
{ 
    int *lis, i, j, max = 0; 
    lis = (int*)malloc(sizeof(int) * n); 
  
    /* Initialize LIS values for all indexes */
    for (i = 0; i < n; i++) 
        lis[i] = 1; 
  
    /* Compute optimized LIS values in bottom up manner */
    for (i = 1; i < n; i++) 
        for (j = 0; j < i; j++) 
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) 
                lis[i] = lis[j] + 1; 
  
    /* Pick maximum of all LIS values */
    for (i = 0; i < n; i++) 
        if (max < lis[i]) 
            max = lis[i]; 
  
    /* Free memory to avoid memory leak */
    free(lis); 

    vector<int> head;
    int size_head = 1;
    head.push_back(arr[0]);
    for(i = 1; i < n; i++) {
        if(DEBUG) printf("analisando: %d\n", arr[i]);
        for(j = 0; j <= size_head; j++) {
            if(j == size_head) {
                if(DEBUG) printf("caso 1\n");
                head.push_back(arr[i]);
                size_head++;
                break;
            }
            // if(arr[i] < head[j]) break;
            if(arr[i] <= head[j]) {
                if(DEBUG) printf("caso 2\n");
                continue;
            }
            if(arr[i] > head[j]) {
                if(DEBUG) printf("caso 4: %d > %d\n", arr[i], head[j]);
                head[j] = arr[i];
                break;
            }
        }
    }

    if(DEBUG) printf("SIZE HEAD: %d\n", size_head);

    printf("%d\n", size_head);
    return max; 
} 

// int lis(int dolls_sizes[], int number_of_dolls) {
// 	int MEMO[number_of_dolls+1];
// 	MEMO[0] = 0;

// 	int amount_nested_dolls = FLAG;
// 	for (int i = 1; i <= number_of_dolls; i++) { 
// 		int amount_nested_dolls_temp = FLAG;

// 		for (int j = i-1; j>=0 ; j--) {
// 			if (dolls_sizes[i] > dolls_sizes[j])
// 			// if (dolls_sizes[i].first > dolls_sizes[j].first && dolls_sizes[i].second > dolls_sizes[j].second)
// 				amount_nested_dolls_temp = max(MEMO[j]+1, amount_nested_dolls_temp);
// 		}	

// 		if (amount_nested_dolls_temp == FLAG)
// 			amount_nested_dolls_temp = 1;

// 		MEMO[i] = amount_nested_dolls_temp;

// 		if (amount_nested_dolls < amount_nested_dolls_temp)
// 			amount_nested_dolls = amount_nested_dolls_temp;

// 		printf("MEMO:\n");
// 		for(int k = 0; k < number_of_dolls+1; k++) {
// 			printf("[%d] = %d\n", k, MEMO[k]);
// 		}	
// 	}

// 	return (amount_nested_dolls);
// 	// return (number_of_dolls-amount_nested_dolls);
// }

void merge(int vector[], int size, int low, int middle, int high, int vector_pair[]){
    int temp[size];
	int temp_pair[size];
    for(int i = low; i <= high; i++){
        temp[i] = vector[i];
		temp_pair[i] = vector_pair[i];
    }
    int i = low;
    int j = middle+1;
    int k = low;

    while (i <= middle && j <= high){
        if(temp[i] <= temp[j]){
            vector[k] = temp[i];
			vector_pair[k] = temp_pair[i];
            ++i;
        }
        else {
            vector[k] = temp[j];
			vector_pair[k] = temp_pair[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle){
        vector[k] = temp[i];
		vector_pair[k] = temp_pair[i];
        ++k;
        ++i;
    }
}

void merge_sort(int vector[], int size, int low, int high, int vector_pair[]){
    if (low < high){
        int middle = (low + high) / 2;
        merge_sort(vector, size, low, middle, vector_pair);
        merge_sort(vector, size, middle+1, high, vector_pair);
        merge(vector, size, low, middle, high, vector_pair);
    }
}

void merge_part_two(int vector[], int vector_pair[], int size) {
    int temp;
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(vector[j] == vector[j+1]) {
                if(vector_pair[j] < vector_pair[j+1]) {
                    temp = vector_pair[j];
                    vector_pair[j] = vector_pair[j+1];
                    vector_pair[j+1] = temp;
                }
            }
        }
    }
}


int russian_nest_dolls(){
	int number_of_dolls;
	cin >> number_of_dolls;

	// vector<pair <int,int>> dolls_sizes;
	int dolls_widths[number_of_dolls+1];
	int dolls_heights[number_of_dolls+1];
	dolls_widths[0] = FLAG;
	dolls_heights[0] = FLAG;

	// dolls_sizes.push_back(make_pair(0, 0));
	int width, height;
	for(int i = 0; i < number_of_dolls; i++) {
		cin >> width;
		cin >> height;
		// dolls_sizes.push_back(make_pair(width, height));
		dolls_widths[i] = width;
		dolls_heights[i] = height;
	}

	merge_sort(dolls_widths, number_of_dolls, 0, number_of_dolls-1, dolls_heights);

    merge_part_two(dolls_widths, dolls_heights, number_of_dolls);

	return lis(dolls_heights, number_of_dolls);
}

int main(void) {
	int number_of_test_cases;
    cin >> number_of_test_cases;
    for(int i = 0; i < number_of_test_cases; i++) printf("%d\n", russian_nest_dolls());
	return 0;
}
