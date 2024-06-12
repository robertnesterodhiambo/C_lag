#include "BlogPost.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>

BlogPost::BlogPost(const std::string& title, const std::string& content, int rating)
    : title(title), content(content), rating(rating) {}

void BlogPost::setTitle(const std::string& title) {
    this->title = title;
}

void BlogPost::setContent(const std::string& content) {
    this->content = content;
}

void BlogPost::setRating(int rating) {
    this->rating = rating;
}

std::string BlogPost::getTitle() const {
    return title;
}

std::string BlogPost::getContent() const {
    return content;
}

int BlogPost::getRating() const {
    return rating;
}

std::vector<BlogPost> BlogPost::fetchPostsFromFile(const std::string& filename) {
    std::vector<BlogPost> posts;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, content;
        int rating;
        if (!(iss >> std::quoted(title) >> std::quoted(content) >> rating)) { break; } // error
        posts.emplace_back(title, content, rating);
    }
    return posts;
}

void BlogPost::addPostToFile(const std::string& filename, const BlogPost& post) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << std::quoted(post.getTitle()) << " "
             << std::quoted(post.getContent()) << " "
             << post.getRating() << std::endl;
    }
}

void BlogPost::updateRatingInFile(const std::string& filename, int postID, int newRating) {
    std::vector<BlogPost> posts = fetchPostsFromFile(filename);
    if (postID >= 0 && postID < posts.size()) {
        posts[postID].setRating(newRating);
        std::ofstream file(filename, std::ios::trunc);
        if (file.is_open()) {
            for (const auto& post : posts) {
                file << std::quoted(post.getTitle()) << " "
                     << std::quoted(post.getContent()) << " "
                     << post.getRating() << std::endl;
            }
        }
    }
}
