#include "myfunctions.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
        cout << "Wrong Input!" << endl;
    else
    {
        int id = getNumber(argv[1]);    //get the memory id
        void* value;

        sem_t* mutex;
        sem_t* queueOrder;
        sem_t* readerAccess;

        value = shmat(id, NULL, 0);     //set a void pointer pointing at the start of the shared memory

        mutex = (sem_t*)value;          //set the semaphore pointers pointing in each semaphore
        queueOrder = (sem_t*)value + sizeof(sem_t);
        readerAccess = (sem_t*)value + 2*sizeof(sem_t);

        sem_destroy(mutex);             //destroy the semaphores
        sem_destroy(queueOrder);
        sem_destroy(readerAccess);

        if(shmctl(id, IPC_RMID, 0) == -1)   //remove the shared memory
            cout << "Failed to remove the shared memory." << endl;
        else
            cout << "Shared memory removed!" << endl;
    }
}
