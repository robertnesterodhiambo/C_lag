#ifndef BLOGPOST_H
#define BLOGPOST_H

#include <string>
#include <vector>
#include <fstream>

class BlogPost {
public:
    BlogPost(const std::string& title, const std::string& content, int rating);
    void setTitle(const std::string& title);
    void setContent(const std::string& content);
    void setRating(int rating);
    std::string getTitle() const;
    std::string getContent() const;
    int getRating() const;

    static std::vector<BlogPost> fetchPostsFromFile(const std::string& filename);
    static void addPostToFile(const std::string& filename, const BlogPost& post);
    static void updateRatingInFile(const std::string& filename, int postID, int newRating);

private:
    std::string title;
    std::string content;
    int rating;
};

#endif
