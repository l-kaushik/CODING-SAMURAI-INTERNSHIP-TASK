/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include "LibraryCatalog.h"
#include <stdexcept>

// display menu
void displayMenu()
{
    std::cout << "\n\n\t\tWelcome to Library's Catalog\n\n"
              << "1. Add a book\n"
              << "2. Borrow a book\n"
              << "3. Return a book\n"
              << "4. Display books\n"
              << "5. Check availability\n"
              << "6. Change availability\n"
              << "7. Import from a file\n"
              << "8. Export to a file\n"
              << "9. Remove a book\n"
              << "10. Exit\n\n"
              << "Choose an option(1-7): ";
}

int isvalidChoice(std::string &choice)
{
    try
    {
        int value = std::stoi(choice);
        if (value > 10 || value < 1)
            throw std::out_of_range("Value should be between 1 and 10");

        return value;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "ERROR: Invalid characters in input" << std::endl
                  << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Out Of Range: " << e.what() << std::endl
                  << std::endl;
    }

    return -1;
}

// this function will take instatnce of object and pointer to memeber function to call them
template <typename T>
T processFunctionCall(LibraryCatalog &catalog, T (LibraryCatalog::*memberFunction)(const std::string &), std::string &temp)
{
    while (true)
    {
        std::cout << "\nEnter ISBN number of book: ";
        std::cin >> temp;
        if (isValidISBN(temp))
        {
            (catalog.*memberFunction)(temp);
            return T;
        }
    }
}

void performAction(LibraryCatalog &catalog, int option)
{
    std::string temp{};
    switch (option)
    {
    // add a book
    case 1:
        catalog.addBook(createBook());
        break;
    // borrow a book
    case 2:
        processFunctionCall(catalog, &LibraryCatalog::borrowBook, temp);
        break;
    // return a book
    case 3:
        processFunctionCall(catalog, &LibraryCatalog::returnBook, temp);
        break;
    // display catalog
    case 4:
        catalog.display();
        break;
    // check availability
    case 5:
        if (processFunctionCall(catalog, &LibraryCatalog::isBookAvailable, temp))
            std::cout << "Available\n";
        break;
    // alter availability
    case 6:
        processFunctionCall(catalog, &LibraryCatalog::alterAvailable, temp);
        break;
    // import from a file
    case 7:
        // function call for importing from a file
        break;
    // export to a file
    case 8:
        // function call for exporting to a file
        break;
    // remove a book
    case 9:
        processFunctionCall(catalog, &LibraryCatalog::removeBook, temp);
        break;
    // exit program
    case 10:
        exit(EXIT_SUCCESS);
    default:
        break;
    }
}

// Main menu function
void menu()
{
    LibraryCatalog catalog;

    std::string choice{};

    while (true)
    {
        displayMenu();
        std::cin >> choice;

        int option = isvalidChoice(choice);

        if (option > 0)
        {
            performAction(catalog, option);
        }
    }
}

int main()
{
    menu();
}