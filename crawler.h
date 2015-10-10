#ifndef CRAWLER_H
#define CRAWLER_H

#include "server.h"
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

using namespace std;

class Server;

class Crawler
{
    private:
        Server * server;
        pthread_t _thread;
        static void * StartThreadFunction(void * crawler)
        {
            return ((Crawler *)crawler)->crawl(crawler);
        }
    protected:
        void * crawl(void * Crawler);
    public:
        Crawler(Server * s);
        bool StartThread();
        bool JoinThread();
};

#endif
