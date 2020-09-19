// 09/09/2020

#include <iostream>
using namespace std;

#include <vector>

void coin_collector() {
    int number_coins;
    cin >> number_coins;

    vector<int> coins; /*!< Vector with the number of coins */
    int coin;
    /*!< Reading the coins */
    for(int i = 0; i < number_coins; i++) {
        cin >> coin;
        coins.push_back(coin);
    }

    /**
     * In all cases, the first and the last coin always will be counted
     * Example: [1, 3, 6, 8, 15, 20]
     * Sum = [0] = 1 (the first coin is always counted) and Number = 1
     * Sum = 1, [1] = 3 [2] = 6. Then, sum+3 = 4 and 4 < 6 [2], so the coin 3 will be counted => Sum += 3 and Number = 2
     * Sum = 4, [2] = 6, [3] = 8. Then, sum+6 = 10 and 10 < 8 [3], so the coin 6 won't be counted
     * Sum = 4, [3] = 8, [4] = 15. Then, sum+8 = 12 and 12 < 15, so the coin 8 will be counted => Sum += 8 and Number = 3
     * Sum = 12, [4] = 15, [5] = 20. Them, sum+15 = 27 and 27 < 20, so the coin 15 won't be counted
     * The last coin is always counted so Number = 4
    */
    int max_number_coins = 2; /*!< The first and the last coin */
    int sum = coins[0];
    for(int i = 1; i < number_coins-1; i++) {
        if(sum + coins[i] < coins[i+1]) {
            sum += coins[i];
            max_number_coins++;
        }
    }

    cout << max_number_coins << endl;
}

int main(void) {
    int number_of_test_cases;
    cin >> number_of_test_cases;

    for(int i = 0; i < number_of_test_cases; i++) 
        coin_collector();

    return 0;
}