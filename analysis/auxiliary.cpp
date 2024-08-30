#include <iostream>
#include <vector>
#include <cstdint>

int adjustToMultipleOfFour(int num)
{
    int a = num;
    if (a % 4 != 0)
    {
        a = a + (4 - (a % 4)) % 4;
    }
    return a;
}

#define Getaddress(binaryData, address) *(reinterpret_cast<const int *>(binaryData.data() + address));
