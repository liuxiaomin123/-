#ifndef MY_MinHEAP_H
#define MY_MinHEAP_H

#include <cassert>

template <typename T>
class MyMinHeap{
private:
	T *data;//从1开始存储元素，0处不放有效内容
	int capacity;//容量
	int count;//当前堆中元素个数

	void shiftUp( int k ){
		data[0] = data[k];

		while( k > 1 && data[0] < data[k>>1] ){
			data[k] = data[k>>1];
			k >>= 1;

		}
		data[k] = data[0];
	}

	void shiftDown( int k ){
		data[0] = data[k];

		while( k<<1 <= count ){

			int j = k << 1;
			if( j + 1 <= count && data[j+1] < data[j] )
				j ++;
			if( data[0] <= data[j] )
				break;

			data[k] = data[j];
			k = j;
		}

		data[k] = data[0];
	}

public:
	MyMinHeap( int capacity){
		data = new T[ capacity + 1 ];
		this->capacity = capacity;
		count = 0;
	}

	//将一个数组建成小顶堆
	MyMinHeap( T a[], int n ){
		data = new T[n+1];
		capacity = n;

		for( int i = 0; i < n; ++i )
			data[i+1] = a[i];
		count = n;

		for( int i = count/2; i > 0; --i )
			shiftDown(i);
	}

	~MyMinHeap(){
		delete[] data;
	}

	int size(){
		return count;
	}

	bool isEmpty(){
		return count == 0;
	}

	void insert( T val ){
		assert( count + 1 <= capacity );
		data[++count] = val;

		shiftUp(count);
	}

	T extractMin(){
		assert( count >= 1 );
		T MinVal = data[1];

		swap( data[1], data[count] );
		count --;

		shiftDown( 1 );

		return MinVal;
	}

	T getMin(){
		assert( count > 0 );
		return data[1];
	}
};

#endif