/*!< UVA 652 */

#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

#define SIZE_OF_BOARD 9
#define AMOUNT_OPTIONS_MOVE 4

struct puzzle {
	vector<char> board;
	int depth;
    int wrong_tiles;
    int empty_position;
    char move;
    /*!< Function to queue priority */
    bool operator< (const puzzle& puzzle2) const {
        return (puzzle2.depth +  puzzle2.wrong_tiles) < (depth + wrong_tiles);
    }
};

/*!< It's h(n). How much the board is far from the final answer */
int count_wrong_tiles(vector<char> board) {
    int wrong_tiles = 0;
    /*!< If the value in the board[i] is diferent from the answer correct that correspond to i+1 */
    for(int i = 0; i < SIZE_OF_BOARD-1; i++) 
        if(board[i] - '0' != i+1) wrong_tiles++;
    return wrong_tiles;
}

/*!< Initialize a new puzzle configuration */
puzzle initialize_puzzle_configuration(puzzle current, int next_empty_position) {
    puzzle next;
    vector<char> new_board;
    int tile;

    /*!< Creating the new board */
    for(int i = 0; i < SIZE_OF_BOARD; i++) 
        new_board.push_back(current.board[i]);  /*!< Copying the vector */
    /*!< Change the position of the empty space */
    tile = current.board[next_empty_position]; 
    new_board[next_empty_position] = 'x';
    new_board[current.empty_position] = tile;
    /*!< Setting the new board with the empty space moved */
    next.board = new_board;

    /*!< Where is the empty position*/
    next.empty_position = next_empty_position;

    /*!< Calculating heuristic */
    next.depth = current.depth + 1; /*!< g(n) */
    next.wrong_tiles = count_wrong_tiles(next.board); /*!< h(n) */
    
    return next;
}

int next_states_puzzle(puzzle current, puzzle next[4]) {
    int index = 0;
    puzzle up, right, down, left;

    /*!< Down */
    if(current.empty_position + 3 < SIZE_OF_BOARD) {
        down = initialize_puzzle_configuration(current, current.empty_position + 3);
        down.move = 'd';
        next[index] = down;
        index++;
    }

    /*!< Up */
    if((current.empty_position - 3) > 0) {
        up = initialize_puzzle_configuration(current, current.empty_position - 3);
        up.move = 'u';
        next[index] = up;
        index++;
    }

    /*!< Right */
    if((current.empty_position+1) % 3 != 0) {
        right = initialize_puzzle_configuration(current, current.empty_position + 1);
        right.move = 'r';
        next[index] = right;
        index++;
    }

    /*!< Left */
    if((current.empty_position + 3) % 3 != 0) {
        left = initialize_puzzle_configuration(current, current.empty_position - 1);
        left.move = 'l';
        next[index] = left;
        index++;
    }

    return index;
}

bool is_solvable(vector<char> board){
    vector<int> s;
    for(int i = 0; i < (int) board.size(); i++) 
        s.push_back(board[i] != 'x' ? board[i] - '0' : 0);

    int inv = 0;
	for (int i = 0; i < (int) s.size(); i++)
		for (int j = i+1; j < (int)s.size(); j++) {
			if (s[i] == 0 || s[j] == 0) continue;
			inv += s[i] > s[j];
		}
	return  (inv%2 == 0) ? true : false;
}

string eight() {    
    priority_queue<puzzle> pq;
    map<vector<char>, string> visited;  

    puzzle current;
    puzzle next_puzzles[AMOUNT_OPTIONS_MOVE];

    vector<char> board;
    /*!< Reading the positions of the tiles */
    char tile; 
    for(int i = 0; i < SIZE_OF_BOARD; i++) {
        scanf("%c ", &tile);
        board.push_back(tile);
        if(tile == 'x') current.empty_position = i; /*!< Initializing the first empty position */
    }

    if(!is_solvable(board))
        return "unsolvable";

    /*!< Initializing the first arrange of the puzzle */
    current.board = board;
    current.depth = 0;
    current.wrong_tiles = count_wrong_tiles(current.board);
    visited[current.board] = "";

    pq.push(current);

    while(!pq.empty()) {
        /*!< Poping the first item, with the lowest heuristic */
        current = pq.top();
        pq.pop();

        /*!< Problem solved! */
        if(current.wrong_tiles == 0) 
            return visited[current.board];
        
        int amount_configurations = next_states_puzzle(current, next_puzzles);
        for(int i = 0; i < amount_configurations; i++) {
            if(visited.count(next_puzzles[i].board) == 0) {
                visited[next_puzzles[i].board] = visited[current.board] + next_puzzles[i].move;
                pq.push(next_puzzles[i]);
            }
        }
    }

    return "unsolvable";
}

int main(void) {
    int number_of_test_cases;
    scanf("%d ", &number_of_test_cases);

    for(int i = 0; i < number_of_test_cases; i++) {
        cout << eight() << endl;
        if(i != number_of_test_cases-1) cout << endl;
    }

    return 0;
}
