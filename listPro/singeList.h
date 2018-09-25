#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <iostream>

using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode( int x ): val(x), next( NULL ){}
};

class SingleList{
public:
	ListNode *head;

public:
	SingleList( int a[], int n ){
		head = createList( a, n );
	}

	~SingleList()
	{
		deleteList();
	}

	ListNode * getHeadPointer(){
		return head;
	}

	void printList(){

		ListNode *curNode = head;

		while( curNode )
		{
			cout << curNode->val << " -> ";
			curNode = curNode->next;
		}

		cout << "NULL" << endl;
	}
	
	ListNode* sortList() {
		if(head == NULL || head->next == NULL)
			return head;

		head = __sortList( head );
		return head;
	}

	//反转链表
	ListNode* reverseList( )
	{
		if( NULL == head )
			return NULL;

		ListNode *curNode = head;
		ListNode *pre = NULL;

		while( curNode )
		{
			ListNode *next = curNode->next;
			curNode->next = pre;
			pre = curNode;
			curNode = next;
		}

		head = pre;
		return head;
	}

private:
	//创建新链表
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

	//删除链表
	void deleteList()
	{
		ListNode *curNode = head;
		while( curNode )
		{
			ListNode *delNode = curNode;
			curNode = curNode->next;
			delete delNode;
		}
	}

	//归并排序对链表进行排序
	ListNode* __sortList( ListNode *head ) {
		if(head == NULL || head->next == NULL)
			return head;

		ListNode* head1 = head;
		ListNode* head2 = getMid(head);
		head1 = __sortList(head1);
		head2 = __sortList(head2);
		return merge(head1, head2);
	}

	//获得链表中间结点
	ListNode* getMid(ListNode* head)
	{
		//guaranteed that at least two nodes
		ListNode* fast = head;
		ListNode* slow = head;
		ListNode* prev = NULL;
		while( fast && fast->next )
		{
			fast = fast->next->next;
			prev = slow;
			slow = slow->next;
		}
		prev->next = NULL;  // cut
		return slow;
	}

	//合并排好序的两个链表
	ListNode* merge(ListNode* head1, ListNode* head2)
	{
		ListNode* newhead = new ListNode(-1);
		ListNode* newtail = newhead;
		while(head1 != NULL && head2 != NULL)
		{
			if(head1->val <= head2->val)
			{
				newtail->next = head1;
				head1 = head1->next;
			}
			else
			{
				newtail->next = head2;
				head2 = head2->next;
			}
			newtail = newtail->next;
			newtail->next = NULL;
		}
		if(head1 != NULL)
			newtail->next = head1;
		if(head2 != NULL)
			newtail->next = head2;
		return newhead->next;
	}
};

#endif