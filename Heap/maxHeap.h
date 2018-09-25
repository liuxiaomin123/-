#ifndef MY_MAXHEAP_H
#define MY_MAXHEAP_H

#include <cassert>

template <typename T>
class MyMaxHeap{
private:
	T *data;//��1��ʼ�洢Ԫ�أ�0��������Ч����
	int capacity;//����
	int count;//��ǰ����Ԫ�ظ���

	void shiftUp( int k ){
		data[0] = data[k];

		while( k > 1 && data[0] > data[k>>1] ){
			data[k] = data[k>>1];
			k >>= 1;
			
		}
		data[k] = data[0];
	}

	void shiftDown( int k ){
		data[0] = data[k];

		while( k<<1 <= count ){
			
			int j = k << 1;
			if( j + 1 <= count && data[j+1] > data[j] )
				j ++;
			if( data[0] >= data[j] )
				break;

			data[k] = data[j];
			k = j;
		}

		data[k] = data[0];
	}

public:
	MyMaxHeap( int capacity){
		data = new T[ capacity + 1 ]();
		this->capacity = capacity;
		count = 0;
	}

	//��һ�����齨�ɴ󶥶�
	MyMaxHeap( T a[], int n ){
		data = new T[n+1]();
		capacity = n;

		for( int i = 0; i < n; ++i )
			data[i+1] = a[i];
		count = n;

		for( int i = count/2; i > 0; --i )
			shiftDown(i);
	}

	~MyMaxHeap(){
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

	T extractMax(){
		assert( count >= 1 );
		T maxVal = data[1];

		swap( data[1], data[count] );
		count --;

		shiftDown( 1 );

		return maxVal;
	}

	T getMax(){
		assert( count > 0 );
		return data[1];
	}
};

#endif