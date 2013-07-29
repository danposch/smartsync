#include "simpledownloader.h"

using namespace SmartSync;

SimpleDownloader::SimpleDownloader(std::string mpd_uri)
{
    this->mpd_uri = mpd_uri;
    //manager = CreateDashManager();
    //manager->Open((char*)mpd.c_str());
}

SimpleDownloader::~SimpleDownloader()
{

}

void SimpleDownloader::operator()()
{
    // here we sould start downloading all segments
    fprintf(stderr, "Test\n");
}
