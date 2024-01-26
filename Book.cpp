#include "Book.h"
#include <limits>

bool isValidISBN(const std::string &ISBN)
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
    int digitsOnly{static_cast<int>(ISBN.length()) - static_cast<int>(std::count(ISBN.begin(), ISBN.end(), '-'))};

    if (!(digitsOnly == 13 || digitsOnly == 10))
    {
        std::cerr << "ERROR: Length of ISBN is must be 10 or 13";
        return false;
    }

    return true;
}

//create a book
Book createBook()
{
    // clearing input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string title{}, author{}, ISBN{};
    int status;

    // validating ISBN number
    while (true)
    {
        std::cout << "Enter ISBN: ";
        try
        {
            std::getline(std::cin, ISBN);
            if (!isValidISBN(ISBN))
                throw std::invalid_argument("ERROR: Your ISBN is invalid\n");
            break;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << "\n\n";
        }
    }

    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);

    // validating status
    while (true)
    {
        std::cout << "Enter status(1 for available and 0 for not available): ";
        try
        {
            std::cin >> status;
            if (status != 1 && status != 0)
                throw std::invalid_argument("ERROR: Invalid input, try again\n");
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << "\n\n";
        }
    }

    return Book(title, author, ISBN, status);
}