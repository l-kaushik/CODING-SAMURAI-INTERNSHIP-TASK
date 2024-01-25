/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include "LibraryCatalog.h"

int main()
{
    Book english("10 ways to learn efficient english", "Leonardo Caprio", "345-345-3744");
    Book hindi("10 ways to speak hindi", "Leonardo Caprio", "345-345-3244");
    Book maths("10 ways to learn maths", "Leonardo Caprio", "345-345-3344");

    LibraryCatalog catalog;
    catalog.addBook(english);
    catalog.addBook(hindi);
    catalog.addBook(maths);
    
    catalog.display("10 ways to");

    return 0;
}