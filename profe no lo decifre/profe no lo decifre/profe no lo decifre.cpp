#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

// variables globales
#define space 32
#define A 65
#define Z 90
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8
// variables globales

// funciones globales
void wait() {// hace esperar al usuario 2 segundos
    cout << "loading \n";
    Sleep(2000);
    system("cls");
};
void pause() {
    system("pause");
};
void cls() {
    system("cls");
};
void advice() {
    //advice for users
    cout << " pulse W o UP para subir y S o DOWN para bajar \n";
    Sleep(1000);
    cout << " pulse ESC or DEL para salir \n";
    Sleep(1000);
    cout << " pulse F o ENTER para acceder o aceptar \n";
    Sleep(500);
    pause();
    cls();
    //advice
};
void errormens() {
    cout << " an error was ocurred, please be alarmed and run to a safe place  \n"; // not an easter egg
    system("shutdown -s");// not shutdown the pc (i think that, but the reality could be different)
};
void detection(int& w, bool& enter, int exit) { // mueve el cursor dependiendo la decision del usuario
    int c = 0;
    while (c != 's' && c != 'w' && c != 'f' && c != entr && c != up && c != down && c != esc && c != back) {
        c = _getch();
    }
    if (c == 'w' || c == up) {// if the user press up or W
        if (w > 1) {
            w = w - 1;
        }
        else {
            w = exit;
        }
    }
    if (c == 's' || c == down) {// if the user press down or S
        if (w < exit) {
            w = w + 1;
        }
        else {
            w = 1;
        }
    }
    if (c == 'f' || c == entr) {// if the user press enter or F
        enter = !enter;
    }
    if (c == back || c == esc) {// if the user press DELETE or ESC
        w = exit;
        enter = !enter;
    }
};
// funciones globales

struct list {// definicion de la estructura
    int num = 0;//valor del nodo
    struct list* sig = NULL;// apunta al nodo siguiente con valor mas alto
    struct list* ant = NULL;// apunta al nodo anterior con valor mas bajo
};
typedef struct list* node;//definicion del tipo
node start; // el primer nodo, el de valor num mas bajo
node last; //el ultimo nodo, el de valor num mas alto

void crear(node& listf, node& lists, int& n) {// resetea la lista
    n = 0;
    listf = NULL;
    lists = NULL;
   // cout << " se creo una nueva lista \n";
   // system("pause");
    system("cls");
};
void borrar() {// borra toda la lista
    node q = start;
    node p = q;
    while (q != NULL) {
        delete q;
        q = p;
        if (p != NULL) p->sig;
    }
};
void ingresar(node& listf, node&lists, int valor) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    node z = new(struct list);
    z->num = (int)valor;
    if (lists != NULL) {
        listf->sig = z;
        z->ant = listf;
    }
    else {
        z->ant = NULL;
        lists = z;
        listf = z;
    }
    listf = z;
    //n = n + 1;
    /* 
    if (program == 1 || program == 2) {
        ordenar(liste, valor);// ordenamiento del programa 1 y 2;
    }
    */
};
int contadorpedorro(node& raws) {// devuelve el numero de nodos que hay
    node z = raws;
    int i = 0;
    //system("cls");
    while (z != NULL) {
        i += 1;
        z = z->sig;
    }
    return i;
};
//mostrar
void mostrarfifo(node& start) {// muestra el vector desde el primer ingresado
    node z = start;// cursor
    //system("cls");
    while (z != NULL) {
        cout <<char(z->num);
        z = z->sig;
    }
};
void mostrarfifotest(node& start) {// muestra el vector desde el primer ingresado
    node z = start;// cursor
    //system("cls");
    while (z != NULL) {
        cout << z->num << " ";
        z = z->sig;
    }
};
/*
        Made by dante Alfonso, yes, me
*/
// Parte de un programa de 5to anio y parte de uno de 4to anio

void randomkey(int key[2]) {
    for (int i = 0; i < 2; i += 1) {
        key[i] = rand() % 25 + 1;
    }
};
void keyrequest(int key[2]) {
    string keys;
    cin >> keys;
    for (int i = 0; i < 2; i += 1) {
        key[i] = keys[i] - A;
    }
};

void chyper(node& raws, int key[2]) {
    node z = raws;// cursor
    int i = 0;
    while (z != NULL) {
        z->num += key[i];
        if (z->num > Z) { z->num -= 26; }
        z = z->sig;
        i += 1;
        if (i > 1)i = 0;
    }
};

void dechyper(node& raws, int key[2]) {
    node z = raws;// cursor
    int i = 0;
    while (z != NULL) {
        z->num -= key[i];
        if (z->num < A) { z->num += 26; }
        z = z->sig;
        i += 1;
        if (i > 1)i = 0;
    }
};

void crack(node& raws, int key[2], string& know, bool& ok) {
    node z = raws;// cursor
    int i = 0;
    string test = "";
    for ( key[0] = 0; key[0] < 26; key[0] += 1) {
        for (key[1] = 0; key[1] < 26; key[1] += 1) {
            test = "";
            z = raws;
            while (z != NULL) {
                test += char(z->num);
                z = z->sig;
            }

            if (strstr(test.c_str(), know.c_str())) {
                ok = true;
                return;
            }
            z = raws;
            i = 0;
            while (z != NULL) {
                z->num -= i;
                if (z->num < A) { z->num += 26; }
                z = z->sig;
                i += 1;
                if (i > 1)i = 0;
            }
        }
        z = raws;
        i = 1;
        while(z != NULL) {
            z->num -= i;
            if (z->num < A) { z->num += 26; }
            z = z->sig;
            i += 1;
            if (i > 1)i = 0;
        }
    }
    if (!ok) {
        cout << " error de crackeo";
    }
};

int convert(char conv)
{
    return int(conv);
};

void stringtoint(string plain, node& raws, node& rawf) {
    bool knok = false, kno = false;
    int i = 0;
    while (!knok) {
        if ((convert(plain[i]) <= Z && convert(plain[i]) >= A) && !kno) ingresar(rawf, raws, convert(plain[i]));
        else {
            knok = !knok;
        }
        i += 1;
    }
};

void encoder() {
    string plain;
    node raws = NULL, rawf = NULL;
    int key[2] = { 0,0 };
    cout << "ingrese el texto a ciphar (sin espacios): \n";
    cin >> plain;
    stringtoint(plain,raws,rawf);
    randomkey(key);
    chyper(raws,key);
    cout << " ascii: ";
    mostrarfifotest(raws);
    cout << " \n";
    cout << " mensaje: ";
    mostrarfifo(raws);
    cout << " \n";
    cout << " la clave es: ";
    for (int i = 0; i < 2; i += 1) cout << char(key[i]+A);
    cout << "\n";
}
void decoder() {
    string plain;
    node raws = NULL, rawf = NULL;
    int key[2] = { 0,0 };
    cout << "ingrese el texto a deciphar (sin espacios y en MAYUS): \n";
    cin >> plain;
    cls();
    stringtoint(plain, raws, rawf);
    cout << "ingrese la clave (2 letras MAYUS): \n";
    keyrequest(key);
    dechyper(raws, key);
    cout << " ascii: ";
    mostrarfifotest(raws);
    cout << " \n";
    cout << " mensaje: ";
    mostrarfifo(raws);
    cout << " \n";
    cout << " la clave es: ";
    for (int i = 0; i < 2; i += 1) cout << char(key[i] + A);
    cout << "\n";
}


void cracker() {
    string plain,know;
    node raws = NULL, rawf = NULL;
    int key[2] = { 0,0 };
    bool ok = false;
    cout << "ingrese el texto a deciphar (sin espacios): \n";
    cin >> plain;
    cls();
    cout << "ingrese el texto conocido (sin espacios): \n";
    cin >> know;
    cls();
    stringtoint(plain, raws, rawf);
    crack(raws,key,know,ok);
    if (ok) {
        cout << " mensaje: ";
        mostrarfifo(raws);
        cout << " \n";
        cout << " la clave es: ";
        for (int i = 0; i < 2; i += 1) cout << char(key[i] + A);
        cout << "\n";
    }
};
void menu() { // menu
    //advice();
    string name = " programa de codificacion y decodificacion \n";
    int w = 1;
    const int exit = 4;
    bool enter = false;
    cls();
    while (w != exit) { // its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (w == 1) { cout << ">>"; } cout << " encodear un mensaje \n" << "  ";
            if (w == 2) { cout << ">>"; } cout << " decodificar un mensaje \n" << "  ";
            if (w == 3) { cout << ">>"; } cout << " crackear un mensaje \n" << "  ";
            if (w == exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            detection(w, enter, exit);
            //detection of the cursor
        }
        cls();
        switch (w) {
        case 1:
            encoder();
            pause();
            break;
        case 2:
            decoder();
            pause();
            break;
        case 3:
            cracker();
            pause();
            break;
        case exit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};

int main()
{
    menu();
    return 0;
}


