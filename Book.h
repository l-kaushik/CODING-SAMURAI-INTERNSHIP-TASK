#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <algorithm>

// Book Data Structure
class Book
{
public:
    // constructor
    Book() = default;
    Book(const std::string &title, const std::string &author, const std::string &ISBN, bool available = true)
        : m_title(title), m_author(author), m_ISBN(ISBN), m_availabilityStatus(available)
    {
        if (!isValidISBN(ISBN))
            exit(EXIT_FAILURE);
    }

    // utility
    bool isValidISBN(const std::string& ISBN);

    // getters
    const std::string &getTitle() { return m_title; }
    const std::string &getAuthor() { return m_author; }
    const std::string &getISBN() { return m_ISBN; }
    bool getAvailablityStatus() { return m_availabilityStatus; }

    // setters
    void setTitle(const std::string &title) { m_title = title; }
    void setAuthor(const std::string &author) { m_author = author; }
    void setISBN(const std::string &ISBN) { m_ISBN = ISBN; }
    void setAvailablityStatus(bool status) { m_availabilityStatus = status; }

    // TODO: implement dislpay function

private:
    std::string m_title{};
    std::string m_author{};
    std::string m_ISBN{};
    bool m_availabilityStatus{};
};

#endif