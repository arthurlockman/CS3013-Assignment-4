#include "crawler.h"

Crawler::Crawler(Server * s)
{
    server = s;
}

bool Crawler::StartThread()
{
    return (pthread_create(&_thread, NULL, &this->StartThreadFunction, this) == 0);
}

bool Crawler::JoinThread()
{
    return (pthread_join(_thread, NULL) == 0);
}

void * Crawler::crawl(void * crawler)
{
    Server * s = ((Crawler *)crawler)->server;

    string next;
    struct stat fileinfo;
    for (;;)
    {
        try
        {
            next = s->getNextFile();
        }
        catch (runtime_error & e)
        {
            break;
        }
        int ret = stat(next.c_str(), &fileinfo);
        if (ret < 0) //bad file, can't stat
        {
            s->lockAndAdd(&s->count_badFiles, 1);
        }
        else if (S_ISREG(fileinfo.st_mode)) //Regular file
        {
            s->lockAndAdd(&s->count_regularFiles, 1);
            s->lockAndAdd(&s->bytes_regularFiles, fileinfo.st_size);
            int infile;
            infile = open(next.c_str(), O_RDONLY);
            if (infile)
            {
                unsigned char buf;
                int cnt = read(infile, &buf, sizeof(unsigned char));
                int isprintable = 1;
                do
                {
                    if (!isprint(buf) && !isspace(buf))
                    {
                        isprintable = 0;
                        break;
                    }
                    cnt = read(infile, &buf, sizeof(unsigned char));
                }
                while (cnt == 1);
                close(infile);
                if (isprintable)
                {
                    s->lockAndAdd(&s->bytes_textFiles, fileinfo.st_size);
                    s->lockAndAdd(&s->count_textFiles, 1);
                }
            }
        }
        else if (S_ISDIR(fileinfo.st_mode)) //Directory
        {
            s->lockAndAdd(&s->count_directories, 1);
        }
        else //is a special file
        {
            s->lockAndAdd(&s->count_specialFiles, 1);
        }
    }
    return NULL;
}
