#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
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
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;

        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

/*
ALGORITHM EXPLANATION:
1. combination of losed addressing and linear probing(find next available slot starting from the front of the table)
2. Each slot stores the key and the index that stores the  collided key 's position
3. If theres a collision -> the "next" will be updated with the collided key's position

THINGS TO CHECK:
1. if theres a duplicate key -> return -1
2. upon successful insertion -> return the index of the slot where the key is inserted
3. 
*/
int HashInsert(int key, HashSlot hashTable[])
{
    int index,next, i; 
    int count = 0, tempIndex, tempKey;

    if(HashFind(key,hashTable) != -1)
        return -1;

    index = hash(key);
    tempIndex = index;
    tempKey = key;
    //check if the hash slot indicator is EMPTY -> if yes, we will insert
    if(hashTable[index].indicator == EMPTY)
    {
        hashTable[index].key = key;
        hashTable[index].indicator = USED;
        return index;
    }
    

    //else, we have >= 1 number of collided keys hashed to this position
    //we will traverse up to the last node 
    int lastindex = index;
    while(hashTable[lastindex].next != -1)
    {
        lastindex = hashTable[lastindex].next;
    }


    for(i = 0; i < TABLESIZE; i++)
    {
        if(hashTable[tempIndex].indicator == EMPTY)
        {
            hashTable[tempIndex].key = key;
            hashTable[lastindex].next = tempIndex;
            hashTable[tempIndex].indicator = USED;
            return tempIndex;
        }
        tempIndex = hash(++tempKey);
    }
    
    //all else fail -> table is full 
    return TABLESIZE;
}



int HashFind(int key, HashSlot hashTable[])
{
    int i, index;
    int count = 0;

    index = hash(key);

    /* we will break out once loop count < TABLESIZE 
       assuming the worst case where TABLESIZE number of elements are hashed into the same index 
       if  
    */

    for(count = 0; count < TABLESIZE; count++)
    {   
        //if the original index is empty (assuming theres no delete function to leave tombstone)
        // then we know that we are looking for a key that doesnt exist
        if(hashTable[index].indicator == EMPTY)
        {
            return -1;
        }

        //if key is at the original hash slot
        else if(hashTable[index].key == key)
        {
            return index;
        }

        //if key is not at the original hash slot but at a different location)
        else if(hashTable[index].key != key && hashTable[index].next != -1)
        {
            //we will update the index 
            index = hashTable[index].next;
        }
    }
    //means we have failed to locate the key 
    return -1;
}