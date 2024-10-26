#include "SortSizeException.h"

SortSizeException::SortSizeException(std::string &message) : message_(message) {}

const char *SortSizeException::what() const noexcept {
    return message_.c_str();
}
