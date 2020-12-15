/*!< CodeForce 530G */

#include <iostream>
using namespace std;

int edit(int size, int set1[], int set2[]){
    int MEMO[size+1][size+1];

	for (int i = 0; i <= size; ++i)
		for (int j = 0; j <=size; j++)	{
			
            /*!< One of vector has ended */
			if (i == 0)
				MEMO[i][j] = j;
			else if (j == 0)
				MEMO[i][j] = i;

            /*!< Both caracters are equal, so keep looking... */
			else if (set1[i-1] == set2[j-1])
						MEMO[i][j] = MEMO[i-1][j-1];

            else MEMO[i][j] = 1 + min(
                MEMO[i-1][j], /*!< Remove */
                MEMO[i][j-1] /*!< Insert */
            );
		}
	return MEMO[size][size];
}

int transformation_to_equal() {
    int aux;
    int amount_numbers;
    cin >> amount_numbers;

    int set1[amount_numbers];
    for(int i = 0; i < amount_numbers; i++) {
        cin >> aux;
        set1[i] = aux;
    }

    int set2[amount_numbers];
    for(int i = 0; i < amount_numbers; i++) {
        cin >> aux;
        set2[i] = aux;
    }

    return edit(amount_numbers, set1, set2);
}


int main(void) {
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for(int i = 0; i < number_of_test_cases; i++) printf("Case %d: %d\n", i+1, transformation_to_equal());
    return 0;
}
