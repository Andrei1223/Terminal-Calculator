#ifndef MYTERMINAL_H
#define MYTERMINAL_H

#include <iostream>
using namespace std;

class MyTerminal {
private:
    bool status;
    char mesaj[200];

public:
    MyTerminal();
    void set_status(bool status);
    void afiseaza_rezultat(double numar, bool valid);
    bool get_status();
    char *get_mesaj();
    char *citeste();

    friend ostream& operator<<(ostream& out, const MyTerminal& terminal);
    friend istream& operator>>(istream& in, MyTerminal& terminal);
};

#endif