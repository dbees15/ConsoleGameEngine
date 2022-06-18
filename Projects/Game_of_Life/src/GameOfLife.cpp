#include "GameOfLife.h"

GameOfLife::GameOfLife(int x, int y)
: ConsoleEngine(x,y), m_game(50,50,"123","12"), m_game1(50,50,"34","345")
{
    counter=0;
    m_game0x = 1;
    m_game0y = 3;

    m_game1x = 1;
    m_game1y = 56;
}

void GameOfLife::loopClear()
{
    fill('@',COLOR::GREEN,0,0,c_screenWidth,c_screenHeight);
}

void GameOfLife::loopMain()
{

    if(counter==10)
    {
        counter = 0;
        if(m_keystates[65]) //A key
        {
            m_game.writeCell(1,10,10);
            m_game.writeCell(1,11,11);
            m_game.writeCell(1,12,11);
            m_game.writeCell(1,12,10);
            m_game.writeCell(1,12,9);
        }

        if(m_keystates[81]) //Q key
        {
            m_game1.writeCell(1,10,10);
            m_game1.writeCell(1,11,11);
            m_game1.writeCell(1,12,11);
            m_game1.writeCell(1,12,10);
            m_game1.writeCell(1,12,9);
        }

        if(m_keystates[83])   //S key
        {
            m_game.update();
        }

        if(m_keystates[87]) //W key
        {
            m_game1.update();
        }

        if(m_keystates[27])
        {
            exitLoop();
        }
    }
    counter++;


    //draw to screen

    drawText(("Generation: "+std::to_string(m_game.getGeneration())),COLOR::WHITE,1,1);
    drawGame(&m_game,1,3);
    drawGame(&m_game1,1,56);

}

void GameOfLife::drawGame(Gol *game, int x, int y)
{
    for(int i=y;i<game->getHeight()+y;i++)
    {
        for(int j=x;j<game->getWidth()+x;j++)
        {
            if(game->getCell(j-x,i-y)==0)    //check if state of cell (i,j) is 0;
            {
                fillPixel(' ',COLOR::WHITE,j,i);
                continue;
            }
            fillPixel('#',COLOR::WHITE,j,i);
        }
    }
}


GameOfLife::~GameOfLife()
{
    //dtor
}

