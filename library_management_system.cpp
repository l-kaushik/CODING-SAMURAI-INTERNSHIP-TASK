/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include <iostream>
#include <string>
#include <vector>
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

class LibraryCatalog
{
public:
    /*TODO:
        - get/list books using ISBN
        - check if catalog is empty <rare case>
    */

    // utility
    bool isEmpty()
    {
        if (m_catalog.size() == 0)
            return true;
        return false;
    }

    // search a book
    bool isPresent(const std::string &ISBN)
    {
        return getBook(ISBN) ? true : false;
    }

    // getters
    const Book *getBook(const std::string &ISBN)
    {
        if (isEmpty())
        {
            std::cout << "Catalog is empty\n";
            return nullptr;
        }

        for (auto &book : m_catalog)
        {
            // if ISBN matches remove the book
            if (book.getISBN() == ISBN)
            {
                return &book; // return book's reference
            }
        }

        return nullptr;
    }

    // add book in catalog
    void addBook(const Book &book)
    {
        // TODO: what if book is already present?
        m_catalog.push_back(book);
        std::cout << "Book added to the catalog.\n";
    }

    // remove book from catalog
    void removeBook(const std::string &ISBN)
    {
        for (auto index{m_catalog.begin()}; index != m_catalog.end(); ++index)
        {
            // if ISBN matches remove the book
            if (index->getISBN() == ISBN)
            {
                m_catalog.erase(index);
                std::cout << "Book with ISBN: " << ISBN << " has removed successfully\n";
                return;
            }
        }

        std::cout << "Book with ISBN: " << ISBN << " either not present in catalog or occuring problems in removing.\n";
    }

    // dislpay catalog
    void displayCatalog()
    {
        for (auto &book : m_catalog)
        {
            // std::cout<<book;
            std::cout << "Title: " << book.getTitle() << std::endl;
            std::cout << "Author: " << book.getAuthor() << std::endl;
            std::cout << "ISBN no.: " << book.getISBN() << std::endl;
            std::cout << std::boolalpha << "Availability Status: " << book.getAvailablityStatus() << std::endl
                      << std::endl;
        }
    }

private:
    std::vector<Book> m_catalog{}; // store list of books
};

// <-------------- FUNCTIONS OF BOOK CLASS -------------->
bool Book::isValidISBN(const std::string &ISBN)
{
    // check if ISBN is empty or not
    if (ISBN.empty())
    {
        std::cerr << "ERROR: ISBN number cannot be empty\n";
        return false;
    }

    // check if first letter is '-'
    if (ISBN[0] == '-')
    {
        std::cerr << "ERROR: ISBN cannot start with '-'\n";
        return false;
    }

    // check if last letter is '-'
    if (ISBN.back() == '-')
    {
        std::cerr << "ERROR: ISBN cannot end with '-'\n";
        return false;
    }

    // check if ISBN contains any invalid character
    for (auto &eachLetter : ISBN)
    {
        if (!(std::isdigit(eachLetter) || eachLetter == '-'))
        {
            std::cerr << "ERROR: Invalid ISBN\n";
            return false;
        }
    }

    // check for length of ISBN
    int digitsOnly{static_cast<int>(ISBN.length()) - 1 - static_cast<int>(std::count(ISBN.begin(), ISBN.end(), '-'))};

    if (!(digitsOnly == 13 || digitsOnly == 10))
    {
        std::cerr << "ERROR: Length of ISBN is must be 10 or 13";
        return false;
    }

    return true;
}

int main()
{
    Book english("10 ways to learn efficient english", "Leonardo Caprio", "345-345-3744");

    LibraryCatalog catalog;
    catalog.addBook(english);
    std::cout << catalog.isPresent("3453345345");

    catalog.displayCatalog();

    return 0;
}