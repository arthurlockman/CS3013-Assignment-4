#include "server.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char ** argv)
{
    int threads = 1;
    if (argc == 3 && strncmp(argv[1], "thread", 6) == 0)
    {
        threads = atoi(argv[2]);
        cout << "Using " << threads << " threads." << endl;
    }
    Server server(threads);
    string lineInput;
    while (getline(cin,lineInput)) {
        /* cout << lineInput << endl; */
        server.addFile(lineInput);
    }
    server.run();
}
