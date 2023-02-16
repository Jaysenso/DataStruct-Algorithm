////////////////////////////////////////////////////////////

#include "stdlib.h"
#include "stdio.h"

////////////////////////////////////////////////////////////

void insert(char *s,int n);
void removes(char *s, int n);

//////////////////////////////////////////////////////////
void main ()
{
	int n;
    char *s;
	int choice;


	printf("How many characters do you want to input:");
	scanf("%d", &n);

	s=(char *)malloc((n+1)*sizeof(char));

    if (s==NULL)
	{
		printf("can't allocate the memory!");
		return;
	}

	printf("Input the string:");
	scanf("%s",s);

	printf("The string is %s\n", s);

	do
	{
		printf("Do you want to 1-insert or 2-remove or 3-quit?:");
		scanf("%d",&choice);
		//getchar(); //to clear the return carriage in the buffer

		if (choice==1)
			insert(s,n);
		else if (choice==2)
			removes(s,n);
	}while (choice!=3);


}

//////////////////////////////////////////
void removes(char *s, int n)
{
    int i;

    if (s == NULL)
        return;

    printf("Resulting String:");
    
    for(i = 1; i < n ; i++)
    {
        s[i-1] = s[i];
        printf("%c", s[i-1]);
    }
    printf("\n");
}

//////////////////////////////////////////
void insert(char *s, int n)
{

    if (s == NULL && n == 0)
        return;

    char new_char, head;
    char *temp = s;
    int char_count = 0;
    int i,k;

    printf("What is the characeter you want to insert:");
    scanf(" %c", &new_char);

    //count the number of char in the string
    while (*temp != '\0')
    {
        char_count++;
        temp++;
    } 

    for(i = char_count ; i >= 0; i--)

    {  
        if(i == 0)
        {
            s[i] = new_char;
            continue;
        }

        s[i] = s[i-1];
    }
    
    printf("Resulting String: ");
    for(i=0;i < n; i++)
        printf("%c",s[i]);

    printf("\n");
}