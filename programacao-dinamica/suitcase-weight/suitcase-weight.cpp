//2020-11-13

#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX_AMOUNT_SUITCASES 20

/*!< Returns true if there is a subet o set[] of size n with sum equal to given sum */
bool weighted_subset_sum(int set[], int n, int sum) {
    bool MEMO[n + 1][sum + 1];
 
    /*!< Initializing the MEMO */
    for (int i = 0; i <= n; i++)
        MEMO[i][0] = true;
    for (int i = 1; i <= sum; i++)
        MEMO[0][i] = false;
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1])
                MEMO[i][j] = MEMO[i - 1][j];
            if (j >= set[i - 1])
                MEMO[i][j] = MEMO[i - 1][j] || MEMO[i - 1][j - set[i - 1]];
        }
    }
  
    return MEMO[n][sum];
}
 
void suitcase_weight() {
    int suitcases_weights[MAX_AMOUNT_SUITCASES];
    int amount_suitcases = 0, sum = 0;

    /*!< Reading the values */
    char auxilar;
    do {
        scanf("%d%c", &suitcases_weights[amount_suitcases], &auxilar);
        sum += suitcases_weights[amount_suitcases];
        amount_suitcases++;
    } while (auxilar != '\n' && auxilar != '\r');

    if(sum % 2 != 0) { /*!< It's impossible to divide the weight equally */
        printf("NO\n");
        return;
    }

    if(weighted_subset_sum(suitcases_weights, amount_suitcases, sum/2))
        printf("YES\n");
    else    
        printf("NO\n");
        
    return;
}

int main(void) {
    int number_of_test_cases;
    scanf("%d\n", &number_of_test_cases);
    for(int i = 0; i < number_of_test_cases; i++) suitcase_weight();
    return 0;
}