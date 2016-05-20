#include "myclass.hpp"
#include "myfunctions.hpp"

myClass::myClass(int n)
{   //a class to create random inputs
    int lB = rand() % n;
    int uB = (rand() % (n - lB)) + lB;
    int sP = (rand() % 10) + 5;
    lowerBound = getString(lB);
    upperBound = getString(uB);
    sleepingPeriod = getString(sP);
}

const char* myClass::getLowerBound()
{
    return lowerBound.c_str();
}

const char* myClass::getUpperBound()
{
    return upperBound.c_str();
}

const char* myClass::getSleepingPeriod()
{
    return sleepingPeriod.c_str();
}
