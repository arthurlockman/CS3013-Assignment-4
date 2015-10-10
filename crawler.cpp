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
                count_badFiles++;
            }
            else if (S_ISREG(fileinfo.st_mode)) //Regular file
            {
                //TODO: check if is text file
                count_regularFiles++;
                bytes_regularFiles += fileinfo.st_size;
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
                        bytes_textFiles += fileinfo.st_size;
                        count_textFiles++;
                    }
                }
            }
            else if (S_ISDIR(fileinfo.st_mode)) //Directory
            {
                count_directories++;
            }
            else //is a special file
            {
                count_specialFiles++;
            }
    return NULL;
}
