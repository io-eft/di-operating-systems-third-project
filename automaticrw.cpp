#include "myentry.hpp"
#include "myfunctions.hpp"
#include "rwfunctions.hpp"
#include "myclass.hpp"
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[])
{   //automatic reader-writer creation. ./automaticrw numberofentries
    if(argc == 2)
    {
        int id = initializer(argv[1]);              //call initializer and get memory id
        int numberOfEntries = getNumber(argv[1]);   //get number of entries from command line argument
        pid_t childrenPid [9];  //create an index for process id's

        string sharedMemoryId = getString(id);      //turn memory id to string

        int processType;                            //set a variable to determine whether the random process will be reader or writer
        srand(time(NULL));

        for(int i = 0; i < 9; i++)
        {   //create the processes
            myClass mc(numberOfEntries);            //create a myclass item that contains random range and sleeping period

            if((childrenPid[i] = fork()) == -1)     //check if fork failed, and save the child process id in the index
            {
                cout << "Fork failed!" << endl;
            }
            else
            {
                if(childrenPid[i] == 0)             //if you are in the child
                {
                    switch(i)
                    {               //decide if it's a reader or a writer
                        case(0):
                        case(1):
                        case(2):
                        case(5):
                        case(7):
                        case(8): if(execl("./reader", "reader", "-r", mc.getLowerBound(), mc.getUpperBound(), "-d", mc.getSleepingPeriod(), "-s", sharedMemoryId.c_str(), NULL) < 0)
                                    cout << "Execl failed! (reader)" << endl;break;
                        case(3):
                        case(4):
                        case(6): if(execl("./writer", "writer", "-r", mc.getLowerBound(), mc.getUpperBound(), "-d", mc.getSleepingPeriod(), "-s", sharedMemoryId.c_str(), NULL) < 0)
                                    cout << "Execl failed! (reader)" << endl;break;
                    }
                }
            }
            sleep(rand() % 3);  //randomize sleeping period so processes are called kind of randomly
        }

        for(int i = 0; i < 9; i++)
        {   //wait until all the children are complete
            waitpid(childrenPid[i], NULL, 0);
        }
        //let the user know that parent is completed
        cout << "Parent completed." << endl << endl;
        callCleanUp(id);    //call cleanup function
    }
    else
        cout << "Wrong input!" << endl;
}
