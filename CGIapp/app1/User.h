#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    User(const std::string& username, const std::string& password);
    std::string getUsername() const;
    bool checkPassword(const std::string& password) const;
    static void addUserToFile(const std::string& filename, const User& user);
    static std::vector<User> fetchUsersFromFile(const std::string& filename);

private:
    std::string username;
    std::string password;
};

#endif
