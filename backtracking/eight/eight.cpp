//2020-10-09 

#include <iostream>
using namespace std;
#include <stdio.h>

#include <queue>
#include <vector>

#define SIZE_OF_BOARD 9
#define AMOUNT_OPTIONS_MOVE 4

struct board {
	vector<char> dataset;
	int depth;
    int wrong_tiles;
    int heuristic;
    int empty_position;
    char forbidden_move;
    char move;
    /*!< Function to queue priority */
    bool operator< (const board& board2) const {
        return board2.heuristic < heuristic;
    }
};

/*!< It's h(n). How much the dataset is far from the final answer */
int count_wrong_tiles(vector<char> dataset) {
    int wrong_tiles = 0;
    /*!< If the value in the dataset[i] is diferent from the answer correct that correspond to i+1 */
    for(int i = 0; i < SIZE_OF_BOARD-1; i++) 
        if(dataset[i] - '0' != i+1) wrong_tiles++;
    return wrong_tiles;
}

/*!< Initialize a new board configuration */
board initialize_board_configuration(board current, int next_empty_position, char forbidden_move) {
    board next;
    vector<char> new_dataset;
    int tile;

    /*!< Creating the new dataset */
    for(int i = 0; i < SIZE_OF_BOARD; i++) 
        new_dataset.push_back(current.dataset[i]);  /*!< Copying the vector */
    /*!< Change the position of the empty space */
    tile = current.dataset[next_empty_position]; 
    new_dataset[next_empty_position] = 'x';
    new_dataset[current.empty_position] = tile;
    /*!< Setting the new dataset with the empty space moved */
    next.dataset = new_dataset;

    /*!< Where is the empty position*/
    next.empty_position = next_empty_position;

    next.forbidden_move = forbidden_move;

    /*!< Calculating heuristic */
    next.depth = current.depth + 1; /*!< g(n) */
    next.wrong_tiles = count_wrong_tiles(next.dataset); /*!< h(n) */
    next.heuristic = next.depth + next.wrong_tiles; /*!< f(n) */
    
    return next;
}

int next_states(board current, board next[4]) {
    int index = 0;
    board up, right, down, left;

    /*!< Up */
    if((current.empty_position - 3 > 0) && current.forbidden_move != 'u') {
        up = initialize_board_configuration(current, current.empty_position - 3, 'd');
        up.move = 'u';
        next[index] = up;
        index++;
    }

    /*!< Right */
    if((current.empty_position+1) % 3 != 0 && current.forbidden_move != 'r') {
        right = initialize_board_configuration(current, current.empty_position + 1, 'l');
        right.move = 'r';
        next[index] = right;
        index++;
    }

    /*!< Down */
    if(current.empty_position + 3 < SIZE_OF_BOARD && current.forbidden_move != 'd') {
        down = initialize_board_configuration(current, current.empty_position + 3, 'u');
        down.move = 'd';
        next[index] = down;
        index++;
    }

    /*!< Left */
    if((current.empty_position + 3) % 3 != 0 && current.forbidden_move != 'l') {
        left = initialize_board_configuration(current, current.empty_position - 1, 'r');
        left.move = 'l';
        next[index] = left;
        index++;
    }

    return index;
}

void eight() {    
    priority_queue<board> pq;
    board current;
    board next[AMOUNT_OPTIONS_MOVE];

    vector<char> dataset;
    /*!< Reading the positions of the tiles */
    char tile; 
    for(int i = 0; i < SIZE_OF_BOARD; i++) {
        scanf("%c ", &tile);
        dataset.push_back(tile);
        if(tile == 'x') current.empty_position = i; /*!< Initializing the first empty position */
    }

    /*!< Initializing the first arrange of the board */
    current.dataset = dataset;
    current.depth = 0;
    current.forbidden_move = 'x';
    current.wrong_tiles = count_wrong_tiles(current.dataset);
    current.heuristic = current.wrong_tiles;

    pq.push(current);

    while(!pq.empty()) {
        /*!< Poping the first item, with the lowest heuristic */
        current = pq.top();
        pq.pop();

        cout << current.move;

        /*!< Problem solved! */
        if(current.wrong_tiles == 0) 
            return;
        
        int amount_configurations = next_states(current, next);
        for(int i = 0; i < amount_configurations; i++) pq.push(next[i]);
    }
    
    return;
}

int main(void) {
    int number_of_test_cases;
    scanf("%d ", &number_of_test_cases);

    for(int i = 0; i < number_of_test_cases; i++) eight();

    return 0;
}