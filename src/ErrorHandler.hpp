#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <iostream>
#include <string>


#ifdef WIN32
#include <Windows.h>
#endif

class ErrorHandler {
public:
    static void raiseError(const std::string& errorMessage);
};

#endif /* ERROR_HANDLER_HPP */
