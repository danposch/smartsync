#include "simpledownloader.h"

using namespace SmartSync;

SimpleDownloader::SimpleDownloader(std::string mpd_uri)
{
    manager = CreateDashManager();
    mpd = manager->Open((char*)mpd_uri.c_str());
}

SimpleDownloader::~SimpleDownloader()
{
}

void SimpleDownloader::operator()()
{
    // here we sould start downloading all segments

    CCNxConnection con;
    std::string base_url = mpd->GetBaseUrls().at(0)->GetUrl();

    if(base_url.find("http://") != std::string::npos)
    {
        base_url = std::string("ccnx:/").append(base_url.substr(7));
    }

    //fprintf(stderr, "Base Url = %s", base_url.c_str());

    std::vector<dash::mpd::IPeriod*> periods =  mpd->GetPeriods();
    for(unsigned int i=0; i<periods.size(); i++)
    {
        std::vector<dash::mpd::ISegmentURL *> slist = periods.at(i)->GetAdaptationSets().at(0)->GetRepresentation().at(0)->GetSegmentList()->GetSegmentURLs();

        for(unsigned int k=0; k<slist.size(); k++)
        {
            if(con.download(base_url + slist.at(k)->GetMediaURI()) != NULL)
                fprintf(stderr, "Downloaded %s\n", (base_url + slist.at(k)->GetMediaURI()).c_str());
            else
                fprintf(stderr, "Error Downloading %s\n", (base_url + slist.at(k)->GetMediaURI()).c_str());
        }
    }
}
