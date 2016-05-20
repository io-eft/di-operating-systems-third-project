#include "readerfunctions.hpp"

void myreader(char* lB, char* uB, char* p, char* sharedMemoryId)
{
    int lowerBound, upperBound, period, shmid, pid;     //declare the variables

    lowerBound = getNumber(lB);         //get variables as int
    upperBound = getNumber(uB);
    period = getNumber(p);
    shmid = getNumber(sharedMemoryId);
    pid = getpid();

    void* value;                //pointer for attached memory

    sem_t* mutex;               //mutex pointers
    sem_t* queueOrder;
    sem_t* readerAccess;

    int* totalReaders;          //pointers for total entries and total readers
    int* totalEntries;

    Entry* e;                   //entry pointer
    //let the user know if it's reader or writer, the pid and time of arrival
    std::cout << "I am a reader! my id is " << pid << " and I arrived at " << time(NULL) << "." << std::endl;

    value = shmat(shmid, NULL, 0);      //attach the shard memory

    mutex = (sem_t*)value;              //set the pointers to the correct memory locations
    queueOrder = (sem_t*)value + sizeof(sem_t);
    readerAccess = (sem_t*)value + 2*sizeof(sem_t);

    totalReaders = (int*)value + 3*sizeof(sem_t);       //set the pointers to the correct memory locations
    totalEntries = (int*)value + sizeof(int) + 3*sizeof(sem_t);
    e = (Entry*)value + 2*sizeof(int) + 3*sizeof(sem_t);

    if(lowerBound > upperBound || lowerBound < 0 || lowerBound >= *totalEntries || upperBound < 0 || upperBound >= *totalEntries)
    {   //check if the range given is out of bounds. If it is, let the user know and detach the shared memory, then exit
        std::cout << "Range out of bounds!" << std::endl;
        detachSharedMemory(value);
        exit(1);
    }

    sem_wait(queueOrder);       //wait at the queue order semaphore
    sem_wait(readerAccess);     //once you pass, wait at the reader Access semaphore
    if(*totalReaders == 0)      //once you pass, check if you are the first reader
        sem_wait(mutex);        //if you are, wait at the mutex semaphore. If not go ahead
    (*totalReaders)++;          //increase the number of total readers
    sem_post(readerAccess);     //let others access the readers variable
    sem_post(queueOrder);       //leave the queue
    //let the user know your id, the time and that you are about to read entries
    std::cout << "My pid is: " << pid << ", time is " << time(NULL) << " and I am about to read entries " << lowerBound << " to " << upperBound << "." << std::endl;

    for(int i = lowerBound; i <= upperBound; i++)
    {   //read the entries in your specified range
        std::cout << "Entry " << i << ": ";
        e[i].printEntry();
    }

    std::cout << "I'll sleep now for " << period << " seconds. (Pid: " << pid << ")." << std::endl << std::endl;
    sleep(period);  //let the user know how long you're going to sleep for, and do so

    sem_wait(readerAccess);     //wait at the reader access semaphore
    (*totalReaders)--;          //once you pass, decrease the number of readers
    if(*totalReaders == 0)      //if you were the last reader
        sem_post(mutex);        //let others access the mutex part
    sem_post(readerAccess);     //let others access the readers varialbe

    detachSharedMemory(value);  //detach the shared memory
}
