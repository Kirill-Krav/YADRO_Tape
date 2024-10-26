#ifndef SORT_OF_TAPE_WITH_LIMIT_RAM_H
#define SORT_OF_TAPE_WITH_LIMIT_RAM_H

#include "SortOfTapeInterface.h"

/*
 * SortOfTapeWithLimitRAM -- алгоритм сортировки лент с ограниченной оперативной памятью
 * data_ -- вектор для хранения данных
 * tapeDevice_ -- указатель на устройство для сортировки лент
 */
class SortOfTapeWithLimitRAM : public SortOfTapeInterface {
public:

    /*
     * Конструктор принимающий:
     * size -- максимальное количество элементов для хранения данных
     */
    SortOfTapeWithLimitRAM(const size_t size);

    ~SortOfTapeWithLimitRAM() = default;

    SortOfTapeWithLimitRAM(const SortOfTapeWithLimitRAM& other) = delete;
    
    SortOfTapeWithLimitRAM(SortOfTapeWithLimitRAM&& other) = delete; 

    SortOfTapeWithLimitRAM& operator=(const SortOfTapeWithLimitRAM& other) = delete;

    SortOfTapeWithLimitRAM& operator=(SortOfTapeWithLimitRAM&& other) noexcept = delete;

    void setTapeDevice(TapeDeviceSorter *tapeDevice) override;

    void sort(std::fstream &inputTape, std::fstream &outputTape) override;

private:

    /*
     * чтение элемента с ленты tape и сдвиг влево
     * возвращает проитанный элемент
     */
    int readElemAndMoveLeftTape(std::fstream &tape);

    /*
     * запись элемента val в ленту tape и сдвиг влево
     */
    void writeElemAndMoveLeftTape(std::fstream &tape, int val);

    /*
     * заполнение вектора data_ с ленты inputTape
     */
    size_t fillAndSortData(std::fstream &inputTape);

    /*
     * Запись во временную ленту outputTmpTape в неубывающем порядке с временной ленты inputTmpTape и вектора data_
     * numElemsOfData -- текущее количество элементов data_
     */
    void writeElemsFromTmpTapeAndDataToTmpTape(std::fstream& inputTmpTape, std::fstream &outputTmpTape, size_t numElemsOfData);

    /*
     * Запись элементов в выходную ленту outputTmpTape с временной ленты tmpTape
     */
    void writeElemsFromTmpTapeToOutputTape(std::fstream& tmpTape, std::fstream &outputTmpTape);

    std::vector<int> data_;

    TapeDeviceSorter *tapeDevice_;
};

#endif
