#pragma once
/** @file */
#ifndef LIST_TABLE_H
#define LIST_TABLE_H

#include "list_origin.h"
#include "list_res.h"
#include "Table.h"
#include <vector>
#include <set>
#include <string>
#include <iostream>

/**Klasa bedaca lista stolikow wczytanych z pliku*/
class List_table : public List_res
{
private:
    //static int instanceCount;  // Statyczna zmienna do œledzenia liczby instancji
    smart ptr; ///< Wskaznik na kolejny obiekt typu Table
    std::set<std::string> cities; ///< Zmienna przechowujaca nazwe danego miasta bez powielania jej
public:

    
    /**Metoda wczytujaca dane dotyczace stolikow z pliku
    @param name Nazwa pliku do wczytania */
    void load_from_file(const std::string& name);

    /**Metoda wyswietlajaca miasta */
    void display_cities();

    /**Metoda wyswietlajaca ilosc siedzen przy stolikach, dostepnych w danym miescie
    @param city Miasto, ktorego stoliki sa wyswietlane */
    void display_seats(std::string& city);

    /**Metoda wyswietlajace wszystkie stoliki dostepne do zarezerwowania w danym mieiscie
    @param city Miasto dla ktorego stoliki sa wyswietlane */
    void display_tables(std::string& city);

    /**Metoda pozwalajaca zarezerwowac dowolna liczbe stolikow w danym miescie
    @param dat Data wprowadzona przez uzytkownika
    @param city Miasto wprowadzone przez uzytkownika
    @param seats Liczba siedzen przy stoliku
    @param thelist Lista zarezerwowanych stolikow, sluzaca do porownania daty rezerwacji
    @return Wektor przechowujacy obiekty typu Table ktore zostaly zarezerwowane */
    std::vector<Table>* choose_table(Date& dat, std::string& city, std::string& seats, List_res& thelist);

    /**Operator strumieniowy wyjscia sluzacy do wypisania zawartosci zbioru miast
    @param s Operator strumieniowy wyjscia
    @param c Zbior miast
    @return Operator strumieniowy wyjscia */
    friend std::ostream& operator << (std::ostream& s, std::set<std::string> c);

    /**Operator strumieniowy wyjscia sluzacy do wypisania zawartosci listy (stolikow wczytanych)
    @param s Operator strumieniowy wyjscia
    @list Lista stolikow wczytanych z pliku
    @return Operator strumieniowy wyjscia */
    friend std::ostream& operator << (std::ostream& s, List_table& list);

    /**Metoda sprawdzajca poprawnosc wprowadzonego miasta
    @param city Ciag znakow wprowadzony od uzytkownika
    @return True gdy miasto zostalo wprowadzone poprawnie, w przeciwnym wypadku wartosc False */
    bool check(std::string& city);

    /**Metoda sprawdzajaca czy ilosc wprowadzonych miejsc przy stoliku jest poprawna
    @param city Wybor miasta wprowadzony przez uzytkownika
    @param seats Ciag znakow wprowadzony przez uzytkownika
    @return True gdy liczba miejsc zostala wprowadzona porawnie, w przeciwnym wypadku wartosc False */
    bool check2(std::string& city, std::string& seats);

    /**Konstruktor jednoargumentowy
    @param tableptr Wskaznik na obiekt typu Table */
    List_table(smart& tableptr);
};

#endif

















//List_table() {
//    instanceCount++;
//}
//
//~List_table() {
//    instanceCount--;
//}
//
//static int getInstanceCount() {
//    return instanceCount;
//}