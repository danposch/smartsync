#include "simpledownloader.h"

using namespace SmartSync;

SimpleDownloader::SimpleDownloader(std::string mpd_uri, unsigned bandwidth_limit)
{
    manager = CreateDashManager();
    mpd = manager->Open((char*)mpd_uri.c_str());
    lastSegmentBytes = 0;
    this->bandwidth_limit = bandwidth_limit;
}

SimpleDownloader::~SimpleDownloader()
{
}

void SimpleDownloader::operator()()
{
    // here we start downloading all segments

    CCNxConnection con;
    std::string base_url = mpd->GetBaseUrls().at(0)->GetUrl();

    if(base_url.find("http://") != std::string::npos)
    {
        base_url = std::string("ccnx:/").append(base_url.substr(7));
    }

    //fprintf(stderr, "Base Url = %s", base_url.c_str());

    std::vector<dash::mpd::IPeriod*> periods =  mpd->GetPeriods();
    ccn_charbuf* seg = NULL;
    for(unsigned int i=0; i<periods.size(); i++)
    {
        std::vector<dash::mpd::ISegmentURL *> slist = periods.at(i)->GetAdaptationSets().at(0)->GetRepresentation().at(0)->GetSegmentList()->GetSegmentURLs();
        for(unsigned int k=0; k<slist.size(); k++)
        {
             gettimeofday(&start, NULL); //restart measurement

            while(getDownloadRate() > bandwidth_limit)
                usleep(5000); //postpone download for 5ms

            seg = con.download(base_url + slist.at(k)->GetMediaURI());
            while(seg == NULL)
            {   seg = con.download(base_url + slist.at(k)->GetMediaURI());
                fprintf(stderr, "Error Downloading %s\n", (base_url + slist.at(k)->GetMediaURI()).c_str());
            }

            lastSegmentBytes = seg->length;
            fprintf(stderr, "Downloaded %s\n", (base_url + slist.at(k)->GetMediaURI()).c_str());
        }
    }
}

unsigned int SimpleDownloader::getDownloadRate()
{
    struct timeval end;
    gettimeofday(&end, NULL);
    long elapsed_ms = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
         elapsed_ms /= 1000;

    if(elapsed_ms < 1 )
        elapsed_ms = 1;

    unsigned int rate_kbits = ((lastSegmentBytes*8)/(elapsed_ms));

    return rate_kbits;
}
