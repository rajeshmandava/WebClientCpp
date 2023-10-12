#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size *nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main(){
    CURL* curl = curl_easy_init();
    if(!curl){
        std::cerr << "Failed to initialize libcurl." << std::endl;
        return 1;
    }

    // Set the target URL
    const char* url = "http://localhost";
    curl_easy_setopt(curl, CURLOPT_URL, url);

    //Set the callback function to handle the response
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    //Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);

    // check for errors
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        //Print the response
        std::cout << "Response from " << url << ":\n" << response << std::endl;
    }
    // Cleanup
    curl_easy_cleanup(curl);

    return 0;
}

