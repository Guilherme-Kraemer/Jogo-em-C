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

//definindo os limites do display
#define LAR 20
#define ALT 14

// definindo como uma variavel logica
bool gameover;
int score;
int i, y, x, p;

//definindo as variaveis
int playerX, playerY;
int enemyX, enemyY;
int shotx, shoty;

//configuracao inicial do jogo, score e local inicial, nao sera mais usada apos esta parte
void Setup()
{
    gameover = false;
    score = 0;

    playerX = LAR / 2;
    playerY = ALT - 1;

    enemyX = LAR / 2;
    enemyY = 0;
}

//funcao para fazer o desenho e movimentacoes na tela usando as variaveis da funcao input e logic e manipulando as da setup
void Draw()
{
    system("CLS");

	//desenhando da borda superior
    for (i = 0; i < LAR + 2; i++)
        printf("#");
    printf("\n");

    for (y = 0; y < ALT; y++)
    {
        for (x = 0; x <= LAR+2; x++)
        {
            if (x == 0 || x == LAR+1)//desenho da borda direita e esquerda
                printf("#");
            else if (x == playerX && y == playerY)
                printf("A");
            else if (x == shotx && y == shoty)
            	printf("|");
            else if (x == enemyX && y == enemyY)//desenho dos personagens
                printf("V");
            
            else 
                printf(" ");//o espaco em branco(sem isso nao funcionou)
        }
        printf("\n");
    }
    
    //desenho da borda inferior
    for (i = 0; i < LAR + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

//funcao especifica para os dados recebidos do teclado, variaveis que vao ser usadas nas funcoes logic e draw
void Input()
{
    if (_kbhit()) //funcao para detectar se houve tecla pressionada
    {
        switch (_getch())//switch para substituir varios if...else e _getch para captar esta tecla
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

//logica do aumento do score e de fim do jogo, com contato no player para fim de jogo e chegada no fim do display para aumento do score
void Logic()
{
    enemyY++;//movimentacoo do inimigo
    shoty--;//movimentacao do tiro

    //caso o jogador encoste no inimigo, acaba o jogo
    if (enemyY == playerY && enemyX == playerX)
        gameover = true;
    
    //caso o tiro encoste no inimigo score+1 e ele retorna para o inicio do display    
    if (shotx == enemyX && shoty == enemyY){
    	score++;
        enemyX = rand() % (LAR - 2) + 1;
        enemyY = 0;
        shotx = playerX;
    	shoty = ALT-2;
    }
    
    //caso o tiro encoste na parte superior do display, o jogador atira novamente
    if (shoty == -1){
    	shotx = playerX;
    	shoty = ALT-2;
    }
    
    //caso o inimigo chege ao final do display volta num lugar aleatorio
    if (enemyY >= ALT)
    {
        enemyX = rand() % (LAR - 2) + 1;
        enemyY = 0;
    }
    //caso o inimigo chege ao final do display volta num lugar aleatorio
}

//uso das funcoes em uma ordem logica, configurando as variaveis com Setup, laco de repeticao para manter o jogo rodando
int main()
{
    Setup(); //funcao fora do loop para os valores iniciais nao ficarem alterando as variaveis durante o jogo
    
    

    while (!gameover) //enquanto a variavel logica for verdadeira, sai do loop, usou while para que o codigo rode pelo menos uma vez
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    
    system("CLS");
    
    printf("\n \n \n \n \n \n \n \n \n \n \n \t SEU SCORE FOI: %d \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n/", score);
    
    Sleep(10);
}

