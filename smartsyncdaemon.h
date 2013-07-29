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

#include <boost/container/list.hpp>
#include <boost/foreach.hpp>

namespace SmartSync
{
    class SmartSyncDaemon
    {
        public:
            SmartSyncDaemon();
            bool start();

        private:

            bool init();
            void simpleSearch(const std::string& mpd_name);

            struct ccn *connection;
            struct ccn_fetch *cf;
            boost::container::list<std::string> names;
    };
}
#endif // SMARTSYNCDAEMON_H
