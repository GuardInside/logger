#include "file_stream_writer.h"

#include <filesystem>
#include <cassert>

namespace
{
    std::string data_stamp()
    {
        // todo:
        return "yyyymmdd";
    }

    std::string file_extansion()
    {
        return ".log";
    }

    uintmax_t max_file_size_byte()
    {
        return 50 * (1024 * 1024);
    }
}

logger::file_stream_writer::file_stream_writer()
{
    _file_name_counter = 0;
}

void logger::file_stream_writer::write(level, const char *text)
{
    if (!_fstream.is_open())
    {
        make_log_dir();
        make_log_file();
    }

    if (std::filesystem::file_size(_file_path) >= max_file_size_byte())
    {
        make_log_file();
    }

    _fstream << text << std::endl;
}

void logger::file_stream_writer::make_log_file()
{
    if (_fstream.is_open())
        _fstream.close();

    _file_path = std::filesystem::path("log") / generate_file_name();

    _fstream.open(_file_path, std::ios_base::out | std::ios_base::app);

    assert(_fstream.is_open());
}

void logger::file_stream_writer::make_log_dir() const
{
    std::filesystem::create_directory("log");
}

std::string logger::file_stream_writer::generate_file_name()
{
    // todo: reset _file_name_counter

    return data_stamp() + std::to_string(_file_name_counter++) + file_extansion();
}
