#pragma once
#include "reservation.h"
#include <iostream>

//int Reservation::counter = 0;

Reservation::Reservation(std::string& c, int& n, int& s, std::string& resname, std::string& com, Date& dat, smart2 next2)
    : Table(c, n, s), name(resname), comments(com), reservdate(dat), pointer2(next2) {

}

void Reservation::display() {
    std::cout << *this;
}


//k 7 arg jeœli w konstruktorze nie zostanie podany wskaŸnik na nastêpny obiekt Reservation (next2), 
// pointer2 nie bêdzie zawiera³ losowego adresu w pamiêci.
Reservation::Reservation(std::string& c, int& n, int& s, std::string& resname, std::string& com, Date& dat)
    : Table(c, n, s), name(resname), comments(com), reservdate(dat) {
    Reservation::pointer2 = nullptr;

}

Reservation::~Reservation() {

}

Reservation::Reservation(const Reservation& r) {
    Reservation::city = r.city;
    Reservation::number = r.number;
    Reservation::seats = r.seats;
    Reservation::name = r.name;
    Reservation::comments = r.comments;
    Reservation::reservdate = r.reservdate;
    Reservation::pointer2 = r.pointer2;
 
}

std::ostream& operator<<(std::ostream& s, Reservation& res) {
    s << "Miasto: " << res.city << "; Stolik nr #" << res.number << "(" << res.seats << "-osobowy) ";

    if (res.reservdate.day < 10) {
        s << "0" << res.reservdate.day << ".";
    }
    else {
        s << res.reservdate.day << ".";
    }

    if (res.reservdate.month < 10) {
        s << "0" << res.reservdate.month << ".";
    }
    else {
        s << res.reservdate.month << ".";
    }

    s << res.reservdate.year << ", ";

    if (res.reservdate.hour < 10) {
        s << "0" << res.reservdate.hour << ":";
    }
    else {
        s << res.reservdate.hour << ":";
    }

    if (res.reservdate.minute < 10) {
        s << "0" << res.reservdate.minute;
    }
    else {
        s << res.reservdate.minute;
    }

    s << '\n' << "Nazwisko: " << res.name << '\n';
    if (!res.comments.empty()) {
        s << "Dodatkowe uwagi: " << res.comments << std::endl;

    }
    return s;
}