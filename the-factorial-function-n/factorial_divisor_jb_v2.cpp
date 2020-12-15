#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

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

int main(void) {
    unsigned int n, m;

    while(cin >> n) {
		cin >> m;

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
			for (map<int, int>::iterator j = decomposicao.begin(); j != decomposicao.end() && quantidade_primos != 0; j++) { /*!< Para cada primo que decompoe o divisor */
				/*!< Enquanto tiver valores que represente o primo */
				/*!< E enquanto o valor atual for divisivel pelo primo */
				while(j->second != 0 && aux % j->first == 0) { 
					aux = aux/j->first;
					quantidade_primos--;
					decomposicao[j->first]--;
				}
			}
		}

		if(quantidade_primos == 0) 
			printf("%d divides %d!\n", m, n);
		else
			printf("%d does not divide %d!\n", m, n);
    }

    return 0;
}