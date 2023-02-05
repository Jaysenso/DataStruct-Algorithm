typedef struct _stack
{
    LinkedList ll;

}stack;

/* since we have to abind the rule of "Stack" -> First in Last Out
we will only be able to touch what is at the top of the stack
hence index always = 0.*/

void push(stack *s, int item)
{
    insertNode(&(s->ll), 0, item);
}


int pop(stack *s)
{
    int item;
    item = (s->ll).head->item;
    removeNode(&(s->ll), 0);
    return item;
}


int peek(stack *s)
{
    return (s->ll).head->item;
}


int isEmptyStack (stack *s)
{
    if ((s->ll).size == 0)
        return 1;
    
    return 0;
}