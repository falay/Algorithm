#include <iostream>
#include "Sponge.h"
#include <string>
using namespace std ;

int main(int argc, char* argv[])
{
	if( argc == 2 ) //default output block size = 512-bit = 64-byte
		SpongeConstruction( argv[1], 512 ) ;
	
	else if( argc == 3 )
		SpongeConstruction( argv[1], atoi(argv[2]) ) ;
	
	else
		cerr << "Invalid usage!\nUsage: ./SHA3 [Input string] [output length]\n" ;		
}