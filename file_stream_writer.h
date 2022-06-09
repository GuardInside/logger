#pragma once

#include "stream_writer.h"

#include "file.h"

namespace logger
{
    class file_stream_writer : public stream_writer
    {
    public:
        file_stream_writer();

        void write(level, const char * text) override;

    private:
        std::fstream _fstream;
    };
}
