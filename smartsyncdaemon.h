#ifndef SMARTSYNCDAEMON_H
#define SMARTSYNCDAEMON_H

extern "C" {
#include <ccn/fetch.h>
#include <ccn/ccn.h>
#include <ccn/charbuf.h>
#include <ccn/uri.h>
#include <ccn/header.h>
#include <ccn/reg_mgmt.h>
}

#include <iostream>
#include <string>
#include <fstream>

#include <boost/container/list.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>


#include "simpledownloader.h"

namespace SmartSync
{
    class SmartSyncDaemon
    {
        public:
            SmartSyncDaemon(unsigned int bandwidth_limit);
            bool start();

        protected:

            bool init();
            void simpleSearch(const std::string& mpd_name);
            std::string storeFile(ccn_charbuf *buf, std::string file_name);

            struct ccn *connection;
            struct ccn_fetch *cf;
            boost::container::list<std::string> names;
            unsigned int bandwidth_limit;
    };
}
#endif // SMARTSYNCDAEMON_H
