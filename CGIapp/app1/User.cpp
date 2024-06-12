#include "User.h"
#include <fstream>
#include <sstream>

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

std::string User::getUsername() const {
    return username;
}

bool User::checkPassword(const std::string& password) const {
    return this->password == password;
}

void User::addUserToFile(const std::string& filename, const User& user) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << user.username << "," << user.password << "\n";
        file.close();
    }
}

std::vector<User> User::fetchUsersFromFile(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line, username, password;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::istringstream ss(line);
            getline(ss, username, ',');
            getline(ss, password, ',');
            users.emplace_back(username, password);
        }
        file.close();
    }
    return users;
}
