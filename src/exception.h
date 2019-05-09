//
// Created by tel on 2019-05-07.
//

#ifndef EPI_CODE_EXCEPTION_H
#define EPI_CODE_EXCEPTION_H

#include <exception>

namespace epi
{

// macro that passes the file:line from which it is raised to an exception's constructor
#define THROW_EXCEPTION(exception, ...) throw exception(__LINE__, __FILE__, __VA_ARGS__);

class Exception : public std::exception
{
public:
    // variadic constructors
    Exception() {}
    template <typename T> Exception(T format, ...) {init(format, (va_start(_va, format), _va)); va_end(_va);}
    template <typename T> Exception(int line, const char *file, T format, ...) {init(file, line, format, (va_start(_va, format), _va)); va_end(_va);}

    virtual ~Exception() throw() {}

    virtual const char* preamble() const throw() {return "Exception";}
    virtual const char* what() const throw() {return messageBuffer;}

protected:
    // overloaded function that converts std::strings to c-strings and leaves c-strings untouched
    static const char* cstr(const char* s) {return s;}
    static const char* cstr(const std::string s) {return s.c_str();}

    // init for formatted error message.
    // Format can be either char* or std::string
    template <typename T> void init(T format, va_list args)
    {
        int offset = snprintf(messageBuffer, MAX_MESSAGE_SIZE, "%s:\n", preamble());
        vsnprintf(messageBuffer + offset, MAX_MESSAGE_SIZE - offset, cstr(format), args);
    }

    // init for formatted error message with file and line.
    // Format can be either char* or std::string
    template <typename T> void init(const char* file, int line, T format, va_list args)
    {
        int offset = snprintf(messageBuffer, MAX_MESSAGE_SIZE, "%s:\n", preamble());
        offset += vsnprintf(messageBuffer + offset, MAX_MESSAGE_SIZE - offset, cstr(format), args);
        snprintf(messageBuffer + offset, MAX_MESSAGE_SIZE - offset, " (%s:%d)", file, line);
    }

protected:
    // 1 larger than 2**10 for cstr terminating '\0' char
    static const int MAX_MESSAGE_SIZE = 1025;
    char messageBuffer[MAX_MESSAGE_SIZE];

    va_list _va;
};

class AssertionError : public Exception
{
public:
    virtual const char* preamble() const throw() {return "Assertion error";}

    template <typename T> AssertionError(T format, ...) {init(format, (va_start(_va, format), _va)); va_end(_va);}
    template <typename T> AssertionError(int line, const char *file, T format, ...) {init(file, line, format, (va_start(_va, format), _va)); va_end(_va);}
};

class ValueError : public Exception
{
public:
    virtual const char* preamble() const throw() {return "Value error";}

    template <typename T> ValueError(T format, ...) {init(format, (va_start(_va, format), _va)); va_end(_va);}
    template <typename T> ValueError(int line, const char *file, T format, ...) {init(file, line, format, (va_start(_va, format), _va)); va_end(_va);}
};

}

#endif //EPI_CODE_EXCEPTION_H
