#include "smartsyncdaemon.h"

using namespace SmartSync;

#define BUFFER_SIZE 4096

SmartSyncDaemon::SmartSyncDaemon()
{
}

bool SmartSyncDaemon::init()
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

bool SmartSyncDaemon::start()
{

    if(!init())
        return false;

    while(true)
    {
        //check here for mpds...
        simpleSearch("ccnx:/itec1/dash/bunny/bunny_full.mpd");
        sleep(3);
    }

    return true;
}

void SmartSyncDaemon::simpleSearch(const std::string& mpd_name )
{
    BOOST_FOREACH(std::string cur, names)
    {
        if ( cur.compare(mpd_name) == 0)
        {
            // we already processed this mpd...
            return;
        }
    }

    // we have to create the interest
    fprintf(stderr, "processing %s\n", mpd_name.c_str());

    struct ccn_charbuf *name = ccn_charbuf_create();
    struct ccn_charbuf *templ = ccn_charbuf_create();
    struct ccn_charbuf *resultbuf = ccn_charbuf_create();
    struct ccn_parsed_ContentObject pcobuf = { 0 };

    if(ccn_name_from_uri(name, mpd_name.c_str()) < 0)
    {
     fprintf(stderr, "Bad CCN URI: %s\n", mpd_name.c_str());
     return;
    }

    ccn_charbuf_append_tt(templ, CCN_DTAG_Interest, CCN_DTAG);
    ccn_charbuf_append_tt(templ, CCN_DTAG_Name, CCN_DTAG);
    ccn_charbuf_append_closer(templ);
    ccnb_tagged_putf(templ, CCN_DTAG_Scope, "%d", 1); // Scope 1 limits propagation to the applications on the originating host.
    ccn_charbuf_append_closer(templ);

    //peek for the mpd

    bool mpd_found = false;
    int res = ccn_get(connection, name, templ, 100, resultbuf, &pcobuf, NULL, 0);

    if (res >= 0)
    {
     if (resultbuf->length > 0)
     {
         names.push_back(mpd_name);
         resultbuf->length = 0; //reset buffer
         mpd_found = true;
     }
    }
    else
     fprintf(stderr, "SmartSync: No MPD found yet.\n");

    if(mpd_found)
    {
        struct ccn_fetch_stream *fs = ccn_fetch_open(cf, name, mpd_name.c_str(), templ, 16, (CCN_V_HIGH | CCN_V_NESTOK), 1);
        char buf[BUFFER_SIZE];
        int ret = 0;

        while(true)
        {
            if(ccn_fetch_poll(cf) > 0)
            {
                ret = ccn_fetch_read(fs, buf, BUFFER_SIZE);
                ccn_charbuf_append(resultbuf, buf, ret);

                if(ret == CCN_FETCH_READ_END ||ret == CCN_FETCH_READ_TIMEOUT)
                {
                    //fprintf(stderr, "Result = %s\n", resultbuf->buf);
                    std::string mpd_path = storeFile(resultbuf, mpd_name);
                    SimpleDownloader downloader(mpd_path);
                    boost::thread t(downloader);

                    ccn_fetch_close(fs);
                    break;
                }
            }
            //else
                //fprintf(stderr, "ccn_fetch_poll <= 0\n");
        }
    }

    ccn_charbuf_destroy(&resultbuf);
    ccn_charbuf_destroy(&templ);
    ccn_charbuf_destroy(&name);
}

std::string SmartSyncDaemon::storeFile(ccn_charbuf *buf, std::string file_name)
{
    std::string path;
    path.append(getenv("HOME"));
    path.append("/.smartsync/");

    file_name = file_name.substr(file_name.rfind('/')+1);

    if(!boost::filesystem::exists(path))
            boost::filesystem::create_directory(path);

    path.append(file_name);
    boost::iostreams::stream_buffer<boost::iostreams::file_sink> file(path.c_str());
    std::ostream out(&file);
    out.write((char*)buf->buf, buf->length);
    out.flush();

    return path;
}
