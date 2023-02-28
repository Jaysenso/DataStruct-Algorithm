//////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////   linked list //////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
	int size;
	ListNode *head;
	ListNode *tail;
} LinkedList;

////////////////////////////////// stack    //////////////////////////////////////////////
typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////
void printList(ListNode *head);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////////////////////////////

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

//////////////////////////////////////////////////

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////////////
// four questions
void removeUntil(Stack *s, int value);
void recursiveReverse(Queue *q);
int palindrome(char *word);
int balanced(char *expression);

//////////////////////////////////////////////////////////////////
/////

int main()
{
	Stack s;
	Queue q;
	int item[] = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
	int i;
	char *word1 = "A man a plan a canal Panama";
	char *word2 = "Superman in the sky";

	//for question 1
	//initialize the stack
	s.ll.head = NULL;
	s.ll.size = 0;
	s.ll.tail = NULL;

	for (i = 0; i<11; i++)
		push(&s, item[i]);

	printList(s.ll.head);
	removeUntil(&s, 5);
	printList(s.ll.head);

	//for question 2
	//initialize the queue
	q.ll.head = NULL;
	q.ll.size = 0;
	q.ll.tail = NULL;

	for (i = 0; i<10; i++)
		enqueue(&q, i);
	printList(q.ll.head);
	recursiveReverse(&q);
	printList(q.ll.head);

	//for question 3
	printf("flag: %d",palindrome(word1)); //*word1="A man a plan a canal Panama";
	printf("flag: %d\n",palindrome(word2));// *word2="Superman in the sky";


	//for question 4
	if (balanced("()")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	if (balanced("[()]")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	if (balanced("{[]()[]}")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	if (balanced("[({{)])")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	return 0;
}

////////////////////////////////////////////////////////////////
//Question 1

void removeUntil(Stack *s, int value)
{

	// write your code here
	int i;
	if (s == NULL)
		return;

	for (i = 0; i < value - 1; i++)
	{
		pop(s);
	}
}

////////////////////////////////////////////////////////////
//Question 2

void recursiveReverse(Queue *q){

	// write your code here
	int i;
	//this is the condition that will end my recursion 
	if (isEmptyQueue(q))
		return;

	//if is not empty, i will dequeue the first element and store it in i
	i = dequeue(q);
	//call recursiveReverse function again to dequeue all the elements till its empty
	recursiveReverse(q);
	//once we hit the condition to stop recursion, we will return and enqueue the last item
	//that we have dequeued, repeating the process till we hit the 1st element that we dequeued.
	//And the final list will be a reversed of the original onex	
	enqueue(q, i);

}

////////////////////////////////////////////////////////////
//Question 3

int palindrome(char *word)
{
/*ALGORITHM EXPLAINATION: ------------------------------------------------------------------
1. We traverse through the char array, ignoring all the spaces
2. We will capitalize all the chars for easier comparison
3. Then we will push & enqueue all the chars into 2 different data structures
4. Pushing into a stack reverses its order while queue retains its original order
5. With this, we can compare the first element by (pop/dequeue) the (top of the stack/the front of queue)
6. If the comparison fails, we know that is not palindrome

NOTE: We only have to check (strlength/2) to know whether its palindrome
--------------------------------------------------------------------------------------------
*/
	Stack s;
	s.ll.head = NULL;
	s.ll.size = 0;	
	
	Queue q;
	q.ll.head = NULL;
	q.ll.size = 0;

	char * read = word;
	char character;
	int half;


	while(*read != '\0')
	{
		if (*read != ' ')
		{
			character = *read;

			if (character>= 65 && character<=90)
				character+=32;

			push(&s, character);
			enqueue(&q, character);
		}
		read++;
	}


	half = q.ll.size / 2;

	while (half > 0)
	{
		if (pop(&s) != dequeue(&q))
			return -1;

		half--;
	}

	return 0;

}



////////////////////////////////////////////////////////////
//Question 4
/*AlGORITHM EXPLANATION******************************************************************************************
1. We traverse through the char array
2. We look for any opening brackets 
3. If theres a opening bracket, we push it into our auxilary stack 
3a.As we traversing through the char array, the auxilary stack will be used to compare against the char aray
4. If the next char is not a opening bracket, we will check if its the closing one (assuming that the input only
	accept brackets)
5. if its not the corresponding closing bracket, we will terminate and return "unbalanced"
*****************************************************************************************************************/
int balanced(char *expression){
	// write your code here
	Stack s;
	s.ll.head = NULL;
	s.ll.size = 0;

	char c;
	char *read = expression;

	while (*read != '\0')
	{
		if (*read == '[' || *read == '{' || *read == '(')
			push(&s, *read);
		
		else
		{
			//if empty stack, means the string started with a closing bracket
			if (isEmptyStack(&s))
				return 0;
		
			//c will store the opening brackets stored in the auxilary stack
			c = pop(&s);

			if (*read == ']' && c != '[')
				return 1;
			else if (*read == ')' && c != '(')
				return 1;
			else if (*read == '}' && c != '{')
				return 1;

		}
		read++;
	}

	return (!isEmptyStack(&s)) ;

}

////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
	int item;

	item = ((s->ll).head)->item;
	removeNode(&(s->ll), 0);
	return item;
}

int peek(Stack *s){
	return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
	if ((s->ll).size == 0)
		return 1;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item){
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
	int item;
	item = ((q->ll).head)->item;
	removeNode(&(q->ll), 0);
	return item;
}

int isEmptyQueue(Queue *q){
	if ((q->ll).size == 0)
		return 1;
	return 0;
}



////////////////////////////////////////////////////////////////////////////////

void printList(ListNode *head){

	ListNode *temp = head;

	if (temp == NULL)
		return;

	while (temp != NULL){
		printf("%d ", temp->item);
		temp = temp->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

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

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->tail = ll->head;
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Inserting as new last node
	if (index == ll->size){
		pre = ll->tail;
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		ll->tail = pre->next;
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));

		if (index == ll->size)
			ll->tail = pre->next;

		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		if (ll->size == 0)
			ll->tail = 0;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		// Removing the last node, update the tail pointer
		if (index == ll->size - 1){
			ll->tail = pre;
			free(pre->next);
			pre->next = NULL;
		}
		else{
			cur = pre->next->next;
			free(pre->next);
			pre->next = cur;
		}
		ll->size--;
		return 0;
	}

	return -1;
}
