//2020-10-29

#include <iostream>
using namespace std;

#define INFINITY 100000

void change() {
    int value, amount_coins;  
    cin >> value;
    cin >> amount_coins;

    int coins[amount_coins];
    for(int i = 0; i < amount_coins; i++) cin >> coins[i];

    int min_sum_coins[value + 1];
    for(int i = 0; i < value+1; i++) min_sum_coins[i] = INFINITY;
    min_sum_coins[0] = 0;

    for(int i = 0; i < amount_coins; i++) {
        for(int j = 0; j <= value; j++) {
            if((j - coins[i] >= 0) && ((min_sum_coins[j - coins[i]] + 1) < min_sum_coins[j]))
                min_sum_coins[j] = (min_sum_coins[j - coins[i]] + 1);
        }
    }

    cout << min_sum_coins[value] << endl;
}

int main(void) {
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for(int i = 0; i < number_of_test_cases; i++) 
        change();
    return 0;
}