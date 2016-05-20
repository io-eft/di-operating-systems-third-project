#include "myentry.hpp"
#include "myclass.hpp"
#include "myfunctions.hpp"
#include "rwfunctions.hpp"
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[])
{   //random reader-writer creation. ./randomrw numberofentries numberofprocesses
    if(argc == 3)
    {
        int id = initializer(argv[1]);              //call initializer and get memory id
        int numberOfEntries = getNumber(argv[1]);   //get number of entries from command line argument
        int numberOfProcesses = getNumber(argv[2]); //get number of random processes from command line argument
        pid_t* childrenPid = new pid_t[numberOfProcesses];  //create an index for process id's

        string sharedMemoryId = getString(id);      //turn memory id to string

        int processType;                            //set a variable to determine whether the random process will be reader or writer
        srand(time(NULL));

        for(int i = 0; i < numberOfProcesses; i++)
        {   //create the random processes
            processType = rand() % 2;               //determine reader or writer
            myClass mc(numberOfEntries);            //create a myclass item that contains random range and sleeping period

            if((childrenPid[i] = fork()) == -1)     //check if fork failed, and save the child process id in the index
            {
                 cout << "Fork failed!" << endl;
            }
            else
            {
                if(childrenPid[i] == 0)             //if you are in the child
                {
                    if(processType == 0)            //call either the reader or the writer
                    {
                        if(execl("./reader", "reader", "-r", mc.getLowerBound(), mc.getUpperBound(), "-d", mc.getSleepingPeriod(), "-s", sharedMemoryId.c_str(), NULL) < 0)
                            cout << "Execl failed! (reader)" << endl;
                    }
                    else
                    {
                        if(execl("./writer", "writer", "-r", mc.getLowerBound(), mc.getUpperBound(), "-d", mc.getSleepingPeriod(), "-s", sharedMemoryId.c_str(), NULL) < 0)
                            cout << "Execl failed! (reader)" << endl;
                    }
                }
            }
            sleep(rand() % 3);  //randomize sleeping period so processes are called kind of randomly
        }
        for(int i = 0; i < numberOfProcesses; i++)
        {   //wait until all the children are complete
            waitpid(childrenPid[i], NULL, 0);
        }
        //let the user know that parent is completed
        cout << "Parent completed." << endl << endl;
        delete[] childrenPid; //free the memory of the index
        callCleanUp(id);    //call cleanup function
    }
    else
        cout << "Wrong input!" << endl;
}
