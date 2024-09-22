/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include "LibraryCatalog.h"

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
              << "Choose an option(1-10): ";
}

int isvalidChoice(std::string &choice, int end, int start = 1)
{
    try
    {
        int value = std::stoi(choice);
        if (value > end || value < start)
            throw std::out_of_range("Value should be between " + std::to_string(end) + " and " + std::to_string(start) + "\n");

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
            return (catalog.*memberFunction)(temp);
        }
    }
}

std::string getFileName()
{
    std::string fileName{};

    while (true)
    {
        try
        {
            std::cout << "Enter a file name without extension or press enter to continue with default name: ";
            std::getline(std::cin, fileName);

            if (fileName.empty())
            {
                //TODO: check if file with default name is already present
                return "LibraryCatalog"s;
            }

            // Check if the file name doesn't have an extension
            size_t dotPos = fileName.find_last_of('.');
            if (dotPos != std::string::npos)
                throw std::ios_base::failure("File name should not have an extension.\n\n");

            return fileName;
        }
        catch (const std::ios_base::failure &e)
        {
            // Clear the error state
            std::cin.clear();

            // Ignore the rest of the input buffer to handle invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cerr << e.what();
        }
    }
}

template <typename T>
// arguments:- <catalog reference, option no., import/export to/from text, import/export to/from binary, filename>
T processFileOperationCalls(LibraryCatalog &catalog, int option, T (LibraryCatalog::*operationInText)(const std::string &), T (LibraryCatalog::*operationInBinary)(const std::string &), const std::string &fileName)
{
    switch (option)
    {
    case 1:
        return (catalog.*operationInText)(fileName);
    case 2:
        return (catalog.*operationInBinary)(fileName);
    default:
        return T();
    }
}

bool processFileOptions(LibraryCatalog &catalog,const std::string &op)
{
    std::string choice{};

    while (true)
    {
        std::cout << "\n\n\t\tChoose an " + op + " operation\n\n"
                  << "1. " + op + " from a text file\n"
                  << "2. " + op + " from a bin file\n"
                  << "3. Exit\n\n"
                  << "Choose an option(1-3): ";
        std::cin >> choice;

        int option{isvalidChoice(choice, 3)};

        // std::string fileName {getFileName()};
        std::string fileName{"LibraryCatalog"};

        if (op == "import")
            return processFileOperationCalls(catalog, option, &LibraryCatalog::importFromText, &LibraryCatalog::importFromBinary, fileName);
        else
            return processFileOperationCalls(catalog, option, &LibraryCatalog::exportToText, &LibraryCatalog::exportToBinary, fileName);
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
        processFileOptions(catalog, "import"s);
        break;
    // export to a file
    case 8:
        processFileOptions(catalog, "export"s);
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

        int option = isvalidChoice(choice, 10);

        performAction(catalog, option);
    }
}

int main()
{
    menu();
}