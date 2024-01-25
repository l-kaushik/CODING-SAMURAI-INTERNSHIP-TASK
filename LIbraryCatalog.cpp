#include "LibraryCatalog.h"

// UTILITY FUNCIONS
bool LibraryCatalog::isEmpty()
{
    if (m_catalog.size() == 0)
        return true;
    return false;
}

// return only digits from ISBN
// eg:- 123-456-7890 = 1234567890

const std::string LibraryCatalog::simplifyISBN(const std::string &ISBN)
{
    std::string digitsOnly(ISBN);
    digitsOnly.erase(std::remove(digitsOnly.begin(), digitsOnly.end(), '-'), digitsOnly.end());
    return digitsOnly;
}

const std::string LibraryCatalog::simplifyISBN(const Book &book)
{
    std::string digitsOnly(book.getISBN());
    digitsOnly.erase(std::remove(digitsOnly.begin(), digitsOnly.end(), '-'), digitsOnly.end());
    return digitsOnly;
}

// search a book
bool LibraryCatalog::isPresent(const std::string &ISBN)
{
    return getBook(ISBN) ? true : false;
}
bool LibraryCatalog::isPresent(const Book &book)
{
    return getBook(book.getISBN()) ? true : false;
}

// getters
const Book *LibraryCatalog::getBook(const std::string &ISBN)
{
    if (isEmpty())
    {
        std::cout<<"hel\n";
        return nullptr;
    }

    for (auto &book : m_catalog)
    {
        std::string digitsOnly{simplifyISBN(ISBN)};

        // if ISBN matches return the book
        if (simplifyISBN(book.getISBN()) == digitsOnly)
        {
            return &book; // return book's reference
        }
    }

    return nullptr;
}

// add book in catalog
void LibraryCatalog::addBook(const Book &book)
{
    if(getBook(book.getISBN()) == nullptr)
    {
        m_catalog.push_back(book);
        std::cout << "Book added to the catalog.\n";
    }
    else
    {
        std::cerr<<"ERROR: Duplicate book found\n";
    }
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
void LibraryCatalog::display()
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
