#pragma once

#include <memory>

namespace logger
{
    class stream_writer;

    enum class level : int
    {
        trace,
        debug,
        info,
        warning,
        error
    };

    class logger
    {
    public:
        enum class out_device : int
        {
            console = 0x1,
            file = 0x2,
            both = console | file
        };

        logger(out_device = out_device::both);

        //!
        virtual void log(const char * msg) const;

        void set_out_device(out_device);

        virtual ~logger();

    public:
        std::unique_ptr<stream_writer> _console_writer;
        std::unique_ptr<stream_writer> _file_writer;
    };
}
