////////////////////////////////////////////////////////////


//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

int searchList(ListNode *head, int value);

void main()
{
	ListNode *head, *p, *temp;
	int n;
    int value;
    int test;

	head=NULL;
	p=NULL;		// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");

	/////////////////////////////////////////////////////////////////
	//Question 2
    do
    {
        scanf("%d",&n);

        if (n != -1)
        {
            //if head == null -> means list is empty
            if(head == NULL)
            {
                head = malloc(sizeof(ListNode));
                head->item = n;
                head->next = NULL;      

                temp = head;
            }
            //else head != NULL ->means we are adding node to the head
            else
            {
                p = malloc(sizeof(ListNode));                
                p->item = n;
                p->next = NULL;

                temp->next = p;
                temp = temp->next;

            }
        }
    }while (n != -1);

    //we point temp to head to traverse down the list and print
    temp = head;

    printf("Current List is: ");

    while (temp != NULL)
    {   
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");


    test = searchList(head,value);
   //////////////////////////////////////////////////////////////////
}

int searchList(ListNode *head, int value)
{

    ListNode *curr = head; 
    int index = 0;

    if (curr == NULL)
    {
        printf("The list is empty.");
        return -1;
    }
    
    printf("Enter value to search for:");
    scanf("%d",&value);

    while(curr != NULL)
    {
        if(curr->item == value)
        {   
            printf("Value %d found at index %d",value, index);
            return 1;
        }
        curr = curr->next;
        index++;
    }

    return -1;

}