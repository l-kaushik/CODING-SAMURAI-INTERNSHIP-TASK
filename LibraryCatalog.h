#ifndef LIBRARY_CATALOG
#define LIBRARY_CATALOG

#include "Book.h"
#include <vector>

class LibraryCatalog
{
public:
    /*TODO:
        - get/list books using ISBN
    */

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

    // dislpay
    void display(const std::string &title = "");

private:
    std::vector<Book> m_catalog{}; // store list of books

    // getter that can modify values    
    Book* m_getBook(const std::string &ISBN);
};

#endif