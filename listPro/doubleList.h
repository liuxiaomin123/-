#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST


struct ListNode1
{
	int val;
	ListNode1* pre, *next;
	ListNode1( int x ) : val(x), pre( NULL ), next( NULL ){}
};

class DoubleList
{
public:
	DoubleList()
	{
		head = NULL;
	}

	DoubleList( int a[], int n ){
		head = createList( a, n );
	}

	void printList()
	{
		ListNode1 *cur = head;
		while( cur )
		{
			cout << cur->val << " -> <- ";
			cur = cur->next;
		}
		cout << "NULL" << endl;
	}

	void removeK( int k )
	{
		ListNode1 *dumpHead = new ListNode1(-1);
		dumpHead->next = head;
		head->pre = dumpHead;
		ListNode1 *cur = dumpHead;
		while( k-- && cur )
			cur = cur->next;

		if( cur ){
			if( cur->next ){
				cur->next->pre = cur->pre;
				cur->pre->next = cur->next;
			}
			else
				cur->pre->next = NULL;
		}

		head = dumpHead->next;
		head->pre = NULL;
	}

	// 寻找第一个比 key 大的结点位置，然后将新节点插入到其前面
	void insert( int key )
	{
		ListNode1 * node = new ListNode1( key );
		if( key < head->val ){
			node->next = head;
			head->pre = node;
			head = node;
			return ;
		}

		ListNode1* cur = head;
		while( cur->next )
		{
			if( cur->val > key )
				break;
			cur = cur->next;
		}

		if( cur->next == NULL && cur->val < key )
		{
			cur->next = node;
			node->pre = cur;
		}
		else
		{
			cur->pre->next = node;
			node->pre = cur->pre;
			node->next = cur;
			cur->pre = node;
		}
	}

private:
	ListNode1* head;

	ListNode1* createList( int a[], int& n )
	{
		if( 0 == n )
			return NULL;

		ListNode1* newHead = new ListNode1( a[0] );
		ListNode1* p = newHead;
		for( int i = 1; i < n; ++ i )
		{
			ListNode1* cur = new ListNode1( a[i] );
			p->next = cur;
			cur->pre = p;
			p = p->next;
		}

		return newHead;
	}

	

};

#endif