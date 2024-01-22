/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include <iostream>
#include <string>
#include <vector>

// Book Data Structure
class Book{
public:

//constructor
Book() = default;
Book(const std::string& title, const std::string& author, const std::string& ISBN, bool available = true)
    : m_title(title), m_author(author), m_ISBN(ISBN), m_availabilityStatus(available) {}

//getters
const std::string& getTitle() {return m_title;}
const std::string& getAuthor() {return m_author;}
const std::string& getISBN() {return m_ISBN;}
bool getAvailablityStatus() {return m_availabilityStatus;}

//setters
void setTitle(const std::string& title) {m_title = title;} 
void setAuthor(const std::string& author) {m_author = author;} 
void setISBN(const std::string& ISBN) {m_ISBN = ISBN;} 
void setAvailablityStatus(bool status) {m_availabilityStatus = status;} 

private:
    std::string m_title{};
    std::string m_author{};
    std::string m_ISBN{};
    bool m_availabilityStatus {};
};

class LibraryCatalog
{
public:

/*TODO:
    - get/list books using ISBN, author name, book name
    - check if catalog is empty <rare case>
    - add book
    - remove book
    - display catalog
*/

private:
    std::vector<Book> m_list_of_books;      // store list of books
    std::vector<int> m_no_of_books_available;   // no. of copies of books present
};


int main()
{
    Book english("10 ways to learn efficient english", "Leonardo Caprio", "345345345");

    std::cout<<english.getTitle()<<std::endl;
    std::cout<<english.getAuthor()<<std::endl;
    std::cout<<english.getAvailablityStatus()<<std::endl;
    std::cout<<english.getISBN()<<std::endl;

    return 0;
}