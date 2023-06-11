#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

#define LAR 20
#define ALT 40

bool gameover;

void ShowConsoleCursor(bool showFlag);
void setCursorPosition(int x, int y);

int score;
int i, y, x, p;
int playerX, playerY;
int enemyX, enemyY;
int shotx, shoty;
int bufferplayer;

void Setup()
{
    gameover = false;
    score = 0;

    playerX = LAR / 2;
    playerY = ALT - 1;

    enemyX = LAR / 2;
    enemyY = 0;

    shotx = LAR / 2;
    shoty = ALT - 2;
    
    for (x=0;x<LAR+1;x++){
    	for(y=0;y<ALT+1;y++){
    		if(x == 0 || x == LAR){	
    		setCursorPosition(x, y);
    		printf("#");}
    		else if(y == 0 || y == ALT){
    		setCursorPosition(x, y);
    		printf("#");
    		}
    	}
    }
}

void Draw()
{
    
    setCursorPosition(playerX, playerY);
    printf("A");
    setCursorPosition(bufferplayer, playerY);
    printf(" ");
    setCursorPosition(0, 0);
    
    setCursorPosition(enemyX, enemyY);
    printf("V");
    setCursorPosition(enemyX, 0);
    printf("#");
    setCursorPosition(0, 0);
    setCursorPosition(enemyX, enemyY-1);
    printf(" ");
    setCursorPosition(0, 0);
    if (enemyY == ALT){
    	setCursorPosition(enemyX, enemyY);
    	printf("#");
    	setCursorPosition(0, 0);
    }
    
    setCursorPosition(shotx, shoty);
    printf("|");
    setCursorPosition(shotx, shoty+1);
    printf(" ");
    setCursorPosition(0,0);
    if (shoty == 0){
    setCursorPosition(shotx, shoty);
    	printf(" ");
    
    	if (shoty == 0){
	    	setCursorPosition(shotx, shoty);
	    	printf("#");
	    	setCursorPosition(0, 0);
    	}
    }
    
    if (shotx == enemyX && shoty-1 == enemyY+1){
    	setCursorPosition(shotx, shoty);
	    	printf("O");
	    	Sleep(20);
    	setCursorPosition(shotx, shoty);
	    	printf(" ");
	    setCursorPosition(0, 0);
    	setCursorPosition(enemyX, enemyY);
	    	printf("O");
	    	Sleep(10);
    	setCursorPosition(enemyX, enemyY);
	    	printf(" ");
	    setCursorPosition(0, 0);
	}	
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (playerX > 1) // Limita o movimento do jogador para não sair da borda
                playerX--;
                bufferplayer = playerX+1;
            break;
        case 'd':
            if (playerX < LAR) // Limita o movimento do jogador para não sair da borda
                playerX++;
                bufferplayer = playerX-1;
            break;
        case 'q':
            gameover = true;
            break;
        }
    }
}

void Logic()
{
    enemyY++;
    shoty--;
	Sleep(30);
    if (enemyY == playerY && enemyX == playerX)
        gameover = true;

    if (shotx == enemyX && shoty == enemyY)
    {
        score++;
        enemyX = rand() % (LAR - 2) + 1;
        enemyY = 0;
        shotx = playerX;
        shoty = ALT - 2;
    }

    if (shoty == -1)
    {
        shotx = playerX;
        shoty = ALT - 2;
    }

    if (enemyY > ALT)
    {
        enemyX = rand() % (LAR - 2) + 1;
        enemyY = 0;
    }
}

int main()
{
    Setup();

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    while (!gameover)
    {
        setCursorPosition(0, 0); // Posiciona o cursor no início da tela
        Draw();
        Input();
        Logic();
    }

    system("CLS");

    printf("\n \n \n \n \n \n \n \n \n \n \n \t SEU SCORE FOI: %d \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n/", score);

    Sleep(10);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void setCursorPosition(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
