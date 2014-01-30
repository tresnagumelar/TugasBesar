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


// lanjut program utama nya 


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
    
        while(maze[musuh1.y][musuh1.x] != ' '){
        musuh1.x = rand()%lebar;
        musuh1.y = rand()%tinggi;
    }
    if(maze[musuh1.y][musuh1.x] == ' '){
        maze[musuh1.y][musuh1.x] = musuh1.sprite;
    }

    Musuh musuh2;
    musuh2.sprite = '<';
    musuh2.x = rand()%lebar;
    musuh2.y = rand()%tinggi;
    musuh2.pastDirX = Left;
    musuh2.pastDirY = Up;

    while(maze[musuh2.y][musuh2.x] != ' '){
        musuh2.x = rand()%lebar;
        musuh2.y = rand()%tinggi;
    }
    if(maze[musuh2.y][musuh2.x] == ' '){
        maze[musuh2.y][musuh2.x] = musuh2.sprite;
    }

    Musuh musuh3;
    musuh3.sprite = '<';
    musuh3.x = rand()%lebar;
    musuh3.y = rand()%tinggi;
    musuh3.pastDirX = Left;
    musuh3.pastDirY = Up;

    while(maze[musuh3.y][musuh3.x] != ' '){
        musuh3.x = rand()%lebar;
        musuh3.y = rand()%tinggi;
    }
    if(maze[musuh3.y][musuh3.x] == ' '){
        maze[musuh3.y][musuh3.x] = musuh3.sprite;
    }

    Musuh musuh4;
    musuh4.sprite = '<';
    musuh4.x = rand()%lebar;
    musuh4.y = rand()%tinggi;
    musuh4.pastDirX = Left;
    musuh4.pastDirY = Up;

    while(maze[musuh4.y][musuh4.x] != ' '){
        musuh4.x = rand()%lebar;
        musuh4.y = rand()%tinggi;
    }
    if(maze[musuh4.y][musuh4.x] == ' '){
        maze[musuh4.y][musuh4.x] = musuh4.sprite;
    }

    Musuh musuh5;
    musuh5.sprite = '<';
    musuh5.x = rand()%lebar;
    musuh5.y = rand()%tinggi;
    musuh5.pastDirX = Left;
    musuh5.pastDirY = Up;

    while(maze[musuh5.y][musuh5.x] != ' '){
        musuh5.x = rand()%lebar;
        musuh5.y = rand()%tinggi;
    }
    if(maze[musuh5.y][musuh5.x] == ' '){
        maze[musuh5.y][musuh5.x] = musuh5.sprite;
    }

    string prevmove1 = "NA";
    string prevmove2 = "NA";
    string prevmove3 = "NA";
    string prevmove4 = "NA";
    string prevmove5 = "NA";
    
    while(kalah){
        if(maze[player.y][player.x] == ' '){
            maze[player.y][player.x] = player.sprite;
    }

    maze[musuh1.y][musuh1.x] = musuh1.sprite;
    maze[musuh2.y][musuh2.x] = musuh2.sprite;
    maze[musuh3.y][musuh3.x] = musuh3.sprite;
    maze[musuh4.y][musuh4.x] = musuh4.sprite;
    maze[musuh5.y][musuh5.x] = musuh5.sprite;

    for(int y=0 ; y<tinggi ; y++){
        cout<<endl;
        for(int x=0 ; x<lebar ; x++){
            cout<<maze[y][x];
        }
    }

    cout<<endl;
    cout<<endl<<"HP: "<<Hp;

    char key = getch();

    switch(key){
        case key_kiri:
            if(maze[player.y][player.x-1] != '#'){
                maze[player.y][player.x] = ' ';
                player.x--;
                if(maze[player.y][player.x-1] == '<'){
                    Hp=Hp-20;
                }
            }
            break;
        case key_atas:
            if(maze[player.y-1][player.x] != '#'){
                maze[player.y][player.x] = ' ';
                player.y--;
                if(maze[player.y-1][player.x] == '<'){
                    Hp=Hp-20;
                }
            }
            break;
        case key_bawah:
            if(maze[player.y+1][player.x] != '#'){
                maze[player.y][player.x] = ' ';
                player.y++;
                if(maze[player.y+1][player.x] == '<'){
                    Hp=Hp-20;
                }
            }
            break;
        case key_kanan:
            if(maze[player.y][player.x+1] != '#'){
                maze[player.y][player.x] = ' ';
                player.x++;
                if(maze[player.y][player.x+1] == '<'){
                    Hp=Hp-20;
                }
            }
            break;
        case 'q':
            exit(0);
            break;
    }
}
     //udah ga error cuma masih overflow, help!

    system("PAUSE");
    return EXIT_SUCCESS;
}
