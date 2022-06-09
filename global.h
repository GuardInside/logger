#pragma once

#if defined(_WIN32)
#   if defined(LOGGER_LIBRARY)
#       define LOGGERSHARED_EXPORT __declspec(dllexport)
#   else
#       define LOGGERSHARED_EXPORT __declspec(dllimport)
#   endif
#endif
