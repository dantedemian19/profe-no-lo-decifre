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
void borrar(node& start) {// borra toda la lista
    node q = start;
    node p = q->sig;
    while (q != NULL) {
        free(q);
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
// Parte de un programa de 5to anio y parte de uno de 4to anio https://github.com/dantedemian19/profe-no-me-aplace

void randomkey(int key[2]) {// devuelve dos valores random para usar como key desde 1 a 25
    for (int i = 0; i < 2; i += 1) {
        key[i] = rand() % 25 + 1;
    }
};
void keyrequest(int key[2]) {// le pide al usuario dos char para usar como clave
    string keys;
    cin >> keys;
    for (int i = 0; i < 2; i += 1) {
        key[i] = keys[i] - A;
    }
};

void chyper(node& raws, int key[2]) {// encripta agregando el valor de una key para espacios pares y otro para impares
    node z = raws;// cursor
    int i = 0;// determina si es par o impar el espacio elegido y que clave usar
    while (z != NULL) {
        z->num += key[i];
        if (z->num > Z) { z->num -= 26; }// si el valor pasa de Z=90, le resta 26, haciendo que 91 -> 65. dando la vuelta el abecedario
        z = z->sig;
        i += 1;//           cuenta si 
        if (i > 1)i = 0;//            el spacio es par o impar
    }
};

void dechyper(node& raws, int key[2]) { // decifra un mensaje, con los valores de key[]
    node z = raws;// cursor
    int i = 0;
    while (z != NULL) {
        z->num -= key[i];
        if (z->num < A) { z->num += 26; }// si el valor es menor de A=65, le suma 26, haciendo que 64 -> 90. dando la vuelta el abecedario
        z = z->sig;
        i += 1;//           cuenta si 
        if (i > 1)i = 0;//            el spacio es par o impar
    }
};

void crack(node& raws, int key[2], string& know, bool& ok) {// busca una conbinacion de valores en key[], en base a una palabra que esta en el mensaje.
    node z = raws;// cursor
    int i = 0;
    string test = "";// valor de testeo del mensaje corrido en base key[]
    if (know.size() > 2) {// verifica que la palabra conocida sea mas grande que la clave
        for (key[0] = 0; key[0] < 26; key[0] += 1) {// modifica los valores del primer valor de key[]
            for (key[1] = 0; key[1] < 26; key[1] += 1) {// modifica los valores del segundo valor de key[]
                test = "";// resetea el valor del string, 
                z = raws;
                while (z != NULL) {
                    test += char(z->num);
                    z = z->sig;
                }
                if (strstr(test.c_str(), know.c_str())) {// verifica si la palabra conocida esta en la convinacion de valores de key que se esta probando
                    ok = true;// verifica que la clave se crackeo con exito
                    return;// regresa a la funcion anterior
                }
                z = raws;
                i = 0;
                while (z != NULL) {// resta un valor a los espacios impares del mensaje
                    z->num -= i;
                    if (z->num < A) { z->num += 26; }// si el valor es menor de A=65, le suma 26, haciendo que 64 -> 90. dando la vuelta el abecedario
                    z = z->sig;
                    i += 1;
                    if (i > 1)i = 0;
                }
            }
            z = raws;
            i = 1;
            while (z != NULL) {// resta un valor a los espacios pares del mensaje
                z->num -= i;
                if (z->num < A) { z->num += 26; }// si el valor es menor de A=65, le suma 26, haciendo que 64 -> 90. dando la vuelta el abecedario
                z = z->sig;
                i += 1;
                if (i > 1)i = 0;
            }
        }
    }
    if (!ok) {// mensaje en caso de que no se haya podido crackear el mensaje o la palabra clave es menor a 3
        cout << " Error de crackeo (probar con palabras conocidas mas largas) \n";
    }
};

int convert(char conv) {// devuelve un valor int que equivale al char en ASCII
    return int(conv);
};

void stringtoint(string plain, node& raws, node& rawf) {// transforma un string en ins y los guarda en un vector dinamico
    bool knok = false, kno = false;
    int i = 0;
    while (!knok) {
        if ((convert(plain[i]) <= Z && convert(plain[i]) >= A) && !kno) ingresar(rawf, raws, convert(plain[i]));// comprueba que el mensaje tenga el formato y si cumple lo guarda en el vector
        else {
            knok = !knok;// si el mensaje no cumple con el formato, deja de almacenar el mensaje en el vectr
        }
        i += 1;
    }
};

void menuencoder(int& s) {// menu para la parte del encoder, para seleccionar si queres una clave random o una especifica
    string name = " desea ingresar la clave o una random \n";
    const int exit = 2;
    bool enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (s == 1) { cout << ">>"; } cout << " clave random \n" << "  ";
            if (s == 2) { cout << ">>"; } cout << " ingresar clave \n" << "  ";
            //detection of the cursor
            detection(s, enter, exit);
            //detection of the cursor
        }
        cls();
};

void encoder() {// parte del programa que se encarga de codificar un mensaje con una clave random o una ingresada
    string plain;// string original
    node raws = NULL, rawf = NULL;// puntas del vector dinamico
    int key[2] = { 0,0 };// la clave en la cual se va a cifrar
    int s = 1;// variable para el menu
    cout << "ingrese el texto a ciphar (sin espacios): \n";
    cin >> plain;
    stringtoint(plain,raws,rawf);
    menuencoder(s);
    if (s == 1)randomkey(key);
    if (s == 2) {
        cout << "ingrese la clave (2 letras MAYUS): \n";
        keyrequest(key);
    }
    cls();
    chyper(raws,key);// cifrado
    // mostrar por pantalla //
    //cout << " ascii: "; //parte para mostrar los valores del mensaje en ASCII
    //mostrarfifotest(raws);
    cout << " \n";
    cout << " mensaje: ";
    mostrarfifo(raws);
    cout << " \n";
    cout << " la clave es: ";
    for (int i = 0; i < 2; i += 1) cout << char(key[i]+A);
    cout << "\n";
    // mostrar por pantalla //
}
void decoder() {// parte del programa que se encarga de decodificar un mensaje con una clave ingresada
    string plain;// string original
    node raws = NULL, rawf = NULL;// puntas del vector dinamico
    int key[2] = { 0,0 };// la clave en la cual se va a decifrar
    cout << "ingrese el texto a deciphar (sin espacios y en MAYUS): \n";
    cin >> plain;
    cls();
    stringtoint(plain, raws, rawf);
    cout << "ingrese la clave (2 letras MAYUS): \n";
    keyrequest(key);
    dechyper(raws, key);
    // mostrar por pantalla //
    //cout << " ascii: "; //parte para mostrar los valores del mensaje en ASCII
    //mostrarfifotest(raws);
    cout << " \n";
    cout << " mensaje: ";
    mostrarfifo(raws);
    cout << " \n";
    cout << " la clave es: ";
    for (int i = 0; i < 2; i += 1) cout << char(key[i] + A);
    cout << "\n";
    // mostrar por pantalla //
}


void cracker() {
    string plain, know;// string original y la palabra conocida
    node raws = NULL, rawf = NULL;// puntas del vector dinamico
    int key[2] = { 0,0 };// la clave en la cual se va a decifrar
    bool ok = false;// verifica si se pudo crackear el mensaje
    cout << "ingrese el texto a deciphar (sin espacios): \n";
    cin >> plain;
    cls();
    cout << "ingrese el texto conocido (sin espacios): \n";
    cin >> know;
    cls();
    stringtoint(plain, raws, rawf);
    crack(raws,key,know,ok);
    // mostrar por pantalla //
    if (ok) {// muestra el resultado, si es que se pudo crackear el mensaje
        cout << " mensaje: ";
        mostrarfifo(raws);
        cout << " \n";
        cout << " la clave es: ";
        for (int i = 0; i < 2; i += 1) cout << char(key[i] + A);
        cout << "\n";
    }
    // mostrar por pantalla //
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
        case 1:// si selecciona codificar
            encoder();
            pause();
            break;
        case 2:// si selecciona decodificar
            decoder();
            pause();
            break;
        case 3:// si selecciona crackear
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


