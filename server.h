#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <string>
#include <stack>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include "crawler.h"
#include <vector>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

class Crawler;

class Server
{
    private:
        int numThreads;
        sem_t sem_updateCounts;
        sem_t sem_filelistaccess;
        stack<string> fileList;
        struct timeval start;
    public:
        Server(int threads);
        ~Server();
        void addFile(string filename);
        void lockAndAdd(unsigned long * val, unsigned long addition);
        string getNextFile();
        void run();
        //Variables to hold counts.
        unsigned long count_badFiles = 0;
        unsigned long count_directories = 0;
        unsigned long count_specialFiles = 0;
        unsigned long count_regularFiles = 0;
        unsigned long bytes_regularFiles = 0;
        unsigned long count_textFiles = 0;
        unsigned long bytes_textFiles = 0;
};

#endif
