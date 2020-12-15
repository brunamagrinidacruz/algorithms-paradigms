/*!< Programacao Dinamica */

#include <iostream>
#include <string>
using namespace std;

#define ASCII 96 /*!< To subtract of ASCII number and transform in 1, 2, 3,... */

/*!< Besides return the min value, also return the operation that return the min value */
int MIN(int insert, int remove, int change, int *operation){
    if (insert <= remove && insert <= change) {
        (*operation) = 1;
        return insert;
    } else if (remove <= change && remove <= insert) {
        (*operation) = 2;
        return remove;
    } else {
        (*operation) = 3;
        return change;
    }
}

int edit(string str1, int str1_length, string str2, int str2_length){
    int MEMO[str1_length+1][str2_length+1];

	for (int i = 0; i <= str1_length; ++i)
		for (int j = 0; j <=str2_length; j++)	{
			
            /*!< One of vector has ended */
			if (i == 0)
				MEMO[i][j] = j;
			else if (j == 0)
				MEMO[i][j] = i;

            /*!< Both caracters are equal, so keep looking... */
			else if (str1[i-1] == str2[j-1])
						MEMO[i][j] = MEMO[i-1][j-1];

            else {
                int operation;

                int min_value = MIN(
                    MEMO[i][j-1], /*!< Insert */
                    MEMO[i-1][j], /*!< Remove */
                    MEMO[i-1][j-1], /*!< Change */
                    &operation
                );

                /*!< Calculating the cost depending on the operation */
                int operation_value;
                if(operation == 1) 
                    operation_value = str2[j-1]-ASCII;
                else if(operation == 2)
                    operation_value = str1[i-1]-ASCII;
                else
                    operation_value = abs((str1[i-1]-ASCII) - (str2[j-1]-ASCII));

                MEMO[i][j] = min_value + operation_value;
            }

		}

	return MEMO[str1_length][str2_length];
}

int main(void) {
    string str1;
    string str2;

    cin >> str1;
    cin >> str2;

    printf("%d\n", edit(str1, str1.length(), str2, str2.length()));

    return 0;
}
