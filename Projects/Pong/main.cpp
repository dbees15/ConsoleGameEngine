#include <iostream>
#include "ConsoleEngine.h"
#include "Vector2d.h"
#include <sstream>
#include <random>

//Recommended window size: 100x80

class Ball
{
public:

Ball()
: m_hitbox(Vector2d(1,1)), m_rootposition(1,1), m_velocity(1,1)
{}

Ball(Vector2d position, Vector2d hitbox, Vector2d velocity)
: m_rootposition(position), m_hitbox(hitbox), m_velocity(velocity)
{}

void reflectMotionX()
{
    m_velocity.SetX(m_velocity.getX()*-1);
}

void reflectMotionY()
{
    m_velocity.SetY(m_velocity.getY()*-1);
}

void updatePosition()
{
    m_rootposition+=m_velocity;
}

const Vector2d &getPosition() const
{
    return m_rootposition;
}

const Vector2d &getHitbox() const
{
    return m_hitbox;
}

const Vector2d &getVelocity() const
{
    return m_velocity;
}

void setVelocity(const Vector2d &v)
{
    m_velocity = v;
}


private:
    Vector2d m_rootposition;
    const Vector2d m_hitbox;
    Vector2d m_velocity;
};

class Paddle
{
public:
    Paddle()
    : m_hitbox(Vector2d(0,0)), m_rootposition(Vector2d(0,0))
    {}

    Paddle(const Vector2d &pos, const Vector2d &hitbox)
    :m_hitbox(hitbox),m_rootposition(pos)
    {

    }


    const Vector2d &getHitbox() const
    {
        return m_hitbox;
    }

    const Vector2d &getPosition() const
    {
        return m_rootposition;
    }


    void move(int direction)
    {
        m_rootposition+=Vector2d(0,direction);
    }

private:
    Vector2d m_rootposition;
    const Vector2d m_hitbox;
};

class Level
{
public:
    Level()
    : m_levelSize(Vector2d(0,0))
    {}

    Level(Vector2d size)
    : m_levelSize(size), m_p1(NULL), m_p2(NULL), m_ball(NULL)
    {
        m_score=0;
        m_highscore=0;
        restart();
    }

    void moveP1(float speed)
    {
        //Vector2d pos = m_p1->getPosition();
        //Vector2d hit = m_p1->getHitbox();
        if(m_p1->getPosition().getY() + speed > -1&&m_p1->getHitbox().getY()+m_p1->getPosition().getY()+speed <m_levelSize.getY())
        {
            m_p1->move(speed);
        }
    }

    void updateBall()
    {
        debug = m_ball->getHitbox().getX()+m_ball->getPosition().getX()+m_ball->getVelocity().getX();
        if(m_ball)
        {
            if(m_ball->getPosition().getY()+m_ball->getVelocity().getY()<0 ||
               m_ball->getHitbox().getY()+m_ball->getPosition().getY()+m_ball->getVelocity().getY()>m_levelSize.getY())
            {
                m_ball->reflectMotionY();
            }

            else if(m_ball->getPosition().getY()+m_ball->getVelocity().getY()<0 ||
               m_ball->getHitbox().getY()+m_ball->getPosition().getY()+m_ball->getVelocity().getY()>m_levelSize.getY())
            {
                m_ball->reflectMotionY();
            }

            else if(m_ball->getHitbox().getX()+m_ball->getPosition().getX()+m_ball->getVelocity().getX()>m_levelSize.getX())
            {
                m_ball->reflectMotionX();
            }

            else if(m_ball->getPosition().getX()+m_ball->getVelocity().getX()<=m_p1->getHitbox().getX()+m_p1->getPosition().getX() &&
               m_ball->getPosition().getY()>= m_p1->getPosition().getY()-m_ball->getHitbox().getY() &&
               m_ball->getPosition().getY()<= m_p1->getHitbox().getY()+m_p1->getPosition().getY())
            {
                m_ball->reflectMotionX();
                m_ball->setVelocity(m_ball->getVelocity()+Vector2d(0.1,0));
                m_score++;
                if(m_score>m_highscore)
                    m_highscore=m_score;
            }

            else if(m_ball->getPosition().getX()+m_ball->getVelocity().getX()<0)
            {
                Beep(100,200);
                restart();
            }

            m_ball->updatePosition();
        }
    }

    void moveP2()
    {

    }

    void restart()
    {
        if(m_ball)
        {
            delete m_ball;
        }
        if(m_p1)
        {
            delete m_p1;
        }
        m_p1 = new Paddle(Vector2d(3 ,m_levelSize.getY()/2-5),Vector2d(2,10));
        m_ball = new Ball(Vector2d(m_levelSize.getX()-10,m_levelSize.getY()/2),Vector2d(2,2),Vector2d(-1,(rand()%200)<100 ?(rand()%100)*0.01 : (rand()%100)*-0.01));
        m_score=0;
    }

    const Paddle &getP1() const
    {
        return *m_p1;
    }

    const Ball &getBall() const
    {
        return *m_ball;
    }

    const Vector2d& getLevelSize() const
    {
        return m_levelSize;
    }

    const size_t getScore() const
    {
        return m_score;
    }

    const size_t getHighScore() const
    {
        return m_highscore;
    }

    int debug;
private:
    Ball *m_ball;
    Paddle *m_p1;
    Paddle *m_p2;

    size_t m_score;
    size_t m_highscore;

    const Vector2d m_levelSize;
};


class Application : public ConsoleEngine
{
public:
    Application(int x,int y)
    : ConsoleEngine(x,y), m_level(Vector2d(c_screenWidth,c_screenHeight-3))
    {
        tick = 0;

        fill(0x2592,TEXT_COLOR(COLOR::BLACK,COLOR::WHITE),0,c_screenHeight-3,c_screenWidth-1,c_screenHeight-3);
    }

    void loopClear()
    {
        fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::BLACK),0,0,c_screenWidth-1,c_screenHeight-4);
        fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::BLACK),0,c_screenHeight-2,c_screenWidth-1,c_screenHeight-1);
    }


    void loopMain()
    {
        if(tick==15)
        {
            if(m_keystates['S'])
            {
                m_level.moveP1(1);
            }
            else if(m_keystates['W'])
            {
                m_level.moveP1(-1);
            }
            else if(m_keystates['R'])
            {
                m_level.restart();
            }

            m_level.updateBall();


            tick=0;
        }
        tick++;

        fill(' ',TEXT_COLOR(COLOR::WHITE,COLOR::WHITE),
             m_level.getP1().getPosition().getX(),m_level.getP1().getPosition().getY(),
             m_level.getP1().getPosition().getX()+m_level.getP1().getHitbox().getX(),
             m_level.getP1().getPosition().getY()+m_level.getP1().getHitbox().getY());

        fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::LIGHTRED),
        m_level.getBall().getPosition().getX(),  m_level.getBall().getPosition().getY(),
        m_level.getBall().getPosition().getX()+ m_level.getBall().getHitbox().getX(),
        m_level.getBall().getPosition().getY()+ m_level.getBall().getHitbox().getY());


        std::ostringstream ss;
        ss<<"Score: "<<m_level.getScore()<<"   High Score: "<<m_level.getHighScore();
        drawText(ss.str(),TEXT_COLOR(COLOR::WHITE,COLOR::BLACK),0,c_screenHeight-2);
    }

private:
int tick;
Level m_level;
};



int main()
{
    srand(time(NULL));
    Application a(100,80);
    a.startLoop();
    return 0;
}
