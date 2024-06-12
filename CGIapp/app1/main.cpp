#include <iostream>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

int main() {
    Cgicc cgi;

    const CgiEnvironment& env = cgi.getEnvironment();
    const_cookie_iterator cookie;

    cout << HTTPHTMLHeader() << endl;
    cout << html() << head(title("Debugging Cookies")) << endl;
    cout << body() << h1("Debugging Cookies") << endl;

    // Output all incoming cookies
    cout << "<p>Received cookies:</p><ul>" << endl;
    for (cookie = env.getCookieList().begin(); cookie != env.getCookieList().end(); ++cookie) {
        cout << "<li>" << cookie->getName() << " = " << cookie->getValue() << "</li>" << endl;
    }
    cout << "</ul>" << endl;

    cout << body() << html() << endl;

    return 0;
}
