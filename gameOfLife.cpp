#define frame_width 10
#define frame_height 10
#include <iostream>
using std::cout;
using std::endl;

enum class cellLife {DEAD, ALIVE};

int main()
{
    /* initialize game board with bool[4][3] */
    /* you are able to control the input stage here before the input interface has been designed */

    const bool board[frame_height][frame_width] = // input board
    {
        {0, 1, 0, 0, 1, 0, 1, 1, 1, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    };

    /* Allocate a dynamic 2 dim array
    bool** initial = new bool* [3]; // requiring memories for capture the input
    for (int i = 0; i < 4; ++i)
        initial[i] = new bool[4];
    //initial[2][2] = board[2][2];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            initial[i][j] = board[i][j];
        }
    }
    */
    bool n_board[frame_height][frame_width];
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            n_board[i][j] = board[i][j];
        }
    }


    static int life_counts_cell = 0;

    for (int i = 0; i <= frame_height-1; i++) {
        for (int j = 0; j <= frame_width-1; j++) {
            if (i > 0 && j > 0 && i < frame_height - 1 && j < frame_width - 1) { // when cursors are inside the grid board.
                if (board[i - 1][j] ) life_counts_cell++;
                if (board[i - 1][j - 1]) life_counts_cell++;
                if (board[i][j - 1]) life_counts_cell++;
                if (board[i - 1][j + 1]) life_counts_cell++;
                if (board[i + 1][j - 1]) life_counts_cell++;
                if (board[i + 1][j]) life_counts_cell++;
                if (board[i][j + 1]) life_counts_cell++;
                if (board[i + 1][j + 1]) life_counts_cell++;
            }
            else if(i == 0 && j == 0){ // Left Upper Corner
                if (board[i][j + 1]) life_counts_cell++;
                if (board[i+1][j]) life_counts_cell++;
                if (board[i + 1][j + 1]) life_counts_cell++;
            }
            else if (i == frame_height - 1 && j == 0) { // Left Bottom Corner
                if (board[i][j+1]) life_counts_cell++;
                if (board[i-1][j]) life_counts_cell++;
                if (board[i-1][j+1]) life_counts_cell++;
            }
            else if (i == frame_height - 1 && j == frame_width - 1) { // Right buttom corner
                if (board[i - 1][j - 1]) life_counts_cell++;
                if (board[i - 1][j]) life_counts_cell++;
                if (board[i][j - 1]) life_counts_cell++;
            }
            else if (i == 0 && j == frame_width - 1) { // Right Upper Corner
                if (board[i][j - 1]) life_counts_cell++;
                if (board[i - 1][j]) life_counts_cell++;
                if (board[i + 1][j - 1]) life_counts_cell++;
            }
            else if (i > 0 && i < frame_height - 1 && j == 0) {// Left borderline without corner blocks OK
                if (board[i + 1][j]) life_counts_cell++;
                if (board[i - 1][j]) life_counts_cell++;
                if (board[i][j + 1]) life_counts_cell++;
                if (board[i - 1][j + 1]) life_counts_cell++;
                if (board[i + 1][j + 1]) life_counts_cell++;
            }
            else if (i > 0 && i < frame_height - 1 && j == frame_width - 1) {// Right borderline without corner blocks ?
                if (board[i - 1][j]) life_counts_cell++;
                if (board[i + 1][j]) life_counts_cell++;
                if (board[i][j - 1]) life_counts_cell++;
                if (board[i + 1][j - 1]) life_counts_cell++;
                if (board[i - 1][j - 1]) life_counts_cell++;
            }
            else if (j > 0 && j < frame_width - 1 && i == 0) {// Upper borderline without corner blocks OK
                if (board[i + 1][j]) life_counts_cell++;
                if (board[i + 1][j - 1]) life_counts_cell++;
                if (board[i + 1][j + 1]) life_counts_cell++;
                if (board[i][j + 1]) life_counts_cell++;
                if (board[i][j - 1]) life_counts_cell++;
            }
            else if (j > 0 && j < frame_width - 1 && i == frame_height - 1) {// Bottom borderline without corner blocks ?
                if (board[i - 1][j]) life_counts_cell++;
                if (board[i - 1][j + 1]) life_counts_cell++;
                if (board[i - 1][j - 1]) life_counts_cell++;
                if (board[i][j + 1]) life_counts_cell++;
                if (board[i][j - 1]) life_counts_cell++;
                cout << board[i - 1][j] << endl;
                cout << board[i - 1][j + 1] << endl;
                cout << board[i - 1][j - 1] << endl;
                cout << board[i][j + 1] << endl;
                cout << board[i][j - 1] << endl;
            }

            cout << "i:"<< i << " j:" << j << endl;
            cout << "DEBUG Espressions" << endl;
            cout << (i > 0 && i < frame_height - 1 && j == 0) << endl;
            cout << (i > 0 && i < frame_height - 1 && j == frame_width - 1) << endl;
            if (life_counts_cell < 2 || life_counts_cell > 3) {
                n_board[i][j] = false;
            }
            else if (life_counts_cell == 3){
                n_board[i][j] = true;
            }
            life_counts_cell = 0;
        }
    }

    cout << "original" << endl;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j])
                cout << "■";
            else cout << "□";
        }
        cout << endl;
    }

    cout << "after first attempt" << endl;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (n_board[i][j])
                cout << "■";
            else cout << "□";
        }
        cout << endl;
    }
}
