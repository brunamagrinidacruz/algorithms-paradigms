//2020-09-25

#include <iostream>
using namespace std;

#include <stdio.h>
#include <queue>
#include <cstring>

struct state{
	int digit[4];
	int depth;
    int heuristic;
    /*!< Função de comparação para fila de prioridade */
    bool operator< (const state& state2) const {
        return state2.heuristic < heuristic;
    }
};

int moves [8][4]= { {-1, 0, 0, 0 },
					 { 1, 0, 0, 0 },
					 { 0,-1, 0, 0 },
					 { 0, 1, 0, 0 },
					 { 0, 0,-1, 0 }, 
					 { 0, 0, 1, 0 },
					 { 0, 0, 0,-1 },
					 { 0, 0, 0, 1 } };

void next_states(state current, state next[8]){
	int i,j;
	for(i=0; i<8; i++){
		next[i] = current;
		next[i].depth = current.depth+1;
		for(j=0; j<4; j++){
			next[i].digit[j] += moves[i][j];
			if (next[i].digit[j]<0)
				next[i].digit[j] = 9;
			if (next[i].digit[j]>9)
				next[i].digit[j] = 0;
		}
	}
}

int equal(state current, state final){
	for (int i=0; i<4; i++)
		if (current.digit[i] != final.digit[i])
			return 0;
	return 1;
}

int calculete_heuristic(state current, state final) {
    int distance_to_final = 0, heuristic = 0;
    for (int i = 0; i < 4; i++) {
        heuristic = current.digit[i] - final.digit[i] >= 0 ? current.digit[i] - final.digit[i] : final.digit[i] - current.digit[i];
        if(heuristic > 5) heuristic = 10 - heuristic; /*!< Girar pelo outro lado */
        distance_to_final += heuristic;
    }
    return distance_to_final + current.depth;
}

int bfs(state current, state final, int visited[10][10][10][10]){
	state next[8];
    priority_queue<state> pq;

    /*!< Note que o estado inicial pode ser inválido */
	if (!visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]]){
        /*!< Marcando a combinação atual como visitada */
		visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]] = 1;
        
        /*!< Inserindo a posição inicial na lista */
        current.heuristic = calculete_heuristic(current, final);
	    pq.push(current);

		while(!pq.empty()) {
            /*!< Pegando o primeiro item, de menor heuristica, da fila */
	        current = pq.top();
			pq.pop();

            /*!< Verificando se o estado atual é o estado final desejado */
			if (equal(current, final))
				return current.depth; /*!< Retornando a profundidade da árvore */

            /*!< Como o estado atual não é o estado desejado, calcula os próximos estados os colocando na fila e continua a busca em largura */
			next_states(current, next);
			for (int i=0; i<8; i++)
				if (!visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]]) {
					visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]] = 1;
                    next[i].heuristic = calculete_heuristic(next[i], final);
                    pq.push(next[i]);
				}
		}
	}
	return -1;
}


int main (){
	int number_of_test_cases, number_of_forbidden_configurations;
	int visited[10][10][10][10];
	state initial, final, aux;

    cin >> number_of_test_cases;

	for (int i = 0; i < number_of_test_cases; i++){
		scanf("%d %d %d %d", &initial.digit[0], &initial.digit[1], &initial.digit[2], &initial.digit[3]);
		scanf("%d %d %d %d", &final.digit[0], &final.digit[1], &final.digit[2], &final.digit[3]);

		memset(visited, 0, sizeof visited);

        cin >> number_of_forbidden_configurations;
		for(int j = 0; j < number_of_forbidden_configurations; j++) {
			scanf("%d %d %d %d", &aux.digit[0], &aux.digit[1], &aux.digit[2], &aux.digit[3]);
			visited[aux.digit[0]][aux.digit[1]][aux.digit[2]][aux.digit[3]] = 1;
		}

		initial.depth=0;
		printf("%d\n", bfs(initial, final, visited));
	}

	return 0;
}