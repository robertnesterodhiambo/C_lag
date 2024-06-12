#include <iostream>
#include <cstdlib>
#include <cstring>
#include <mysql/mysql.h> // Include MySQL headers

using namespace std;

int main() {
    // Print HTTP header
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Account Creation Result</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";

    // Retrieve form data from environment variables
    char *data = getenv("QUERY_STRING");
    char username[100], email[100], password[100];
    
    // Parse query string to get form inputs
    sscanf(data, "username=%[^&]&email=%[^&]&password=%s", username, email, password);

    // Connect to MySQL database
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *server = "localhost";
    const char *user = "root"; // Replace with your MySQL username
    const char *password_db = "password"; // Replace with your MySQL password
    const char *database = "test1";

    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server, user, password_db, database, 0, NULL, 0)) {
        cout << "<p>Error connecting to database: " << mysql_error(conn) << "</p>\n";
        return 1;
    }

    // Prepare SQL query to insert user data
    string query = "INSERT INTO user (username, email, password) VALUES ('" + string(username) + "', '" + string(email) + "', '" + string(password) + "')";

    // Execute SQL query
    if (mysql_query(conn, query.c_str())) {
        cout << "<p>Error inserting data into table: " << mysql_error(conn) << "</p>\n";
    } else {
        cout << "<h2>Account created successfully!</h2>\n";
        cout << "<p>Username: " << username << "</p>\n";
        cout << "<p>Email: " << email << "</p>\n";
        // You can add more details as needed
    }

    // Clean up
    mysql_close(conn);

    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}
