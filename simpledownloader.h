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

#include <fstream>
#include <string>

namespace SmartSync
{
    class SimpleDownloader
    {
       public:
        SimpleDownloader(std::string mpd_uri);
        ~SimpleDownloader();
        void operator()();

        protected:
            std::string mpd_uri;
            dash::IDASHManager* manager;

    };

}
#endif // SIMPLEDOWNLOADER_H
