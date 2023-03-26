#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }
    

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}


int HashInsert(int key, HashSlot hashTable[])
{
    int i = 0;
    int deletedIndex = -1;
    int comparisons = 0;
    int hashValue;

    for(i = 0; i < TABLESIZE; i++)
    {
        if (i == TABLESIZE)
            return TABLESIZE;

        hashValue = (hash1(key) + (i * hash2(key))) % TABLESIZE;

        //This is the earliest hash location we can put -> however, we have to continue searching
        //to see if theres an existing key in the hash table
        if(hashTable[hashValue].indicator == DELETED && deletedIndex == -1)
           deletedIndex = hashValue;

        //if we found an empty hash location and deletedIndex hasn't been updated
        //then we know the key doesnt exist in the hash table -> proceed to insert it into the hash table
        //EDGE CASE: Assuming we fill the table and delete all the elements -> insert will show duplicate key
        //instead of table is full. 
        if(hashTable[hashValue].indicator == EMPTY)
        {
            if(deletedIndex == -1)
               deletedIndex = hashValue;

            hashTable[deletedIndex].key = key;
            hashTable[deletedIndex].indicator = USED;
            return comparisons;
        }
        
        //we will only increment key comparison when our key is compared to another key
        if(hashTable[hashValue].indicator == USED)
        {
            comparisons++;

            //duplicate key detected -> return -1
            if(hashTable[hashValue].key == key)
                return -1;
        }
    }

    hashTable[deletedIndex].key = key;
    hashTable[deletedIndex].indicator = USED;
    return comparisons;
}

int HashDelete(int key, HashSlot hashTable[])
{

    int i = 0;
    int comparisons = 0;
    int hashValue;

    for(i = 0; i <= TABLESIZE; i++)
    {   
        hashValue = (hash1(key) + (i * hash2(key))) % TABLESIZE;

        //comparison only increments when we are actually comparing to keys -》 be it DELETED or USED
        if(hashTable[hashValue].indicator != EMPTY)
            comparisons++;

        //deleting non-existing key
        if(hashTable[hashValue].indicator == EMPTY)
            return -1;
            
        //we found our key
        if(hashTable[hashValue].indicator == USED && hashTable[hashValue].key == key)
        {
            hashTable[hashValue].indicator = DELETED;
            return comparisons;
        }
        
    }
    //deleting key does not exist
    return -1;
}






