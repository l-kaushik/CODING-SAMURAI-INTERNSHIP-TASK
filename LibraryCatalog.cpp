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
        if (book->getAvailabilityStatus())
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

    if (book->getAvailabilityStatus())
        book->setAvailabilityStatus(false);
    else
        book->setAvailabilityStatus(true);
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
        m_getBook(ISBN)->setAvailabilityStatus(false);
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
        m_getBook(ISBN)->setAvailabilityStatus(true);
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
            std::cout << std::boolalpha << "Availability Status: " << book.getAvailabilityStatus() << std::endl;
            std::cout << "---------------------------------------------\n";
        }
    }
}

auto getCurrentTime()
{
    // getting current time point (durations)
    auto now{std::chrono::system_clock::now()};

    // converting time point to a time_t object (converting durations into seconds)
    std::time_t currentTime{std::chrono::system_clock::to_time_t(now)};

    // converting time_t object to tm struct (converting seconds into human readable form)
    std::tm *localtime = std::localtime(&currentTime);

    return std::asctime(localtime);
}

bool LibraryCatalog::importFromText(const std::string &fileName)
{
    std::ifstream inputFile(fileName + ".txt");

    if (!inputFile.is_open())
    {
        return false;
    }

    // this will store each line read from inputFile stream
    std::string line{};

    // store position of cursor in line
    std::size_t pos{};

    // temporary variables to store read data
    std::string title{}, author{}, ISBN{};
    bool status_code{};
    int entries_read{};

    while (std::getline(inputFile, line))
    {

        // skip empty line, export time and dashed line
        if (line == "" || line.find("Export Time: ") != std::string::npos || line.find("----") != std::string::npos)
        {
            continue;
        }

        // skip "Title: " and save rest of data till \n in title variable
        if ((pos = line.find("Title: ")) != std::string::npos)
        {
            title = line.substr(pos + 7, line.find('\n'));
            line.erase(pos); // erasing already read data from line
            entries_read++;
        }

        if ((pos = line.find("Author: ")) != std::string::npos)
        {
            author = line.substr(pos + 8, line.find('\n'));
            line.erase(pos);
            entries_read++;
        }

        if ((pos = line.find("ISBN no.: ")) != std::string::npos)
        {
            ISBN = line.substr(pos + 10, line.find('\n'));
            line.erase(pos);
            entries_read++;
        }

        if ((pos = line.find("Availability Status: ")) != std::string::npos)
        {
            if ((line.substr(pos + 21, line.find('\n'))) == "true")
                status_code = true;
            else
                status_code = false;
            line.erase(pos);
            entries_read++;
        }

        if (entries_read == 4)
        {
            addBook(Book(title, author, ISBN, status_code));
            entries_read = 0;
            std::cout << std::endl;
        }
    }
    inputFile.close();

    return true;
};

bool LibraryCatalog::importFromBinary(const std::string &fileName)
{
    std::ifstream inputFile(fileName + ".txt");

    if (!inputFile.is_open())
    {
        return false;
    }

    // this will store each line read from inputFile stream
    std::string line{};

    // store position of cursor in line
    std::size_t pos{};

    // temporary variables to store read data
    std::string title{}, author{}, ISBN{};
    bool status_code{};
    int entries_read{};

    while (std::getline(inputFile, line))
    {

        // skip empty line, export time and dashed line
        if (line == "" || line.find("Export Time: ") != std::string::npos || line.find("----") != std::string::npos)
        {
            continue;
        }

        // skip "Title: " and save rest of data till \n in title variable
        if ((pos = line.find("Title: ")) != std::string::npos)
        {
            title = line.substr(pos + 7, line.find('\n'));
            line.erase(pos); // erasing already read data from line
            entries_read++;
        }

        if ((pos = line.find("Author: ")) != std::string::npos)
        {
            author = line.substr(pos + 8, line.find('\n'));
            line.erase(pos);
            entries_read++;
        }

        if ((pos = line.find("ISBN no.: ")) != std::string::npos)
        {
            ISBN = line.substr(pos + 10, line.find('\n'));
            line.erase(pos);
            entries_read++;
        }

        if ((pos = line.find("Availability Status: ")) != std::string::npos)
        {
            if ((line.substr(pos + 21, line.find('\n'))) == "true")
                status_code = true;
            else
                status_code = false;
            line.erase(pos);
            entries_read++;
        }

        if (entries_read == 4)
        {
            addBook(Book(title, author, ISBN, status_code));
            entries_read = 0;
            std::cout << std::endl;
        }
    }
    inputFile.close();

    return true;
};

bool LibraryCatalog::exportToBinary(const std::string &fileName)
{
    std::ofstream outputFile(fileName + ".bin", std::ios::binary | std::ios::app);

    if (!outputFile.is_open())
    {
        return false;
    }

    // Write export time (assuming it's a string)
    std::string exportTime = std::string("\nExport Time: ") + getCurrentTime();
    outputFile.write(exportTime.c_str(), static_cast<std::streamsize>(exportTime.size()));

    // Separator
    std::string separator = "---------------------------------------------\n";
    outputFile.write(separator.c_str(), static_cast<std::streamsize>(separator.size()));

    // Write book data
    for (const auto &eachBook : m_catalog)
    {
        // Write each string field
        outputFile.write(eachBook.getTitle().c_str(), static_cast<std::streamsize>(eachBook.getTitle().size()));
        outputFile.write(eachBook.getAuthor().c_str(), static_cast<std::streamsize>(eachBook.getAuthor().size()));
        outputFile.write(eachBook.getISBN().c_str(), static_cast<std::streamsize>(eachBook.getISBN().size()));

        // Write bool as a single byte
        bool availabilityStatus = eachBook.getAvailabilityStatus();
        outputFile.write(reinterpret_cast<const char *>(&availabilityStatus), sizeof(availabilityStatus));

        // Separator
        outputFile.write(separator.c_str(), static_cast<std::streamsize>(separator.size()));
    }

    outputFile.close();
    return true;
}

bool LibraryCatalog::exportToText(const std::string &fileName)
{
    std::ofstream outputFile(fileName + ".txt", std::ios::app);

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << "\nExport Time: " << getCurrentTime();

    outputFile << "---------------------------------------------\n";

    for (auto &eachBook : m_catalog)
    {
        outputFile << "Title: " << eachBook.getTitle() << '\n';
        outputFile << "Author: " << eachBook.getAuthor() << '\n';
        outputFile << "ISBN no.: " << eachBook.getISBN() << '\n';
        outputFile << std::boolalpha << "Availability Status: " << eachBook.getAvailabilityStatus() << '\n';
        outputFile << "---------------------------------------------\n";
    }
    outputFile.close();

    return true;
}
