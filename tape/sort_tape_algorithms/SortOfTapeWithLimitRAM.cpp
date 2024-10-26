#include "../exceptions/SortSizeException.h"
#include "SortOfTapeWithLimitRAM.h"

#include <algorithm>

SortOfTapeWithLimitRAM::SortOfTapeWithLimitRAM(const size_t size) {
    if (size < 1) {
        std::string message = "Size of SortOfTapeWithLimitRAM must be greater than 0";
        throw SortSizeException(message);
    }
    data_.resize(size);
}

void SortOfTapeWithLimitRAM::setTapeDevice(TapeDeviceSorter *tapeDevice) {
    tapeDevice_ = tapeDevice;
}

int SortOfTapeWithLimitRAM::readElemAndMoveLeftTape(std::fstream &tape) {
    int val = tapeDevice_->readElement(tape);
    tapeDevice_->moveTapeLeft(tape);
    return val;
}

void SortOfTapeWithLimitRAM::writeElemAndMoveLeftTape(std::fstream &tape, int val) {
    tapeDevice_->writeElement(tape, val);
    tapeDevice_->moveTapeLeft(tape);
}

size_t SortOfTapeWithLimitRAM::fillAndSortData(std::fstream &inputTape) {
    size_t i = 0;
    for (; i < data_.size() && !inputTape.eof(); i++) {
        data_[i] = readElemAndMoveLeftTape(inputTape);
    }
    std::sort(data_.begin(), data_.begin() + i);
    return i;
}

void SortOfTapeWithLimitRAM::writeElemsFromTmpTapeAndDataToTmpTape(std::fstream& inputTmpTape, std::fstream &outputTmpTape, size_t numElemsOfData) {
    int i = 0, valOfInputTmp;
    while (valOfInputTmp = readElemAndMoveLeftTape(inputTmpTape), !inputTmpTape.eof()) {
        if (i >= numElemsOfData) {
            writeElemAndMoveLeftTape(outputTmpTape, valOfInputTmp);
            continue;
        }
        bool isWriteFromTape = 0;
        for (; i < numElemsOfData; i++) {
            if (valOfInputTmp < data_[i]) {
                writeElemAndMoveLeftTape(outputTmpTape, valOfInputTmp);
                isWriteFromTape = 1;
                break;
            } else {
                writeElemAndMoveLeftTape(outputTmpTape, data_[i]);
            }
        }
        if (!isWriteFromTape) {
            writeElemAndMoveLeftTape(outputTmpTape, valOfInputTmp);
        }
    }
    for (; i < numElemsOfData; i++) {
        writeElemAndMoveLeftTape(outputTmpTape, data_[i]);
    }
    tapeDevice_->rewindTape(inputTmpTape);
    tapeDevice_->rewindTape(outputTmpTape);
}

void SortOfTapeWithLimitRAM::writeElemsFromTmpTapeToOutputTape(std::fstream& inputTmpTape, std::fstream &outputTmpTape) {
    while (!inputTmpTape.eof()) {
        int numElems = 0;
        for (int i = 0; (i < data_.size()) && (data_[i] = readElemAndMoveLeftTape(inputTmpTape), !inputTmpTape.eof()); i++, numElems++) {
        }
        for (int i = 0; i < numElems; i++) {
            writeElemAndMoveLeftTape(outputTmpTape, data_[i]);
        }
    }
}

void SortOfTapeWithLimitRAM::sort(std::fstream &inputTape, std::fstream &outputTape) {
    bool firstOrSecondTape = 1;

    while (!inputTape.eof()) {
        
        firstOrSecondTape ^= 1;

        size_t numElems = fillAndSortData(inputTape);
        
        std::fstream& inputTmpTape = firstOrSecondTape ? tapeDevice_->getTmpTapeFirst() : tapeDevice_->getTmpTapeSecond();
        std::fstream& outputTmpTape = !firstOrSecondTape ? tapeDevice_->getTmpTapeFirst() : tapeDevice_->getTmpTapeSecond();

        writeElemsFromTmpTapeAndDataToTmpTape(inputTmpTape, outputTmpTape, numElems);
    }

    std::fstream& inputTmpTape = !firstOrSecondTape ? tapeDevice_->getTmpTapeFirst() : tapeDevice_->getTmpTapeSecond();
    
    writeElemsFromTmpTapeToOutputTape(inputTmpTape, outputTape);
}
