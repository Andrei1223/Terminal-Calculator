#include "Calculator.h"
#include "Operatie.h"
#include <iostream>

using namespace std;

// construcori
Calculator::Calculator()
{
    dimensiune_operatii = 0;
}

Calculator::~Calculator()
{
    operatii.clear();
}

Calculator::Calculator(char *operatii, double *numere)
{
    construire_vect(operatii, numere);
    //afisare_vect();
}

void Calculator::construire_vect(char *operatii, double *numere)
{
    int i = 0, j = 0, prio = 0;
    if (strlen(operatii) == 1) {
        Operatie op(numere[j], operatii[i], numere[j+1], true, true, prioritate(operatii[i]) + prio);
        this->operatii.push_back(op);
        return ;
    }

    // se parcurg 2 cate 2 operatii
    for (i = 0; i < strlen(operatii) - 1; i++) {

        // se calculeaza prioritatea bazandu se pe peranteze
        if (operatii[i] == ')' || operatii[i] == ']') {    
            prio -= 100;
            continue;
        }
        if ((operatii[i] == '(' || operatii[i] == '[')) {
            prio += 100;
            continue;
        }

        if (prioritate(operatii[i]) >= prioritate(operatii[i + 1])) {
            // se adauga o noua operatie in vector
            if (i != 0 && prioritate(operatii[i - 1]) == -1) {
                Operatie op(0, operatii[i], numere[j+1], false, true, prioritate(operatii[i]) + prio);
                this->operatii.push_back(op);
            }
            else {
                Operatie op(numere[j], operatii[i], numere[j+1], true, true, prioritate(operatii[i]) + prio);
                this->operatii.push_back(op);
            }
            
        }
        else {
            // se verifica daca se afla o paranteza inchisa in saptele operatiei
            if (i != 0 && prioritate(operatii[i - 1]) == -1) {
                Operatie op(0, operatii[i], numere[j+1], false, true, prioritate(operatii[i]) + prio);
                this->operatii.push_back(op);
            }
            else {
                Operatie op(numere[j], operatii[i], 0, true, false, prioritate(operatii[i]) + prio);
                this->operatii.push_back(op);
            }
        }
        j++;
    }

    // se adauga ultimul element
    if (operatii[i] != ')' && operatii[i] != ']') {
        // se uita la ultima operatie
        if (prioritate(operatii[i - 1]) > prioritate(operatii[i])) { // || prioritate(operatii[i-1]) == -1
            // se adauga o noua operatie in vector
            Operatie op(0, operatii[i], numere[j+1], false, true, prioritate(operatii[i]) + prio);
            this->operatii.push_back(op);
        } 
        else if (prioritate(operatii[i - 1]) <= prioritate(operatii[i])) {

            if (prioritate(operatii[i - 1]) == -1) {
                Operatie op(0, operatii[i], numere[j+1], false, true, prioritate(operatii[i]) + prio);
                this->operatii.push_back(op);
            }
            else {
                Operatie op(numere[j], operatii[i], numere[j+1], true, true, prioritate(operatii[i]) + prio);
                this->operatii.push_back(op);
            }
        }
    }
}

double Calculator::calculare()
{
    // se parcurg operatiile
    while (operatii.size() > 1) {
        int i, max_prio = -1000, indice = 0;
        Operatie op;

        for (i = 0; i < operatii.size() && operatii.size() > 1; i++) {
            op = operatii.at(i);

            // se cauta cele cu prioritatea cea mai mare
            if (op.get_dreapta() == op.get_stanga() && op.get_dreapta() == true && op.get_prioritate() > max_prio) {
                max_prio = op.get_prioritate();
                indice = i;
            }
        }

        //cout << indice;
        i = indice;

        op = operatii.at(i);

        // se executa operatia cu prioritatea cea mai mare
        op.executa_operatie();

        Operatie stanga, dreapta;
        // TODO for (1+3) * (1+3)
        if (i == 0) {
            dreapta = operatii.at(i + 1);
            dreapta.set_operator1(op.get_rezultat());
            dreapta.set_stanga(true);

            // se modifica vectorul
            operatii.at(i + 1) = dreapta;
        }
        else if (i == operatii.size() - 1) {

            stanga = operatii.at(i - 1);
            stanga.set_operator2(op.get_rezultat());

            stanga.set_dreapta(true);

            // se modifica vectorul
            operatii.at(i - 1) = stanga;
        }
        else {
            dreapta = operatii.at(i + 1);
            stanga = operatii.at(i - 1);

            // se verifica prioritatile
            if (dreapta.get_prioritate() >= stanga.get_prioritate()) {
                //cout <<"-)- " <<stanga.get_operator1()<<" "<<stanga.get_stanga()<<op.get_rezultat()<<endl;

                dreapta.set_operator1(op.get_rezultat());
                dreapta.set_stanga(true);

                // se face 0 operatorul stang din ecuatia din stanga
                Operatie aux = operatii.at(i - 1);
                aux.set_operator2(0);
                aux.set_dreapta(false);
                operatii.at(i - 1) = aux;

                // se modifica vectorul
                operatii.at(i + 1) = dreapta;
            }
            else {
                stanga.set_operator2(op.get_rezultat());
                stanga.set_dreapta(true);

                // se face 0 operatorul stang din ecuatia din stanga
                Operatie aux = operatii.at(i + 1);
                aux.set_operator1(0);
                aux.set_stanga(true);
                operatii.at(i + 1) = aux;

                // se modifica vectorul
                operatii.at(i - 1) = stanga;
            }
        }

        // se sterge operatia din vector
        operatii.erase(operatii.begin() + i);
        //afisare_vect();
    }

    Operatie op = operatii.at(0);
    op.executa_operatie();

    return op.get_rezultat();
}

int Calculator::prioritate(char operatie)
{
    if (operatie == '+')
        return 1;
    if (operatie == '-')
        return 2;
    if (operatie == '*')
        return 3;
    if (operatie == '/')
        return 4;
    if (operatie == '^')
        return 5;
    if (operatie == '#')
        return 5;
    if (operatie == '[' )
        return 6;
    if (operatie == '(')
        return 7;
    return -1;
}

ostream& operator<<(ostream& out, const Calculator& calc) {

    out << "Dimensiune operatii: " << calc.dimensiune_operatii << endl;
    /*out << "Operatii: ";
    for (int i = 0; i < calc.dimensiune_operatii; ++i) 
    {
        out << calc.operatii[i] << " ";
    }*/
    out << endl;
    return out;
}

istream& operator>>(istream& in, Calculator& calc) {
    // Introdu date pentru obiectul Calculator
    cout << "Introduceti dimensiunea operatiilor: ";
    in >> calc.dimensiune_operatii;

    /*cout << "Introduceti operatiile (unul cate unul): ";
    for (int i = 0; i < calc.dimensiune_operatii; ++i) {
        Operatie op;
        in >> op;
        calc.operatii.push_back(op);
    }*/

    return in;
}