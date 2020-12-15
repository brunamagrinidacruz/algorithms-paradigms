#include <iostream>
using namespace std;

#include <vector>

void ratina_mase(int *total_paths, vector<vector<int>> *board, const int size, int x, int y) {
    /*!< Mark this position as visited */
    (*board)[x][y] = 1;
    if(x == (size-1) && y == (size-1)) {
        (*total_paths)++;
    } else {
        int next_position;

        next_position = y+1; /*!< Right */
        if(next_position < size && (*board)[x][next_position] != 1) 
            ratina_mase(total_paths, board, size, x, next_position);
        
        next_position = x+1; /*! Down */
        if(next_position < size && (*board)[next_position][y] != 1)
            ratina_mase(total_paths, board, size, next_position, y);

        next_position = y-1; /*! Left */
        if(next_position >= 0 && (*board)[x][next_position] != 1) 
            ratina_mase(total_paths, board, size, x, next_position);

        next_position = x-1; /*! Up */
        if(next_position >= 0 && (*board)[next_position][y] != 1)
            ratina_mase(total_paths, board, size, next_position, y);
    }
    /*!< Here we are going to return to who call this position, so this position it's not visited anymore */
    (*board)[x][y] = 0;
}

int main(void) {
    vector<vector<int>> board;

    int size;
    cin >> size;

    int cell;
    /*!< Reading the board */
    for(int i = 0; i < size; i++) {
        vector<int> line_board;
        vector<bool> line_path;
        for(int j = 0; j < size; j++) {
            cin >> cell;
            line_board.push_back(cell);
        }
        board.push_back(line_board);
    }   

    int total_paths = 0;
    ratina_mase(&total_paths, &board, size, 0, 0);

    cout << total_paths << endl;

    return 0;
}
