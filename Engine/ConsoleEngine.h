#ifndef CONSOLEENGINE_H
#define CONSOLEENGINE_H
#include <iostream>
#include <math.h>
#include <random>
#include <chrono>
#include <string>
#include <windows.h>


enum class COLOR
{
    RED,
    LIGHTRED,
    GREEN,
    LIGHTGREEN,
    BLUE,
    LIGHTBLUE,
    LIGHTERBLUE,
    CYAN,
    YELLOW,
    LIGHTYELLOW,
    PURPLE,
    LIGHTPURPLE,
    GREY,
    LIGHTGREY,
    WHITE,
    BLACK,
    RANDOM
};

struct TEXT_COLOR
{
    TEXT_COLOR(COLOR foreground,COLOR background=COLOR::BLACK)
    : Foreground_Color(foreground),Background_Color(background)
    {
    }

    COLOR Foreground_Color;
    COLOR Background_Color;
};


class ConsoleEngine
{
    friend class BaseEvent;
public:
    ConsoleEngine();
    ConsoleEngine(size_t width, size_t height);
    ~ConsoleEngine();

    int constructConsole(const size_t width, const size_t height);
    void startLoop();
    void exitLoop();

    void loop();

    virtual void fillPixel(wchar_t c,const TEXT_COLOR &col,int x,int y);
    virtual void fill(wchar_t c,const TEXT_COLOR &col,int x1,int y1,int x2=-1,int y2=-1);
    virtual void fill(wchar_t c,const TEXT_COLOR &col);
    virtual void drawLine(wchar_t c,const TEXT_COLOR &col,int x1,int y1,int x2, int y2);
    virtual void drawText(std::string str,const TEXT_COLOR &col,int x1, int y1);

    virtual void loopClear();
    virtual void loopMain() = 0;

protected:
    CHAR_INFO *screen;
    HANDLE m_hConsole;
    const size_t c_screenWidth;
    const size_t c_screenHeight;
    bool m_keystates[256];

private:
    DWORD m_dwBytesWritten;
    bool m_isLooping;
    void handleInputs();
    WORD TEXT_COLORToWORD(const TEXT_COLOR &tc) const;       //returns WORD for use in CHAR_INFO.Attributes
};



#endif // CONSOLEENGINE_H
