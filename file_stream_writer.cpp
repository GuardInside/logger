#include "file_stream_writer.h"

FileStreamWriter::FileStreamWriter()
{
    fstream.setDevice(&file);
    fstream.setCodec("utf-8");
}

void FileStreamWriter::write(ILogger::LogLevel, const QString &msg)
{
    if( !file.isOpen() )
        if( !file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append | QIODevice::Unbuffered) )
            return;

    fstream << msg << endl;
}

logger::file_stream_writer::file_stream_writer()
{

}

void logger::file_stream_writer::write(level, const char *text)
{
    if (!_fstream.is_open())
    {
        if (_fstream.open())
    }
}
