#ifndef MY_INDEXMAXHEAP_H
#define MY_INDEXMAXHEAP_H

#include <cassert>

template <typename Item>
class IndexMaxHeap{
private:
	Item *data; //最大索引堆中的数据
	int *index; //最大索引堆中的索引, indexes[x] = i 表示索引i在x的位置
	int *reverse; //最大索引堆中的反向索引, reverse[i] = x 表示索引i在x的位置
	int count;
	int capacity;

	void shiftUp( int k ){
		index[0] = index[k];

		while( k > 1 && data[index[k/2]] < data[index[0]] ){
			index[k] = index[k/2];
			reverse[index[k]] = k;
			k /= 2;
		}
		index[k] = index[0];
		reverse[index[k]] = k;
	}

	void shiftDown( int k ){
		index[0] = index[k];
		
		while( 2*k <= count ){
			int j = 2*k;
			if( j + 1 <= count && data[index[j+1]] > data[index[j]] )
				++ j;
			if( data[index[0]] >= data[index[j]] )break;

			index[k] = index[j];
			reverse[index[k]] = k;

			k = j;
		}
		index[k] = index[0];
		reverse[index[k]] = k;
	}

public:
	IndexMaxHeap( int capacity ){
		data = new Item[capacity+1];
		index = new int[capacity+1];
		reverse = new int[capacity+1]();

		this->capacity = capacity;
		count = 0;
	}

	IndexMaxHeap( Item t[], int n ){
		data = new Item[n+1];
		index = new int[n+1];
		reverse = new int[n+1]();
		capacity = n;
		count = 0;

		for( int i = 0; i < n; ++i ){
			data[i+1] = t[i];
			++ count;
			index[count] = i+1;
		}

		for( int i = count/2; i >= 1; --i )
			shiftDown(i);
	}

	~IndexMaxHeap(){
		delete[] data;
		delete[] index;
		delete[] reverse;
	}

	int size(){
		return count;
	}

	bool isEmpty(){
		return count == 0;
	}

	void insert( int i, Item val ){
		assert( count + 1 <= capacity );
		assert( i + 1 >= 1  && i + 1 <= capacity );

		i ++; //对用户而言，索引都是从0开始的
		data[i] = val;
		index[count+1] = i;
		reverse[i] = count + 1;
		count ++;

		shiftUp(count);
	}

	Item extractMax(){
		assert( count >= 1 );
		Item res = data[index[1]];
		swap( index[1], index[count] );
		reverse[index[count]] = 0;

		count --;

		if( count ){
			reverse[index[1]] = 1;
			shiftDown(1);
		}
		
		return res;
	}

	Item getMax(){
		assert( count >= 1 );
		return data[index[1]];
	}

	int getMaxIndex(){
		assert( count >= 1 );
		return index[1] - 1;
	}
	
	Item getItem( int i ){
		assert( i + 1 >= 1 && i + 1 <= count );
		return data[i+1];
	}
};

#endif