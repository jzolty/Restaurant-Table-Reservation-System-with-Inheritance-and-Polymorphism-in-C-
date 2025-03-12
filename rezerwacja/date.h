/** @file */
#pragma once
#ifndef DATE_H
#define DATE_H

#include "table_origin.h"

/**Klasa Date zawierajaca dane dotyczace daty rezerwacji */
class Date : public TableOrigin {
public:
	int year; //Zmienna przechowujaca rok rezerwacji stolika

	int month; //Zmienna przechowuajca miesiac rezerwacji stolika

	int day; //Zmienna przechowujaca dzien rezerwacji stolika

	int hour; //Zmienna przechowujaca godzine rezerwacji stolika

	int minute; //Zmienna przechowujaca minute rezerwacji stolika

public:

	/**Metoda sluzaca do wyswietlania daty */
	void display(); 

	/**
	 * @brief Sprawdza, czy rezerwacja dla danej daty miesci si� w okresie dwoch godzin.
	 *
	 * Funkcja ta porownuje date wywo�ujacego obiektu z data podan� jako parametr
	 * i zwraca true, jesli mi�dzy nimi nie ma wi�cej ni� 2 godzin roznicy czasu.
	 * W przeciwnym razie zwraca false.
	 *
	 * @param d Data, ktora nale�y porownac z data wywokujacego obiektu.
	 * @return true, jesli miedzy datami nie ma wi�cej ni� 2 godzin roznicy czasu.
	 * @return false, jesli miedzy datami jest wi�cej ni� 2 godziny roznicy czasu.
	 */
	bool isWithinTwoHours(const Date& d) const;

	/** @brief Przeci��ony operator por�wnania dla daty.
	*
	* Ten operator porownuje dwie daty i zwraca true, jesli s� identyczne,
	* tj. jesli dzie�, miesi�c, rok, godzina i minuta s� identyczne.
	* W przeciwnym razie zwraca false.
	*
	* @param other Druga data do porownania.
	* @return true, jesli daty s� identyczne.
	* @return false, jesli daty s� ro�ne.
	*/
	bool operator == (const Date& d) const; 

	/**Konstruktor piecioargumentowy
	@param y Rok rezerwacji stolika
	@param d Dzien rezerwacji stolika
	@param h Godzina rezerwacji stolika
	@param min Minuta rezerwacji stolika */
	Date(int& y, int& m, int& d, int& h, int& min);

	/**Konstruktor bezargumentowy */
	Date();  

	//zaprzyjaznione klasy maja dostep do prywatnych i chronioncyh skladowych klasy Date przez klasy list_res i reservation
	friend class List_res;

	friend class Reservation;

};

#endif
