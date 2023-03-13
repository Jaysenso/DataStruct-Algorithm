#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize;
   int nSize;
   HashTableNode *Table;
} HashTable;

int Hash(int,int);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0;
    Q3Hash.nSize = 0;
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter number of data to be inserted:\n");
            scanf("%d",&size);

            Q3Hash.hSize = (int)size/ LOAD_FACTOR;
            printf("Q3Hash.hSize is %d ",Q3Hash.hSize);
            Q3Hash.nSize = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));

            for(i=0;i<Q3Hash.hSize;i++){
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q3Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q3Hash.hSize;i++)
    {
        while(Q3Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q3Hash.Table);

    return 0;
    system("pause");
}

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q3Hash, int key)
{
    //get the index of the linked list
    int index = Hash(key, Q3Hash.hSize);
    //we start at the head of the linked list
    ListNode *curr = Q3Hash.Table[index].head;

    while(curr != NULL)
    {
        //if current node has the desired key, we will return curr.
        if (curr->key == key)
            return curr;
        
        curr = curr->next;
    }
    // if we reached the end of the linked list without finding the node, we will return NULL
    return NULL; 

}

int HashInsert(HashTable* Q3HashPtr, int key)
{
    //get the index of the linked list
    int index = Hash(key, Q3HashPtr->hSize); 
    //start at the head of the linked list 
    ListNode *curr = Q3HashPtr->Table[index].head;
    ListNode *prev = NULL;

    while(curr != NULL) //we traverse to the end of the linked list -> where we will insert the new key
    {
        if (curr->key == key) //if the current node has the desired key -> we have a duplicate
            return 0;

        prev = curr;
        curr = curr->next;
    }

    //if we reached this point, means the key is not duplicate -> so we can insert a new node at the end
    ListNode *d = malloc(sizeof(ListNode));
    d->key = key;
    d->next = NULL;

    //if prev == NULL -> linked list was empty since we previously declare prev = curr hence curr == NULL
    if(prev == NULL)        
        Q3HashPtr->Table[index].head = d;
    else
        prev->next = d;

    //upon successful insertion of the new key, we will increment the size of the linked list & 
    //the total number of nodes in the hash table.
    Q3HashPtr->Table[index].size++;
    Q3HashPtr->nSize++;

/* EXTRA - resize if number of entries is greater than the number of slots */

    //check if we need to resize the hash table to maintian the load factor
    //if yes -> we will multiply the size of hash table by 2 of number of entries
/*   if (Q3HashPtr->nSize > LOAD_FACTOR * Q3HashPtr->hSize)
    {
        int new_hSize = 2 * Q3HashPtr->nSize;
        HashTableNode *new_table = (HashTableNode*)malloc(sizeof(HashTableNode) * new_hsize);

        //initialize the table
        for(int i = 0; i < new_hsize; i++)
        {
            new_Table[i].head = NULL;
            new_Table[i].size = 0;
        }
    }
*/

}

void HashPrint(HashTable Q3Hash)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q3Hash.hSize;i++)
    {
        temp =Q3Hash.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
