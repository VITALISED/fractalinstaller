#include "download_file.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

void DownloadFile(const std::string &url, const std::string &outputFilePath)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;

    curl = curl_easy_init();
    if (curl)
    {
        const char *output_cstr = outputFilePath.c_str();
        fp = fopen(output_cstr, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        std::printf("%x", res);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    curl_easy_cleanup(curl);
}