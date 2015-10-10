#include "server.h"

Server::Server(int threads)
{
    numThreads = threads;
    sem_init(&sem_updateCounts, 0, 1);
    sem_init(&sem_filelistaccess, 0, 1);
}

Server::~Server()
{
    sem_destroy(&sem_updateCounts);
    sem_destroy(&sem_filelistaccess);
}

void Server::addFile(string filename)
{
    fileList.push(filename);
}

void Server::lockAndAdd(unsigned long * val, unsigned long addition)
{
    sem_wait(&sem_updateCounts);
    &val += addition;
    sem_post(&sem_updateCounts);
}

/**
 * Get the next file for processing from the stack.
 */
string Server::getNextFile()
{
    sem_wait(&sem_filelistaccess);
    if (fileList.empty())
        throw runtime_error("No more files.");
    string file = fileList.top();
    fileList.pop();
    sem_post(&sem_filelistaccess);
    return file;
}

/**
 * Run the server with the specified number of threads.
 */
void Server::run()
{
    if (numThreads == 1)
    {
        string next;
        struct stat fileinfo;
        for (;;)
        {
            try
            {
                next = this->getNextFile();
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
        }
    } else
    {
    }

    cout << "Bad files: " << count_badFiles << endl;
    cout << "Directories: " << count_directories << endl;
    cout << "Regular Files: " << count_regularFiles << endl;
    cout << "Special Files: " << count_specialFiles << endl;
    cout << "Regular File Bytes: " << bytes_regularFiles << endl;
    cout << "Text Files: " << count_textFiles << endl;
    cout << "Text File Bytes: " << bytes_textFiles << endl;
}

