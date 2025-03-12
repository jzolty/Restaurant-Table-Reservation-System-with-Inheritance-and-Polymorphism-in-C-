#include "list_table.h"
#include "list_res.h"

#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    //inicjalizacja zmiennych
    const std::string base = "baza.txt";
    const std::string base2 = "rezerwacje.txt";
    smart start; // wskaŸnik na table 
    smart2 res_start; // wskaŸnik na rezerwacje
    List_table tables(start); // head listy stolikow
    List_res reserved(res_start); // head (pierwszy) listy rezerwacji

    //wczytywanie danych z plikow
    tables.load_from_file(base); 
    reserved.load_from_file(base2);

    bool next = true;
    bool next2 = false;
    bool next3 = false;

    do
    {
        std::cin.clear();
        tables.display_cities();

        std::string choice_city;
        std::getline(std::cin, choice_city);

        if (choice_city == "0") { break; } //pierwsze przerwanie 

        if (choice_city == "1")
        {
            while (true)
            {
                system("cls");
                reserved.display();
                std::cout << "\nWybierz numer zamowienia z ktorego chcesz zrezygnowac (jesli chcesz wrocic do poprzedniego menu wpisz 0): \n" << std::endl;
                int chosenReservation = reserved.getIndexFromUser();

                while (chosenReservation < 0 || chosenReservation > reserved.getReservationNumber()) {
                    std::cout << "\nNiepoprawny wybor, wprowadz liczbe!\n" << std::endl;
                    chosenReservation = reserved.getIndexFromUser();
                }

                if (chosenReservation == 0) break;

                reserved.removeFromList(chosenReservation);
            }
        }
        else if (next2 = tables.check(choice_city))  //Sprawdzanie dostêpnoœci stolików
        {
            system("cls");
            tables.display_seats(choice_city);

            do
            {
                std::string seats_choice;
                std::getline(std::cin, seats_choice);
                if (seats_choice == "0") { break; }
                else if (seats_choice == "1") {}
                else {
                    std::cout << "\nPodana opcja nie istnieje\n" << std::endl;
                    next2 = false;
                    continue;
                };

                do
                {
                    system("cls");

                    std::string datechoice;
                    std::cout << "Podaj date i godzine rezerwacji (dd-mm-rrrr, hh:min) (jesli chcesz wrocic, wybierz '0'):\n" << std::endl;

                    std::getline(std::cin, datechoice);

                    if (datechoice == "0") { next2 = false; system("cls"); tables.display_seats(choice_city); break; }

                    if (next3 = reserved.checkdate(choice_city, datechoice))
                    {
                        system("cls");

                        std::string reservename;
                        std::string comments = "";
                        std::string choicenext;

                        Date dateofreserv = reserved.getdate(datechoice);

                        //Funkcja choose_table() zwraca wskaŸnik ptr do wektora Table. 
                        std::vector<Table>* ptr = tables.choose_table(dateofreserv, choice_city, seats_choice, reserved);
                        std::vector<Table> chosentables;

                        if (ptr == nullptr) // ptr mo¿e byæ nullptr (pustym wskaŸnikiem), 
                        //nie uda³o siê wybraæ ¿adnych stolików do rezerwacji.
                        {
                            next3 = false;
                            continue;
                        }
                        else {
                            chosentables = *ptr; //kopiuje zawartoœæ wektora wskazywanego przez ptr do wektora chosentables.
                            delete ptr; //usuwa dynamicznie alokowany wektor,
                        }

                        std::cout << "\nWprowadz nazwisko na jakie ma zostac zapisana rezerwacja: ";
                        std::getline(std::cin, reservename);
                        std::cout << std::endl << "Dodatkowe uwagi do zamowienia (jesli brak, wcisnij enter): ";
                        std::getline(std::cin, comments);

                        for (auto& chosentable : chosentables)
                        {
                            Reservation newreservation(chosentable.city, chosentable.number, chosentable.seats, reservename, comments, dateofreserv);
                            reserved.addtolist(newreservation);

                            std::cout << std::endl;
                            newreservation.display();
                        }

                        std::cin.get();
                        do
                        {
                            system("cls");
                            std::cout << "Czy chcesz dokonac kolejnej rezerwacji? Wpisz 't' lub 'n': \n" << std::endl;

                            std::getline(std::cin, choicenext);

                            if (choicenext == "n")
                            {
                                next = false;
                            }
                            else if (choicenext != "t" && choicenext != "n")
                            {
                                std::cout << "Wpisz 't' lub 'n'!";
                                std::cin.get();
                            }
                        } while (choicenext != "t" && choicenext != "n");
                    }
                } while (!next3);
            } while (!next2);
        }
    } while (next);
    reserved.savetofile(base2);

    return 0;
}
