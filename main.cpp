#include <fstream>

#include "smartsyncdaemon.h"

using namespace std;

int main()
{
    fprintf(stderr, "Running the SmartSync Daemon...\n");

    SmartSync::SmartSyncDaemon daemon;

    if (!daemon.start())
        fprintf(stderr, "Could not start the SmartSync Daemon\n");

    fprintf(stderr, "Exiting SmartSyncDaemon.\n");
    return 0;
}

