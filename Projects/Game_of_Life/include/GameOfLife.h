#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "ConsoleEngine.h"
#include "Gol.h"

class GameOfLife : public ConsoleEngine
{
    public:
        GameOfLife(int x, int y);

        void loopClear();
        void loopMain();

        virtual ~GameOfLife();
    private:
        int counter;
        Gol m_game;
        Gol m_game1;

        int m_game0x;
        int m_game0y;

        int m_game1x;
        int m_game1y;

        //Private Methods

        void drawGame(Gol *game, int x, int y);
};

#endif // GAMEOFLIFE_H
