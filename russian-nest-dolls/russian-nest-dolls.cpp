/*!< UVA 11368 */
/*!< Programacao Dinamica */

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

/**
* Esta funcao utiliza o vetor head_lis para armazenar os maiores valores "cabecas" de cada possivel LIS
* A logica utilizada foi a explicada pelo Savio na aula da turma A do dia 20/11/2020 no tempo 28:30
*/
int pseudolis(int array[], int size) { 
    vector<int> head_lis;
    int size_head = 1;

    head_lis.push_back(array[0]);

    for(int i = 1; i < size; i++) {
        for(int j = 0; j <= size_head; j++) {
            if(j == size_head) {
                head_lis.push_back(array[i]);
                size_head++;
                break;
            }
            if(array[i] > head_lis[j]) {
                head_lis[j] = array[i];
                break;
            }
        }
    }

    return size_head; 
} 

/*!< O vector_pair é o vetor que apenas acompanha a ordenação do vector */
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

/*!< Dada o conjunto (largura, altura) ordenado por ordem ascendente de largura, quando duas larguras são iguais, ordena por alturas de forma decrescente */
void order_heights_by_downward(int dolls_widths[], int dolls_heights[], int size) {
    int temp;
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(dolls_widths[j] == dolls_widths[j+1] && dolls_heights[j] < dolls_heights[j+1]) {
                temp = dolls_heights[j];
                dolls_heights[j] = dolls_heights[j+1];
                dolls_heights[j+1] = temp;
            }
        }
    }
}


int russian_nest_dolls(){
	int number_of_dolls;
	cin >> number_of_dolls;

	int dolls_widths[number_of_dolls];
	int dolls_heights[number_of_dolls];

	int width, height;
	for(int i = 0; i < number_of_dolls; i++) {
		cin >> width;
		cin >> height;
		dolls_widths[i] = width;
		dolls_heights[i] = height;
	}

	merge_sort(dolls_widths, number_of_dolls, 0, number_of_dolls-1, dolls_heights); /*!< Ordenando largura por ordem ascendente */
    order_heights_by_downward(dolls_widths, dolls_heights, number_of_dolls);

	return pseudolis(dolls_heights, number_of_dolls);
}

int main(void) {
	int number_of_test_cases;
    cin >> number_of_test_cases;
    for(int i = 0; i < number_of_test_cases; i++) printf("%d\n", russian_nest_dolls());
	return 0;
}
