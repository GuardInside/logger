#include "logger.h"
#include "console_stream_writer.h"
#include "file_stream_writer.h"

#include <ctime>

namespace
{
    std::string time_stamp()
    {
        // todo: const width

        const auto current_time = std::time(0);
        const auto tm = std::localtime(&current_time);

        return std::to_string(tm->tm_hour) + ':' + std::to_string(tm->tm_min) + ':' + std::to_string(tm->tm_sec) + '.' + std::to_string(0);
    }

    std::string level_label(logger::level l)
    {
        using logger::level;

        switch  (l)
        {
            case level::trace: return "trace";
            case level::debug: return "debug";
            case level::info: return "info";
            case level::warning: return "warning";
            case level::error: return "error";
        }

        return {};
    }
}

logger::logger::logger(out_device out_device)
{
    set_out_device(out_device);
}

void logger::logger::log(const char *msg) const
{
    const auto level = level::debug;
    const auto text = time_stamp() + '\t' + level_label(level) + '\t'+ msg;

    if (_console_writer)
        _console_writer->write(level, text.c_str());

    if (_file_writer)
        _file_writer->write(level, text.c_str());
}

void logger::logger::set_out_device(out_device out_device)
{
    if ((int)out_device & (int)out_device::console)
    {
        _console_writer = std::make_unique<console_stream_writer>();
    }

    if ((int)out_device & (int)out_device::file)
    {
        _file_writer = std::make_unique<file_stream_writer>();
    }
}

logger::logger::~logger()
{
    ;
}
