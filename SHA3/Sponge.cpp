#include <iostream>
#include <string>
#include <string.h>
#include "Sponge.h"
#include "InternalFun.h"

using namespace std;

#define bitRate   576 
#define capacity  1024




void SpongeConstruction(string inputString, int outputLen) 
{
	// Transform the input string into binary bits
	string Name = inputString ;
	BinaryTransfer( inputString ) ;
						
	// Padding using Multirate
	vector< Binary > Message = Padding( inputString ) ; 	
	
	//Initialize the state variable
	Binary stateVar ;
		
	// Absorbing phase
	for(int i=0; i<Message.size(); i++)
	{	
		stateVar ^= Message[i] ;				
		stateVar  = internalFun( stateVar ) ;

	}
	
	// Squeezing phase
	string hashVal = stateVar.to_string().substr(0, bitRate)  ;
	while( hashVal.length() < outputLen )
	{
		stateVar = internalFun( stateVar ) ;	
		hashVal += stateVar.to_string().substr(0, bitRate) ;	
	}	
	
	// Print the hash value to the stdout
	PrintHex( hashVal.substr(0, outputLen) ) ;
}


void BinaryTransfer(string& inputString)
{
	string binary = "" ;
	
	for(int i=0; i<inputString.length(); i++)
	{
		for(int k=7; k>=0; k--)
			if( ((inputString[i] >> k) & 0x01) )
				binary += "1" ;
			else
				binary += "0" ;
	}	
	
	inputString = binary ;
}



vector< Binary > Padding(string inputString) 
{
	vector<Binary> Message ;
	
	int numOfBits = inputString.length() ;
	string multiPadding = "1" ;
	
	
	/*** Multi Padding ***/
	int extraLen = (bitRate - numOfBits % bitRate) ;
	
	
	if( extraLen > 1 )
	{	
		for(int i=1; i<=extraLen-2; i++ )
			multiPadding += "0" ;
		
		multiPadding += "1" ;
	}	
	inputString += multiPadding ;

	
	/*** Input Parsing ***/	
	for(int i=0; i<inputString.length(); i+=bitRate)
	{
		string Append(capacity, '0') ;
		Binary tmpBin( inputString.substr(i, bitRate) + Append ) ;
		Message.push_back( tmpBin ) ;
	}	
		
	return Message ;		
}


/*** Print the hash value in hex ***/
void PrintHex(string hashVal) 
{
	
	for(int i=0; i<hashVal.length(); i+=4)
	{
		string Ahex = hashVal.substr(i, 4) ; 
		int Val = 0 ;
		
		for(int k=0; k<4; k++)
			if( Ahex[k]-'0' )	
				Val += (1 << (3-k)) ;
		
		if( Val < 10 )	cout << Val ;
		else	cout << (char)(Val+55) ;			
	}		
}
