#include <iostream> // acabei usando printf nas coisas por que dizem que é mais rápido kk
#include <windows.h>
#include <conio.h>  //kbhit

#define screenWidth 20
#define screenHeight 14

#define KEY_UP 80
#define KEY_DOWN 72
#define KEY_RIGHT 77
#define KEY_LEFT 75

using namespace std;

int i, f;

void ShowConsoleCursor(bool showFlag);
void setCursorPosition(int x, int y);

class game {
    //Frame atual e frame buffer
    char frameAtual[screenWidth][screenWidth], buffer[screenWidth][screenWidth];
    char Player, screen;
    int plX, plY;
        
    public:
        //Inicia a posição do player na tela e seta os dois frames como vazio
        void Init() {
            Player = 'A';
            screen = '#';
            plX = 7; plY = -10;
            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    frameAtual[x][y] = buffer[x][y] = ' ';
                }
            }
            }
            frameAtual[plX][plY] = Player;
            
        }   
        void MainL() {
            bool loop = true;
            DrawAll();
            while (loop == true) {
                UpdateBuffer();
                Move();
                SelDraw();
            }
        }
    private:
        //função bem simples para registrar o movimento
        void Move() {
            char keyPressed;
            if (kbhit()) {
                keyPressed = getch();

                switch(keyPressed){ //esse switch analisa qual tecla foi digitada
                    case KEY_UP: // Seta para cima
                        frameAtual[plX][plY] = ' ';
                        plY += 1;
                        frameAtual[plX][plY] = Player;
                    break;
                        
                    case KEY_DOWN: // Seta para baixo
                        frameAtual[plX][plY] = ' ';
                        plY -= 1;
                        frameAtual[plX][plY] = Player;
                    break;
                    
                    case KEY_RIGHT: // Seta para direita
                        frameAtual[plX][plY] = ' ';
                        plX += 1;
                        frameAtual[plX][plY] = Player;
                    break;
                    
                    case KEY_LEFT: // Seta para esquerda
                        frameAtual[plX][plY] = ' ';
                        plX -= 1;
                        frameAtual[plX][plY] = Player;
                    break;
                }
            }
        }
        
        //primeira função de criar a tela vazia
        void DrawAll() {
            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    printf("%c", frameAtual[x][y]);
                }
                printf("\n");
            }
        }
        //Atualização de frame seletivo - Checa as diferenças no buffer e no frame atual e corrige elas
        void SelDraw() {
            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    if (frameAtual[x][y] != buffer[x][y]) {
                        setCursorPosition(x,y); printf("%c", frameAtual[x][y]);
                    }
                }
            }
        }
        
        //Atualizar o buffer setando oq está no frame mais recente nele
        void UpdateBuffer() {
            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    buffer[x][y] = frameAtual[x][y];
                }
            }
        }
};

int main() {
    
    ShowConsoleCursor(false);
    
    game g;
    g.Init();
    g.MainL();
    return 0;
}
//Tirar o cursor da tela (opcional)
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
//Pode ser um gotoxy ou qualquer outra função para manipular a posição do cursor 
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}