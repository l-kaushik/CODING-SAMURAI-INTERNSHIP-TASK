#ifndef LIBRARY_CATALOG
#define LIBRARY_CATALOG

#include "Book.h"
#include <vector>

class LibraryCatalog
{
public:
    /*TODO:
        - get/list books using ISBN
        - check if catalog is empty <rare case>
    */

    // utility
    bool isEmpty();
    const std::string simplifyISBN(const std::string &ISBN);
    const std::string simplifyISBN(const Book& book);

    // search a book
    bool isPresent(const std::string &ISBN);
    bool isPresent(const Book& book);

    // getters
    const Book *getBook(const std::string &ISBN);

    // add book in catalog
    void addBook(const Book &book);

    // remove book from catalog
    void removeBook(const std::string &ISBN);

    // dislpay catalog
    void display();

private:
    std::vector<Book> m_catalog{}; // store list of books
};

#endif