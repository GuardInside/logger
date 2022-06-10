#pragma once

#include "stream_writer.h"

#include <fstream>
#include <filesystem>

namespace logger
{
    class file_stream_writer : public stream_writer
    {
    public:
        file_stream_writer();

        void write(level, const char * text) override;

    private:
        void make_log_file();
        void make_log_dir() const;
        std::string generate_file_name();

    private:
        std::filesystem::path _file_path;

        uintmax_t _file_name_counter;

        std::fstream _fstream;
    };
}
