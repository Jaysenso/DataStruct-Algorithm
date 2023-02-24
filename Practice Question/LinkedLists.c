////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _listnode{
	int num;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int num;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;

////////////////////////////////////////////////////////////////////
////////////
void printList(ListNode *head);
ListNode * findNode(ListNode *head, int index);
int insertNode(ListNode **ptrHead, int index, int value);

// these are for the practice questions
int moveMaxToFront(ListNode **ptrHead);
int concatenate(ListNode **ptrHead1, ListNode *head2);
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);
int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);

////////////////////////////////////////////////////////////////////
////////////

int main()
{
	int i;
	ListNode *head = NULL;
	ListNode *dupRevHead = NULL;
	ListNode *oddHead = NULL;
	ListNode *evenHead = NULL;
	ListNode *list1Head = NULL, *list2Head = NULL;
	ListNode *combAltHead = NULL;
	DblListNode *dblHead = NULL;
	LinkedList llist;
	int size = 0;
    int test;

    insertNode(&dupRevHead, 0, 9);
    insertNode(&dupRevHead, 0, 8);
    insertNode(&dupRevHead, 0, 3);
    insertNode(&dupRevHead, 0, 1);
    insertNode(&dupRevHead, 0, 10);

    insertNode(&head, 0, 2);
    insertNode(&head, 0, 3);
    insertNode(&head, 0, 4);
    insertNode(&head, 0, 5);
    insertNode(&head, 0, 6);






	////////////////////////////////////////////////////////////////////////
	//the following are for the PRACTICE QUESTIONS

	printf("\n\nNow for the practice questions");
    ListNode *curr = dupRevHead;

	//1.moveMaxToFront()
	printf("\n************** moveMaxToFront *******************\n");
	moveMaxToFront(&dupRevHead);
	printList(dupRevHead);

	//2. concatenate()
	printf("\n************** concatenate() *******************\n");
    test = concatenate(&head, dupRevHead);
	printf("concat status:%d",test);
	printf("concatenate(current list, duplicate reverse list)\n  ");
	printList(head);

	//3.combineAlternating()
	printf("\n************** combineAlternating() *******************\n");
	for (i = 3; i > 0; i--)				//build linked list 1
		insertNode(&list1Head, 0, i);
	for (i = 13; i > 10; i--)			//build linked list 2
		insertNode(&list2Head, 0, i);
	printf("List 1:");
	printList(list1Head);
	printf("List 2: ");
	printList(list2Head);
	combineAlternating(&combAltHead, list1Head, list2Head);
	printf("After combineAlternating(): ");
	printList(combAltHead);

	//4. insertDbl()
	printf("\n************** insertDbl() *******************\n");
	printf("insertDbl()\nDoubly-linked list: ");
	insertDbl(&dblHead, 0, 10);
	insertDbl(&dblHead, 0, 20);
	insertDbl(&dblHead, 1, 30);
	insertDbl(&dblHead, 2, 40);
	printDblList(dblHead);
	return 0;
}

////////////////////////////////////////////////////////////////////
////////////

void printList(ListNode *head){
	ListNode *cur = head;

	if (cur == NULL)
		return;

	printf("the current linked list is:\n");
	while (cur != NULL){
		printf("%d ", cur->num);
		cur = cur->next;
	}
	printf("\n");
}

void printDblList(DblListNode *head){
	if (head == NULL) return;
	while (head != NULL){
		printf("%d ", head->num);
		head = head->next;
	}
	printf("\n");
}

ListNode * findNode(ListNode *head, int index){
	if (head == NULL || index < 0) return NULL;
	while (index > 0){
		head = head->next;
		if (head == NULL)
			return NULL;
		index--;
	}
	return head;
}


int insertNode(ListNode **ptrHead, int index, int value){
	ListNode *pre, *cur;
	// If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		return 0;
	}
	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ptrHead, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->num = value;
		pre->next->next = cur;
		return 0;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////
////////////

int removeNode(ListNode **ptrHead, int index){

	// write your code here
}

////////////////////////////////////////////////////////////////////////////////
////////////

int removeNode2(LinkedList *ll, int index) {

	// write your code here
}



int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList)
{

	// write your code here

}

int duplicateReverse(ListNode *head, ListNode **ptrNewHead){

	// write your code here

}

////////////////////////////////////////////////////////////////////
////////////

int moveMaxToFront(ListNode **ptrHead)
{
	//sanity check
    if (*ptrHead == NULL)
        return -1;
    
    ListNode *curr = *ptrHead;
    ListNode *head = *ptrHead;
    ListNode *prev;

    int max = INT_MIN;
    int i;

    while(curr != NULL)
    {
        if(curr->num >= max)
        {
            max = curr->num;
        }
        curr = curr->next;
    }   

    curr = (*ptrHead);
    prev = NULL;

    while(curr != NULL)
    {

        if(curr->num == max)
        {
            if(prev == NULL)
            {
                return 1;
            }

            prev->next = curr->next;
            curr->next = *ptrHead;
            *ptrHead = curr;
            return 1;
        }

        prev = curr;
        curr = curr->next;

    }
    return -1;
}


int concatenate(ListNode **ptrHead1, ListNode *head2)
{
    //both lists are empty
    if (*ptrHead1 == NULL && head2 == NULL)
        return -1;

    //if list 1 is empty, we will point ptrHead1 to list 2.
    else if (*ptrHead1 == NULL)
    {
        *ptrHead1 = head2;
        return 1;
    }

    //else means both lists exist ->we concatenate both lists
    ListNode *curr = *ptrHead1; 
    //to traverse to the end of list 
    while(curr->next != NULL)
        curr = curr->next;
    
    //curr will stop the last node of the 1st list
    //then we point the last node to the 1st node of the 2nd list
    curr->next = head2;
    head2 = NULL;

    return 1;



}


int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2){

	//sanity check (if both lists are empty, we just return)
    if(head1 == NULL && head2 == NULL)
        return -1;
    //if head1 == NULl, we point ptrHead to head2;
    else if (head1 == NULL)
    {
        *ptrHead = head2;
        return 1;
    }
    //if head2 == NULl, we point ptrHead to head1;
    else if (head2 == NULL)
    {
        *ptrHead = head1;
        return 1;
    }

    //else means both lists are not empty, we will alternate starting from head1 then head2.
    ListNode *curr_head1 = head1;
    ListNode *curr_head2 = head2;
    ListNode *curr_ptrHead = *ptrHead;
    int i = 0;

    while(1)
    {

        if (curr_head1 != NULL)
        {

            insertNode(ptrHead,i , curr_head1->num);
            curr_head1 = curr_head1->next;
            i++;
        }

        if (curr_head2 != NULL)
        {
            insertNode(ptrHead,i  , curr_head2->num);
            curr_head2 = curr_head2->next;
            i++;
        }
        // variable i will keep track of our index

        //means we have exhausted both lists, we will break out of the loop
        if(curr_head1 == NULL && curr_head2 == NULL)
            break;
    }
    
}


int insertDbl(DblListNode **ptrHead, int index, int value){

	// write your code here

}


////////////////////////////////////////////////////////////////////