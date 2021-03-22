#define frame_width 50
#define frame_height 20
#define ITERATE_TIME 100
#define DELAY_BETWEEN_ITERATION 30

#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;
using std::string;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coordScreen = { 0, 0 };    // home for the cursor

int main()
{
    /* initialize game board with bool[4][3] */
    /* you are able to control the input stage here before the input interface has been designed */
    system("cls");
    srand(time(0));
    bool board[frame_height][frame_width] = // input board
    
    {
        {0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
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
    bool n_board[frame_height][frame_width] = {0, 0};
    bool original_board[frame_height][frame_width];
    /*
    for (int i = 0; i < frame_height; i++) {
        for (int j = 0; j < frame_width; j++) {
            board[i][j] = original_board[i][j] = rand()%2;
        }
    }
    */
    for (int i = 0; i < frame_height; i++) {
        for (int j = 0; j < frame_width; j++) {
            original_board[i][j] = board[i][j];
        }
    }

    static int life_counts_cell = 0;
    static int iteration_times = 0;
    do {
        
        for (int i = 0; i <= frame_height - 1; i++) {
            for (int j = 0; j <= frame_width - 1; j++) {
                if (i > 0 && j > 0 && i < frame_height - 1 && j < frame_width - 1) { // when cursors are inside the grid board.
                    if (board[i - 1][j]) life_counts_cell++;
                    if (board[i - 1][j - 1]) life_counts_cell++;
                    if (board[i][j - 1]) life_counts_cell++;
                    if (board[i - 1][j + 1]) life_counts_cell++;
                    if (board[i + 1][j - 1]) life_counts_cell++;
                    if (board[i + 1][j]) life_counts_cell++;
                    if (board[i][j + 1]) life_counts_cell++;
                    if (board[i + 1][j + 1]) life_counts_cell++;
                }
                else if (i == 0 && j == 0) { // Left Upper Corner
                    if (board[i][j + 1]) life_counts_cell++;
                    if (board[i + 1][j]) life_counts_cell++;
                    if (board[i + 1][j + 1]) life_counts_cell++;
                }
                else if (i == frame_height - 1 && j == 0) { // Left Bottom Corner
                    if (board[i][j + 1]) life_counts_cell++;
                    if (board[i - 1][j]) life_counts_cell++;
                    if (board[i - 1][j + 1]) life_counts_cell++;
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
                }
                if (life_counts_cell < 2 || life_counts_cell > 3) {
                    n_board[i][j] = false;
                }
                else if (life_counts_cell == 3) {
                    n_board[i][j] = true;
                }
                life_counts_cell = 0;
            }
        }
        iteration_times++;
        cout << "\nITERATOR IS RUNNING..." << endl;
        for (int i = 0; i < frame_height; i++) {
            for (int j = 0; j < frame_width; j++) {
                board[i][j] = n_board[i][j];
            }
        }
        Sleep(DELAY_BETWEEN_ITERATION);
        //system("cls");

        // A better way to clean console without flashing
        
        SetConsoleCursorPosition(hConsole, coordScreen);

        cout << "-------------- " << iteration_times - 1 << " --------------" << endl;
        for (int i = 0; i < frame_height; i++) {
            for (int j = 0; j < frame_width; j++) {
                if (n_board[i][j])
                    cout << "■";
                else cout << "□";
            }
            cout << endl;
        }
        for (int i = 0; i < 2 * frame_width * iteration_times / ITERATE_TIME; i++) {
            cout << ">";
        }
    } while (!(iteration_times == ITERATE_TIME));
    cout << endl;

    system("cls");

    cout << "original array" << endl;

    for (int i = 0; i < frame_height; i++) {
        for (int j = 0; j < frame_width; j++) {
            if (original_board[i][j])
                cout << "■";
            else cout << "□";
        }
        cout << endl;
    }
    cout << "result " << iteration_times << endl;
    for (int i = 0; i < frame_height; i++) {
        for (int j = 0; j < frame_width; j++) {
            if (n_board[i][j])
                cout << "■";
            else cout << "□";
        }
        cout << endl;
    }

    cout << "Process has stopped after " << ITERATE_TIME << " time(s) of iterations" << endl;
    system("pause >nul");
    return 0;
}
