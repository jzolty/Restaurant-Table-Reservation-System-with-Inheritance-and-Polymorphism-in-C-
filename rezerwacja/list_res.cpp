#pragma once
#include "list_res.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>

int List_res::getIndexFromUser() {
    int chosenReservation = 0;
    std::string reserveChoice;
    std::getline(std::cin, reserveChoice);
    std::stringstream ss;
    char sign;
    ss << reserveChoice;
    while (ss >> sign) {
        if (!std::isdigit(sign)) {
            return -1;
        }
        chosenReservation *= 10;
        chosenReservation += (sign - '0');
    }
    return chosenReservation;
}

int List_res::getReservationNumber() {  //pobiera indeks rezerwacji
    return this->reservation_number;
}


void List_res::load_from_file(const std::string& name) {
    std::ifstream file(name);
    smart2 p = this->ptr;
    std::string place, table, seats, resdate, resname, comments;
    int day_, month_, year_, hour_, minute_, t_number, seats_;

    if (file.is_open()) {
        while (true) {
            std::getline(file, place, ',');
            if (file.eof() || place.empty())
                break;

            std::getline(file, table, '#');
            std::getline(file, table, ','); t_number = std::stoi(table);
            std::getline(file, seats, '-'); seats_ = std::stoi(seats);
            std::getline(file, seats, ',');
            std::getline(file, resdate, '.'); day_ = std::stoi(resdate);
            std::getline(file, resdate, '.'); month_ = std::stoi(resdate);
            std::getline(file, resdate, ','); year_ = std::stoi(resdate);
            std::getline(file, resdate, ':'); hour_ = std::stoi(resdate);
            std::getline(file, resdate, ','); minute_ = std::stoi(resdate);
            std::getline(file, resname, ',');
            std::getline(file, comments);

            this->reservation_number++;

            Date d(year_, month_, day_, hour_, minute_);
            p = std::make_shared<Reservation>(place, t_number, seats_, resname, comments, d, this->ptr);
            this->ptr = p;
        }
    }
    file.close();
}

List_res::List_res(smart2& resptr) {  //konsturkot inicjalizuje wskaznik ptr na liste rezerwacji i ustawia liczbe rezerwacji na 0 
    ptr = resptr;
    this->reservation_number = 0;
}

List_res::List_res() {  //konstruktor domyslny 
    List_res::ptr = nullptr;
    this->reservation_number = 0;
}

void List_res::getSeat(std::string& chosenSeat) {  //pobiera wybor miejsca od uzytkownika
    std::getline(std::cin, chosenSeat);
    int seatsnumber;
    try {
        seatsnumber = std::stoi(chosenSeat);
    }
    catch (const std::exception&) {
    }
}

bool List_res::checkdate(std::string& city, std::string& stringdate) {
    std::stringstream ss;
    char sign;
    std::string year_, month_, day_, hour_, minute_;
    int resyear, resmonth, resday, reshour, resminute;
    ss << stringdate; int i = 1;

    while (ss >> sign) {
        if (!std::isdigit(sign) && (sign != '-' && sign != ':' && sign != ',')) {
            std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
            std::cin.get();
            return false;
        }

        if (i <= 2) {
            day_.push_back(sign);
        }
        if (i == 3 && (sign != '-' && sign != '.')) {
            std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
            std::cin.get();
            return false;
        }

        if (i > 3 && i <= 5) {
            month_.push_back(sign);
        }

        if (i == 6 && (sign != '-' && sign != '.')) {
            std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
            std::cin.get();
            return false;
        }
        if (i >= 7 && i < 11) {
            year_.push_back(sign);
        }

        if (i == 11 && sign != ',') {
            std::cout << "\nPo podaniu daty nalezy wpisac przecinek i wprowadzic po nim godzine\n" << std::endl;
            std::cin.get();
            return false;
        }
        if (i > 11 && i <= 13) {
            hour_.push_back(sign);
        }

        if (i == 14 && sign != ':') {
            std::cout << "\nPodaj godzine rezerwacji w formacie (hh:min), np. 18:30\n" << std::endl;
            std::cin.get();
            return false;
        }
        if (i > 14 && i <= 16) {
            minute_.push_back(sign);
        }

        i++;
    }
    if (i != 17) {
        std::cout << "\nNiepoprawne wprowadzone dane\n" << std::endl;
        std::cin.get();
        return false;
    }
    resday = std::stoi(day_);
    resmonth = std::stoi(month_);
    if (resmonth < 1 || resmonth > 12) {
        std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
        std::cin.get();
        return false;
    }
    if ((resmonth == 1 || resmonth == 3 || resmonth == 5 || resmonth == 7 || resmonth == 8 || resmonth == 10 || resmonth == 12) && (resday < 1 || resday > 31)) {
        std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
        std::cin.get();
        return false;
    }
    if ((resmonth == 4 || resmonth == 6 || resmonth == 9 || resmonth == 11) && (resday < 1 || resday > 30)) {
        std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
        std::cin.get();
        return false;
    }
    if (resmonth == 2 && (resday < 1 || resday > 29)) {
        std::cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << std::endl;
        std::cin.get();
        return false;
    }
    resyear = std::stoi(year_);
    if (resyear < 2024 || resyear > 2030) {
        std::cout << "\nWprowadz poprawny rok\n" << std::endl;
        std::cin.get();
        return false;
    }
    reshour = std::stoi(hour_);
    if (reshour < 14 || reshour > 22) {
        std::cout << "\nPrzyjmujemy rezerwacje miedzy godzina 14 a 22.\n" << std::endl;
        std::cin.get();
        return false;
    }
    resminute = std::stoi(minute_);
    if (resminute < 0 || resminute > 59) {
        std::cout << "\nNiepoprawna minuta rezerwacji\n" << std::endl;
        std::cin.get();
        return false;
    }
    if ((resyear == 2024 && resmonth < 6) || (resyear == 2024 && resmonth == 6 && resday < 21)) {
        std::cout << "\nNiepoprawne dane rezerwacji\n" << std::endl;
        std::cin.get();
        return false;
    }
    ss.str("");
    ss.clear();
    return true;
}

Date List_res::getdate(std::string& stringdate) {
    std::stringstream ss;
    char sign;
    std::string year_, month_, day_, hour_, minute_;
    int resyear, resmonth, resday, reshour, resminute;
    ss << stringdate;
    int i = 1;
    while (ss >> sign) {
        if (i <= 2) {
            day_.push_back(sign);
        }

        if (i > 3 && i <= 5) {
            month_.push_back(sign);
        }

        if (i >= 7 && i < 11) {
            year_.push_back(sign);
        }

        if (i > 11 && i <= 13) {
            hour_.push_back(sign);
        }

        if (i > 14 && i <= 16) {
            minute_.push_back(sign);
        }
        i++;
    }
    resday = std::stoi(day_);
    resmonth = std::stoi(month_);
    resyear = std::stoi(year_);
    reshour = std::stoi(hour_);
    resminute = std::stoi(minute_);

    Date newdate(resyear, resmonth, resday, reshour, resminute);
    return newdate;
}

void List_res::addtolist(Reservation& res) {
    smart2 R = std::make_shared<Reservation>(res);
    R->pointer2 = this->ptr;
    this->ptr = R;
    this->reservation_number++;
}

bool List_res::removeFromList(int primaryKey) {
    smart2 p = this->ptr;
    smart2 temp;

    if (primaryKey != 1) {
        while ((primaryKey--) > 2) {
            p = p->pointer2;
        }

        temp = p->pointer2;
        p->pointer2 = nullptr;
        this->reservation_number--;

        if (temp->pointer2) {
            p->pointer2 = temp->pointer2;
        }
    }
    else {
        this->reservation_number--;
        this->ptr = this->ptr->pointer2;
    }

    std::cin.get();
    this->display();
    return true;
}

void List_res::display() {
    std::cout << *this;
}

std::ostream& operator << (std::ostream& s, List_res& list) {
    smart2 p = list.ptr;
    int index = 1;
    while (p) {
        std::cout << index++ << ". ";
        s << *p;
        p = p->pointer2;
        std::cout << '\n';
    }
    return s;
}

void List_res::savetofile(const std::string& name) {
    std::ofstream file;
    file.open(name);
    smart2 p = this->ptr;
    while (p) {
        file << p->city << ", " << "Stolik nr #" << p->number << ", " << p->seats << "-osobowy, ";

        if (p->reservdate.day < 10) {
            file << "0" << p->reservdate.day << ".";
        }
        else {
            file << p->reservdate.day << ".";
        }

        if (p->reservdate.month < 10) {
            file << "0" << p->reservdate.month << ".";
        }
        else {
            file << p->reservdate.month << ".";
        }

        file << p->reservdate.year << ", ";

        if (p->reservdate.hour < 10) {
            file << "0" << p->reservdate.hour << ":";
        }
        else {
            file << p->reservdate.hour << ":";
        }

        if (p->reservdate.minute < 10) {
            file << "0" << p->reservdate.minute;
        }
        else {
            file << p->reservdate.minute;
        }
        file << ", " << p->name << ", " << p->comments << std::endl;

        p = p->pointer2;
    }
    file.close();
}
