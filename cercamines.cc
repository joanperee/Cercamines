#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// PRE: -
// POST: Removes all previous console output
void clearConsole() {
    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Linux and MacOS
        system("clear");
    #endif
} 

void outputRules() 
{
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

typedef vector<string> Row;
typedef vector<Row> Matrix_s;
typedef vector<vector<int>> Matrix_int;

// PRE: recieves a range of possible values
// POST: generates a random number within the range
int randNum(int min, int max) {
    return min + rand()%(max - min + 1);
}

// PRE: -
// POST: creates the matrix with 10 random allocated mines
Matrix_int minesMatrix() {
    Matrix_int mines(8, vector<int>(8, 0));
    srand(static_cast<unsigned int>(time(nullptr)));
    int numMines = 10;
    int min = 0; 
    int max = 7;
    while (numMines > 0) {
        mines[randNum(min, max)][randNum(min, max)] = 1;
        --numMines;
    }
    return mines;
}

void firstUncoverGrid(Matrix_s& mat, Matrix_int mines, string move, bool& gameOver) {
    int a = int(move[0] - 'a');
    int b = int(move[1] - '1');
    int count = 0;
    int cellsToUncover = 10;
    if (mat[a][b] == 1) gameOver = true;
    else {
        while (cellsToUncover > 0) {
        mat[a][b] = " " + to_string(countMinesCell(mines, a, b));
        printGrid(mat, move, type);
        --cellsToUncover;
        }   
    }
}

int countMinesCell(Matrix_int mines, int a, int b) {
    int count = 0;
    if (mines[a][b] == 1) count = count + 10; // If count = 10 then is mine
    else {
        // Case 1: middle cells
        if ((a > 0 and b > 0) and (a < 7 and b < 7)) {
            if (mines[a - 1][b - 1] == 1) ++count;
            if (mines[a - 1][b] == 1) ++count;
            if (mines[a - 1][b + 1] == 1) ++count;
            if (mines[a][b - 1] == 1) ++count;
            if (mines[a][b + 1] == 1) ++count;
            if (mines[a + 1][b - 1] == 1) ++count;
            if (mines[a + 1][b] == 1) ++count;
            if (mines[a + 1][b + 1] == 1) ++count;
        }

        // Case 2: upper border cells
        else if (a == 0 and b > 0 and b < 7) {
            if (mines[a][b - 1] == 1) ++count;
            if (mines[a][b + 1] == 1) ++count;
            if (mines[a - 1][b - 1] == 1) ++count;
            if (mines[a - 1][b] == 1) ++count;
            if (mines[a - 1][b + 1] == 1) ++count;
        }

        // Case 3: left border cells
        else if (b == 0 and a > 0 and a < 7) {
            if (mines[a - 1][b] == 1) ++count;
            if (mines[a - 1][b + 1] == 1) ++count;
            if (mines[a][b + 1] == 1) ++count;
            if (mines[a + 1][b + 1] == 1) ++count;
            if (mines[a + 1][b]) ++count;
        }

        // Case 4: lower border cells
        else if (a == 7 and b > 0 and b < 7) {
            if (mines[a][b - 1] == 1) ++count;
            if (mines[a - 1][b - 1] == 1) ++count;
            if (mines[a - 1][b] == 1) ++count;
            if (mines[a - 1][b + 1] == 1) ++count;
            if (mines[a][b + 1] == 1) ++count;
        }

        // Case 5: right border cells
        else if (b == 7 and a > 0 and a < 7) {
            if (mines[a - 1][b] == 1) ++count;
            if (mines[a - 1][b - 1] == 1) ++count;
            if (mines[a][b - 1] == 1) ++count;
            if (mines[a + 1][b - 1] == 1) ++count;
            if (mines[a + 1][b] == 1) ++count;
        }

        // Case 6: corner cells
        else {
            if (mines[a + 1][b] == 1) ++count;
            if (mines[a + 1][b + 1] == 1) ++count;
            if (mines[a][b + 1] == 1) ++count;
        }
    }
    return count;
}

// PRE: -
// POST: Prints a 10x10 grid with cells. Labels for rows and columns. 
void printGrid(Matrix_s& mat, string move, int type) {
    if (move != "blank") {
        int a = int(move[0] - 'a');
        int b = int(move[1] - '1');
        if (type == 1) mat[a][b] = uncoverMine(minesMatrix(), a, b);
        else mat[a][b] = " 🚩";
    }
    cout << endl;
    cout << "   1   2   3   4   5   6   7   8" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << char(i + 65) << ' ';
        for (int j = 0; j < 8; ++j) {
            cout << mat[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // 1. Rules and start
    outputRules();
    string s;
    bool start = false;
    while (not start and cin >> s) {
        if (s == "ok") start = true;
    }

    // 2. Game in progress
    Matrix_s mat(8, Row(8, "◽")); // For output
    Matrix_int mines = minesMatrix(); // Storing all the mines
    string move1; 
    string move = "blank"; 
    int type = 0; 
    bool gameOver = false;
    if (start) {
        
        clearConsole(); 
        // Crhonometre starts here
        printGrid(mat, move, type); 
        cout << "Casella a seleccionar: ";
        cin >> move1;
        firstUncoverGrid(mat, mines, move1); 
        
        // Following implementation under construction/debugging
        while (not gameOver) {
            cout << "(1) Destapar casella       (2) Marcar mina" << endl;
            cout << "Selecciona la opció d'entrada: ";
            cout << endl;
            cin >> type;
            cout << "Casella a seleccionar: ";
            cin >> move;
            clearConsole();
            printGrid(mat, move, type);
        }
    }

    // 3. Lost/Won end game outputs
    if (gameOver) {
        // Possible enhancement: make a function to discover where were all the mines left
        cout << "YOU LOST :(" << endl;
        clearConsole();
    }
    else {
        cout << "YOU WON :)" << endl;
        clearConsole();
    }

}