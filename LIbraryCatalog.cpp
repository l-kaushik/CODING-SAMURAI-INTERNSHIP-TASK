#include "LibraryCatalog.h"

// utility
bool LibraryCatalog::isEmpty()
{
    if (m_catalog.size() == 0)
        return true;
    return false;
}

// search a book
bool LibraryCatalog::isPresent(const std::string &ISBN)
{
    return getBook(ISBN) ? true : false;
}

// getters
const Book* LibraryCatalog::getBook(const std::string &ISBN)
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
void LibraryCatalog::addBook(const Book &book)
{
    // TODO: what if book is already present?
    m_catalog.push_back(book);
    std::cout << "Book added to the catalog.\n";
}

// remove book from catalog
void LibraryCatalog::removeBook(const std::string &ISBN)
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
void LibraryCatalog::displayCatalog()
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
