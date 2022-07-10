#include <iostream>
#include "ConsoleEngine.h"
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>

const int SPAWN_LOCATION = 5;

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct Segment
{
    Segment(int x, int y)
    : m_x(x), m_y(y)
    {
    }

    Segment &operator=(const Segment &other)
    {
        m_x = other.m_x;
        m_y = other.m_y;
        return *this;
    }

    bool operator==(const Segment &other) const
    {
        return(m_x==other.m_x && m_y==other.m_y);
    }

    int m_x;
    int m_y;
};


class Snake
{
public:

    Snake()
    : headDirection(Direction::UP),m_xBound(20), m_yBound(20),food(Segment(0,0)),score(0),highscore(0)
    {
        body.push_back(Segment(SPAWN_LOCATION,SPAWN_LOCATION));
        grow();
        food = Segment(rand()%m_xBound,rand()%m_yBound);
    }

    Snake(size_t xbound, size_t ybound)
    : headDirection(Direction::UP),m_xBound(xbound), m_yBound(ybound),food(Segment(0,0)),score(0),highscore(0)
    {
        body.push_back(Segment(SPAWN_LOCATION,SPAWN_LOCATION));
        grow();
        food = Segment(rand()%m_xBound-1,rand()%m_yBound-1);
    }

    void updatePositions()
    {
        for(size_t i = body.size()-1;i>0;i--)
        {
            body[i] = body[i-1];
        }

        switch(headDirection)
        {
        case Direction::UP:
            if(body[0].m_y+1<m_yBound)
                body[0].m_y++;
            break;
        case Direction::DOWN:
            if(body[0].m_y-1>=0)
                body[0].m_y--;
            break;
        case Direction::LEFT:
            if(body[0].m_x-1>=0)
                body[0].m_x--;
            break;
        case Direction::RIGHT:
            if(body[0].m_x+1<m_xBound)
                body[0].m_x++;
            break;
        }
        checkCollision();
    }

    void checkCollision()
    {
        if(body[0]==food)
        {
            //Beep(200,100);
            grow();
            relocate_food();
            score++;
            if(score>highscore)
                highscore=score;
        }
        for(int i=1;i<body.size();i++)
        {
            if(body[i]==body[0])
            {
                die();
                break;
            }
        }
    }

    void setDirection(const Direction d)
    {
        if(d!=Direction::NONE)
            headDirection = d;
    }

    void die()
    {
        //Beep(90,200);
        score = 0;
        body.clear();
        headDirection = Direction::UP;
        body.push_back(Segment(SPAWN_LOCATION,SPAWN_LOCATION));
        grow();
        relocate_food();
    }

    void grow()
    {
        for(int i=0;i<3;i++)
        {
            body.push_back(Segment(body.back()));
        }
    }

    void relocate_food()
    {
        food = Segment(rand()%(m_xBound-1),rand()%(m_yBound-3));
        for(int i=0;i<body.size();i++)
        {
            if(food == body[i])
                relocate_food();
        }

    }

    size_t size()
    {
        return body.size();
    }

    const Segment &getSegment(int s) const
    {
        if(s<0)
        {
            return food;
        }
        return body[s];
    }

    size_t getScore()
    {
        return score;
    }
    size_t getHighScore()
    {
        return highscore;
    }

private:
    std::vector<Segment> body;
    Direction headDirection;
    Segment food;
    const size_t m_xBound;
    const size_t m_yBound;
    size_t score;
    size_t highscore;
};


class Demo : public ConsoleEngine
{
public:
    Demo()
    : s(c_screenWidth,c_screenHeight-2),m_tick(0)
    {
        for(int i=0;i<c_screenWidth;i++)
        {
            fill('=',TEXT_COLOR(COLOR::WHITE,COLOR::BLACK),0,c_screenHeight-2,c_screenWidth-1,c_screenHeight-2);
        }
    }

    Demo(size_t screenw, size_t screenh)
    : ConsoleEngine(screenw,screenh), s(c_screenWidth,c_screenHeight-2),m_tick(0)
    {
        for(int i=0;i<c_screenWidth;i++)
        {
            fill('=',TEXT_COLOR(COLOR::WHITE,COLOR::BLACK),0,c_screenHeight-2,c_screenWidth-1,c_screenHeight-2);
        }
    }


    void loopMain()
    {
        if(m_tick==100)
        {
            s.setDirection(getDirectionFromKey());
            s.updatePositions();
            m_tick=0;
        }
        for(int i=0;i<s.size();i++)
        {
            fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::LIGHTGREEN),s.getSegment(i).m_x,s.getSegment(i).m_y);
        }
        fill('@',TEXT_COLOR(COLOR::LIGHTRED,COLOR::BLACK),s.getSegment(-1).m_x,s.getSegment(-1).m_y);

        std::ostringstream ss;
        //ss<<s.getSegment(-1).m_x<<" "<<s.getSegment(-1).m_y<<" || "<<s.getSegment(0).m_x<<" "<<s.getSegment(0).m_y;
        ss<<"Score: "<<s.getScore()<<"    "<<"High Score: "<<s.getHighScore();
        drawText(ss.str(),TEXT_COLOR(COLOR::WHITE,COLOR::BLACK),0, c_screenHeight-1);
        m_tick++;
    }

    void loopClear()
    {
        fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::BLACK),0,0,c_screenWidth-1,c_screenHeight-3);
        fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::BLACK),0,c_screenHeight-1,30,c_screenHeight-1);
    }

    Direction getDirectionFromKey()
    {
        if(m_keystates['W'])
            return Direction::DOWN;
        else if(m_keystates['S'])
            return Direction::UP;
        else if(m_keystates['A'])
            return Direction::LEFT;
        else if (m_keystates['D'])
            return Direction::RIGHT;
        else
            return Direction::NONE;
    }

private:
    Snake s;
    size_t m_tick;
};


int main()
{
    Demo d(30,30);
    d.startLoop();

    return 0;
}
