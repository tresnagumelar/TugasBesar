#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
#include <conio.h>
#include <time.h>


using namespace std;

const int key_kiri = 'a', key_kanan = 'd', key_atas = 'w', key_bawah = 's'; //tombol untuk menggerakan player
const int tinggi=25 , lebar=40; //ukuran papan maze
bool kalah = true; //inisialisasi permainan belum dimenangkan (kalah = true)
int Hp=100; //inisialisasi Nyawa player
int Point=0;

enum DirectionX {Right, Left}; //arah pergerakan di bidang X
enum DirectionY {Up, Down}; //arah pergerakan di bidang Y

struct Pemain{
    char sprite;
    int x;
    int y;
};

struct Musuh{
    char sprite;
    int x;
    int y;
    DirectionX pastDirX;
    DirectionY pastDirY;
};


unsigned char MoveMusuh(Musuh& musuh, unsigned char maze[tinggi][lebar], int i, int j, string& smove, bool& nc){
    if(nc){
        bool goUp = false;
        //memungkinkan arah pergerakan ke atas, bawah, samping kanan dan kiri
        //psb = kemungkinan pergerakan
        bool psbUp = false;  
        bool psbDown = false;
        bool psbRight = false;
        bool psbLeft = false;

        //pergerakan musuh 
        if(maze[musuh.y][musuh.x+1] != '#'){//Kanan
            psbRight = true;
        }
        if(maze[musuh.y][musuh.x-1] != '#'){//Kiri
            psbLeft = true;
        }
        if(maze[musuh.y+1][musuh.x] != '#'){//Bawah
            psbDown = true;
        }
        if(maze[musuh.y-1][musuh.x] != '#'){//Atas
            psbUp = true;
        }

        //jalur perpindahan
        enum Mv {up, right, down, left, NA};
        Mv move = NA;

        //perpindahan sebelumnya
        if(smove == "up"){
            move = up;
        }
        else if(smove == "right"){
            move = right;
        }
        else if(smove == "down"){
            move = down;
        }
        else if(smove == "left"){
            move = left;
        }
        else{
            move = NA;
        }

        if(musuh.pastDirX == Right && !psbRight){
            if(musuh.pastDirY == Up){
                if(psbUp){
                    move = up;
                }
                else if(psbDown && move != up){
                    move = down;
                }
                else if(psbLeft){
                    move = left;
                }
                else{
                    move = down;
                }
            }
            else{
                if(psbDown){
                    move = down;
                }
                else if(psbUp && move != down){
                    move = up;
                }
                else if(psbLeft){
                    move = left;
                }
                else{
                    move = up;
                }
            }
        }
        else if(musuh.pastDirX == Right && psbRight){
            move = right;
        }
        else if(musuh.pastDirX == Left && !psbLeft){
            if(musuh.pastDirY == Up){
                if(psbUp){
                    move = up;
                }
                else if(psbDown && move != up){
                    move = down;
                }
                else if(psbRight){
                    move = right;
                }
                else{
                    move = down;
                }
            }
            else{
                if(psbDown){
                    move = down;
                }
                else if(psbUp && move != down){
                    move = up;
                }
                else if(psbRight){
                    move = right;
                }
                else{
                    move = up;
                }
            }
        }
        else if(musuh.pastDirX == Left && psbLeft){
            move = left;
        }
        else if(musuh.pastDirY == Up && !psbUp){
            if(musuh.pastDirX == Right){
                if(psbRight){
                    move = right;
                }
                else if(psbLeft && move != right){
                    move = left;
                }
                else if(psbDown){
                    move = down;
                }
                else{
                    move = left;
                }
            }
            else{
                if(psbLeft){
                    move = left;
                }
                else if(psbRight && move != left){
                    move = right;
                }
                else if(psbDown){
                    move = down;
                }
                else{
                    move = right;
                }
            }
        }
        else if(musuh.pastDirY == Up && psbUp){
            move = up;
        }
        else if(musuh.pastDirY == Down && !psbDown){
            if(musuh.pastDirX == Right){
                if(psbRight){
                    move = right;
                }
                else if(psbLeft && move != right){
                    move = left;
                }
                else if(psbUp){
                    move = up;
                }
                else{
                    move = left;
                }
            }
            else{
                if(psbLeft){
                    move = left;
                }
                else if(psbRight && move != left){
                    move = right;
                }
                else if(psbRight){
                    move = up;
                }
                else{
                    move = right;
                }
            }
        }
        else if(musuh.pastDirY == Down && psbDown){
            move = down;
        }

        
        switch(move){
            case up:
                maze[musuh.y][musuh.x] = ' ';
                musuh.pastDirY = Up;
                smove = "up";
                musuh.y--;
                break;
            case right:
                maze[musuh.y][musuh.x] = ' ';
                musuh.pastDirX = Right;
                smove = "right";
                musuh.x++;
                break;
            case down:
                maze[musuh.y][musuh.x] = ' ';
                musuh.pastDirY = Down;
                smove = "down";
                musuh.y++;
                break;
            case left:
                maze[musuh.y][musuh.x] = ' ';
                musuh.pastDirX = Left;
                smove = "left";
                musuh.x--;
                break;
            case NA:
                smove = "NA";
                break;
        }
    }
    nc = false;
    return maze[i][j];
}




int main()
{
     unsigned char maze[tinggi][lebar] = {
    '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
    ' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',
    '#','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#',' ','#',
    '#',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ','#',
    '#',' ','#','#',' ','#','#','#',' ','#',' ','#',' ','#',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#',
    '#',' ','#',' ',' ','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ','#',
    '#',' ','#',' ','#','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#',' ','#',
    '#',' ','#',' ','#',' ',' ','#',' ','#','#','#','#',' ','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ','#',' ','#','#',' ','#',' ','#',' ',' ',' ',' ','#',' ',' ',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#',' ','#','#',' ','#',' ','#','#',
    '#',' ','#',' ',' ',' ',' ','#',' ','#','#','#','#',' ','#','#','#','#','#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#','#',' ',' ','#',' ','#',' ',' ','#',
    '#',' ','#','#','#','#',' ','#',' ',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ','#',' ','#','#','#','#','#',' ','#',
    '#',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#','#',' ',' ',' ','#',' ','#',' ','#',
    '#',' ','#','#',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',
    '#',' ','#',' ',' ','#',' ','#',' ','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',
    '#',' ','#',' ','#','#',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',
    '#',' ','#',' ','#',' ',' ','#',' ','#','#','#','#','#','#',' ','#',' ','#','#',' ','#','#','#','#','#','#','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',
    '#',' ','#',' ','#',' ','#','#',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#',
    '#',' ','#',' ','#',' ',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',
    '#',' ','#','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',
    '#',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',
    '#',' ','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ',' ',' ','#',' ','#','#','#',' ','#',
    '#',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#','#','#',' ','#',' ','#',' ','#',' ','#',
    '#',' ','#','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#',
    '#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',
    '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
    };

    Pemain player;
    player.sprite = '@';
    player.x = 0;
    player.y = 1;

    Musuh musuh1;
    musuh1.sprite = '<';
    musuh1.x = rand()%lebar;
    musuh1.y = rand()%tinggi;
    musuh1.pastDirX = Left;
    musuh1.pastDirY = Up;

    system("PAUSE");
    return EXIT_SUCCESS;
}
