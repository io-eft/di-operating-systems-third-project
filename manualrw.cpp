#include "myentry.hpp"
#include "myfunctions.hpp"
#include "rwfunctions.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        int id = initializer(argv[1]);  //call the initializer and get the memory id;

        while(1)
        {   //run this loop until the user types exit
            cout << "Waiting for other processes. Type 'exit' to clear shared memory after all processes have terminated." << endl;
            string s;
            getline(cin, s);
            if(s == "exit")
                break;
        }

        callCleanUp(id);                //call the cleanup function
    }
    else
        cout << "Wrong input!" << endl;
}
