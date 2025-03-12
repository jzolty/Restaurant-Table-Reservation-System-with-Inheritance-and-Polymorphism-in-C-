#pragma once
#include "table.h"
#include <iostream>

Table::Table(std::string& c, int& n, int& s, smart& next): city(c), number(n), seats(s), pointer(next) {} // konstruktor z argumentem ze wska�nikiem

Table::Table(std::string& c, int& n, int& s) : city(c), number(n), seats(s) {} // konstruktor z argumentami

void Table::display()
{
    std::cout << *this;
    // przeci��am operator (nie mog� wypisa� obiekt wi�c wy�wietlam go przez referencj�)
    // gwiazdka to stolik a this to wska�nik
}

std::ostream& operator<<(std::ostream& s, Table& t) // operator strumieniowy przeci��ony dla stolika
{
    s << t.city << "; " << "Stolik " << t.seats << "-osobowy nr #" << t.number << std::endl;
    return s;
}

Table::Table() {} // konstruktor domy�lny
