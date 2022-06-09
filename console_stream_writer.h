#pragma once

#include "stream_writer.h"

namespace logger
{
    class console_stream_writer : public stream_writer
    {
    public:
        console_stream_writer();

        void write(level, const char * text) override;
    };
}
