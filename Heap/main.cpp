#include <iostream>
#include "maxHeap.h"
#include "minHeap.h"
#include "IndexMaxHeap.h"

using namespace std;

template <typename T>
void printArray( T *arr, int n ){
	
	for( int i = 0; i < n; ++i )
		cout << arr[i] << " ";

	cout << endl;
}

int main()
{
	srand(NULL);

	int *t = new int[10];

	for( int i = 0; i < 10; ++i )
		t[i] = rand()%1000;

	cout << "ԭʼ����Ϊ��";
	printArray( t, 10 );

	IndexMaxHeap<int> maxheap( t, 10 );
	MyMinHeap<int> minHeap( t, 10 );
	cout << "����Ԫ�ظ�����" << maxheap.size() << endl
		<< "���ֵΪ��" << maxheap.getMax() << endl
		<< "�����" << endl;
	
	for( int i = 9; i >= 0; --i )
		t[i] = maxheap.extractMax();
	printArray( t, 10 );

	for( int i = 9; i >= 0; --i )
		t[i] = minHeap.extractMin();
	printArray( t, 10 );

	system( "pause" );
	return 0;
}