typedef struct _queue
{
    LinkedList ll;
} Queue;


void enqueue(Queue *q, int item)
{
    //Enqueueing a new item -> adding a new node to the end of the linked list
    insert(&(q->ll), q->ll.size, item);
}


int dequeue(Queue *q)
{
    int item;
    //we have to store the front node 's value in a temp variable
    item = ((q->ll).head)->item;
    removeNode(&(q->ll), 0);
}


int peek(Queue *q)
{
    return ((q->ll).head)->item;
}


int isEmptyQueue(Queue *q)
{
    if ((q->ll).size == 0)
        return 1;
    return 0;
}