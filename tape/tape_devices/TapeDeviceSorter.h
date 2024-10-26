#ifndef TAPE_DEVICE_SORTER_H
#define TAPE_DEVICE_SORTER_H

#include "../sort_tape_algorithms/SortOfTapeInterface.h"
#include "TapeDeviceInterface.h"

#include <fstream>
#include <vector>

class SortOfTapeInterface;

/*
 * TapeDeviceSorter -- класс для сортировки элементов ленты, содержащий поля:
 * inputTape_ -- входная лента 
 * outputTape_ -- выходная лента
 * tmpTapeFirst_ -- первая временная входная лента
 * tmpTapeSecond_ -- вторая временная входная лента
 * sortAlgorithm_ -- указатель на алгоритм сортировки ленты
 * delayMove_ -- задержка сдвига ленты влево или вправо
 * delayRewind_ -- задержка перемотки ленты в начало
 * delayIO_ -- задержка на чтение и записи элементов в ленту 
 */
class TapeDeviceSorter : public TapeDeviceInterface {
public:

    /*
     * Конструктор класса принимающий:
     * inputTape -- название файла входной ленты
     * outputTape -- название файла выходной ленты
     * sortAlgorithm -- указатель на класс интерфейса алгоритмов сортировок
     */
    TapeDeviceSorter(const std::string &inputTape, const std::string &outputTape, SortOfTapeInterface *sortAlgorithm);
    
    ~TapeDeviceSorter();
    
    TapeDeviceSorter(const TapeDeviceSorter& other) = delete;
    
    TapeDeviceSorter(TapeDeviceSorter&& other) = delete; 

    TapeDeviceSorter& operator=(const TapeDeviceSorter& other) = delete;

    TapeDeviceSorter& operator=(TapeDeviceSorter&& other) noexcept = delete;

    int readElement(std::fstream &tape) const override;
    
    void writeElement(std::fstream &tape, int val) const override;

    void moveTapeRight(std::fstream &tape) override;

    void moveTapeLeft(std::fstream &tape) override;

    void rewindTape(std::fstream &tape) override;

    void sort();

    std::fstream& getInputTape();

    std::fstream& getOutputTape();

    std::fstream& getTmpTapeFirst();

    std::fstream& getTmpTapeSecond();

    size_t getDelayMove() const;

    size_t getDelayRewind() const;

    size_t getDelayIO() const;

private:
    std::fstream inputTape_;
    std::fstream outputTape_;

    std::fstream tmpTapeFirst_;
    std::fstream tmpTapeSecond_;

    SortOfTapeInterface *sortAlgorithm_;

    size_t delayMove_ = 0;
    size_t delayRewind_ = 0;
    size_t delayIO_ = 0;
};

#endif
