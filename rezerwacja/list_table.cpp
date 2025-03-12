#pragma once
#include "list_table.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>  

void List_table::load_from_file(const std::string& name)
{
    std::ifstream file(name);
    smart p = this->ptr; //wskaznik na tabla
    std::string city, line, t_number, seats;
    int seats_, table;
    std::stringstream ss;
    char sign;

    //sposob w jaki rezerwacja ma byc zapisana do pliku
    if (file.good())
    {
        while (!file.eof())
        {
            std::getline(file, city);
            cities.insert(city);
            int i = 0;
            do
            {
                i++;
                if (i % 2 == 1)
                {
                    std::getline(file, line);
                    if (line.empty())
                    {
                        break;
                    }
                    ss << line;
                    while (ss >> sign)
                    {
                        if (std::isdigit(sign))
                        {
                            seats.push_back(sign);
                        }
                    }
                    seats_ = std::stoi(seats);
                    seats.clear();
                    ss.str("");
                    ss.clear();
                }
                else
                {
                    std::getline(file, line);
                    ss << line;
                    while (ss >> sign)
                    {
                        if (std::isdigit(sign))
                        {
                            t_number = sign;
                            table = std::stoi(t_number);
                            p = std::make_shared<Table>(city, table, seats_, this->ptr);
                            this->ptr = p;
                        }
                    }
                    ss.str("");
                    ss.clear();
                }

            } while (!file.eof());
        }
    }
    file.close();
}


std::ostream& operator << (std::ostream& s, std::set<std::string> c) //przeciazenie operatora dla zbioru miast(bo set jako drugi argument), zbior miast to set(wylapuje rodzaje)
{
    for (auto iter = c.begin(); iter != c.end(); ++iter)
    {
        s << ">" << *iter << std::endl;
    }
    return s;
}

std::ostream& operator << (std::ostream& s, List_table& list) //przeciazenie operatorow dla listy stolikow
{
    smart p = list.ptr;
    while (p)
    {
        s << *p;
        p = p->pointer;
    }
    return s;
}

void List_table::display_cities()
{
    system("cls");
    std::cout << "====DOSTEPNE MIASTA====";
    std::cout << std::endl << cities << std::endl;
    std::cout << "Aby zakonczyc, wprowadz '0'" << std::endl;
    std::cout << std::endl << "Wprowadz nazwe miasta, w ktorym chcesz dokonac rezerwacji lub nacisnij '1' aby zobaczyc liste aktualnych rezerwacji\n" << std::endl;

}

List_table::List_table(smart& tableptr) //stworzenie wskaznika na kolejnyt element listy stolikow
{
    List_table::ptr = tableptr;
}

bool List_table::check(std::string& city) //sprawdza miasto i literka po literce sprawdza czy nazwa ktora wprowadziles zgadza sie z ktoryms miastem(sprawdza kazde az do konca)
{
    std::string cityupper;
    char sign;
    std::stringstream ss;
    ss << city;
    while (ss >> sign)
    {
        sign = std::toupper(sign);
        cityupper.push_back(sign);
    }

    ss.str("");
    ss.clear();

    city[0] = std::toupper(city[0]);
    for (int i = 1; i < city.size(); i++) {
        city[i] = std::tolower(city[i]);
    }

    int i = 0;
    for (auto iter = cities.begin(); iter != cities.end(); ++iter)
    {
        std::string place = *iter;
        std::string iterupper = "";
        ss << place;
        while (ss >> sign)
        {
            sign = std::toupper(sign);
            iterupper.push_back(sign);
        }
        ss.clear();
        ss.str("");
        if (iterupper == cityupper)
            return true;
        else
            i++;
    }

    if (i == cities.size())
    {
        std::cout << std::endl << "Niepoprawnie wprowadzone dane, sprobuj ponownie!" << std::endl;
        std::cin.get();
        return false;
    }

    return true;
}

void List_table::display_seats(std::string& city) //dla konkretnego miasta, sprawdza liste wszystkich stolikow, jesli stolik zgadza sie z miastem to wypisze stolik, zlicza ich ilosc
{
    std::stringstream ss;
    char sign;
    ss << city;
    std::string cityupper = "";
    while (ss >> sign)
    {
        sign = std::toupper(sign);
        cityupper.push_back(sign);
    }
    ss.str("");
    ss.clear();
    std::cout << "=====" << cityupper << "=====" << std::endl << "Dostepne stoliki:" << std::endl;

    smart p = this->ptr;
    int x = 0;
    std::vector<std::pair<int, int>> tables;

    while (p)
    {
        std::string pcity = p->city;
        ss << pcity;
        pcity = "";
        while (ss >> sign)
        {
            sign = std::toupper(sign);
            pcity.push_back(sign);
        }
        ss.str("");
        ss.clear();

        if (pcity == cityupper)
        {
            bool alreadyExists = false;
            for (auto& t : tables) {
                if (t.first == p->seats)
                {
                    t.second++;
                    alreadyExists = true;
                }
            }
            if (!alreadyExists)
            {
                tables.push_back(std::make_pair(p->seats, 1));
            }
            x = p->seats;
        }
        p = p->pointer;
    }

    for (auto t : tables) {
        std::cout << "Stoliki " << t.first << "-osobowe, ilosc: " << t.second << std::endl;
    }

    std::cout << "\nAby przejsc do rezerwacji godziny wybierz '1', aby wrocic do wyboru miasta wpisz '0'.";
    std::cout << " \nJezeli ilosc stolikow po wybraniu godziny bedzie sie roznila to oznacza ze nie sa juz dostepne.\n" << std::endl;
}

void List_table::display_tables(std::string& city) //wyswietla stoliki dla konkretnego miasta
{
    smart p = this->ptr;
    while (p)
    {

        if (p->city.compare(city) == 0)
        {
            std::cout << *p;
        }
        p = p->pointer;

    }
}

bool List_table::check2(std::string& city, std::string& seats) //sprawdza czy liczba osob jest prawidlowa z pojemnoscia stolika 
{
    std::stringstream ss;
    char sign;
    ss << seats;
    while (ss >> sign)
    {
        if (!std::isdigit(sign))
        {
            std::cout << "Niepoprawny wybor, wprowadz liczbe!" << std::endl;
            std::cin.get();
            return false;
        }
    }
    int seatsnr = std::stoi(seats);
    ss.str("");
    ss.clear();
    smart p = this->ptr;
    std::string cityupper;
    std::string pcity;
    ss << city;
    while (ss >> sign)
    {
        sign = std::toupper(sign);
        cityupper.push_back(sign);
    }
    ss.str("");
    ss.clear();
    while (p)
    {
        pcity = p->city;
        ss << pcity;
        pcity = "";
        while (ss >> sign)
        {
            sign = std::toupper(sign);
            pcity.push_back(sign);
        }
        ss.str("");
        ss.clear();
        if (pcity == cityupper && p->seats == seatsnr)
        {
            return true;
        }
        p = p->pointer;
    }
    std::cout << "Nie posiadamy wolnych stolikow dla podanej liczby osob!" << std::endl;
    std::cin.get();
    return false;

}

std::vector<Table>* List_table::choose_table(Date& dat, std::string& city, std::string& seats, List_res& thelist) //faktyczna rezerwacja stoikow z podanej listy(jest tutaj system rezerwacji wielokrotnej)
{
    std::vector<int> chosenTableNumbers;
    std::string tableNumbersString;
    smart p = this->ptr;
    smart2 thelistp = thelist.ptr;
    std::stringstream ss;
    char sign;
    std::string pcity;
    std::vector <int> notfree;
    int selectedTableSeatsCount;
    std::vector<Table>* returnedTables = new std::vector<Table>(); //zmienna dynamiczna 

    while (thelistp)
    {
        std::string thelistpcity = thelistp->city; //Pobiera nazwê miasta z bie¿¹cego elementu listy rezerwacji i zapis do thelistpcity

        //czy nazwa miasta, data rez jest taka sama i czy data  mieœci siê w przedziale dwóch godzin od daty rezerwacji 
        if (thelistpcity.compare(city) == 0 && dat == thelistp->reservdate && dat.isWithinTwoHours(thelistp->reservdate)) //jezeli data i wprowadzone miasto sa poprawne, dodawanie zarezerwowanego stolika do wektora 
        {
            int reserved = thelistp->number; //numer zarezerwowanego stolika (thelistp->number) jest dodawany do wektora 
            notfree.push_back(reserved);
        }
        thelistp = thelistp->pointer2; //Ustawia wskaŸnik thelistp na nastêpny element listy rezerwacji, aby kontynuowaæ przeszukiwanie.
    }
    int x = 0;
    int freenr;
    bool goodinput = false;
    do {
        p = this->ptr;  // przejœcie do nastêpnego elementu listy
        system("cls");
        std::cout << "Dostepne stoliki: " << std::endl;
        std::vector <int> freetables; //przechowuje stolik
        std::vector <int> freetablesSeats; //przechowuje pojemnosc stolika
        while (p)
        {
            bool free = true;
            pcity = p->city;


            for (auto iter = notfree.begin(); iter != notfree.end(); iter++) //sprawdzanie czy stolik jest zarezerwowany 
            {
                if (*iter == p->number)
                    free = false;
            }


            if (pcity.compare(city) == 0 && free == true) //jesli stolik jest wolny to zostanie wyswietlony
            {
                p->display();
                x++;
                freenr = p->number;
                freetables.push_back(freenr);
                freetablesSeats.push_back(p->seats);

            }
            p = p->pointer;
        }
        if (x != 0)
        {

            bool digit = true;
            std::cout << "\nWybierz numery stolikow aby je zarezerwowac, aby wrocic do wyboru daty wpisz '0'\n";
            std::cout << "Sekwencja musi byc zakonczona przecinkiem (poprawny format '4,22,1,'): \n" << std::endl;
            std::getline(std::cin, tableNumbersString);
            if (tableNumbersString.empty() || tableNumbersString == "0") //dopis
            {
                std::cout << "\nZly wybor, wprowadz liczby jeszcze raz";
                std::cin.get();
                goodinput = false;
            }
            else if (tableNumbersString.compare("0") == 0)
            {
                return nullptr;
            }
            else
            {

                int subStrStart = 0;
                int subInt;
                std::string substr;
                for (int i = 0; i < tableNumbersString.size(); i++)
                {
                    if (tableNumbersString[i] == ',') //przecinek do oddzielenia numerow stolikow
                    {
                        substr = tableNumbersString.substr(subStrStart, i - subStrStart); //wyluskanie numeru przed przecinkiem

                        try
                        {
                            subInt = std::stoi(substr); //zmieniamy na liczbe
                            if (std::find(chosenTableNumbers.begin(), chosenTableNumbers.end(), subInt) == chosenTableNumbers.end()) //sprawdza czy numer sie nie powtarza, jezeli nie to dodaje do wektora 
                            {
                                chosenTableNumbers.push_back(subInt);
                                subStrStart = i + 1; //przechodzimy na kolejny numer 
                            }
                            else
                            {

                                std::cout << "\nZle sformatowane wejscie, nie mozna zarezerwowac tego samego stolika dwukrotnie";
                                std::cin.get(); digit = false; break;
                            }


                        }
                        catch (const std::exception&)
                        {
                            std::cout << "\nZle sformatowane wejscie, wprowadz liczby jeszcze raz";
                            std::cin.get(); digit = false; break;
                        }

                    }
                }

                if (digit) //jesli wprowadzone dane byly poprawne
                {
                    goodinput = true;
                    for (auto table : chosenTableNumbers) //dla kazdego wybranego wczesniej stolika
                    {
                        auto it = std::find(freetables.begin(), freetables.end(), table); //szukamy wprowadzonego numeru w wektorze z wolnymi stolikami
                        if (it == freetables.end()) {
                            goodinput = false;
                            break;
                        }

                        Table t(city, table, freetablesSeats.at(std::distance(freetables.begin(), it))); //jezeli wybrane stoliki sa wolne tworzymy obiekt typu table  
                        returnedTables->push_back(t); //dodajemy go do wektora

                    }
                    if (!goodinput)
                    {

                        std::cout << "\nTaki stolik jest niedostepny lub nie istnieje, sprobuj ponownie";
                        std::cin.get();
                    }
                }
            }
        }
    } while (!goodinput);

    //delete returnedTables;

    return returnedTables;
}
