#include <iostream>
#include <fstream>      // File handling
#include <mysql/mysql.h>  // MariaDB/MySQL C Connector header

using namespace std;

// Function to insert user data into MySQL
void insertData(const string& username, const string& email, const string& password) {
    MYSQL *conn;

    // Initialize connection handler
    conn = mysql_init(NULL);

    // Connect to MySQL database
    if (!mysql_real_connect(conn, "localhost", "root", "your_password", "test1", 0, NULL, 0)) {
        cerr << "Connection error: " << mysql_error(conn) << endl;
        return;
    }

    // Prepare SQL query to insert data into 'user' table
    string query = "INSERT INTO user (username, email, password) VALUES ('" + username + "', '" + email + "', '" + password + "')";

    // Execute SQL query
    if (mysql_query(conn, query.c_str())) {
        cerr << "Query error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return;
    }

    cout << "User created successfully!" << endl;

    // Close MySQL connection
    mysql_close(conn);
}

// Function to authenticate user login
bool loginUser(const string& username, const string& password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection handler
    conn = mysql_init(NULL);

    // Connect to MySQL database
    if (!mysql_real_connect(conn, "localhost", "root", "your_password", "test1", 0, NULL, 0)) {
        cerr << "Connection error: " << mysql_error(conn) << endl;
        return false;
    }

    // Prepare SQL query to fetch user data
    string query = "SELECT * FROM user WHERE username = '" + username + "' AND password = '" + password + "'";
    
    // Execute SQL query
    if (mysql_query(conn, query.c_str())) {
        cerr << "Query error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return false;
    }

    // Store query result
    res = mysql_store_result(conn);

    // Check if user exists and password matches
    if ((row = mysql_fetch_row(res)) != NULL) {
        mysql_free_result(res);
        mysql_close(conn);
        return true;
    } else {
        mysql_free_result(res);
        mysql_close(conn);
        return false;
    }
}

// Function to create a post and store it in a text file
void createPost(const string& username, const string& postContent) {
    ofstream outFile;
    string filename = username + "_posts.txt";

    // Check if file exists, create it if missing
    if (!ifstream(filename.c_str())) {
        outFile.open(filename.c_str());
        outFile.close();
    }

    outFile.open(filename.c_str(), ios::app); // Append mode

    if (!outFile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Write post content to file
    outFile << postContent << endl;
    outFile.close();

    cout << "Post created and saved successfully!" << endl;
}

int main() {
    string choice;
    cout << "Welcome! Do you want to:" << endl;
    cout << "1. Create an account" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == "1") {
        // Account creation process
        string username, email, password;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

        // Insert data into MySQL
        insertData(username, email, password);
    } else if (choice == "2") {
        // Login process
        string loginUsername, loginPassword;
        cout << "Enter username for login: ";
        cin >> loginUsername;
        cout << "Enter password for login: ";
        cin >> loginPassword;

        if (loginUser(loginUsername, loginPassword)) {
            cout << "Login successful!" << endl;

            // Create a post
            string postContent;
            cout << "\nEnter your post content: ";
            cin.ignore(); // Clear input buffer
            getline(cin, postContent);

            // Save post to file
            createPost(loginUsername, postContent);
        } else {
            cout << "Login failed. Incorrect username or password." << endl;
        }
    } else {
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }

    return 0;
}
