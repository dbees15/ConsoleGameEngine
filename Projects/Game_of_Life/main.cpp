#include <iostream>
#include "GameOfLife.h"

using namespace std;

int main()
{
    GameOfLife game(107,55);
    game.startLoop();
    return 0;
}
