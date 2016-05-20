#ifndef __MYCLASS__HPP
#define __MYCLASS__HPP
#include <iostream>
#include<sys/types.h>
#include <string>
#include <time.h>

class myClass
{
    std::string lowerBound;
    std::string upperBound;
    std::string sleepingPeriod;
    
    public:
	myClass(int n);
        const char* getLowerBound();
	const char* getUpperBound();
	const char* getSleepingPeriod();
};


#endif

