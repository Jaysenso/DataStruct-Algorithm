#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;

    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
	ll->sum =0;
}

/*
pseudocode:
	1. we will compute the sum at every new insertion of an element and compare it with the sum
	2. if we found the (sum of elements == c) -> we found a possible sequence (store this into a linkedlist)
	3. if we (sum of elements > c) -> we have went over the range and we will have to backtrack to a point where (sum < c)
	4. this will be done recursively till we reached (c == c) 

constraints:
	sumToC function does not return any value -> i have to compute it within the linked list
	and remove (the last)

ALGORITHM EXPLAINATION:
	1.
*/
void sumToC(LinkedList* ll, int C, ArrayList* al)
{
	//our sum has exceeded the target C
	if(ll->sum > C)
		return;

	//if sum == C -> we will add this to our arrayList
	else if(ll->sum == C)
	{	
		//initialize the new Array Node
		ArrayNode *newNode = (ArrayNode *)malloc(sizeof(ArrayNode));
		newNode->itemArray = (int *)malloc(ll->size * sizeof(int));	
		newNode->sizeArray = ll->size;		
		
		//we will update the item Array with the elements in the linked list's sequence
		ListNode *curr = ll->head;
		for(int i = 0; i < ll->size; i++)
		{
			newNode->itemArray[i] = curr->item;
			curr = curr->next;
		}

		newNode->next = NULL;

		//means that our ArrayList is empty 
		if(al->head == NULL)
			al->head = newNode;
		
		//we will traverse to the end of the list and insert the newNode
		else
		{
			ArrayNode *temp = al->head;
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}

		//after every successful insertion we will increment arrayList size
		al->size++;
		return;
	}
	
	int start  = 1;

	//we do this to determine which interger to try next by finding the last integer in the linked list
	if(ll->size > 0)
	{
		ListNode *tail = findNode(*ll, ll->size - 1);
		start = tail->item + 1;
	}

	//Recursive case: adding all positive intergers less than the targeted sum 
	for(int j = start; j <= C; j++)
	{	
		//duplicate status check
		int duplicate = 0;
		ListNode *currElement = ll->head;

		//sanity check ensuring that we only traverse when theres a list
		if(currElement != NULL)
		{
			while(currElement != NULL)
			{	
				//if we found a duplicate, we will update our status and breakoff
				if(j == currElement->item)
				{
					duplicate = 1;
					break;
				}
				currElement = currElement->next;
			}
		}
	
		if(!duplicate)
		{
			insertNode(ll , ll->size , j);
			//if we exit the recusion -> means we are backtracking hence we will remove the last node in the linked list
			sumToC(ll , C , al);
			removeNode(ll , ll->size - 1);
		}
	}

}
