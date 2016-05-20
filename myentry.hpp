#ifndef __MYENTRY__HPP
#define __MYENTRY__HPP
#include <iostream>
#include<sys/types.h>
#include <string>
#include <time.h>

class Entry
{
    int time;
    int pid;
    bool def;
    
    public:
	Entry(int t, int p);	
	void printEntry();
	void setTime(int t);
	void setPid(int p);
	void setDefByInit();
	void setDefByWriter();
};


#endif

