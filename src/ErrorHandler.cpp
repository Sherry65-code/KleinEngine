#include "ErrorHandler.hpp"
#include "__macros__only_hpp.hpp"

void ErrorHandler::raiseError(const std::string& errorMessage) {
#ifdef WIN32
    MessageBox(nullptr, errorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
#else
    std::cerr << "ERROR: " << errorMessage << std::endl;
#endif
}