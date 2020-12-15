/*!< UVA 160 */

#include <iostream>
#include <bitset>
#include <vector>
#include <map>

using namespace std;

long long size_crivo;

/*!< Bitset works as boolean (0 or 1) but uses only 1 bit */
bitset<100> bs;
vector<long long> primes;

void crivo(long long n){
	size_crivo = n +1;

	bs.set(); /*!< Initializes as true */  
	bs[0] = bs[1] = 0;

	for (long long i = 2; i <= size_crivo; i++){   /*!< Runs through the crio */
		if (bs[i]) { /*!< If it is a prime, eliminates all its multiples and puts in the primes vector */
			for (long long j = i*i; j <= size_crivo; j+=i) 
				bs[j] = 0;
			primes.push_back(i);
		}
	}

}

map<int, int> prime_factors(long long n){
	map<int, int> fatores; 
	long long FP;

	long long ind = 0;
	FP = primes[ind]; /*!< First prime is 2 */ 

	while (FP*FP <= n) {   
		while ( n % FP == 0){
			fatores[FP]++;
			n = n / FP;
		}
		FP = primes[++ind];
	}

	if (n != 1) 
		fatores[n]++;

	return fatores;

}

int main(void) {
    int number;

	crivo(100);

    scanf("%d", &number);
    while(number != 0) {
        map<int, int> amount_prime; /*!< Creates a relationship between [prime][amount prime]*/

		/*!< Given a number, calculates the prime to [2...number] and count the amount to each prime */
        for(int i = 2; i <= number; i++) { 
            map<int, int> m = prime_factors(i);
            for (map<int, int>::iterator j = m.begin(); j != m.end(); j++) 
				amount_prime[j->first] += j->second; /*!< To each factor, count the amount of each prime */
        }

        printf("%3d! =", number);

        int amount_numbers_line = 1;
        map<int, int>::iterator amount_prime_iterator; 
		
		/*!< Print to each prime the amount */
        for (amount_prime_iterator = amount_prime.begin(); amount_prime_iterator != amount_prime.end(); ++amount_prime_iterator) { 
            if(amount_numbers_line == 16) {
                printf("\n%9d", amount_prime_iterator->second); 
                amount_numbers_line = 0;
            } else {
                printf("%3d", amount_prime_iterator->second);
                amount_numbers_line++;
            }
            
        } 
  
        printf("\n");

        scanf("%d", &number);
    }

    return 0;
}
