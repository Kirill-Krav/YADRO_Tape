#ifndef SORT_SIZE_EXCEPTION_H
#define SORT_SIZE_EXCEPTION_H

#include <exception>
#include <string>

/*
 * Исключение при неправильной задачи параметра размера данных для сортировки
 */
class SortSizeException : public std::exception {
public:
    SortSizeException(std::string &message);

    const char *what() const noexcept override;

private:
    std::string message_;
};

#endif
