#ifndef CCNXCONNECTION_H
#define CCNXCONNECTION_H

extern "C" {
#include <ccn/fetch.h>
#include <ccn/ccn.h>
#include <ccn/charbuf.h>
#include <ccn/uri.h>
#include <ccn/header.h>
#include <ccn/reg_mgmt.h>
}

#include <string>

namespace SmartSync
{

    class CCNxConnection
    {
    public:
        CCNxConnection();
        ~CCNxConnection();

        ccn_charbuf *download(std::string file_uri);

    private:

        bool init();
        struct ccn *connection;
        struct ccn_fetch *cf;
    };
}
#endif // CCNXCONNECTION_H
