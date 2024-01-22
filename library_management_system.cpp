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

//TODO: implement dislpay function

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
*/

//add book in catalog
void addBook(const Book& book)
{
    //TODO: what if book is already present?
    m_catalog.push_back(book);
    std::cout<<"Book added to the catalog.\n";
}

// remove book from catalog
void removeBook(const std::string& ISBN)
{   
    for(auto index{m_catalog.begin()}; index != m_catalog.end(); ++index)
    {
        // if ISBN matches remove the book
        if(index->getISBN() == ISBN){
            m_catalog.erase(index);
            std::cout<<"Book with ISBN: "<< ISBN << " has removed successfully\n";
            return;
        }
    }

    std::cout<<"Book with ISBN: "<< ISBN << " either not present in catalog or occuring problems in removing.\n";
}

// dislpay catalog
void displayCatalog()
{
    for (auto &book: m_catalog)
    {
        // std::cout<<book;
        std::cout<<"Title: "<<book.getTitle()<<std::endl;
        std::cout<<"Author: "<<book.getAuthor()<<std::endl;
        std::cout<<"ISBN no.: "<<book.getISBN()<<std::endl;
        std::cout<<"Availability Status: "<<book.getAvailablityStatus()<<std::endl<<std::endl;
    }
}

private:
    std::vector<Book> m_catalog{};      // store list of books
};


int main()
{
    Book english("10 ways to learn efficient english", "Leonardo Caprio", "345345345");

    LibraryCatalog catalog;
    catalog.addBook(english);
    catalog.displayCatalog();
    catalog.removeBook(english.getISBN());
    catalog.displayCatalog();

    return 0;
}