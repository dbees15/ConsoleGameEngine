#ifndef GOL_H
#define GOL_H
#include <string>
#include <sstream>

class Gol
{
    public:
        Gol(unsigned int x, unsigned int y, std::string brule, std::string srule);
        Gol(unsigned int x, unsigned int y);
        virtual ~Gol();

        void update();  //advances simulation state by one
        bool getCell(unsigned int x, unsigned int y);     //returns cell state at position (x,y)
        void writeCell(bool s, unsigned int x, unsigned int y);   //writes state s to position (x,y)

        unsigned int getWidth();    //return level width
        unsigned int getHeight();   //return level height
        unsigned short getBirthRule();  //returns birth rule in binary format
        unsigned short getSurvivalRule();   //returns survival rule in binary format
        unsigned int getGeneration();    //returns current generation number

    private:
        bool **m_readlevel;  //current state of game
        bool **m_writelevel;    //future state of game
        const unsigned int m_width; //effective width of level
        const unsigned int m_height;    //effective height of level
        unsigned short m_survivalrule;  //survival rule in binary format
        unsigned short m_birthrule;     //birth rule in binary format
        unsigned int m_generation;  //current generation
};

#endif // GOL_H
