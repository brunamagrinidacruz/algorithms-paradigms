#include <iostream>
#include <bitset>
#include <vector>
#include <map>

using namespace std;

long long size_crivo;

/*!< Bitset works as boolean (0 or 1) but uses only 1 bit */
bitset<46341> bs;
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

void factorial_divisor(long long n, long long m) {
	if(n == m) {
		printf("%lld divides %lld!\n", m, n);
		return;
	}

	map<int, int> primos_n, primos_m;

	for(int i = 2; i <= n; i++) { 
		map<int, int> map_f = prime_factors(i);
		for (map<int, int>::iterator j = map_f.begin(); j != map_f.end(); j++) {
			primos_n[j->first] += j->second; /*!< To each factor, count the amount of each prime */
		}
	}

	primos_m = prime_factors(m);

	for (map<int, int>::iterator i = primos_m.begin(); i != primos_m.end(); i++) {
		if(primos_n[i->first] == 0 || primos_n[i->first] < primos_m[i->first]) {
			printf("%lld does not divide %lld!\n", m, n);
			return;
		}
	}

	printf("%lld divides %lld!\n", m, n);
}

int main(void) {
    long long n, m;

	crivo(46341);

    while(cin >> n) {
		cin >> m;
		factorial_divisor(n, m);	
    }

    return 0;
}
