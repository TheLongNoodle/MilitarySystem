#ifndef UTILS_H
#define UTILS_H

#include <cstring>

namespace utils
{
inline char* dupString(const char* s)
{
    if (!s) return nullptr;
    std::size_t n = std::strlen(s);
    char* p = new char[n + 1];
    std::strcpy(p, s);
    return p;
}
}

#endif
