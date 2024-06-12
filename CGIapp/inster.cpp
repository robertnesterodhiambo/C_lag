#include <iostream>
#include <mysql/mysql.h>

using namespace std;

// Function to connect to MySQL and insert data into the 'user' table
void insertUserData(const string& username, const string& email, const string& password) {
    MYSQL *conn;

    // Initialize connection handler
    conn = mysql_init(NULL);

    // Connect to MySQL database using the XAMPP socket path
    if (!mysql_real_connect(conn, "localhost", "root", "", "test1", 0, "/opt/lampp/var/mysql/mysql.sock", 0)) {
        cerr << "Connection error: " << mysql_error(conn) << endl;
        return;
    }

    // Construct INSERT query
    string query = "INSERT INTO user (username, email, password) VALUES ('" + username + "', '" + email + "', '" + password + "')";

    // Execute query to insert data
    if (mysql_query(conn, query.c_str())) {
        cerr << "Query error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return;
    }

    // Print success message
    cout << "User data inserted successfully!" << endl;

    // Close MySQL connection
    mysql_close(conn);
}

int main() {
    // Example: Inserting a user
    string username = "johndoe";
    string email = "johndoe@example.com";
    string password = "securepassword123";

    // Call function to insert user data into MySQL table
    insertUserData(username, email, password);

    return 0;
}
