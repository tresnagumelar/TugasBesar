#include <cstdlib>
#include <iostream>

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

//edit lagi bro

int main(int argc, char *argv[])
{
    system("PAUSE");
    return EXIT_SUCCESS;
}
