#include "file.h"

namespace
{
    std::string data_stamp()
    {
        return "yyyyMMdd";
    }

    std::string generate_file_name()
    {
        return
    }
}

LogFile::LogFile(const QString &directory, int max_byte_size)
    : counter (0)
    , max_size (max_byte_size)
    , dir (directory)
{
    if (!QDir(dir).exists())
        QDir::current().mkdir(dir);

    setFileName(generateFileName());
}

qint64 LogFile::writeData(const char *data, qint64 len)
{
    if( size() > max_size )
        ++(counter);

    const auto newFileName = generateFileName();

    if (fileName() != newFileName)
        if (!reopen(newFileName))
            return 0;

    return QFile::writeData(data, len);
}


QString LogFile::generateFileName()
{
    return QString("%1%2%3.log").arg(dir, QDate::currentDate().toString("yyyyMMdd")).arg(counter);
}

bool LogFile::reopen(const QString &name)
{
    const auto currentOpenMode = openMode();

    close();
    setFileName(name);
    return open(currentOpenMode);
}

LogFile::LogFile(const char *directory, int max_byte_size)
{

}
