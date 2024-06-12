#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for getenv()
#include <cstring> // for strtok()

using namespace std;

// Function to read and return the contents of a file as a string
string getFileContents(const char *fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();
    return content;
}

int main() {
    // Print HTTP header content type
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html><body>\n";

    // Read and output the contents of index.html
    string htmlContent = getFileContents("/home/dragon/Git/C_lag/CGIapp/index.html");
    cout << htmlContent;

    // Retrieve form data from CGI environment variables
    char *data;
    data = getenv("QUERY_STRING");
    cout << "<p>QUERY_STRING: " << (data ? data : "null") << "</p>\n";

    // Parse form data (example assumes 'username', 'password', 'usertype' fields)
    char *token = strtok(data, "&");
    string username, password, usertype;
    while (token != NULL) {
        char *key = strtok(token, "=");
        char *value = strtok(NULL, "=");
        if (key && value) {
            if (strcmp(key, "username") == 0) {
                username = value;
            } else if (strcmp(key, "password") == 0) {
                password = value;
            } else if (strcmp(key, "usertype") == 0) {
                usertype = value;
            }
        }
        token = strtok(NULL, "&");
    }

    // Debug prints
    cout << "<p>Username: " << username << "</p>\n";
    cout << "<p>Password: " << password << "</p>\n";
    cout << "<p>User Type: " << usertype << "</p>\n";

    cout << "</body></html>\n";

    return 0;
}
