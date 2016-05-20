#include "writerfunctions.hpp"

void mywriter(char* lB, char* uB, char* p, char* sharedMemoryId)
{
    int lowerBound, upperBound, period, shmid, pid;     //declare the variables

    lowerBound = getNumber(lB); //get variables as int
    upperBound = getNumber(uB);
    period = getNumber(p);
    shmid = getNumber(sharedMemoryId);
    pid = getpid();

    void* value;    //pointer for attached memory

    sem_t* mutex;       //mutex pointers
    sem_t* queueOrder;
    int* totalEntries;

    Entry* e;           //entry pointer
    //let the user know if it's reader or writer, the pid and time of arrival
    std::cout << "I am a writer! my id is " << pid << " and I arrived at " << time(NULL) << "." << std::endl;

    value = shmat(shmid, NULL, 0);  //attach the shard memory

    mutex = (sem_t*)value;  //set the pointers to the correct memory locations
    queueOrder = (sem_t*)value + sizeof(sem_t);
    totalEntries = (int*)value + sizeof(int) + 3*sizeof(sem_t);
    e = (Entry*)value + 2*sizeof(int) + 3*sizeof(sem_t);

    if(lowerBound > upperBound || lowerBound < 0 || lowerBound >= *totalEntries || upperBound < 0 || upperBound >= *totalEntries)
    {   //check if the range given is out of bounds. If it is, let the user know and detach the shared memory, then exit
        std::cout << "Range out of bounds!" << std::endl;
        detachSharedMemory(value);
        exit(1);
    }

    sem_wait(queueOrder);   //wait at the order semaphore
    sem_wait(mutex);        //once you proceed, wait at the mutex semaphore
    //let the user know your id, the time and that you are about to modify entries
    std::cout << "My pid is: " << pid << ", time is " << time(NULL) << " and I am about to modify entries " << lowerBound << " to " << upperBound << "." << std::endl;

    for(int i = lowerBound; i <= upperBound; i++)
    {
        std::cout << "Entry " << i << " used to be: ";
        e[i].printEntry();          //let the user know what the entry used to be
        e[i].setPid(pid);           //change it
        e[i].setDefByWriter();
        e[i].setTime(time(NULL));
        std::cout << "Entry " << i << " now is: ";
        e[i].printEntry();          //let the user know what the entry is now
    }

    std::cout << "I'll sleep now for " << period << " seconds. (Pid: " << pid << ")." << std::endl << std::endl;
    sleep(period);                  //let the user know how long you're going to sleep for, and do so

    sem_post(mutex);                //let others know you've exited the mutex part
    sem_post(queueOrder);           //let others know you've done with your turn in the queue

    detachSharedMemory(value);      //detach the shared memory
}
