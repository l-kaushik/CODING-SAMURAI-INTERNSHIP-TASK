#include "Book.h"


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
    int digitsOnly{static_cast<int>(ISBN.length()) - static_cast<int>(std::count(ISBN.begin(), ISBN.end(), '-'))};

    if (!(digitsOnly == 13 || digitsOnly == 10))
    {
        std::cerr << "ERROR: Length of ISBN is must be 10 or 13";
        return false;
    }

    return true;
}
