#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Operatie.h"
#include "MyVector.h"

#include <iostream>


class Calculator{
private:
    MyVector operatii;
    int dimensiune_operatii;

    void construire_vect(char *operatii, double *numere);
    void sterge_op(char *operatii, int poz);
    void sterge_num(double *numere, int poz);
    void parcurgere_operatii(char *operatii, double *numere, int poz_op, int poz_num);
    int prioritate(char operatie);
    void auxx(int i);

    void afisare_vect(); // TODO delete

public:
    Calculator();// constructor implicit
    ~Calculator();// destructor
    Calculator(char *operatii, double *numere);

    double calculare();

    friend ostream& operator<<(ostream& out, const Calculator& calc);
    friend istream& operator>>(istream& in, Calculator& calc);
};

#endif