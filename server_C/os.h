#ifndef C_CLIENT_OS_H
#define C_CLIENT_OS_H
#define LINUX
#if defined(__unix) || defined(__unix__) || defined(unix) || defined(linux)
#define LINUX
#endif // __UNIX
#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS
#endif // _WIN32 || _WIN64


#endif // !C_CLIENT_OS_H

