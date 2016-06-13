#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "InternalFun.h"
using namespace std ;



bitset<64> RC[24] = 
{ 
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808A,
	0x8000000080008000,
	0x000000000000808B,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008A,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000A,
	0x000000008000808B,
	0x800000000000008B,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800A,
	0x800000008000000A,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008
};





const int Rotation[5][5] =
{ 
    {0,36,3,41,18},
    {1,44,10,45,2},
    {62,6,43,15,61},
    {28,55,25,21,56},
    {27,20,39,8,14}
};
 
 

 
 
Binary internalFun(Binary stateVar) 
{
	
	for(int i=0; i<24; i++)
		stateVar = roundFun( stateVar, RC[i] ) ;
	
	return stateVar ;
}


/** Specail mod : compute n % r **/
int Mod(int n, const int r)
{
	if( n >= 0 )
		return n % r ;
	else
	{
		while( n < 0 )
			n += r ;
		return n ;
	}	
}


void UpdateState(auto& willUpdate, auto& Latest)
{
	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
		{		
			willUpdate[x][y] = Latest[x][y] ;
			Latest[x][y] = 0 ;
		}	
}

/*** Round function is modified in MSHA-3 ***/
Binary roundFun(Binary stateVar, bitset<64> singleRC)
{

	/*** Bits mapping ***/
	bitset<64> a[5][5] ;	

	int indexState = 1599 ;
	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
			for(int z=0; z<64; z++)
				a[x][y][z] = (stateVar[indexState--] == 1) ;
	
	/** Reserved for a : avoid fast updating **/
	bitset<64> updateA[5][5] ;	

	/*** Theta ***/
	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
			for(int z=0; z<64; z++)
			{
				// Summation of index y
				bitset<1> temp1, temp2 ;
				for(int i=0; i<5; i++)
				{	
					temp1 ^= ( a[Mod(x-1, 5)][i][z] == 1 ) ;	
					temp2 ^= ( a[Mod(x+1, 5)][i][Mod(z-1, 64)] == 1)  ;
				}
				
				updateA[x][y][z] = a[x][y][z] ^ ( (temp1 ^ temp2) == 1 );
			}	
	UpdateState(a, updateA) ;
	

	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
			for(int z=0; z<64; z++)	
			updateA[x][y][z] = a[x][y][Mod(z-Rotation[x][y], 64)] ;

	UpdateState(a, updateA) ;

	
	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
			for(int z=0; z<64; z++)	
				updateA[y][(2*x+3*y)%5][z] = a[x][y][z] ;
				
	UpdateState(a, updateA) ;
	

	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
			for(int z=0; z<64; z++)	
				updateA[x][y][z] = a[x][y][z] ^ (~a[(x+1)%5][y][z]) & a[(x+2)%5][y][z] ;
			
	UpdateState(a, updateA) ;
	
	
	string revRC = singleRC.to_string() ;
	reverse(revRC.begin(), revRC.end()) ;
	bitset<64> revSingle(revRC) ;
	a[0][0] ^= revSingle ;

	
		
	/*** Recover to binary string ***/
	string newState = "" ;
	for(int y=0; y<5; y++)
		for(int x=0; x<5; x++)
		{
			string revTmp = a[x][y].to_string() ;	
			reverse(revTmp.begin(), revTmp.end()) ;		
			newState += revTmp ;	
		}	
			
	return Binary(newState) ;		
}
