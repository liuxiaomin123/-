#include <iostream>
#include "singeList.h"
#include "doubleList.h"
#include "mergeList.h"

using namespace std;

ListNode * createList( int a[], int n ){
	if( 0 == n )
		return NULL;

	ListNode *head = new ListNode( a[0] );
	ListNode *curNode = head;

	for( int i = 1; i < n; ++i ){
		curNode->next = new ListNode( a[i] );
		curNode = curNode->next;
	}

	return head;
}

ListNode* reverse( ListNode* head )
{
	ListNode* cur= head, *pre = NULL;
	if( head == NULL || head->next == NULL )
		return head;
	while( cur )
	{
		ListNode *temp = cur->next;
		cur->next= pre;
		pre = cur;
		cur = temp;
	}

	return pre;
}

ListNode* merge( ListNode* one, ListNode* two )
{
	ListNode* cur = NULL;
	ListNode* p1 = one, *p2 = two;
	if( p1->val < p2->val )
	{
		ListNode* post = p1->next;
		p1->next = cur;
		cur = p1;
		p1 = post;
	}
	else if( p1->val == p2->val )
	{
		ListNode* post = p1->next;
		p1->next = cur;
		cur = p1;
		p1 = post;
		p2 = p2->next;
	}
	else{
		ListNode* post = p2->next;
		p2->next = cur;
		cur = p2;
		p2 = post;
	}

	while( p1 && p2 )
	{
		if( p1->val < p2->val ){
			if( cur->val != p1->val ){
				ListNode *post = p1->next;
				p1->next = cur;
				cur = p1;
				p1 = post;
			}
			else{
				p1 = p1->next;
			}

		}
		else if ( p1->val == p2->val ){
			if( cur->val != p1->val ){
				ListNode *post = p1->next;
				p1->next = cur;
				cur = p1;
				p1 = post;
				p2 = p2->next;
			}
			else{
				p1 = p1->next;
			} 
		}
		else{
			if( cur->val != p2->val ){
				ListNode *post = p2->next;
				p2->next = cur;
				cur = p2;
				p2 = post;
			}
			else{
				p2 = p2->next;
			}

		}
	}

	while( p1 )
	{
		ListNode *post = p1->next;
		p1->next = cur;
		cur = p1;
		p1= post;
	}

	while( p2 )
	{
		ListNode *post = p2->next;
		p2->next = cur;
		cur = p2;
		p2 = post;
	}

	return cur;

}
int main()
{
// 	int a[] = { 1, 2, 3, 4, 5 };
// 	int n = sizeof(a) / sizeof(int);
// 
// 	ListNode *head = createList( a, n );
// 	printList( head );
// 
// 	head = reverseList( head );
// 	printList( head );
// 
// 	deleteList( head );
// 	head = NULL;

// 	int l1[] = { 1, 3, 3, 3, 4, 5, 6 };
// 	int n = sizeof(l1) / sizeof(int);
// 	DoubleList * sl = new DoubleList( l1, n );
// 	sl->printList();
// 	sl->removeK( 1 );
// 	sl->printList();
// 	sl->insert( 3 );
// 	sl->printList();

	int l1[] = { 1, 2, 3, 3, 4 };
	int l2[] = { 2, 3, 4, 5 };

	ListNode* one = createList( l1, 5 );
	ListNode* two = createList( l2, 4 );
	ListNode* newHead = merge( one, two );

	system( "pause" );
	
}