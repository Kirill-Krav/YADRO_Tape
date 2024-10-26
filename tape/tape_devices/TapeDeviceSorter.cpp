#include "../exceptions/OpenFileException.h"
#include "../sort_tape_algorithms/SortOfTapeWithLimitRAM.h"
#include "TapeDeviceSorter.h"

#include <chrono>
#include <thread>

TapeDeviceSorter::TapeDeviceSorter(const std::string &inputTape, const std::string &outputTape, SortOfTapeInterface *sortAlgorithm)
    : sortAlgorithm_(sortAlgorithm)
{
    inputTape_.open(inputTape);
    if (!inputTape_.is_open()) {
        std::string message = "Can't open file " + inputTape;
        throw OpenFileException(message);
    }

    outputTape_.open(outputTape);
    if (!outputTape_.is_open()) {
        std::string message = "Can't open file " + outputTape;
        throw OpenFileException(message);
    }

    tmpTapeFirst_.open("./tmp/tmpFirstTape.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (!tmpTapeFirst_.is_open()) {
        std::string message = "Can't open file ./tmp/tmpFirstTape.txt";
        throw OpenFileException(message);
    }

    tmpTapeSecond_.open("./tmp/tmpSecondTape.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (!tmpTapeFirst_.is_open()) {
        std::string message = "Can't open file ./tmp/tmpFirstTape.txt";
        throw OpenFileException(message);
    }

    std::ifstream config;
    config.open("config.txt");
    if (config.is_open()) {
        std::string key, value;
        while (!config.eof()) {
            config >> key;
            if (config.eof()) {
                break;
            }
            config >> value;
            if (key == "delayIO") {
                delayIO_ = stoi(value);
            } else if (key == "delayMove") {
                delayMove_ = stoi(value);
            } else if (key == "delayRewind") {
                delayRewind_ = stoi(value);
            }
        }
    }

    sortAlgorithm_->setTapeDevice(this);
}

TapeDeviceSorter::~TapeDeviceSorter() {
    inputTape_.close();
    outputTape_.close();
    tmpTapeFirst_.close();
    tmpTapeSecond_.close();
}

int TapeDeviceSorter::readElement(std::fstream &tape) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayIO_));
    int val;
    tape >> val;
    return val;
}

void TapeDeviceSorter::writeElement(std::fstream &tape, int val) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayIO_));
    tape << val << " ";
}

void TapeDeviceSorter::moveTapeRight(std::fstream &tape) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMove_));
}

void TapeDeviceSorter::moveTapeLeft(std::fstream &tape) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMove_));
}

void TapeDeviceSorter::rewindTape(std::fstream &tape) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayRewind_));
    tape.clear();
    tape.seekg(0, std::ios::beg);
}

void TapeDeviceSorter::sort() {
    sortAlgorithm_->sort(inputTape_, outputTape_);
}

std::fstream& TapeDeviceSorter::getInputTape() {
    return inputTape_;
}

std::fstream& TapeDeviceSorter::getOutputTape() {
    return outputTape_;
}

std::fstream& TapeDeviceSorter::getTmpTapeFirst() {
    return tmpTapeFirst_;
}

std::fstream& TapeDeviceSorter::getTmpTapeSecond() {
    return tmpTapeSecond_;
}

size_t TapeDeviceSorter::getDelayMove() const {
    return delayMove_;
}

size_t TapeDeviceSorter::getDelayRewind() const {
    return delayRewind_;
}

size_t TapeDeviceSorter::getDelayIO() const {
    return delayIO_;
}
