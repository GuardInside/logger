#pragma once

#include <fstream>

/// Класс файла лога
///
/// Автоматически задает имя файлу в соответствии с текущей датой.
/// Автоматически создает новый файл и продолжает запись в него
/// при достижении предельного размера.
class LogFile
{
public:
    LogFile(const char *directory = "log/", int max_byte_size = 50 * (1024 * 1024));

private:
    int _file_counter;
    int _max_file_size_Mb;
};
