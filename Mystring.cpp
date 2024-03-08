#include "MyString.h"
//#include <stack>

// valoarea de inceput a stringului
#define LEN_STR 100

using namespace std;

// constructori
MyString::MyString()
{
    dim_sir_numere = LEN_STR;
    dim_sir_complet = LEN_STR;
    dim_sir_semne = LEN_STR;
    sir_complet = new char[dim_sir_complet];
    sir_semne = new char[dim_sir_semne];
    sir_numere = new double[dim_sir_numere];
}

MyString::MyString(const MyString& obiect)
{
   this->dim_sir_numere = obiect.dim_sir_numere;
    this->dim_sir_semne = obiect.dim_sir_semne;
    this->dim_sir_complet = obiect.dim_sir_complet;

    this->sir_complet = new char[this->dim_sir_complet];
    strcpy(this->sir_complet, obiect.sir_complet);

    this->sir_semne = new char[this->dim_sir_semne];
    strcpy(this->sir_semne, obiect.sir_semne);

    this->sir_numere = new double[this->dim_sir_numere];
    for (unsigned int i = 0; i < this->dim_sir_numere; i++) {
        this->sir_numere[i] = obiect.sir_numere[i];
    }
}


// constructor generic
MyString::~MyString()
{
    if (this->sir_complet != nullptr)
        delete[]this->sir_complet;
    if(this->sir_numere != nullptr)
        delete[]this->sir_numere;
    if(this->sir_semne != nullptr)
        delete[]this->sir_semne;
}

MyString& MyString::operator=(const MyString& obiect)
{
    if (this != &obiect) {
        // Eliberează resursele existente
        delete[] this->sir_complet;
        delete[] this->sir_semne;
        delete[] this->sir_numere;

        // Copiază resursele din obiectul sursă
        this->dim_sir_numere = obiect.dim_sir_numere;
        this->dim_sir_semne = obiect.dim_sir_semne;
        this->dim_sir_complet = obiect.dim_sir_complet;

        this->sir_complet = new char[this->dim_sir_complet];
        strcpy(this->sir_complet, obiect.sir_complet);

        this->sir_semne = new char[this->dim_sir_semne];
        strcpy(this->sir_semne, obiect.sir_semne);

        this->sir_numere = new double[this->dim_sir_numere];
        for (unsigned int i = 0; i < this->dim_sir_numere; i++) {
            this->sir_numere[i] = obiect.sir_numere[i];
        }
    }

    return *this;
}

void MyString::schimba_dim(){

    if (dim_sir_complet != LEN_STR){
        sir_complet = (char *)realloc(sir_complet, dim_sir_complet * sizeof(char));
    }
    if (dim_sir_numere != LEN_STR){
        sir_numere = (double *)realloc(sir_numere, dim_sir_numere * sizeof(double));
    }
    if (dim_sir_semne != LEN_STR){
        sir_semne = (char *)realloc(sir_semne, dim_sir_semne * sizeof(char));
    }
}

void MyString::set_dim_sir_complet(){
    if (this->sir_complet != nullptr)
        delete[]this->sir_complet;
    
    this->sir_complet = new char[this->dim_sir_complet];
}

void MyString::set_dim_sir_numere(){
    if (this->sir_numere != nullptr)
        delete[]this->sir_numere;
    
    this->sir_numere = new double[this->dim_sir_numere];
}

void MyString::set_dim_sir_semne(){
    if (this->sir_semne != nullptr)
        delete[]this->sir_semne;
    
    this->sir_semne = new char[this->dim_sir_semne];
}

// functie oentru verificarea ecuatiei
bool MyString::verificare_semne(char *sir)
{
    // daca este gol sirul
    if (strlen(sir) == 0)
        return false;

    char* pointer = nullptr;
    bool ok = 1;
    int nr = 0;

    // se numara numarul de aparitii ale caracterelor valide
    pointer = strpbrk(sir, "0.123456789+-*/^#()[]\n ");
    while (pointer != nullptr)
    {
        pointer = strpbrk(pointer + 1, "0.123456789+-*/^#()[]\n ");
        nr++;
    }

    // se verifica nr de caractere valide cu nr de caractere din sir
    if (strlen(sir) != nr)
        return false;

    // se verifica daca parantezele sunt corecte
    if (verificare_paranteze(sir) == false)
        return false;

    // se verifica sintaxa ecuatiei
    if (verificare_sintaxa(sir) == false)
        return false;
    
    return ok;
}

// fucntie care verifica daca caracterul apare in sirul constant
bool MyString::verifica_daca_apare(char caracter, const char *sir)
{
    const char *ptr = sir;

    while (*ptr) {

        if (*ptr == caracter)
            return true;

        ptr++;
    }

    return false;
}

// functie strnchr implementata
char *MyString::strnchr(char *ptr, const char caract, int num)
{
    int i;
    for (i = 0; i < num; i++) {
        if (ptr[i] == caract)
            return ptr + i;
    }

    return nullptr;
}

bool MyString::verificare_sintaxa(char *sir)
{
    char *simbol = strpbrk(sir, "0.123456789+-*/^#()[]\n"), *previous = nullptr;

    // se parcurge sirul ignorand spatiile
    while (simbol) {
        // se trece la urmatoarea iteratie
        previous = simbol;
        simbol = strpbrk(simbol + 1, "0.123456789+-*/^#()[]\n");

        // se verifica daca s a terminal sirul
        if (simbol == nullptr)
            return true;

        // se verifica operatiile valide
        

        // 1) se verifica daca se afla 2 semne unul langa altul
        if (verifica_daca_apare(*previous, "+-*/^#") && verifica_daca_apare(*simbol, "+-*/^#"))
            return false;

        // 2) se verifica daca intre 2 numere se afla spatii
        if (verifica_daca_apare(*previous, "0123456789") && // se verifica daca e numar
            verifica_daca_apare(*simbol, "0123456789") && // se verifica daca e numar
            strnchr(previous, ' ', simbol - previous + 1) != nullptr // se verifica daca e spatiu intre numere
            )
            return false;
        
    }

    return true;
}

// functie care verifica parantezele din ecuatie
bool MyString::verificare_paranteze(char *sir)
{
    // se creaza o stiva
    int stiva[150]; // se considera ca '(' este 1 și '[' este 2
        int top = 0; // variabilă pentru a urmari varful stivei
        bool valid = true;
        int semn;

        while (*sir && valid) {
            switch (*sir) {
                case '(':
                    if (top < 1000)
                        stiva[top++] = 1;
                    else
                        return false; // Depășirea capacității stivei
                    break;
                case '[':
                    if (top < 1000)
                        stiva[top++] = 2;
                    else
                        return false; // Depășirea capacității stivei
                    break;
                case ')':
                    if (top == 0)
                        return false;
                    semn = stiva[--top];

                    if (semn == 2)
                        valid = false; // Se iese din while
                    break;
                case ']':
                    if (top == 0)
                        return false;
                    semn = stiva[--top];

                    if (semn == 1)
                        valid = false; // Se iese din while
                    break;
                default:
                    break;
            }

            sir++;
        }

        if (top != 0 || valid == false)
            return false;

        return true;
    
}

bool MyString::set_sir_complet(char *sir){
    
    if (verificare_semne(sir) == 1) {
        dim_sir_complet = strlen(sir) + 1;
        set_dim_sir_complet();

        strcpy(sir_complet, sir);

        extragere_numere();
        extragere_semne();

        //afisare_numere();
        // se modifica daca este 3*(-1) sa se transmita -1 in vectorul de numere
        modificare_num_negative();

        return true;
    }
    else {
        cout << "format gresit pt ecuatie" << '\n';

        // se pune pe 0 dimensiunea vectorilor
        this->dim_sir_numere = 0;
        this->dim_sir_semne = 0;
        set_dim_sir_numere();
        set_dim_sir_semne();

        return false;
    }
}

void MyString::modificare_num_negative()
{
    // se cauta simbolul '-'
    int i = 0, j = 0, numar_minus = 0;
    for (i = 0; i < dim_sir_semne; i++) {
        // se numara al catelea minus e
        if (sir_semne[i] == '-')
            numar_minus++;

        // se verifica daca este (-num) sau -num la inceput de rand
        if (sir_semne[i] == '-' && verifica_daca_apare(sir_semne[i + 1], "(") == false && i == 0) {
            // se sterge semnul din vector
            strcpy(sir_semne, sir_semne + 1);

            // se modifica dimensiunea
            dim_sir_semne--;
            sir_numere[j] *= (-1);
            j++;
        }
        else if (sir_semne[i] == '-' && i!=0 && sir_semne[i - 1] == '('
                                     && i!=dim_sir_semne-1 && sir_semne[i + 1] == ')'
                                     && verificare_cond_minus(numar_minus)) {

            strcpy(sir_semne + i - 1, sir_semne + i + 2);
            dim_sir_semne -= 3;
            //afisare_numere();

            sir_numere[j] *= (-1);
            j++;
        }// se verifica daca este o paranteza


        if (verifica_daca_apare(sir_semne[i], "[()]") == false) {
            j++;
        }
    }
}

bool MyString::verificare_cond_minus(int num_minus)
{
    // se parcurge ecuatia
    int i, num = 0;
    for (i = 0; i < dim_sir_complet; i++) {
        // se cauta al num_minus lea minus
        if (sir_complet[i] == '-')
            num++;

        if (num == num_minus)
            break;
    }

    // se verifica daca in stanga minusului se afla un numar sau o operatie
    while (1) {
        i--;

        // se ignora space urile
        if (sir_complet[i] == ' ')
            continue;


        if (verifica_daca_apare(sir_complet[i], "(") == true)
            return true;

        return false;
    }
}

void MyString::extragere_semne() {
    char* pointer_semn = strpbrk(sir_complet, "+-()^*/#[]");
    dim_sir_semne = 0;
    while (pointer_semn != NULL)
    {
        sir_semne[dim_sir_semne] = *pointer_semn;
        this->dim_sir_semne++;
        pointer_semn = strpbrk(pointer_semn + 1, "+-()^*/#[]");
    }
    schimba_dim();
}

void MyString::extragere_numere() {
    char* pointer_inceput, *pointer_final;
    char* pointer_numar = strpbrk(sir_complet, "0123456789");
    char aux[20];
    dim_sir_numere = 0;

    while (pointer_numar != NULL) 
    { 
        pointer_inceput = pointer_numar;
        pointer_final = strpbrk(pointer_inceput + 1, "+-()^/*#[] \n\0");

        if (pointer_final == NULL) {
            pointer_final = pointer_inceput + strlen(pointer_inceput);  
        }

        if (pointer_final - pointer_inceput < sizeof(aux)) {
            strncpy(aux, pointer_inceput, pointer_final - pointer_inceput);
            aux[pointer_final - pointer_inceput] = '\0';

            double extracted_number = strtod(aux, nullptr);
            sir_numere[dim_sir_numere] = extracted_number;
            dim_sir_numere++;
        }

        pointer_numar = strpbrk(pointer_final, "0123456789");
    }

    schimba_dim();
}

void MyString::afisare_numere()
{
    int i;
    for (i = 0; i < dim_sir_numere; i++){
        cout << sir_numere[i] << " ";
    }

    cout << '\n';
}

// se definesc getteri
double* MyString::get_sir_numere()
{
    return sir_numere;
}

char* MyString::get_sir_semne()
{
    return sir_semne;
}

char* MyString::get_sir_complet()
{
    return sir_complet;
}

unsigned int MyString::get_dim_sir_complet()
{
    return dim_sir_complet;
}

unsigned int MyString::get_dim_sir_semne()
{
    return dim_sir_semne;
}

unsigned int MyString::get_dim_sir_numere()
{
    return dim_sir_numere;
}

ostream& operator<<(ostream& out, const MyString& str) 
{
    out << "sir_complet: " << str.sir_complet << endl;
    out << "sir_semne: " << str.sir_semne << endl;
    out << "sir_numere: ";
    for (unsigned int i = 0; i < str.dim_sir_numere; ++i) {
        out << str.sir_numere[i] << " ";
    }
    out << endl;
    out << "dim_sir_complet: " << str.dim_sir_complet << endl;
    out << "dim_sir_semne: " << str.dim_sir_semne << endl;
    out << "dim_sir_numere: " << str.dim_sir_numere << endl;
    return out;
}

istream& operator>>(istream& in, MyString& str) 
{
    cout << "Introduceti sirul complet: ";
    in >> str.sir_complet;
    return in;
}