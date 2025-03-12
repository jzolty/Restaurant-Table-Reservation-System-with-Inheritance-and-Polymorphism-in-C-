/** @file */
#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include "Table.h"
#include "Date.h"

/**Klasa bedaca rezerwacja stolika dokonana przez uzytkownika*/
class Reservation : public Table
{
private:

    //static int counter; ///<Zmienna statyczna wyswietlajaca ilosc rezerwacji znajdujacych sie w pliku
    std::string name; ///<Zmienna przechowujace imie i nazwisko osoby rezerwujacej
    std::string comments; ///<Zmienna przechowujaca dodatkowe uwagi do zamowienia
    Date reservdate; ///<Zmienna przechowujaca date rezerwacji

    typedef std::shared_ptr<Reservation> smart2; ///<Typedef dla wskaznika na obiekt typu Reservation
    smart2 pointer2; ///<Wskaznik na kolejny obiekt typu Reservation

    friend class List_res;

public:

    /**Konstruktor siedmioargumentowy
    @param c Miasto
    @param n Numer stolika
    @param resname Nazwisko rezerwacji
    @param com Dodatkowe uwagi
    @param dat Data rezerwacji
    @param next2 Wskaznik na nastepny obiekt*/
    Reservation(std::string& c, int& n, int& s, std::string& resname, std::string& com, Date& dat, smart2 next2);

    /**Konstruktor szescioargumentowy
    @param c Miasto
    @param n Numer stolika
    @param resname Nazwisko rezerwacji
    @param com Dodatkowe uwagi
    @param dat Data rezerwacji */
    Reservation(std::string& c, int& n, int& s, std::string& resname, std::string& com, Date& dat);

    /**Konstruktor kopiujacy
    @param r Obiekt ktorego dane sa kopiowane*/
    Reservation(const Reservation& r);

    /**Destruktor bezargumentowy klasy Reservation*/
    ~Reservation(); //troche zbedny ale jest

    /**Metoda wypisujaca dane klasy */
    void display();

    friend class List_table;

    /**Operator strumieniowy wyjscia
    @param s Operator strumieniowy wyjscia
    @param list Lista do wypisania
    @return Operator strumieniowy wyjscia */
    friend std::ostream& operator << (std::ostream& s, List_res& list);

    /**Operator strumieniowy wyjscia
    @param s Operator strumieniowy wyjscia
    @param res Rezerwacja do wypisania
    @return Operator strumieniowy wyjscia */
    friend std::ostream& operator << (std::ostream& s, Reservation& res);
};

//uzywane do uproszczenia zapisu typu std::shared_ptr<Reservation>, lepsza czytelnosc 
typedef std::shared_ptr<Reservation> smart2;

#endif
