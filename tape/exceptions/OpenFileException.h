#ifndef OPEN_FILE_EXCEPTION_H
#define OPEN_FILE_EXCEPTION_H

#include <exception>
#include <string>

/*
 * Исключение при неудачной попытки открыть файл
 */
class OpenFileException : public std::exception {
public:
    OpenFileException();

    OpenFileException(std::string &message);

    const char *what() const noexcept override;

private:
    std::string message_;
};

#endif
