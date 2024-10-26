#include "OpenFileException.h"

OpenFileException::OpenFileException() : message_("Can't open the file") {}

OpenFileException::OpenFileException(std::string &message) : message_(message) {}

const char *OpenFileException::what() const noexcept {
    return message_.c_str();
}
