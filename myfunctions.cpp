#include "myfunctions.hpp"

int createSharedMemory(int s)
{   //create shared memory
    int id;
    id = shmget(IPC_PRIVATE, s, 0666);
    if(id == -1)
    {   //if creating fails, let the user know and exit
        std::cout << "Failed to create the memory segment, exiting." << std::endl;
        exit(1);
    }
    return id;  //return the process id
}

void initializeSemaphore(sem_t* s, int pshared, int value)
{   //initialize the semaphore
    if(sem_init(s, pshared, value) == -1)
    {
        std::cout << "Couldn't initialize the semaphore, exiting." << std::endl;
        exit(1);
    }
}

int getNumber(char* c)
{   //get number from a c_string using stringstream
    int number = 5;
    std::stringstream ss(c);
    if(!(ss >> number))
        std::cout << "Wrong input, setting to default (5)." << std::endl;
    return number;
}

void detachSharedMemory(void* v)
{   //detach the sahred memory, letting the user know the process id, and also let him know if it fails
    if(shmdt(v) == -1)
        std::cout << "Failed to detach shared memory!" << std::endl;
    else
        std::cout <<"Shared memory detached! (PID: " << getpid() << ")" << std::endl << std::endl;
}

std::string getString(int n)
{   //turn number to string using stringstream
    std::stringstream ss;
    std::string s;
    ss << n;
    ss >> s;
    return s;
}
