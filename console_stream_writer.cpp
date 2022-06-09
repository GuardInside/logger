#include "ConsoleStreamWriter.h"
#include <cstdio>

#if defined (Q_OS_WIN)
#include <windows.h>
#endif

namespace {
    enum class Color
    {
        #if defined (Q_OS_WIN)
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

        #if defined (Q_OS_LINUX)
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

    QTextStream& operator<< (QTextStream& os, const Color& color)
    {
        #if defined (Q_OS_WIN)
        Q_UNUSED(os)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
        #endif

        #if defined (Q_OS_LINUX)
        return os << "\033[" << color << "m";
        #endif

        return os;
    }
}

ConsoleStreamWriter::ConsoleStreamWriter()
    : cstream(stdout)
{
    ;
}

void ConsoleStreamWriter::write(ILogger::LogLevel logLevel, const QString &msg)
{
    setColor(logLevel);
    cstream << msg << endl << Color::DEFAULT;
}

void ConsoleStreamWriter::setColor(ILogger::LogLevel logLevel)
{
    switch( logLevel )
    {
        case ILogger::Trace:
            cstream << Color::FG_BRIGHT_BLUE; break;
        case ILogger::Debug:
            cstream << Color::FG_BRIGHT_WHITE; break;
        case ILogger::Info:
            cstream << Color::FG_BRIGHT_YELLOW; break;
        case ILogger::Warning:
            cstream << Color::FG_YELLOW; break;
        case ILogger::Error:
            cstream << Color::FG_BRIGHT_RED; break;
        case ILogger::Fatal:
            cstream << Color::FG_RED; break;
        default:
            cstream << Color::DEFAULT; break;
    }
}
