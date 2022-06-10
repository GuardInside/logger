#include "console_stream_writer.h"

#include <iostream>

#if defined (OS_WIN)
#include <windows.h>
#endif

namespace {
    enum class Color
    {
        #if defined (OS_WIN)
        FG_RED      = FOREGROUND_RED,
        FG_GREEN    = FOREGROUND_GREEN,
        FG_YELLOW   = FG_RED | FG_GREEN,
        FG_BLUE     = FOREGROUND_BLUE,
        FG_WHIE     = FG_RED | FG_GREEN | FG_BLUE,
        FG_BRIGHT_RED      = FG_RED | FOREGROUND_INTENSITY,
        FG_BRIGHT_GREEN    = FG_GREEN | FOREGROUND_INTENSITY,
        FG_BRIGHT_YELLOW   = FG_YELLOW | FOREGROUND_INTENSITY,
        FG_BRIGHT_BLUE     = FG_BLUE | FOREGROUND_INTENSITY,
        FG_BRIGHT_WHITE    = FG_WHIE | FOREGROUND_INTENSITY,

        BG_RED      = BACKGROUND_RED,
        BG_GREEN    = BACKGROUND_GREEN,
        BG_YELLOW   = BG_RED | BG_GREEN,
        BG_BLUE     = BACKGROUND_BLUE,
        BG_WHITE    = BG_RED | BG_GREEN | BG_BLUE,
        BG_BRIGHT_RED      = BG_RED | BACKGROUND_INTENSITY,
        BG_BRIGHT_GREEN    = BG_GREEN | BACKGROUND_INTENSITY,
        BG_BRIGHT_YELLOW   = BG_YELLOW | BACKGROUND_INTENSITY,
        BG_BRIGHT_BLUE     = BG_BLUE | BACKGROUND_INTENSITY,
        BG_BRIGHT_WHITE    = BG_WHITE | BACKGROUND_INTENSITY,

        DEFAULT = FG_YELLOW | FG_BLUE
        #endif

        #if defined (OS_LINUX)
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_WHITE    = 37
        FG_BRIGHT_RED      = 91,
        FG_BRIGHT_GREEN    = 92,
        FG_BRIGHT_YELLOW   = 93,
        FG_BRIGHT_BLUE     = 94,
        FG_BRIGHT_WHITE    = 97,

        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_YELLOW   = 43,
        BG_BLUE     = 44,
        BG_WHITE    = 47,
        BG_BRIGHT_RED      = 101,
        BG_BRIGHT_GREEN    = 102,
        BG_BRIGHT_YELLOW   = 103,
        BG_BRIGHT_BLUE     = 104,
        BG_BRIGHT_WHITE    = 107,

        DEFAULT = 0
        #endif
    };

    std::ostream& operator<< (std::ostream& os, const Color& color)
    {
        #if defined (OS_WIN)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
        #endif

        #if defined (OS_LINUX)
        return os << "\033[" << color << "m";
        #endif

        return os;
    }

    Color text_color(logger::level l)
    {
        using logger::level;

        switch (l)
        {
            case level::trace:
                return Color::FG_BRIGHT_BLUE;
            case level::debug:
                return Color::FG_BRIGHT_WHITE;
            case level::info:
                return Color::FG_BRIGHT_YELLOW;
            case level::warning:
                return Color::FG_YELLOW;
            case level::error:
                return Color::FG_BRIGHT_RED;
        }

        return Color::DEFAULT;
    }
}

logger::console_stream_writer::console_stream_writer()
{
    ;
}

void logger::console_stream_writer::write(level level, const char *text)
{
    std::cout << text_color(level) << text << std::endl << Color::DEFAULT;
}
