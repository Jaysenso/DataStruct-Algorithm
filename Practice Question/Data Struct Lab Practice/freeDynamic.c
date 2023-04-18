////////////////////////////////////////////////////////////


//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

void createLL(ListNode **head);
void printLL(ListNode *head);
void deleteAll(ListNode **head, char choice_deletion);
int searchList(ListNode *head,int value);


void main()
{
	ListNode *head;
	int n;
    int value,test;
    char choice,choice_deletion;


	head=NULL;	// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");

	/////////////////////////////////////////////////////////////////
	//Question 2
    printf("1: Create a linked list\n");
    printf("2: Search value in linked list\n");
    printf("3: Delete linked list.\n");
    printf("0: Quit;\n");

    choice = 1;
    while(choice != 0)
    {
        
        printf("Please input your choice(1/2/3/0): ");
        if(scanf(" %d",&choice) > 0)
        {
            switch(choice)
            {
                case(1): createLL(&head);
                         break;

                case(2): printf("Enter value to search for:");
                         scanf("%d",&value);
                         test = searchList(head,value);
                         break;

                case(3): printf("Do you wan to delete Linked List?");
                         scanf(" %c",&choice_deletion);
                         deleteAll(&head,choice_deletion);
                         break;

                case(0): break;
                
                default: printf("Choices unknown\n");

            }

        
        }
    }

   //////////////////////////////////////////////////////////////////
}


void createLL(ListNode **head)
{  
    ListNode *temp, *p;
    int n;

    printf("Enter a list of nubmers, terminated by the value -1:");
    do
    {
        scanf("%d",&n);
        if (n != -1)
        {
            //if head == null -> means list is empty
            if(*head == NULL)
            {
                *head = malloc(sizeof(ListNode));
                (*head)->item = n;
                (*head)->next = NULL;          
                temp = *head;
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
    printLL(*head);
}


void printLL(ListNode *head)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    
    ListNode *temp;
    //we point temp to head to traverse down the list and print
    temp = head;

    printf("Current List is: ");
    while (temp != NULL)
    {   
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
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

    while(curr != NULL)
    {   
        if(curr->item == value)
        {   
            printf("Value %d found at index %d\n",value, index);
            return 1;
        }
        curr = curr->next;
        index++;
    }

    return -1;

}

void deleteAll(ListNode **head,char choice_deletion)
{   
    if (*head == NULL)
        {
            printf("There is nothing to delete!\n");
            return;
        }
    ListNode *prev = *head;

    if (choice_deletion == 'y')
    {
        while (*head != NULL) 
        {   
            *head = (*head)->next;
            free(prev); 
            prev = *head;
        }   
        printLL(*head);
    }

}


