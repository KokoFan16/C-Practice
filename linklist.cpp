#include <iostream>

using namespace std;

struct listNode
{
	int x;
	listNode* next;
};

listNode* append(listNode* head, int x)
{
	listNode* newNode = new listNode();
	newNode->next = NULL;
	newNode->x = x;
	listNode* tmp = head;
	if (head == NULL) {
		head = newNode;
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
	return head;
}

void traversal(listNode* head)
{
	while (head)
	{
		cout << head->x << endl;
		head = head->next;
	}
}

listNode* searchNode(listNode* head, int x)
{
	while (head)
	{
		if (head->x == x) {
			return head;
		}
		else
		{
			head = head->next;
		}
	}
}

listNode* deleteNode(listNode* head, int x)
{
	if (head == NULL)
	{
		return head;
	}
	else if (head->next == NULL)
	{
		if (head->x == x) {
			return	NULL;
		}
		else
		{
			return head;
		}
	}
	else
	{
		listNode* pNode = new listNode;
		pNode = head;
		while (pNode->next)
		{
			if (pNode->next->x == x)
			{
				pNode->next = pNode->next->next;
				break;
			}
			else
			{
				pNode = pNode->next;
			}
		}

	}
	return head;
}


int main()
{
	listNode* head = new listNode();
	head->x = 0;
	head->next = NULL;
	for (int i = 1; i < 5; i++)
	{
		append(head, i);
	} 

	head = deleteNode(head, 0);
	traversal(head);
}
