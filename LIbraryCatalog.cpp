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

// check availability
bool LibraryCatalog::isBookAvailable(const std::string &ISBN)
{
    auto book = getBook(ISBN);
    if (book)
    {
        if (book->getAvailablityStatus())
        {
            return true;
        }

        std::cout << "Book is not available right now\n";
        return false;
    }

    std::cerr << "ERROR: Book Not Found\n";
    return false;
}

bool LibraryCatalog::isBookAvailable(const Book &book)
{
    return isBookAvailable(book.getISBN());
}

// alter availablility of a book
void LibraryCatalog::alterAvailable(const std::string &ISBN)
{
    // get book
    Book *book = m_getBook(ISBN);

    if (book == nullptr)
    {
        std::cerr << "ERROR: Book with ISBN number " << ISBN << " is not present in catalog\n";
        return;
    }

    if (book->getAvailablityStatus())
        book->setAvailablityStatus(false);
    else
        book->setAvailablityStatus(true);
}

// getters
const Book *LibraryCatalog::getBook(const std::string &ISBN)
{
    if (isEmpty())
    {
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

Book *LibraryCatalog::m_getBook(const std::string &ISBN)
{
    if (isEmpty())
    {
        return nullptr;
    }

    for (auto &book : m_catalog)
    {
        std::string digitsOnly{simplifyISBN(ISBN)};

        // if ISBN matches return the book
        if (simplifyISBN(book.getISBN()) == digitsOnly)
        {
            return &book; // return book's address
        }
    }
    return nullptr;
}

// add book in catalog
void LibraryCatalog::addBook(const Book &book)
{
    if (getBook(book.getISBN()) == nullptr)
    {
        m_catalog.push_back(book);
        std::cout << "Book added to the catalog.\n";
    }
    else
    {
        std::cerr << "ERROR: Duplicate book found\n";
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

void LibraryCatalog::borrowBook(const std::string &ISBN)
{
    if (isBookAvailable(ISBN))
    {
        m_getBook(ISBN)->setAvailablityStatus(false);
        std::cout << "Book borrowed successfully\n";
    }
    else
    {
        std::cout << "ERROR: Book cannot be borrowed\n";
    }
}
void LibraryCatalog::borrowBook(Book &book)
{
    borrowBook(book.getISBN());
}

// return book
void LibraryCatalog::returnBook(const std::string &ISBN)
{
    if (isPresent(ISBN))
    {
        m_getBook(ISBN)->setAvailablityStatus(true);
        std::cout << "Book returned successfully\n";
    }
    else
    {
        std::cerr << "ERROR: Book Not Found\n";
    }
}

void LibraryCatalog::returnBook(Book &book)
{
    returnBook(book.getISBN());
}

// dislpay catalog
void LibraryCatalog::display(const std::string &title)
{
    if (isEmpty())
    {
        std::cout << "Catalog is empty\n";
        return;
    }

    bool once{false};

    for (auto &book : m_catalog)
    {
        // if title is present then display only books with same title otherwise display all books
        if (title == "" || (title != "" && book.getTitle() == title))
        {
            if (!once)
            {
                std::cout << "---------------------------------------------\n";
                once = true;
            }

            // std::cout<<book;
            std::cout << "Title: " << book.getTitle() << std::endl;
            std::cout << "Author: " << book.getAuthor() << std::endl;
            std::cout << "ISBN no.: " << book.getISBN() << std::endl;
            std::cout << std::boolalpha << "Availability Status: " << book.getAvailablityStatus() << std::endl;
            std::cout << "---------------------------------------------\n";
        }
    }
}

auto getCurrentTime()
{
    // getting current time point (durations)
    auto now {std::chrono::system_clock::now()};

    // converting time point to a time_t object (converting durations into seconds)
    std::time_t currentTime {std::chrono::system_clock::to_time_t(now)};

    // converting time_t object to tm struct (converting seconds into human readable form)
    std:: tm *localtime = std::localtime(&currentTime);

    return std::asctime(localtime);
}

bool LibraryCatalog::exportToText()
{
    std::ofstream outputFile("LibraryCatalog.txt", std::ios::app);

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << "\nExport Time: " << getCurrentTime();

    outputFile << "---------------------------------------------\n";

    for (auto &eachBook : m_catalog)
    {
        outputFile << "Title: " << eachBook.getTitle() << std::endl;
        outputFile << "Author: " << eachBook.getAuthor() << std::endl;
        outputFile << "ISBN no.: " << eachBook.getISBN() << std::endl;
        outputFile << std::boolalpha << "Availability Status: " << eachBook.getAvailablityStatus() << std::endl;
        outputFile << "---------------------------------------------\n";
    }
    outputFile.close();

    return true;
}