#pragma once
#include "date.h"
#include <iostream>



Date::Date(int& y, int& m, int& d, int& h, int& min) : year(y), month(m), day(d), hour(h), minute(min) {} //tez ale argumentowy
//Date::Date(const int& y, const int& m, const int& d, const int& h, const  int& min) : year(y), month(m), day(d), hour(h), minute(min) {} //tez ale argumentowy


//bool TF dla daty (zabezpiecza zeby nie zarezerwowac jednego stolika nie szybciej niz 2h po wczesniejszej rezerwacji lub przed)
bool Date::isWithinTwoHours(const Date& d) const {
	int diff;
	if (hour > d.hour) {
		diff = (hour - d.hour) * 60 + (minute - d.minute);
	}
	else if (hour < d.hour) {
		diff = (d.hour - hour) * 60 + (d.minute - minute);
	}
	else {
		diff = abs(minute - d.minute);
	}
	return diff < 120;
}

//operator przeciazeniowy
bool Date::operator==(const Date& other) const {
	return (day == other.day && month == other.month && year == other.year && hour == other.hour && minute == other.minute);
}


Date::Date() {} //konstruktor domyslny

void Date::display() //wyswietlanie daty
{
	if (Date::day < 10)
	{
		std::cout << "0" << Date::day << ".";
	}
	else
	{
		std::cout << Date::day << ".";
	}

	if (Date::month < 10)
	{
		std::cout << "0" << Date::month << ".";
	}
	else
	{
		std::cout << Date::month << ".";
	}

	std::cout << Date::year << ", ";

	if (Date::hour < 10)
	{
		std::cout << "0" << Date::hour << ":";
	}
	else
	{
		std::cout << Date::hour << ":";
	}

	if (Date::minute < 10)
	{
		std::cout << "0" << Date::minute;
	}
	else
	{
		std::cout << Date::minute;
	}

}