#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include "analysis/Ascill.cpp"

// 从文件读取二进制数据
std::vector<uint8_t> readFileToVector(const std::string &filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate); // 以二进制模式打开文件，并移动到文件末尾
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::streamsize fileSize = file.tellg(); // 获取文件大小
    file.seekg(0, std::ios::beg);            // 返回到文件开头

    std::vector<uint8_t> contents(static_cast<size_t>(fileSize));   // 创建一个足够大的向量
    file.read(reinterpret_cast<char *>(contents.data()), fileSize); // 读取文件内容到向量

    if (!file)
    {
        throw std::runtime_error("Failed to read file: " + filePath);
    }

    return contents;
}

int main()
{

    std::string inputString;
    int inputInt;

    std::cout << "请输入路径: ";
    std::getline(std::cin, inputString);

    std::cout << "1. Ascill" << std::endl;

    std::cout << "配置类型: ";
    std::cin >> inputInt;

    try
    {
        std::vector<uint8_t> binaryData = readFileToVector(inputString);

        Ascill::GameObjectData data;
        switch (inputInt)
        {
        case 1:
            Ascill::parseBinaryDataAndWriteToFile(binaryData, "SDF-Output.txt");
            break;

        default:
            break;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
