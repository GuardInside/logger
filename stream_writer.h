#pragma once

#include "logger.h"

namespace logger
{
    class stream_writer
    {
    public:
        virtual void write(level logLevel, const char * text) = 0;

        virtual ~stream_writer() = default;
    };
}
