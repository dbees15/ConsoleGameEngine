#include <iostream>
#include "GameOfLife.h"

using namespace std;

int main()
{
    GameOfLife game(70,109);
    game.startLoop();
    return 0;
}
