#include "../intelhex_class/intelhexclass.h"
#include <iostream>
#include <fstream>
#include <vector>

// Create a variable for the intel hex data
intelhex hexclass;

std::vector<uint8_t> getPayloadBuf(uint32_t payload_len)
{
    std::vector<uint8_t> payload_buf;
    return payload_buf;
}

bool openHexFile(char* fileInput)
{
    // Create an input stream
    std::ifstream intelHexInput;
    intelHexInput.open(fileInput, std::ios::in);
    if(!intelHexInput.good())
	{
    	std::cerr << "Error: couldn't open " <<fileInput << std::endl;
    	return false;
	}
    cout << "File opened: " << fileInput << endl;

    /* Decode both files                                                      */
    intelHexInput >> hexclass;

    /* Check for errors or warnings                                           */
    if ((hexclass.getNoWarnings() || hexclass.getNoErrors()) != 0)
    {
        std::cerr << "File " << fileInput << " contained errors or warnings." << std::endl;
        return false;
    }

    /* Set start addresses */
    hexclass.begin();

    unsigned long startAddr, endAddr;
    if(!hexclass.startAddress(&startAddr))
    {
        std::cerr << "Error: couldn't get start address" << std::endl;
        return false;
    }
    if(!hexclass.endAddress(&endAddr))
    {
        std::cerr << "Error: couldn't get end address" << std::endl;
        return false;
    }
    cout << "Start address: 0x" << std::hex << startAddr << endl;
    cout << "End address: 0x" << std::hex << endAddr << endl;
    cout << "Data length: 0x" << std::hex << hexclass.size() << endl;
}
int main(int argc, char const *argv[])
{
    std::uint32_t payload_len = 512u;
    char* fileInput = "test.hex";
    std::vector<uint8_t> payload_buf;
    openHexFile(fileInput);
    // print start address
    cout << "Start address: 0x" << std::hex << hexclass.currentAddress() << endl;

    unsigned char tempdata = 0; 
    // for (uint64_t i = 0; i < payload_len; i++)
    // {
    //     hexclass.getData(&tempdata);
    //     payload_buf.push_back(tempdata);
    //     ++hexclass;
    // }
    while (hexclass.endOfData() == false)
    {
        hexclass.getData(&tempdata);
        payload_buf.push_back(tempdata);
        if ((hexclass.currentAddress()+1) != (++hexclass).currentAddress())
        {
            cout << "Now is new sector. Current Address: 0x" << std::hex << hexclass.currentAddress() << endl;
        }
    }

    // print end address
    cout << "End address: 0x" << std::hex << hexclass.currentAddress() - 1 << endl;

    return 0;
}
