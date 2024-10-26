#ifndef TAPE_DEVICE_INTERFACE_H
#define TAPE_DEVICE_INTERFACE_H

#include <string>

/*
 * Интерфейс устройств для работы с лентами
 */
class TapeDeviceInterface {
public:

    /*
     * readElement -- чтение элемента с ленты tape
     * возвращает прочитанное элемент
     */
    virtual int readElement(std::fstream &tape) const = 0;
    
    /*
     * writeElement -- запись элемента val в ленту tape
     */
    virtual void writeElement(std::fstream &tape, int val) const = 0;

    /*
     * moveTapeRight -- сдвиг ленты tape вправо
     */
    virtual void moveTapeRight(std::fstream &tape) = 0;

    /*
     * moveTapeLeft -- сдвиг ленты tape влево
     */
    virtual void moveTapeLeft(std::fstream &tape) = 0;

    /*
     * rewindTape -- перемотка ленты tape в начало
     */
    virtual void rewindTape(std::fstream &tape) = 0;
};

#endif
