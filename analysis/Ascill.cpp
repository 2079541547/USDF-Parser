#include <iostream>
#include <vector>
#include <cstdint>
#include "auxiliary.cpp"
#include <fstream>

namespace Ascill
{
    struct GameObjectData
    {
        int Offset;
        int m_FileID;
        int m_PathID;
        std::string m_Name;
    };

    // 解析函数
    // 函数用于解析二进制数据并打印/写入文件
    void parseBinaryDataAndWriteToFile(const std::vector<uint8_t> &binaryData, const std::string &outputFilePath)
    {
        std::ofstream outputFile(outputFilePath, std::ios::app); // 以追加模式打开文件

        // 使用reinterpret_cast直接读取4字节的整数值
        int fileID = Getaddress(binaryData, 4);
        int pathID = Getaddress(binaryData, 8);

        int fileID_1 = Getaddress(binaryData, 12);
        int pathID_1 = Getaddress(binaryData, 16);

        int nameLength = Getaddress(binaryData, 28);

        // 从数据中提取字符串
        std::string name(reinterpret_cast<const char *>(binaryData.data() + 32), nameLength);

        // 更新偏移量
        int offset = 32 + adjustToMultipleOfFour(nameLength);
        std::cout << "offset: " << offset << std::endl;

        int fileID_2 = Getaddress(binaryData, offset + 4);
        int pathID_2 = Getaddress(binaryData, offset + 8);

        int m_VersionLength = Getaddress(binaryData, offset + 20); // 获取版本号的长度

        std::string m_Version(reinterpret_cast<const char *>(binaryData.data() + offset + 24), m_VersionLength);
        std::cout << "m_Version: " << m_Version << std::endl;

        offset += adjustToMultipleOfFour(m_VersionLength) + 24; // 更新偏移
        std::cout << "offset: " << offset << std::endl;         // 打印偏移

        int m_SourceFontFileGUIDLength = Getaddress(binaryData, offset);
        std::string m_SourceFontFileGUID(reinterpret_cast<const char *>(binaryData.data() + offset + 4), m_SourceFontFileGUIDLength);

        offset += adjustToMultipleOfFour(m_SourceFontFileGUIDLength) + 4;
        std::cout << "offset: " << offset << std::endl; // 打印偏移

        int fileID_3 = Getaddress(binaryData, offset);
        int pathID_3 = Getaddress(binaryData, offset + 4);

        int m_FamilyNameLength = Getaddress(binaryData, offset + 20);
        std::string m_FamilyName(reinterpret_cast<const char *>(binaryData.data() + offset + 24), m_FamilyNameLength);

        offset += adjustToMultipleOfFour(m_FamilyNameLength) + 24; // 更新偏移
        std::cout << "offset: " << offset << std::endl;            // 打印偏移

        int m_StyleNameLength = Getaddress(binaryData, offset);
        std::string m_StyleName(reinterpret_cast<const char *>(binaryData.data() + offset + 4), m_StyleNameLength);

        offset += adjustToMultipleOfFour(m_StyleNameLength) + 4 + 6680; // 更新偏移
        std::cout << "offset: " << offset << std::endl;            // 打印偏移

        int fileID_4 = Getaddress(binaryData, offset);
        int pathID_4 = Getaddress(binaryData, offset + 4);

        offset +=  88 + 2624; // 更新偏移
        std::cout << "offset: " << offset << std::endl;            // 打印偏移

        int fileID_5 = Getaddress(binaryData, offset);
        int pathID_5 = Getaddress(binaryData, offset + 4);

        offset += 48; // 更新偏移
        std::cout << "offset: " << offset << std::endl;            // 打印偏移

        int m_SourceFontFileGUIDLength_1 = Getaddress(binaryData, offset);
        std::string m_SourceFontFileGUID_1(reinterpret_cast<const char *>(binaryData.data() + offset + 4), m_SourceFontFileGUIDLength_1);

        // 打印信息
        std::cout << "m_FileID: " << fileID << std::endl;
        std::cout << "m_PathID: " << pathID << std::endl;
        std::cout << "m_FileID: " << fileID_1 << std::endl;
        std::cout << "m_PathID: " << pathID_1 << std::endl;
        std::cout << "m_Name: " << name << std::endl;
        std::cout << "m_FileID: " << fileID_2 << std::endl;
        std::cout << "m_PathID: " << pathID_2 << std::endl;
        std::cout << "m_SourceFontFileGUID: " << m_SourceFontFileGUID << std::endl;
        std::cout << "m_FileID: " << fileID_3 << std::endl;
        std::cout << "m_PathID: " << pathID_3 << std::endl;
        std::cout << "m_FamilyName: " << m_FamilyName << std::endl;
        std::cout << "m_StyleName: " << m_StyleName << std::endl;
        std::cout << "m_FileID: " << fileID_4 << std::endl;
        std::cout << "m_PathID: " << pathID_4 << std::endl;
        std::cout << "m_FileID: " << fileID_5 << std::endl;
        std::cout << "m_PathID: " << pathID_5 << std::endl;
        std::cout << "m_SourceFontFileGUID: " << m_SourceFontFileGUID_1 << std::endl;


        // 写入文件
        outputFile << "此工具获取的不一定正确，GUID是20个字节长度的，即20个字符" << "\n";
        outputFile << "m_FileID: " << fileID << "\n";
        outputFile << "m_PathID: " << pathID << "\n";
        outputFile << "m_FileID: " << fileID_1 << "\n";
        outputFile << "m_PathID: " << pathID_1 << "\n";
        outputFile << "m_Name: " << name << "\n";
        outputFile << "m_FileID: " << fileID << "\n";
        outputFile << "m_PathID: " << pathID << "\n";
        outputFile << "m_FileID: " << fileID_1 << "\n";
        outputFile << "m_PathID: " << pathID_1 << "\n";
        outputFile << "m_Name: " << name << "\n";
        outputFile << "m_FileID: " << fileID_2 << "\n";
        outputFile << "m_PathID: " << pathID_2 << "\n";
        outputFile << "m_SourceFontFileGUID: " << m_SourceFontFileGUID << "\n";
        outputFile << "m_FileID: " << fileID_3 << "\n";
        outputFile << "m_PathID: " << pathID_3 << "\n";
        outputFile << "m_FamilyName: " << m_FamilyName << "\n";
        outputFile << "m_StyleName: " << m_StyleName << "\n";
        outputFile << "m_FileID: " << fileID_4 << "\n";
        outputFile << "m_PathID: " << pathID_4 << "\n";
        outputFile << "m_FileID: " << fileID_5 << "\n";
        outputFile << "m_PathID: " << pathID_5 << "\n";
        outputFile << "m_SourceFontFileGUID: " << m_SourceFontFileGUID_1 << "\n";

        outputFile.close(); // 关闭文件
    }

}
