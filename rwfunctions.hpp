#ifndef __RWFUNCTIONS__HPP
#define __RWFUNCTIONS__HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <string>

int initializer(char* c);

void callCleanUp(int id);

#endif

