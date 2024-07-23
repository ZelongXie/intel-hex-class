#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "../intelhex_class/intelhexclass.h"

using namespace std;

char *program_name;

// Usage for this program
void usage()
{
    cerr << "Usage is " << program_name <<
                 " [file]" << " [file]" << endl;
    exit (EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    // Create an input stream
	std::ifstream intelHexInput;
	
	// Create a string to store lines of Intel Hex info
	std::string intelHexLine;
	
	// Create a variable of the class we are testing
	intelhex classTest;
	
	// Make class verbose
	classTest.verboseOn();
	
	// Output carriage return with new line
	classTest.carriageReturnOn();
	
	// Output hex values in lower case
	classTest.lowerCaseOn();
	
	// The program name is the first argument - save for later use
	program_name = argv[0];

	// Make sure there are only <command> and 1 x <file> arguments	
	if(argc != 2) {
    	usage();
    }
    	
	intelHexInput.open(argv[1], ifstream::in);
	
	if(!intelHexInput.good())
	{
    	std::cerr << "Error: couldn't open " << argv[1] << std::endl;
    	usage();
	}
	
    cout << "Running IntelHEX Class Test" << endl;
    
    intelHexInput >> classTest;
    
    cout << "Final address is 0x" << setw(2) << setfill('0') << uppercase << hex << classTest.currentAddress() << endl;

    cout << "File contained " << classTest.getNoWarnings() << " warnings and "
         << classTest.getNoErrors() << " errors." << endl;
	unsigned char tempdata = 0;

	classTest.getData(&tempdata);
    cout<<"Data is 0x"<<setw(2) << setfill('0') << uppercase << hex<<tempdata<<endl;
    while (classTest.getNoErrors() > 0)
    {
        string message;
        
        classTest.popNextError(message);
        
        cout << message << endl;
    }
    
    while (classTest.getNoWarnings() > 0)
    {
        string message;
        
        classTest.popNextWarning(message);
        
        cout << message << endl;
    }

    return(0);
}

