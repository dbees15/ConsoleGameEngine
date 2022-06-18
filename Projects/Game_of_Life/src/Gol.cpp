#include "Gol.h"

//brule and srule must be input as strings, rules such are "0123" are standard, input as integer would omit 0
Gol::Gol(unsigned int x, unsigned int y, std::string brule, std::string srule)
: m_width(x), m_height(y), m_survivalrule(0), m_birthrule(0), m_generation(0)
{
    //allocate both read and write arrays
    m_readlevel = new bool*[y+2];
    m_writelevel = new bool*[y+2];
    for(int i=0;i<y+2;i++)
    {
        m_readlevel[i] = new bool[x+2];
        m_writelevel[i] = new bool[x+2];
    }

    //initialize both read and write arrays to 0
    for(int i=0;i<y+2;i++)
    {
        for(int j=0;j<x+2;j++)
        {
            m_readlevel[j][i] = 0;
            m_writelevel[j][i] = 0;
        }
    }

    unsigned short int *temp = &m_birthrule;
    std::string *strtemp = &brule;

    for(int i=0;i<=1;i++)
    {
        if(strtemp->size()==0)  //skip if null string
            continue;

        std::stringstream ss(*strtemp);
        char num;   //extracted char from ss
        while(ss.get(num))
        {
            num -= 48;  //convert from symbol to number
            int binarytemp = 1 << num;
            *temp = *temp | binarytemp;
        }

        temp = &m_survivalrule;
        strtemp = &srule;
    }

}


Gol::Gol(unsigned int x, unsigned int y)
: m_width(x), m_height(y), m_generation(0)
{
    //allocate both read and write arrays
    m_readlevel = new bool*[y+2];
    m_writelevel = new bool*[y+2];
    for(int i=0;i<y+2;i++)
    {
        m_readlevel[i] = new bool[x+2];
        m_writelevel[i] = new bool[x+2];
    }

    //initialize both read and write arrays to 0
    for(int i=0;i<y+2;i++)
    {
        for(int j=0;j<x+2;j++)
        {
            m_readlevel[j][i] = 0;
            m_writelevel[j][i] = 0;
        }
    }

    //Default survival and birth rules to Conway's Game of Life
    m_survivalrule = 0b000001100;
    m_birthrule = 0b000001000;
}

Gol::~Gol()
{
    //deallocate both read and write arrays
    for(int i=0;i<m_height+2;i++)
    {
        delete m_readlevel[i];
        delete m_writelevel[i];
    }

    delete m_readlevel;
    delete m_writelevel;
}



void Gol::update()  //advances simulation state by one
{
    //update every cell one at a time
    for(int i=1;i<=m_height;i++)    //y axis
    {
        for(int j=1;j<=m_width;j++) //x axis
        {
            unsigned short int count = 0;  //number of living neighboring cells

            //iterate through 8 adjacent cells to (i,j) and (i,j)
            for(int y=0;y<3;y++)
            {
                for(int x=0;x<3;x++)
                {
                    count+= (y==1 && x==1) ? 0 : m_readlevel[x-1+j][y-1+i];
                }
            }

            count = 1 << count; //convert to binary format (eg. 3 is now 0b000001000)

            //rule implementation
            if(m_readlevel[j][i])   //if current cell is alive
            {
                 if(m_survivalrule & count)  //survival condition
                {
                    m_writelevel[j][i] = 1;
                }
                else
                {
                    m_writelevel[j][i] = 0;
                }

            }
            else    //if current cell is dead
            {
                if(m_birthrule & count)    //birth condition
                {
                    m_writelevel[j][i] = 1;
                }
                else
                {
                    m_writelevel[j][i] = 0;
                }
            }
        }
    }

    //swap read and write levels
    bool **temp = m_readlevel;
    m_readlevel = m_writelevel;
    m_writelevel = temp;

    m_generation++;
}

bool Gol::getCell(unsigned int x, unsigned int y)     //returns cell state at position (x,y)
{
    return m_readlevel[x+1][y+1];
}

void Gol::writeCell(bool s, unsigned int x, unsigned int y)   //writes state s to position (x,y)
{
    m_readlevel[x+1][y+1] = s;  //Note: implement protection
}

unsigned int Gol::getWidth() //return level width
{
    return m_width;
}

unsigned int Gol::getHeight()    //return level height
{
    return m_height;
}

unsigned short Gol::getBirthRule()  //returns birth rule in binary format
{
    return m_birthrule;
}

unsigned short Gol::getSurvivalRule()   //returns survival rule in binary format
{
    return m_survivalrule;
}

unsigned int Gol::getGeneration()
{
    return m_generation;
}
