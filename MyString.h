#ifndef MYSTRING_H
#define MYSTRING_H

// definesc dimensiunea initiala a sirului
#define LEN_STR 100

#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private: 
    char* sir_complet;
    char* sir_semne;
    double* sir_numere;
    unsigned int dim_sir_complet;
    unsigned int dim_sir_semne;
    unsigned int dim_sir_numere;
    
    void extragere_semne();
    void extragere_numere();
    void schimba_dim();
    void set_dim_sir_complet();
    void set_dim_sir_numere();
    void set_dim_sir_semne();
    double all_to_double(char *sir);
    bool verificare_semne(char *sir);
    bool verificare_sintaxa(char *sir);
    bool verificare_paranteze(char *sir);
    bool verifica_daca_apare(char caracter, const char *sir);
    char *strnchr(char *ptr, const char caract, int num);
    void modificare_num_negative();
    bool verificare_cond_minus(int num_minus);

public:
    MyString(); //constructor implicit

    //regula celor 3
    MyString(const MyString& str);
    ~MyString(); //destructor
    MyString& operator=(const MyString& obiect);

    bool set_sir_complet(char *sir);
    void afisare_numere();
    double *get_sir_numere();
    char *get_sir_semne();
    char *get_sir_complet();
    unsigned int get_dim_sir_complet();
    unsigned int get_dim_sir_semne();
    unsigned int get_dim_sir_numere();

    //bool operator==(const MyString& str1, const MyString& str2); 

    friend ostream& operator<<(ostream& out, const MyString& str);
    friend istream& operator>>(istream& in, MyString& str);
};

#endif

