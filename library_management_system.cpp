/*
Project Title:- Command-Line Library Management System
Date Started:- 22-01-2024
Author:- Lokesh Kaushik
*/

#include <iostream>
#include <string>
#include <string_view>

// Book Data Structure
class Book{
public:

//constructor

//getters
const std::string& getTitle() {return m_title;}
const std::string& getAuthor() {return m_author;}
const std::string& getISBN() {return m_ISBN;}
bool getAvailablityStatus() {return m_availabilityStatus;}

//setters
void setTitle(std::string_view title) {m_title = title;} 
void setAuthor(std::string_view author) {m_author = author;} 
void setISBN(std::string_view ISBN) {m_ISBN = ISBN;} 
void setAvailablityStatus(bool status) {m_availabilityStatus = status;} 

private:
    std::string m_title{};
    std::string m_author{};
    std::string m_ISBN{};
    bool m_availabilityStatus {};
};


int main()
{
    Book english;

    english.setTitle("10 ways to learn efficient english.");
    english.setAuthor("Leonardo Caprio.");
    english.setISBN("34534535363");
    english.setAvailablityStatus(true);

    std::cout<<english.getTitle()<<std::endl;
    std::cout<<english.getAuthor()<<std::endl;
    std::cout<<english.getAvailablityStatus()<<std::endl;
    std::cout<<english.getISBN()<<std::endl;

    return 0;
}