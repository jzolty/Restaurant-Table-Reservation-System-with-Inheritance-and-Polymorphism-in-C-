/**@file*/
#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <memory>
#include "table_origin.h"

/**Klasa Table zawierajaca dane dotyczace stolika */
class Table : public TableOrigin
{
public:
    std::string city; ///< Zmienna przechowuj�ca miasto, w kt�rym znajduje si� stolik
    int number; ///< Zmienna przechowuj�ca numer stolika
    int seats; ///< Zmienna przechowuj�ca liczb� miejsc przy stoliku

    typedef std::shared_ptr<Table> smart; ///< Typydef dla wska�nika na kolejny obiekt typu Reservation

    /**Konstruktor czteroargumentowy
    @param c Miasto
    @param n Numer stolika
    @param s Liczba miejsc przy stoliku
    @param next Wskaznik na nastepny obiekt typu Table */
    Table(std::string& c, int& n, int& s, smart& next);

    /***Konstruktor trojargumentowy
    @param c Miasto
    @param n Numer stolika
    @param s Liczba miejsc przy stoliku */
    Table(std::string& c, int& n, int& s);

    /**Konstruktor bezargumentowy */
    Table();

    /**Metoda wyswietlajaca dane stolika */
    void display();

private:
    smart pointer; ///< Wska�nik na kolejny obiekt typu Table

    friend class List_table;

    /**Operator strumieniowy wyjscia
    @param s Operator strumieniowy wyjscia
    @param list Lista stolikow wczytanych z pliku
    @return Operator strumieniowy wyjscia */
    friend std::ostream& operator<<(std::ostream& s, List_table& list);

    /**Operator strumieniowy wyjscia
    @param s operator strumieniowy wyjscia
    @param t Stolik ktorego dane zostana wypisane
    @return Operator strumieniowy wyjscia */
    friend std::ostream& operator<<(std::ostream& s, Table& t);
};

typedef std::shared_ptr<Table> smart;

#endif
