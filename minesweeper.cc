#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
// New libraries here
using namespace std;

// Multi-dimensional arrays defs
typedef vector<int> Row;
typedef vector<Row> Matrix;
typedef vector<string> Row_str;
typedef vector<Row_str> Matrix_str;

// PRE: -
// POST: Removes all previous console output
void clearConsole() {
    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Linux and MacOS
        system("clear");
    #endif
} 

void outputRules() {
    cout << endl;
    cout << "💣 😜 BENVINGUT AL CERCAMINES 😜 💣" << endl;
    cout << "_____________________________________" << endl;
    cout << endl;
    cout << "          😎 COM JUGAR 😎       " << endl; 
    cout << endl;
    cout << "💡 El joc del cercamines consisteix en destapar totes les caselles" << endl;
    cout << "   d'un tauler que no contenen una mina amagada a dins." << endl;
    cout << endl;
    cout << "💡 L'usuari ha d'introduir el codi alfanumèric en minúscules per" << endl;
    cout << "   destapar el seu contingut. Per exemple: a2, d7, g5..." << endl;
    cout << endl;
    cout << "💡 Si la casella no conté una mina, es descobrirà un nombre. Aquest" << endl;
    cout << "   nombre és el total de mines que hi ha a les caselles del voltant." << endl;
    cout << endl;
    cout << "⭕ Per exemple: si es destapa una casella i apareix un 2 vol dir que" << endl;
    cout << "   hi ha 2 mines entre les 8 caselles del voltant." << endl;
    cout << endl;
    cout << "🆗 Si vols començar, escriu \"ok\"" << endl;
}

// PRE: recieves a range of possible values
// POST: generates a random number within the range
int randNum(int min, int max) {
    return min + rand()%(max - min + 1);
    // The seed generation line: 
    // srand(static_cast<unsigned int>(time(nullptr)));
}

// PRE: -
// POST: returns a matrix with 10 mines (1 = mine, 0 = no mine)
Matrix generateMines(int dimension) {
    srand(static_cast<unsigned int>(time(nullptr)));
    Matrix mat(dimension, Row(dimension, 0));
    int numMines = 10;
    while (numMines > 0) {
        mat[randNum(0, (dimension - 1))][randNum(0, (dimension - 1))] = 1;
        --numMines;
    }
    return mat;
}

void printGrid(Matrix_str &mat, int dimension) {
    cout << endl;
    cout << "   1   2   3   4   5   6   7   8" << endl;
    // cout << "  ------------------------------" << endl;
    for (int i = 0; i < dimension; ++i) {
        cout << char(i + 65) << ' ';
        for (int j = 0; j < dimension; ++j) {
            cout << mat[i][j] << "  ";
        }
        cout << endl;
        // cout << "  ------------------------------" << endl;
    }
    cout << endl;
}

void uncoverGrid(Matrix_str &mat, Matrix &hiddenMines, string move, bool &gameOver) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int x = int(move[0] - 'a');
    int y = int(move[1] - '1');
    int count = 0;
    int cellsToUncover = randNum(8, 15);
    if (mat[x][y] == 1) gameOver = true;
    else {
        while (cellsToUncover > 0) {
        mat[x][y] = " " + to_string(countMinesCell(hiddenMines, x, y));
        printGrid(mat, move, type); //ALERTA
        --cellsToUncover;
        }   
    }
}

int main()
{
    // 1. Rules, game config. and start
    outputRules();
    string s;
    bool start = false;
    while (not start and cin >> s) if (s == "ok") start = true;
    int dimension = 8;
    Matrix_str grid(dimension, Row_str(dimension, "◽"));
    Matrix hiddenMines = generateMines(dimension);
    printGrid(grid, dimension);

    // 2. First to partially uncover the grid 
    bool gameOver = false;
    string move;
    cout << "Casella a seleccionar: ";
    cin >> move;
    uncoverGrid(grid, move);
    if (gameOver) cout << "Has perdut."
    else {

        // 3. Game in progress
        string m;
        while (not gameOver and cin >> m) {
                
        }
    }
}

// POSSIBLE GAME UPDATES
// 1. Difficulty levels (more grid sizes) 
// 2. Randomize the first grid uncover
// 3. Initialize a crhonometer when user starts playing
// 4. Create a new game based on minesweeper
// 5. Create a webApp for the game