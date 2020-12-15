#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <math.h>


#define DEBUG 0

using namespace std;

long long size_crivo;

/*!< Bitset works as boolean (0 or 1) but uses only 1 bit */
bitset<1000000> bs;
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

map<int, int> primeFactorsNotCrive(unsigned int N) {
	map<int, int> factors;
	unsigned int c;
	int i;
	double src;

	c = N;
	while((c % 2) == 0) {
		factors[2]++;
		c /= 2;
	}

	i = 3;
	src = sqrt(c);
	while(i <= src) {
		if((c % i) == 0) {
			factors[i]++;
			c /= i;
			src = sqrt(c);
		} else {
			i += 2;
		}
	}

	if(c > 1) {
		factors[c]++;
	}

	return factors;
}

// vector<unsigned int> primeFactorsNotCrive(unsigned int N) {
// 	vector<unsigned int> factors;
// 	unsigned int c;
// 	unsigned int i;
// 	double src;

// 	c = N;
// 	while((c % 2) == 0) {
// 		factors.push_back(2);
// 		c /= 2;
// 	}

// 	i = 3;
// 	src = sqrt(c);
// 	while(i <= src) {
// 		if((c % i) == 0) {
// 			factors.push_back(i);
// 			c /= i;
// 			src = sqrt(c);
// 		} else {
// 			i += 2;
// 		}
// 	}

// 	if(c > 1) {
// 		factors.push_back(c);
// 	}

// 	return factors;
// }

void factorial_divisor(unsigned int n, unsigned int m) {
	if(n == m) {
		printf("%d divides %d!\n", m, n);
		return;
	}

	map<int, int> decomposicao = primeFactorsNotCrive(m); /*!< Calculando a decomposicao em primos do divisor */

	int quantidade_primos = 0;
	for (map<int, int>::iterator j = decomposicao.begin(); j != decomposicao.end(); j++) 
		quantidade_primos += j->second;

	unsigned int aux;
	for(int i = n; i >=2 && quantidade_primos != 0; i--) { /*!< Procura para cada parte do número n, ou seja, de [n... 2] */
		aux = i;
		for (map<int, int>::iterator j = decomposicao.begin(); j != decomposicao.end(); j++) { 
			if(DEBUG) printf("i: %d -> aux: %d | j->first: %d | j->second: %d | qtd_primos: %d\n", i, aux, j->first, j->second, quantidade_primos);
			while(j->second != 0 && aux % j->first == 0) {
				if(DEBUG) printf("         entrou no while com aux: %d, j->first: %d e j->second: %d\n", aux, j->first, j->second);
				aux = aux/j->first;
				quantidade_primos--;
				decomposicao[j->first]--;
			}
		}
	}

	if(DEBUG) printf("qtd de primos: %d\n", quantidade_primos);

	if(quantidade_primos == 0) 
		printf("%d divides %d!\n", m, n);
	else
		printf("%d does not divide %d!\n", m, n);
	

}

int main(void) {
    unsigned int n, m;

	crivo(1000000);

    while(cin >> n) {
		cin >> m;
		factorial_divisor(n, m);	
    }

    return 0;
}