#ifndef SORT_OF_TAPE_INTERFACE_H
#define SORT_OF_TAPE_INTERFACE_H

#include "../tape_devices/TapeDeviceSorter.h"

class TapeDeviceSorter;

/*
 * Интерфейс алгоритмов сортировок лент
 */
class SortOfTapeInterface {
public:

    /*
     * setTapeDevice -- привязка к устройству для сортировки лент tapeDevice
     */
    virtual void setTapeDevice(TapeDeviceSorter *tapeDevice) = 0;

    /*
     * sort -- сортировка входной ленты inputTape и вывод результата в выходную ленту outputTape
     */
    virtual void sort(std::fstream &inputTape, std::fstream &outputTape) = 0;
};

#endif
