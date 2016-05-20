#ifndef __MYFUNCTIONS__HPP
#define __MYFUNCTIONS__HPP
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

int createSharedMemory(int s);

void initializeSemaphore(sem_t* s, int pshared, int value);

int getNumber(char* c);

void detachSharedMemory(void* v);

std::string getString(int n);

void printtime();

#endif

