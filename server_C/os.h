#ifndef C_SERVER_OS_H
#define C_SERVER_OS_H

#ifdef __UNIX || __UNIX__ || UNIX
#define LINUX
#endif // __UNIX
#ifdef _WIN32 || _WIN64
#define WINDOWS
#endif // _WIN32 || _WIN64


#endif // !C_SERVER_OS_H