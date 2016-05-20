#include "writerfunctions.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 8)
        cout << "Wrong Input" << endl;
    else
    {   //check the input and call the mywriter function properly
        if(strcmp(argv[1], "-r") == 0 && strcmp(argv[4], "-d") == 0 && strcmp(argv[6], "-s") == 0)
            mywriter(argv[2], argv[3], argv[5], argv[7]);
        else
        {
            if(strcmp(argv[1], "-r") == 0 && strcmp(argv[4], "-s") == 0 && strcmp(argv[6], "-d") == 0)
                mywriter(argv[2], argv[3], argv[7], argv[5]);
            else
            {
                if(strcmp(argv[1], "-d") == 0 && strcmp(argv[3], "-r") == 0 && strcmp(argv[6], "-s") == 0)
                    mywriter(argv[4], argv[5], argv[2], argv[7]);
                else
                {
                    if(strcmp(argv[1], "-d") == 0 && strcmp(argv[3], "-s") == 0 && strcmp(argv[5], "-r") == 0)
                        mywriter(argv[6], argv[7], argv[2], argv[4]);
                    else
                    {
                        if(strcmp(argv[1], "-s") == 0 && strcmp(argv[3], "-r") == 0 && strcmp(argv[6], "-d") == 0)
                            mywriter(argv[4], argv[5], argv[7], argv[2]);
                        else
                        {
                            if(strcmp(argv[1], "-s") == 0 && strcmp(argv[3], "-d") == 0 && strcmp(argv[5], "-r") == 0)
                                mywriter(argv[6], argv[7], argv[4], argv[2]);
                            else
                                cout << "Wrong input" << endl;
                        }
                    }
                }
            }
        }
    }
}
