
#include <iostream>

#include <ctime>

#include <cstdlib>

#include <windows.h>

using namespace std;

const int BOARD_SIZE = 10;
const int num_ships = 5;

char playerBoard[BOARD_SIZE][BOARD_SIZE]; 
char computerBoard[BOARD_SIZE][BOARD_SIZE];  
char playerShots[BOARD_SIZE][BOARD_SIZE];   
char computerShots[BOARD_SIZE][BOARD_SIZE]; 


void initializeBoards() {
    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            playerBoard[i][j] = ' ';
            computerBoard[i][j] = ' ';
            playerShots[i][j] = ' ';
            computerShots[i][j] = ' ';
        }
    }
}


void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) 
{
    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        for (int j = 0; j < BOARD_SIZE; ++j) 
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

void placeShips(char board[BOARD_SIZE][BOARD_SIZE]) 
{

    int shipSizes[num_ships] = { 1, 1, 1, 1, 1 };

    for (int i = 0; i < num_ships; ++i) {
        
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;

        
        while (board[x][y] != ' ') {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        }

        
        board[x][y] = 'S';  
    }
}

void playerShot(char computerBoard[BOARD_SIZE][BOARD_SIZE], char playerShots[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;

    cout << "Введите координаты для стрельбы(строчку, колону по типу 0 0) ";
    cin >> x >> y;

    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        cout << "НЕПРАВИЛЬНЫЕ КООРДИНАТЫ\n";
        return;
    }

    if (playerShots[x][y] != ' ') {
        cout << "Вы уже стреляли в это место! Попробуйте еще\n";
        return;
    }

    playerShots[x][y] = 'X';  

    if (computerBoard[x][y] == 'H') 
    {
        cout << "ПОПАЛ!\n";
        computerBoard[x][y] = 'H';  
    }
    else {
        cout << "Целься лучше:)!\n";
    }
}

void computerShot(char playerBoard[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;

    
    x = rand() % BOARD_SIZE;
    y = rand() % BOARD_SIZE;

    
    while (playerBoard[x][y] != ' ') {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    }

    
    if (playerBoard[x][y] == 'H') {
        cout << "Бот стрельнул в координаты (" << x << ", " << y << ")!\n";
        playerBoard[x][y] = 'H';  
    }
    else {
        cout << "Бот промохнулся по координатам (" << x << ", " << y << ").\n";
        playerBoard[x][y] = 'M';  
    }
}


bool areAllShipsSunk(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 'S') {
                return false;  
            }
        }
    }
    return true;  
}


int main()
{
    setlocale(LC_ALL, "rus");
    system("color 0d");

    initializeBoards();
    
    cout << "---------------------------------\n";
    cout << "| Добро пожаловать в игру 'Морской бой'! |\n";
    cout << "|          Удачи в битве!         |\n";
    cout << "---------------------------------\n\n";



    // Размещение кораблей на доске игрока и компьютера
    placeShips(playerBoard);
    placeShips(computerBoard);

    cout << "Игра началась!\n\n";

    while (true) {
        cout << "-------------------------\n";
        cout << "|   Ход игрока   |\n";
        cout << "-------------------------\n";
        cout << "Ваша доска:\n";
        displayBoard(playerShots);
        cout << "\n";
        playerShot(computerBoard, playerShots);
        if (areAllShipsSunk(computerBoard)) {
            cout << "\n-------------------------\n";
            cout << "|   Поздравляем! Вы победили!   |\n";
            cout << "-------------------------\n";
            break;
        }

        cout << "---------------------------\n";
        cout << "|   Ход компьютера   |\n";
        cout << "---------------------------\n";
        cout << "Доска компьютера:\n";
        computerShot(playerBoard);
        displayBoard(playerBoard);
        cout << "\n";
        if (areAllShipsSunk(playerBoard)) {
            cout << "\n----------------------------\n";
            cout << "|   Компьютер победил.   |\n";
            cout << "----------------------------\n";
            break;
        }
    }

    return 0;

}


