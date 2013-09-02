#ifndef SIMPLEDOWNLOADER_H
#define SIMPLEDOWNLOADER_H

extern "C" {
#include <ccn/fetch.h>
#include <ccn/ccn.h>
#include <ccn/charbuf.h>
#include <ccn/uri.h>
#include <ccn/header.h>
#include <ccn/reg_mgmt.h>
}

#include "libdash.h"
#include <boost/shared_ptr.hpp>

#include <fstream>
#include <string>
#include <sys/time.h>
#include <unistd.h>

#include "ccnxconnection.h"

namespace SmartSync
{
    class SimpleDownloader
    {
       public:
        SimpleDownloader(std::string mpd_uri, unsigned int bandwidth_limit);
        ~SimpleDownloader();
        void operator()();

        protected:
            dash::mpd::IMPD* mpd;
            dash::IDASHManager* manager;
            struct timeval start;
            unsigned long bytesDownloaded;
            unsigned int bandwidth_limit;

            unsigned int getDownloadRate();

    };

}
#endif // SIMPLEDOWNLOADER_H
