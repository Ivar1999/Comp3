#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h>
#include <fstream>
#define numrows 6
#define numcolumns 6

struct Login {

    char grid[4][4];
    char password[20]{};
    std::string thisfilepath;
    Login(std::string filepath) {
        int A = 65;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                grid[i][j] = A++;
            }
        }

        std::ifstream PWFile;
        PWFile.open(filepath.c_str());
        thisfilepath = filepath;
        PWFile >> password;
        PWFile.close();
    }
    ~Login() {
        std::ofstream OS;
        OS.open(thisfilepath.c_str());
        OS.write(password, strlen(password));
        OS.close();
    }
    void printGrid(){ // edit
        for (int i = 0; i < 4; i++)
        {
            std::cout << "| ";
            for (int j = 0; j < 4; j++)
            {
                std::cout << grid[i][j] << " | ";
            }
            std::cout << std::endl;
            std::cout << "-----------------" << std::endl;
        }

    }
    std::string getpassword() {

        int letters = 1;
        int Px = 0;
        int Py = 0;
        std::string attempt;
        attempt.push_back(grid[Px][Py]);
        grid[Px][Py] = '*';
        printGrid();
        std::cout << attempt;
        do
        {
        int key = _getch();
        key = tolower(key);
            switch (key)
            {
            case 'w':
                if (Px > 0)
                {
                    Px--;
                }
                else continue;
                letters++;
                break;
            case 'a':
                if (Py > 0)
                {
                    Py--;
                }
                else continue;
                letters++;
                break;
            case 's':
                if (Px + 1 < 4)
                {
                    Px++;
                }
                else continue;
                letters++;
                break;
            case 'd':
                if (Py + 1 < 4)
                {
                    Py++;
                }
                else continue;
                letters++;
                break;
            default:
                break;
            }
            attempt.push_back(grid[Px][Py]);
            grid[Px][Py] = '*';
            system("cls");
            printGrid();
            std::cout << attempt << std::endl;
        } while (letters < strlen(password));
        makegrid();
        return attempt;

    }
    bool checkpassword(std::string attempt) {

        if (attempt.size() != strlen(password))
        {
            return false;
        }
        for (int i = 0; i < 4; i++)
        {

            if (attempt.at(i) != password[i])
            {
                return false;
            }

        }
        return true;

    }
    bool run() {
        return checkpassword(getpassword());
    }
    void changepassword() {
        std::string newpas = getpassword();
        memset(password, 0, 20);
        memcpy(password, newpas.c_str(), newpas.length());
    }
    void makegrid() {
        int A = 65;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                grid[i][j] = A++;
            }
        }
    }
};

void play();
struct Player
{
    char board[numrows][numcolumns];
    char invisibleboard[numrows][numcolumns];
    virtual void shoot() {

        std::string ShotSelect;


            std::cin >> ShotSelect;
            if (ShotSelect.length() == 2)
            {
                if (ShotSelect[0] >= 'A' && ShotSelect[0] <= 'F')
                {
                    ShotSelect[1] -= 48;
                    if (ShotSelect[1] >= 1 && ShotSelect[1] <= 6)
                    {
                        int x = ShotSelect[0] - 65;
                        int y = numrows - ShotSelect[1];
                        if (board[y][x] == 'M' || board[y][x] == 'H')
                        {
                            std::cout << "Cell has already been selected before, you lost a shot." << std::endl;
                        }
                        if (board[y][x] == 'S')
                        {
                            std::cout << "You Hit a enemy ship" << std::endl; // edit
                            board[y][x] = 'H';
                            invisibleboard[y][x] = 'H';
                        }
                        else if (board[y][x] == ' ')
                        {
                            std::cout << "You Miss" << std::endl; // edit
                            board[y][x] = 'M';
                            invisibleboard[y][x] = 'M';
                        }

                    }
                }

            }

    }

    void makeEmptyBoard() {
        for (int i = 0; i < numrows; i++)
        {
            for (int j = 0; j < numcolumns; j++)
            {
                board[i][j] = ' ';
                invisibleboard[i][j] = ' ';
            }
        }
    }
    int randomRow() {
        return std::rand() % numrows;
    }
    int randomColumn() {
        return std::rand() % numcolumns;
    }
    void writeLetters() {
        int startvalue = 65;
        std::cout << " ";
        for (int i = 0; i < numcolumns; i++)
        {
            std::cout << (char)startvalue++ << " ";
        }
        std::cout << std::endl;
    }
    void makeBoard(int numberOfShips) {
        int currentships = 0;
        while (currentships < numberOfShips)
        {
            int x = randomColumn();
            int y = randomRow();
            if (board[y][x] == ' ')
            {
                board[y][x] = 'S';
                currentships++;
            }

        }

    }
    void printBoard() {
        //system("cls");
        int sidenumber = numrows;
        for (int i = 0; i < numrows; i++)
        {
            std::cout << sidenumber--;
            for (int j = 0; j < numcolumns; j++)
            {
                std::cout << "|" << board[i][j];
            }
            std::cout << "|" << std::endl;
        }
        std::cout << " -------------" << std::endl;
        writeLetters();
    }
    void printinvisibleBoard() {
       // system("cls");
        int sidenumber = numrows;
        for (int i = 0; i < numrows; i++)
        {
            std::cout << sidenumber--;
            for (int j = 0; j < numcolumns; j++)
            {
                std::cout << "|" << invisibleboard[i][j];
            }
            std::cout << "|" << std::endl;
        }
        std::cout << " -------------" << std::endl;
        writeLetters();
    }
    void makeBoard3(int numberOfShips) {

        int currentships = 0;
        while (currentships < numberOfShips)
        {
            int x = randomColumn();
            int y = randomRow();
            if (board[y][x] == ' '&& y+2 < 6 && board[y+1][x] == ' ' && board[y+2][x] == ' ')
            {
                board[y][x] = 'S';
                board[y + 1][x] = 'S';
                board[y + 2][x] = 'S';
                currentships++;
            }
            if (y+2 > 6 && board[y][x] == ' ' && x + 2 < 6 && board[y][x+1] == ' ' && board[y][x+2] == ' ')
            {
                board[y][x] = 'S';
                board[y][x+1] = 'S';
                board[y][x+2] = 'S';
                currentships++;
            }

        }

    }
    int boardcount() {
        int shipsleft = 0;
        for (int i = 0; i < numrows; i++)
        {
            for (int j = 0; j < numcolumns; j++)
            {
                if (board[i][j] == 'S')
                {
                    shipsleft++;
                }

            }
        }
        return shipsleft;
    }
};
struct Enemy :public Player
{
    void shoot() override {
    Test:

        int x = randomColumn();
        int y = randomRow();
 
        
        if (board[y][x] == 'M')
        {
            int x = randomColumn();
            int y = randomRow();
            std::cout << x << "," << y;
            goto Test;
        }
        if (board[y][x] == 'H')
        {
            int x = randomColumn();
            int y = randomRow();
            std::cout << x << "," << y;
            goto Test;
        }


        if (board[y][x] == 'S')
        {
            std::cout << "Enemy Hit your ship." << std::endl; // edit
            board[y][x] = 'H';
            invisibleboard[y][x] = 'H';
        }
        else if (board[y][x] == ' ')
        {
            std::cout << "Enemy Miss" << std::endl; // edit
            board[y][x] = 'M';
            invisibleboard[y][x] = 'M';
        }

    }

};

void play() {
    int ships = 3;
    Player player;
    Enemy aiplayer;
    //YOUR BOARD
    aiplayer.makeEmptyBoard();
    aiplayer.makeBoard3(ships); //can be swapped to makeBoard(ships)
    //aiplayer.printBoard();
    //system("pause");
    //ENEMY BOARD
    player.makeEmptyBoard();
    player.makeBoard3(ships); //can be swapped to makeBoard(ships)
    //player.printBoard();
    //player.printinvisibleBoard();
    //player.shoot(); // ai player shoots while player shoots
    int playerships = 9;
    int aiships = 9;
    do
    {
        system("cls");
        std::cout << "Your board:" << std::endl;
        aiplayer.printBoard();
        std::cout << "You have >" << playerships << "< Ships left." << std::endl;
        std::cout << "\n\nEnemy board:" << std::endl;
        player.printinvisibleBoard();
        std::cout << "Enemy have >" << aiships << "< Ships left." << std::endl;
        std::cout << "\nMake your shot, for example: B3" << std::endl;
        player.shoot();
        aiplayer.shoot();

        aiships = player.boardcount();
        playerships = aiplayer.boardcount();
    } while (playerships > 0 && aiships > 0);

    system("cls");
    std::cout << "Your board:" << std::endl;
    aiplayer.printBoard();
    std::cout << "\n\nEnemy board:" << std::endl;
    player.printBoard();

    if (playerships > aiships)
    {
        std::cout << "\n\nEnemy has 0 more ships left. You won!" << std::endl;
    }
    else if (playerships == aiships)
    {
        std::cout << "\n\nYou both have 0 ships left. It's a draw." << std::endl;
    }
    else if (playerships < aiships)
    {
        std::cout << "\n\The enemy has destoyed your ships.\nYou has 0 more ships left. You lost." << std::endl;
    }


    system("pause");
    //aiplayer.shoot();
    //player.makeBoard3(ships);
    //aiplayer.makeBoard3(ships);
}

int main()
{

    Login login("PasswordFile.txt");
    if (login.run())
    {
        int option = 0;
        do
        {
            system("cls");
            std::cout << "Correct password. Welcome user." << std::endl;
            std::cout << "\n\n1:Change the password" << std::endl;
            std::cout << "2:Play battleship" << std::endl;
            std::cout << "3:Quit Program" << std::endl;

            std::cin >> option;
            switch (option)
            {
            case 1:
                login.changepassword();
                break;
            case 2:
                srand(time(NULL));
                play();
                break;
            default:
                break;
            }

        } while (option != 3);
        std::cout << "\nProgram will now close, Good Bye!" << std::endl;


    }
    else
    {
        std::cout << "Wrong password. Program is now closing." << std::endl;
    }


    return 0;
}
