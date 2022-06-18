#include "ConsoleEngine.h"

ConsoleEngine::ConsoleEngine()
:c_screenWidth(120),c_screenHeight(40)
{
    constructConsole(c_screenWidth,c_screenHeight);
}

ConsoleEngine::ConsoleEngine(size_t width, size_t height)
:c_screenWidth(width),c_screenHeight(height)
{
    constructConsole(c_screenWidth,c_screenHeight);
}

ConsoleEngine::~ConsoleEngine()
{
    delete[] screen;
}

int ConsoleEngine::constructConsole(size_t width, size_t height)
{
    screen = new CHAR_INFO[width*height];
    m_hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
    SetConsoleActiveScreenBuffer(m_hConsole);
    m_dwBytesWritten = 0;
    return 1;
}
void ConsoleEngine::startLoop()
{
    m_isLooping=true;
    loop();
}
void ConsoleEngine::exitLoop()
{
    m_isLooping=false;
}

void ConsoleEngine::loop()
{
    srand(time(NULL));
    SMALL_RECT window;
    window.Top=0;
    window.Left=0;
    window.Bottom=c_screenHeight-1;
    window.Right =c_screenWidth-1;
    while(m_isLooping)
    {
        loopClear();
        handleInputs();
        loopMain();
        WriteConsoleOutput(m_hConsole,screen,{c_screenWidth,c_screenHeight},{0,0},&window);
    }
}


void ConsoleEngine::handleInputs()
{
    for(int i=0;i<256;i++)
    {
        m_keystates[i] = false;
        if(GetAsyncKeyState(i))
        {
            m_keystates[i] = true;
        }
    }
}

WORD ConsoleEngine::TEXT_COLORToWORD(const TEXT_COLOR &tc) const
{
    COLOR colptr[2] = {tc.Foreground_Color,tc.Background_Color};
    int col[2] = {0,0};
    for(int i=0;i<2;i++)
    {
        switch(colptr[i])
        {
        case COLOR::BLACK:
            break;
        case COLOR::WHITE:
            col[i] = 15;
            break;
        case COLOR::GREY:
            col[i] = 8;
            break;
        case COLOR::RED:
            col[i] = 4;
            break;
        case COLOR::GREEN:
            col[i] = 2;
            break;
        case COLOR::BLUE:
            col[i] = 1;
            break;
        case COLOR::YELLOW:
            col[i] = 6;
            break;
        case COLOR::PURPLE:
            col[i] = 5;
            break;
        case COLOR::CYAN:
            col[i] = 11;
            break;
        case COLOR::LIGHTRED:
            col[i] = 12;
            break;
        case COLOR::LIGHTGREEN:
            col[i] = 10;
            break;
        case COLOR::LIGHTBLUE:
            col[i] = 9;
            break;
        case COLOR::LIGHTERBLUE:
            col[i] = 6;
            break;
        case COLOR::LIGHTYELLOW:
            col[i] = 14;
            break;
        case COLOR::LIGHTPURPLE:
            col[i] = 13;
            break;
        case COLOR::LIGHTGREY:
            col[i] = 8;
            break;
        case COLOR::RANDOM:
            col[i] = rand()%15;
            break;
        }
    }
    return col[0]+(col[1]*16);
}

void ConsoleEngine::loopClear()
{
    fill(' ',TEXT_COLOR(COLOR::BLACK,COLOR::BLACK));
}

void ConsoleEngine::fillPixel(wchar_t c,const TEXT_COLOR &col,int x,int y)
{
    if(x>=0 && x<c_screenWidth &&
       y>=0 && y<c_screenHeight  )     //check if in bounds
    {
        screen[x+y*c_screenWidth].Char.UnicodeChar = c;
        int color;
        screen[x+y*c_screenWidth].Attributes = TEXT_COLORToWORD(col);
    }
}


void ConsoleEngine::fill(wchar_t c,const TEXT_COLOR &col,int x1,int y1,int x2,int y2)
{
    if(y2<0||x2<0)
    {
        fillPixel(c,col,x1,y1);
    }
    else
    {
        for(int y=0;y<=abs(y2-y1);y++)
        {
            for(int x=0;x<=abs(x2-x1);x++)
            {
                fillPixel(c,col,x1+x,y1+y);
            }
        }
    }
}

void ConsoleEngine::fill(wchar_t c,const TEXT_COLOR &col)
{
    for(int i=0;i<c_screenHeight*c_screenWidth;i++)
    {
        screen[i].Char.UnicodeChar = c;
        int color;
        screen[i].Attributes = TEXT_COLORToWORD(col);
    }
}
void ConsoleEngine::drawLine(wchar_t c,const TEXT_COLOR &col,int x1,int y1,int x2, int y2)
{
    int dvectorX = x2-x1;
    int dvectorY = y2-y1;
    for(double t=0;t<=1;t+=1.0/(abs(float(1+dvectorX)*(1+dvectorY)*0.5)))
    {
        fillPixel(c,col,static_cast<int>(x1+dvectorX*t),y1+static_cast<int>(dvectorY*t));
    }
}

void ConsoleEngine::drawText(std::string str,const TEXT_COLOR &col,int x1, int y1)
{
    for(size_t i = 0;i<str.size();i++)
    {
        fill(str[i],col,x1+i,y1);
    }
}

