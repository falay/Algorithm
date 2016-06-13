#ifndef INTERNAL_FUN_H
#define INTERNAL_FUN_H

#include <string>
#include <bitset>

#define stateSize 1600
using std::string ;
using std::bitset ;

typedef bitset<stateSize> Binary ;

Binary internalFun(Binary stateVar) ;
Binary roundFun(Binary stateVar, bitset<64> singleRC) ;
void constructRC() ;
int Mod(int n,const int r) ;
void UpdateState(auto& willUpdate, auto& Latest) ;


#endif 