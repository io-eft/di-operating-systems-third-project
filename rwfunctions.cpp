#include "myentry.hpp"
#include "myfunctions.hpp"
#include "rwfunctions.hpp"

int initializer(char* c)
{
    int numberOfEntries = getNumber(c);     //get the number of entries
    int id = 0;             //variable for shared memory id
    int *totalReaders;      //int pointer to set total readers
    int *totalEntries;      //int pointer to set total entries

    size_t  siz = 3*sizeof(sem_t) + 2*sizeof(int) + sizeof(Entry[numberOfEntries]);     //calculate the size

    void* value;            //void pointer for shared memory

    sem_t* mutex;           //pointers for semaphores
    sem_t* queueOrder;
    sem_t* readerAccess;

    Entry* e;               //pointer for entries

    id = createSharedMemory(siz);       //create the shared memory and get its id

    std::cout << "Allocated, id is = " << id << std::endl;      //let the user know the id of the shared memory
    value = shmat(id, NULL, 0);         //attach the shared memory

    mutex = (sem_t*)value;              //point the semaphore pointers at the correct memory locations
    queueOrder = (sem_t*)value + sizeof(sem_t);
    readerAccess = (sem_t*)value + 2*sizeof(sem_t);

    totalReaders = (int*)value + 3*sizeof(sem_t);               //set the totalReaders and totalEntries pointers at the proper locations
    totalEntries = (int*)value + sizeof(int) + 3*sizeof(sem_t);

    e = (Entry*)value + 2*sizeof(int) + 3*sizeof(sem_t);        //set the entry pointer at the proper locations

    int pid = getpid();         //get the process id to set the entries

    *totalReaders = 0;          //set the totalReaders to 0
    *totalEntries = numberOfEntries;    //set the totalEntries to the proper number

    for(int i = 0; i < numberOfEntries; i++)
    {   //initialize the entry index
        e[i].setPid(pid);
        e[i].setTime(time(NULL));
        e[i].setDefByInit();
    }
    //initialize the semaphores
    initializeSemaphore(mutex, 1, 1);
    initializeSemaphore(queueOrder, 1, 1);
    initializeSemaphore(readerAccess, 1, 1);
    //print the entries
    for(int i = 0; i < numberOfEntries; i++)
        e[i].printEntry();
    std::cout << std::endl;
    detachSharedMemory(value);      //detach the shared memory
    return id;             //return the shared memory id
}

void callCleanUp(int id)
{
    std::string s = getString(id);  //turn the id to string
    if(execl("./cleanup", "cleanup", s.c_str(), NULL) < 0)  //call cleanup proccess with execl
        std::cout << "Execl failed! (cleanup). Please call cleanup with input: " << id << "to clear the shared memory." << std::endl;
}
