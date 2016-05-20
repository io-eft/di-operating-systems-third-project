#include "myentry.hpp"

Entry::Entry(int t, int p): time(t), pid(p) {}

void Entry::printEntry()
{
    std::cout << "Set by process: " << pid << ". Time: " << time;   //print the process id and time
    if(def)
        std::cout << " (Initialiser).";     //check if it was set by the initializer or not
    else
        std::cout << ".";
    std::cout << std::endl;
}

void Entry::setTime(int t)
{
    time = t;   //set the time
}

void Entry::setPid(int p)
{
    pid = p;    //set the pid
}

void Entry::setDefByInit()
{
    def = true; //set by initializer
}

void Entry::setDefByWriter()
{
    def = false;    //set by writer
}
