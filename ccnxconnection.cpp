#include "ccnxconnection.h"

#define BUFFER_SIZE 4096

using namespace SmartSync;

CCNxConnection::CCNxConnection()
{
    init();
}

CCNxConnection::~CCNxConnection()
{
    if(this->cf != NULL)
        ccn_fetch_destroy(cf);

    if(connection != NULL)
    {
        ccn_disconnect(connection);
        ccn_destroy(&connection);
    }

}

bool CCNxConnection::init()
{
    if( (connection = ccn_create()) == NULL )
    {
        fprintf(stderr, "ccn_create() failed.\n");
        return false;
    }

    if( ccn_connect(connection, NULL) == -1)
    {
        fprintf(stderr, "ccn_connect() failed. Make sure ccnd is running!\n");
        return false;
    }

    if( (this->cf = ccn_fetch_new(connection)) == NULL)
    {
        fprintf(stderr, "ccn_fetch_new() failed.\n");
        return false;
    }

    return true;
}

ccn_charbuf* CCNxConnection::download(std::string file_uri)
{

    fprintf(stderr, "CCN URI: %s\n", file_uri.c_str());

    struct ccn_charbuf *name = ccn_charbuf_create();
    struct ccn_charbuf *resultbuf = ccn_charbuf_create();

    if(ccn_name_from_uri(name, file_uri.c_str()) < 0)
    {
     fprintf(stderr, "Bad CCN URI: %s\n", file_uri.c_str());
     return NULL;
    }

    struct ccn_fetch_stream *fs = ccn_fetch_open(cf, name, file_uri.c_str(), NULL, 16, (CCN_V_HIGH | CCN_V_NESTOK), 1);
    char buf[BUFFER_SIZE];
    int ret = 0;

    while(true)
    {
        if(ccn_fetch_poll(cf) > 0)
        {
            ret = ccn_fetch_read(fs, buf, BUFFER_SIZE);
            fprintf(stderr, "ret = %d\n", ret);
            ccn_charbuf_append(resultbuf, buf, ret);

            if(ret == CCN_FETCH_READ_END ||ret == CCN_FETCH_READ_TIMEOUT)
            {
                ccn_fetch_close(fs);
                break;
            }
        }
        /*else
        {
            fprintf(stderr, "ccn_fetch_poll <= 0\n");
            sleep(1);
        }*/
    }

    return resultbuf;
}
