#include <gtest/gtest.h>

#include "../tape/sort_tape_algorithms/SortOfTapeWithLimitRAM.h"
#include "../tape/tape_devices/TapeDeviceSorter.h"
#include "../tape/exceptions/OpenFileException.h"
#include "../tape/exceptions/SortSizeException.h"

std::vector<int> tape = {11, 62, 23, 45, 24, 96, 81, 53, 92, 53, 76, 23, 54, 39, 70, 36, 87, 7, 42, 95, 95, 12, 93, 26, 30};
std::vector<int> sortedTape = {7, 11, 12, 23, 23, 24, 26, 30, 36, 39, 42, 45, 53, 53, 54, 62, 70, 76, 81, 87, 92, 93, 95, 95, 96};

/*
 * Создание файлов для входной и выходной ленты
 * а также заполнение входной ленты
 */
void createInputAndOutputTape() {
    std::ofstream fout("inputTapeTest.txt");
    for (int i = 0; i < tape.size() - 1; i++) {
        fout << tape[i] << " ";
    }
    fout << tape.back();
    fout.close();
    fout.open("outputTapeTest.txt");
    fout.close();
}


TEST(TapeDevice, UnableOpenFileOfInputTape) {
    /*
     * Проверка на неудачное открытие файла входной ленты
     * Ожидаем получить исключение открытие файла
     */
    createInputAndOutputTape();

    std::string inputTape = "errorInputNameTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";

    std::string message = "Can't open file " + inputTape;
    EXPECT_THROW(TapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10)), OpenFileException);
}

TEST(TapeDevice, UnableOpenFileOfOutputTape) {
    /*
     * Проверка на неудачное открытие файла выходной ленты
     * Ожидаем получить исключение открытие файла
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "errorOutputNameTapeTest.txt";

    std::string message = "Can't open file " + outputTape;
    EXPECT_THROW(TapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10)), OpenFileException);
}

TEST(TapeDevice, CheckDelaysWithConfig) {
    /*
     * Проверка чтения конфига задержек
     * Ожидаем получить такие же значения, которые задаются в конфиге
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";

    std::ofstream config("config.txt", std::fstream::trunc);
    config << "delayIO 123\n";
    config << "delayMove 456\n";
    config << "delayRewind 789";
    config.close();

    TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10));

    EXPECT_EQ(tapeDeviceSorter.getDelayIO(), 123u);
    EXPECT_EQ(tapeDeviceSorter.getDelayMove(), 456u);
    EXPECT_EQ(tapeDeviceSorter.getDelayRewind(), 789u);
    
    remove("config.txt");
}

TEST(TapeDevice, CheckDelaysWithoutConfig) {
    /*
     * Проверка задержек при отсутствии файла конфига
     * Ожидаем, что значения задержек будут равны 0
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";

    TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10));

    EXPECT_EQ(tapeDeviceSorter.getDelayIO(), 0u);
    EXPECT_EQ(tapeDeviceSorter.getDelayMove(), 0u);
    EXPECT_EQ(tapeDeviceSorter.getDelayRewind(), 0u);
}

TEST(TapeDevice, TestReadElement) {
    /*
     * Проверка метода readElement класса TapeDeviceSorter
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";

    TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10));

    std::vector<int> readResponse;

    std::fstream &tapeInput = tapeDeviceSorter.getInputTape();

    while (!tapeInput.eof()) {
        int val = tapeDeviceSorter.readElement(tapeInput);
        readResponse.push_back(val);
    }

    EXPECT_EQ(readResponse, tape);
}

TEST(TapeDevice, TestWriteElement) {
    /*
     * Проверка метода writeElement класса TapeDeviceSorter
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";
    
    {
        TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10));

        std::fstream &tapeOutput = tapeDeviceSorter.getOutputTape();

        for (int i = 0; i < tape.size(); i++){
            tapeDeviceSorter.writeElement(tapeOutput, tape[i]);
        }
    }

    std::ifstream fin(outputTape);
    std::vector<int> writeResponse;
    int val;

    while (fin >> val, !fin.eof()) {
        writeResponse.push_back(val);
    }
    
    EXPECT_EQ(writeResponse, tape);
}

TEST(SortAlgorithm, TestSortSizeException) {
    /*
     * Проверка на неправильный размер данных для сортировки
     * Ожидаем получить исключение размера выделенных данных для сортировки
     */
    EXPECT_THROW(SortOfTapeWithLimitRAM(0), SortSizeException);
}

TEST(SortAlgorithm, TestSortAlgorithmWithLimit1) {
    /*
     * Проверка сортировки с ограничением в 1 элемент
     * Ожидаем получить правильно отсортированную ленту
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";
    
    {
        TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(1));
        tapeDeviceSorter.sort();
    }

    std::ifstream fin(outputTape);
    std::vector<int> response;
    int val;

    while (fin >> val, !fin.eof()) {
        response.push_back(val);
    }

    EXPECT_EQ(response, sortedTape);
}

TEST(SortAlgorithm, TestSortAlgorithmWithLimit10) {
    /*
     * Проверка сортировки с ограничением в 10 элементов (меньше чем задано элементов в ленте)
     * Ожидаем получить правильно отсортированную ленту
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";
    
    {
        TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(10));
        tapeDeviceSorter.sort();
    }

    std::ifstream fin(outputTape);
    std::vector<int> response;
    int val;

    while (fin >> val, !fin.eof()) {
        response.push_back(val);
    }

    EXPECT_EQ(response, sortedTape);
}

TEST(SortAlgorithm, TestSortAlgorithmWithLimit25) {
    /*
     * Проверка сортировки с ограничением в 25 элемент (равное количество элементов в ленте)
     * Ожидаем получить правильно отсортированную ленту
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";
    
    {
        TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(25));
        tapeDeviceSorter.sort();
    }

    std::ifstream fin(outputTape);
    std::vector<int> response;
    int val;

    while (fin >> val, !fin.eof()) {
        response.push_back(val);
    }

    EXPECT_EQ(response, sortedTape);
}

TEST(SortAlgorithm, TestSortAlgorithmWithLimit50) {
    /*
     * Проверка сортировки с ограничением в 50 элементов (больше чем задано элементов в ленте)
     * Ожидаем получить правильно отсортированную ленту
     */
    createInputAndOutputTape();

    std::string inputTape = "inputTapeTest.txt";
    std::string outputTape = "outputTapeTest.txt";
    
    {
        TapeDeviceSorter tapeDeviceSorter(inputTape, outputTape, new SortOfTapeWithLimitRAM(50));
        tapeDeviceSorter.sort();
    }

    std::ifstream fin(outputTape);
    std::vector<int> response;
    int val;

    while (fin >> val, !fin.eof()) {
        response.push_back(val);
    }

    EXPECT_EQ(response, sortedTape);
}
