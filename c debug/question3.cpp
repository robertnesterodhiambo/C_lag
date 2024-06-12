#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <curl/curl.h>

// Function to write data fetched by libcurl to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc &e) {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

// Function to fetch content from a URL using libcurl
std::string fetchURL(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

// Function to extract image URLs from HTML using regex
std::vector<std::string> extractImageURLs(const std::string& html) {
    std::vector<std::string> imageUrls;
    std::regex imgRegex(R"(<img[^>]*src=["']([^"']*)["'])", std::regex::icase);
    std::regex hrefRegex(R"(<a[^>]*href=["']([^"']*\.(jpg|jpeg|png|gif))["'])", std::regex::icase);
    std::smatch match;
    std::string::const_iterator searchStart(html.cbegin());

    while (std::regex_search(searchStart, html.cend(), match, imgRegex)) {
        imageUrls.push_back(match[1]);
        searchStart = match.suffix().first;
    }

    searchStart = html.cbegin();
    while (std::regex_search(searchStart, html.cend(), match, hrefRegex)) {
        imageUrls.push_back(match[1]);
        searchStart = match.suffix().first;
    }

    return imageUrls;
}

// Main function
int main() {
    std::string url = "http://www.enseignement.polytechnique.fr/index.html";
    std::string htmlContent = fetchURL(url);

    if (htmlContent.empty()) {
        std::cerr << "Failed to fetch the web page content." << std::endl;
        return 1;
    }

    std::vector<std::string> imageUrls = extractImageURLs(htmlContent);

    for (const std::string& imageUrl : imageUrls) {
        std::cout << imageUrl << std::endl;
    }

    return 0;
}
