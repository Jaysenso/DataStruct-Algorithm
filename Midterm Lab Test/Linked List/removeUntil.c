//////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
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
	palindrome(word1); //*word1="A man a plan a canal Panama";
	palindrome(word2);// *word2="Superman in the sky";


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

	system("pause");
	return 0;
}

////////////////////////////////////////////////////////////////
//Question 1

void removeUntil(Stack *s, int value)
{

	if (s == NULL || pop(s) == value)
		return;

	int popped_var;

	while(!isEmptyStack(s))
	{
		popped_var = pop(s);

		if(popped_var == value)
			break;
	}
}

////////////////////////////////////////////////////////////
//Question 2

void recursiveReverse(Queue *q){

	int i;
    if (q == NULL || isEmptyQueue(q))
        return;

    i = dequeue(q);
    recursiveReverse(q);

    enqueue(q,i);
    

}

////////////////////////////////////////////////////////////
//Question 3
/*ALGORITHM EXPLAINATION: ------------------------------------------------------------------
1. We traverse through the char array, ignoring all the spaces
2. We will capitalize all the chars for easier comparison
3. Then we will push & enqueue all the chars into 2 different data structures
4. Pushing into a stack reverses its order while queue retains its original order
5. With this, we can compare the first element by (pop/dequeue) the (top of the stack/the front of queue)
6. If the comparison fails, we know that is not palindrome
NOTE: We only have to check (strlength/2) to know whether its palindrome*/

int palindrome(char *word){
    
    char *read = word;
    char character;
    int half;

    Stack s;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;

    Queue q;
    q.ll.head = NULL;
    q.ll.tail = NULL;
    q.ll.size = 0;

    //traverse through the entire string till NULL
    while(*read != '\0')
    {
        //capitalized 65-90 / small letter 97-122
        //ignore all the spaces
        if(*read != ' ')
        {
            character = *read;
            //if its cap, we lowecase it
            if (character >= 65 && character <= 90)
                character += 32;

            push(&s,character);
            enqueue(&q,character);
        }
        read++;
    } 

    half = q.ll.size / 2;

    while(half > 0)
    {   
        if(pop(&s) != dequeue(&q))
        {
            printf("%s is not a palindrome\n",word);
            return -1;
        }
        
        half--;
    }
    printf("%s is a palindrome\n",word);
    return 0;
}



////////////////////////////////////////////////////////////
//Question 4

/// @brief  
/// @param expression 
/// @return 
int balanced(char *expression){

	char *read = expression;

	Stack s;
	s.ll.head = NULL;
	s.ll.tail = NULL;
	s.ll.size = 0;
	char peeked;

	while (*read != '\0')
	{
		if(*read == '{' || *read == '[' || *read == '(')
			push(&s,*read);

		else
		{
			peeked = peek(&s);

			if(*read == '}' && peeked == '{')
				pop(&s);
			else if (*read == ']' && peeked == '[')
				pop(&s);
			else if (*read == ')' && peeked == '(')
				pop(&s);
			else 
				return 1;
		}
		read++;

	}
	return (!isEmptyStack(&s));

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