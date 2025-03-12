#pragma once
#include "table.h"
#include <iostream>

Table::Table(std::string& c, int& n, int& s, smart& next): city(c), number(n), seats(s), pointer(next) {} // konstruktor z argumentem ze wskaŸnikiem

Table::Table(std::string& c, int& n, int& s) : city(c), number(n), seats(s) {} // konstruktor z argumentami

void Table::display()
{
    std::cout << *this;
    // przeci¹¿am operator (nie mogê wypisaæ obiekt wiêc wyœwietlam go przez referencjê)
    // gwiazdka to stolik a this to wskaŸnik
}

std::ostream& operator<<(std::ostream& s, Table& t) // operator strumieniowy przeci¹¿ony dla stolika
{
    s << t.city << "; " << "Stolik " << t.seats << "-osobowy nr #" << t.number << std::endl;
    return s;
}

Table::Table() {} // konstruktor domyœlny
