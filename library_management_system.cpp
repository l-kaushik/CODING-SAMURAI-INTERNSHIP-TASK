/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include "LibraryCatalog.h"
#include "stdexcept"

// display menu
void displayMenu()
{
    std::cout << "\n\n\t\tWelcome to Library's Catalog\n\n"
              << "1. Add a book\n"
              << "2. Borrow a book\n"
              << "3. Return a book\n"
              << "4. Display books\n"
              << "5. Check availability\n"
              << "6. Remove a book\n"
              << "7. Exit\n\n"
              << "Choose an option(1-7): ";
}

int isvalidChoice(std::string &choice)
{
    try
    {
        int value = std::stoi(choice);
        if (value > 8 || value < 1)
            throw std::out_of_range("Value should be between 1 and 7");

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

void performAction(LibraryCatalog& catalog, int option)
{
    std::string temp{};
    switch (option)
    {
    case 1:
        catalog.addBook(createBook());
        break;
    case 2:
        while (true)
        {
            std::cout << "Enter ISBN number of book: ";
            std::cin >> temp;
            if (isValidISBN(temp))
            {
                catalog.borrowBook(temp);
                break;
            }
        }
        break;
    case 3:
        while (true)
        {
            std::cout << "Enter ISBN number of book: ";
            std::cin >> temp;
            if (isValidISBN(temp))
            {
                catalog.returnBook(temp);
                break;
            }
        }
        break;
    case 4:
        catalog.display();
        break;
    case 5:
        while (true)
        {
            std::cout << "Enter ISBN number of book: ";
            std::cin >> temp;
            if (isValidISBN(temp))
            {
                if (catalog.isBookAvailable(temp))
                    std::cout << "Available\n";
                break;
            }
        }
        break;
    case 6:
        while (true)
        {
            std::cout << "Enter ISBN number of book: ";
            std::cin >> temp;
            if (isValidISBN(temp))
            {
                catalog.removeBook(temp);
                break;
            }
        }
        break;
    case 7:
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