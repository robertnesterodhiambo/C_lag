#include <iostream>
#include <fstream>  // For file handling
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

int main() {
    Cgicc cgi;

    // Retrieve form data
    form_iterator username = cgi.getElement("username");
    form_iterator password = cgi.getElement("password");
    form_iterator email = cgi.getElement("email");

    cout << HTTPHTMLHeader() << endl;
    cout << html() << head(title("Registration Result")) << endl;
    cout << body() << h1("Registration Result") << endl;

    // Dummy registration logic (replace with actual logic)
    if (username != cgi.getElements().end() && password != cgi.getElements().end() && email != cgi.getElements().end()) {
        string usernameValue = **username;
        string passwordValue = **password;
        string emailValue = **email;

        // Example: Store user information in a text file (replace with database storage)
        ofstream usersFile("users.txt", ios::app);  // Open file for appending
        if (usersFile.is_open()) {
            usersFile << usernameValue << "," << passwordValue << "," << emailValue << endl;
            usersFile.close();
            cout << p("Account created successfully!") << endl;
        } else {
            cout << p("Error: Unable to open file for user storage.") << endl;
        }
    } else {
        cout << p("Incomplete form submission.") << endl;
    }

    cout << body() << html() << endl;

    return 0;
}
