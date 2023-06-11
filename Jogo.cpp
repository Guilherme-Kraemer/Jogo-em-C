#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
// stdio.h para scanf e printf
//stdbool.h para uso de false e true como 0 e 1
// stdlib.h para uso da funcoes system
// windows.h para uso dos algumas funcionalidades do windows
// conio.h para usar a funcao getch, qual nao apresenta o caracter na  tela
#define WIDTH 80
#define HEIGHT 24
//definindo os limites do display

bool gameover;
int score;

int playerX, playerY;
int enemyX, enemyY;
//definindo as variaveis

void Setup()
{
    gameover = false;
    score = 0;

    playerX = WIDTH / 2;
    playerY = HEIGHT - 1;

    enemyX = WIDTH / 2;
    enemyY = 0;
}
//configuracao inicial do jogo, score e local inicial dos bonecos, nao sera mais usada no jogo

void Draw()
{
    system("CLS");

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x <= WIDTH+2; x++)
        {
            if (x == 0 || x == WIDTH+1)
                printf("#");
            else if (x == playerX && y == playerY)
                printf("A");
            else if (x == enemyX && y == enemyY)
                printf("V");
            else 
                printf(" ");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}
//funcao para fazer o desenho e movimentacoes na tela usando as variaveis da funcao input e logic e manipulando as da setup

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                playerX--;
                break;
            case 'd':
                playerX++;
                break;
            case 'q':
                gameover = true;
                break;
        }
    }
}
//funcao especifica para os dados recebidos do teclado, variaveis que vao ser usadas nas funcoes logic e draw
void Logic()
{
    enemyY++;

    if (enemyY == playerY && enemyX == playerX)
        gameover = true;

    if (enemyY >= HEIGHT)
    {
        score++;
        enemyX = rand() % (WIDTH - 2) + 1;
        enemyY = 0;
    }
}
//logica do aumento do score e de fim do jogo, com contato no player para fim de jogo e chegada no fim do display para aumento do score

int main()
{
    Setup();

    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        Sleep(1);
    }

    return 0;
}
//uso das funcoes em uma ordem logica, configurando as variaveis com Setup, laco de repeticao para manter o jogo rodando ate que na funcao logic gameover=truen
