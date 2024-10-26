#include "sort_tape_algorithms/SortOfTapeWithLimitRAM.h"
#include "tape_devices/TapeDeviceSorter.h"

#include <iostream>

int main(int argc, char *argv[]){
    if(argc != 3){
        std::cerr << "Wrong number of arguments: [program_name] [file_of_input_tape] [file_of_output_tape]" << std::endl;
        return -1;
    }
    try{
        SortOfTapeWithLimitRAM* sortAlgorithm = new SortOfTapeWithLimitRAM(10);
        TapeDeviceSorter tapeDeviceSorter(argv[1], argv[2], sortAlgorithm);
        tapeDeviceSorter.sort();
    } catch (std::exception &ex) {
        std::cout << ex.what();
        return -1;
    }
    return 0;
}
