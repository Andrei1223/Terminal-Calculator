#include "MyString.h"
#include "Operatie.h"
#include "MyTerminal.h"
#include "Calculator.h"
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    MyTerminal terminal;

    // the main loop
    while (terminal.get_status()) {
        MyString string;
    
        // read the string
        terminal.citeste();
        

        // se verifica daca nu s a citit "exit"
        if (terminal.get_status()) {
            bool status = true;
            status = string.set_sir_complet(terminal.get_mesaj());

            if (status == false)
                continue;

            // se defineste o noua operatie
            Calculator calculator(string.get_sir_semne(), string.get_sir_numere());

            terminal.afiseaza_rezultat(calculator.calculare(), true);
        }
    }
}
