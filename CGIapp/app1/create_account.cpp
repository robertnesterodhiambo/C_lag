#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    // Print necessary CGI headers
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html><body>";

    // Retrieve form data from CGI environment
    string username, password;
    cin >> username >> password;

    // Open file for appending accounts
    ofstream outfile("/home/dragon/Git/C_lag/CGIapp/accounts.txt", ios::app);  // Adjust path as needed
    if (!outfile) {
        cerr << "Error opening file for writing!" << endl;
        return EXIT_FAILURE;
    }

    // Write username and password to file
    outfile << username << " " << password << endl;
    outfile.close();

    // Display success message
    cout << "<h2>Account created successfully!</h2>";

    cout << "</body></html>";
    return EXIT_SUCCESS;
}
