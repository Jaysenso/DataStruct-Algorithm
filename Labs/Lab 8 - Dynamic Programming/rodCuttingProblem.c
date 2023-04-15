#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

//memory
int *r;

int cr_recursive(int *p, int n)
{

    int revenue = -1;
    int i;

    //we have no more rod to cut -> to end our recursion and sanity check
    if (n == 0)
        return 0;

    for(i = 1; i <= n; i++)
    {
        revenue = max(revenue , p[i] + cr_recursive(p , n - i));
    }

    return revenue;
}

//similar to recursion function but with memoization where we store the computed solution 
int cr_top_down_dp(int *p, int n)
{

    int revenue = -1;
    int i;

    //we check if it  has already exists
    if (r[n] >= 0)
        return r[n];
        
    //here onwards is similar to the recursion  function
    if (n == 0)
        return 0;

    for(i = 1; i <= n; i++)
    {
        revenue = max(revenue , p[i] + cr_recursive(p , n - i));
    }

    r[n] = revenue;

    return revenue;
    
}

int cr_bottom_up_dp(int *p, int n)
{
    int i, j ,revenue;

    //since r[i] is initialized to -1 in main , we safe assign to make sure length 0 gives me $0 in revenue 
    r[0] = 0;

    //outer for loop will calculate the revenue for length 1,2...n and update the r table
    for (i = 1; i <= n; i++)
    {
        revenue = -1;

        //inner for loop will be the one computing which cut will give me the max revenue 
        for(j = 1; j <= i ; j++)
        {
            revenue = max(revenue , p[j] + r[i-j]);      
        }

        //populate the revenue to respective length in the r table
        r[i] = revenue;
    }
    return r[n];
}

void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,5,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;

    printf("n is :%d\n",n);
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {
            printf("The maximun value is: %d \n", cr_recursive(p,n));
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_top_down_dp(p,n));
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_bottom_up_dp(p,n));
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }
}