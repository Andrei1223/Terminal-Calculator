#include "MyTerminal.h"

#include<iostream>
using namespace std;

MyTerminal::MyTerminal(){
    status = true;
}

void MyTerminal::set_status(bool status){
    this->status = status;
}

void MyTerminal::afiseaza_rezultat(double numar, bool valid){
    
    if (valid){
        cout << numar << endl;
    }
    else {
        cout << "eroare" << endl;
    }
}

bool MyTerminal::get_status(){
    return status;
}

char *MyTerminal::citeste(){
    cin.getline(mesaj, sizeof(mesaj));

    if (strcmp(mesaj, "exit") == 0){
        status = false;
    }
    return mesaj;
}

char *MyTerminal::get_mesaj(){
    return mesaj;
}

ostream& operator<<(ostream& out, const MyTerminal& terminal) 
{
    out << "Status: " << (terminal.status ? "Activ" : "Inactiv") << "\nMesaj: " << terminal.mesaj << endl;
    return out;
}

istream& operator>>(istream& in, MyTerminal& terminal) 
{
    cout << "Introdu statusul (0 pentru Inactiv, 1 pentru Activ): ";
    in >> terminal.status;
    cout << "Introdu mesajul: ";
    in.ignore(); // Ignora caracterul newline ramas in buffer
    in.getline(terminal.mesaj, sizeof(terminal.mesaj));
    return in;
}