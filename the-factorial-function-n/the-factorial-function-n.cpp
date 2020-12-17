#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

/*!< Calculando os fatores primos de (n) */
map<int, int> fatores_primos(unsigned int N) {
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

bool divide(unsigned int n, unsigned int m) {
	/*!< Calculando a decomposicao em primos do divisor (m) */
	/** Exemplificacao do retorno
	* (2, 3), (3, 1), (5, 3)....
	* Ha 3 aparicoes para o primo 2, ha 1 aparicao para o primo 3, ha 3 aparicoes para o primo 5, etc...
	*/
	map<int, int> decomposicao = fatores_primos(m); 

	unsigned int divisor;
	double qtd;
	/*!< Para cada fator primo do divisor (m) */
	for (map<int, int>::iterator it = decomposicao.begin(); it!=decomposicao.end(); it++) { 
		divisor = it->first; 

		/*!< Calcula a quantidade de termos primos em n */
		qtd = 0;

		/*!< Enquanto o divisor for MENOR ou IGUAL a n, continue... */  
		while (divisor <= n) { 
			qtd = qtd + n / divisor;  
			divisor = divisor * it->first;
		}

		/*!< Se a quantidade de fatores de m não cabe em n, nao e divisor */
		if (qtd < it->second)     
			return false;
	}

	return true;
}

int main(void) {
    unsigned int n, m;

    while(cin >> n) {
		cin >> m;

		if (m == 0) /*!< Nao ha divisao por zero */
			printf("%u does not divide %u!\n", m, n);
		else if(m <= n) 
			printf("%d divides %d!\n", m, n);
		else
			if(divide(n, m)) 
				printf("%d divides %d!\n", m, n);
			else
				printf("%d does not divide %d!\n", m, n);
    }

    return 0;
}