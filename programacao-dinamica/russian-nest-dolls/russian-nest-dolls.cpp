#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

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

    printf("LIS: %d\n", lis(dolls_heights, number_of_dolls));
	return number_of_dolls-lis(dolls_heights, number_of_dolls)+1;
}

int main(void) {
	int number_of_test_cases;
    cin >> number_of_test_cases;
    for(int i = 0; i < number_of_test_cases; i++) printf("RESULTADO: %d\n", russian_nest_dolls());
	return 0;
}
