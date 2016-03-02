// This program is a HeapSort practice,
// including building a Max heap and sort the array with heap sort


#include <iostream>
#include <time.h>
using namespace std ;



void Swap(int& A, int& B)
{
	int Tmp = A ;
	A = B ;
	B = Tmp ;
}

// Build the Max Heap of subtree rooted at index i (To fill the C++ index convention)
// e.g: Array[i-1] is in index i
void MaxHeapify(int* Array, int i, int Length)
{
	int Largest = i;
	int RightChild = i * 2 + 1 ;
	int LeftChild  = i * 2  ;
		
	if( LeftChild <= Length ) // Left child exists	
		if( i <= Length && Array[i-1] < Array[LeftChild-1] )	
			Largest = LeftChild ;
	
	if( RightChild <= Length ) // Right child exists
		if( i <= Length && Array[Largest-1] < Array[RightChild-1] )
			Largest = RightChild ;
		
	if( Largest != i )
	{	
		Swap( Array[i-1], Array[Largest-1] ) ;
		MaxHeapify(Array, Largest, Length) ;		
	}
}	


void BuildMaxHeap(int* Array, int Length)
{
	for(int i=Length/2; i>=1; i--)
		MaxHeapify(Array, i, Length) ;
}

void HeapSort(int* Array, int Length)
{
	BuildMaxHeap(Array, Length) ;
	
	for(int i=Length; i>=2; i--)
	{
		Swap(Array[0], Array[i-1]) ;
		MaxHeapify(Array, 1, i-1) ;
	}	
}


void PrintArray(int* Array, int Length, bool IsSorted)
{
	if( !IsSorted )
		cout << "**************The oringinal array is**************\n" ;
	else
		cout << "**************The sorted array is**************\n" ;
	
	for(int i=0; i<Length; i++)
		cout << Array[i] <<" " ;
	cout << endl ;
}



void HeapSortDriver(int NumOfTest)
{
	// Generating random NumOfTest sequences of numbers between 1 ~ 1000 (unsorted)
	int** HeapTest = new int* [NumOfTest] ;
	
	srand( time(NULL) ) ;
	for(int i=0; i<NumOfTest; i++)
	{		
		int Length = rand() % 100 + 100 ; // at most 199 numbers per test 
		HeapTest[i] = new int [Length] ;
		
		for(int j=0; j<Length; j++)
			HeapTest[i][j] = rand() % 1000 + 1 ;

		cout << "Test case " << i+1 << endl ;
		PrintArray(HeapTest[i], Length, false) ;
		HeapSort( HeapTest[i], Length ) ;	
		PrintArray(HeapTest[i], Length, true) ;
		cout << endl ;
	}
			
}
	
	

int main(int argc, char* argv[])
{
	
	if( argc == 2 )
		HeapSortDriver( atoi(argv[1]) ) ;
	else
		cerr << "Usage: ./HeapSort [NumOfTest]\n" ;	
} 