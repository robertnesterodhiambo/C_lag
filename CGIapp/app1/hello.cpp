#include <iostream>
using namespace std;

int main() {
    // Print the HTTP header
    cout << "Content-type: text/html\r\n\r\n";

    // Print the HTML content
    cout << "<html>\n";
    cout << "<head><title>CGI Script Output</title></head>\n";
    cout << "<body>\n";
    cout << "<h1>Hello, World!</h1>\n";
    cout << "<p>This is a simple CGI script written in C++.</p>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}
