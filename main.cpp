#include <fstream>
#include <climits>

#include "smartsyncdaemon.h"

using namespace std;

int main(int argc, char *argv[])
{

    unsigned int bandwidth_limit = UINT_MAX;

    if(argc == 2)
        sscanf (argv[1], "%i", &bandwidth_limit);

    fprintf(stderr, "Running the SmartSync Daemon with bandwidth limit %ukbit/s ...\n", bandwidth_limit);

    SmartSync::SmartSyncDaemon daemon(bandwidth_limit);

    if (!daemon.start())
        fprintf(stderr, "Could not start the SmartSync Daemon\n");

    fprintf(stderr, "Exiting SmartSyncDaemon.\n");
    return 0;
}

