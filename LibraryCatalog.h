#ifndef LIBRARY_CATALOG
#define LIBRARY_CATALOG

#include "Book.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdexcept>

class LibraryCatalog
{
public:
    // utility
    bool isEmpty();
    const std::string simplifyISBN(const std::string &ISBN);
    const std::string simplifyISBN(const Book &book);

    // search a book
    bool isPresent(const std::string &ISBN);
    bool isPresent(const Book &book);

    //check availability of a book
    bool isBookAvailable(const std::string &ISBN);
    bool isBookAvailable(const Book &book);

    //alter availability of a book
    void alterAvailable(const std::string &ISBN);

    // getters
    const Book *getBook(const std::string &ISBN);

    // add book in catalog
    void addBook(const Book &book);

    // remove book from catalog
    void removeBook(const std::string &ISBN);

    //borrow book
    void borrowBook(const std::string &ISBN);
    void borrowBook(Book &book);

    //return book
    void returnBook(const std::string &ISBN);
    void returnBook(Book &book);
    
    // dislpay
    void display(const std::string &title = "");

    //Import from a file
    bool importFromText();

    //Export to a file
    bool exportToText();

private:
    std::vector<Book> m_catalog{}; // store list of books

    // getter that can modify values    
    Book* m_getBook(const std::string &ISBN);
};

// main menu function
void menu();
#endif