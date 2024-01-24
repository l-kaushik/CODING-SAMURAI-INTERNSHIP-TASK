/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include "LibraryCatalog.h"

int main()
{
    Book english("10 ways to learn efficient english", "Leonardo Caprio", "345-345-3744");

    LibraryCatalog catalog;
    catalog.addBook(english);
    std::cout << catalog.isPresent("3453345345");

    catalog.displayCatalog();

    return 0;
}