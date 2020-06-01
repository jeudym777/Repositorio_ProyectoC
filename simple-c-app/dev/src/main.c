#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//------------------------- Estructura de datos  ---------------------------------
typedef enum { CELULAR, TELEFONO, INTERNACIONAL } Tipo;
struct Celular{
    char* numero;
};
struct Telefono{
    char* numero;
};
struct Internacional{
    char* numero;
};
struct nodoLista{
    void* mumeroX;
    Tipo tipo;
    struct nodoLista* sig;
} *cabeza;

void* nuevoCelular (char* m){
    struct Celular* elNumero;
    elNumero = (struct Celular*) malloc(sizeof(struct Celular));
    elNumero->numero = m;
    return elNumero;
}
void* nuevoTelefono(char* m ){
    struct Telefono* elTelefono;
    elTelefono = (struct Telefono*) malloc(sizeof(struct Telefono));
    elTelefono->numero = m;
    return elTelefono;
}
void* nuevoInternacional(char* m ){
    struct Internacional* elInternacionalxd;
    elInternacionalxd = (struct Internacional*) malloc(sizeof(struct Internacional));
    elInternacionalxd->numero = m;
    return elInternacionalxd;
}

void insertarNumeroX(void* nuevoArticulo, Tipo tipo){
    struct nodoLista* nn = NULL;
    nn = (struct nodoLista*) malloc(sizeof(struct nodoLista));
    nn->mumeroX=nuevoArticulo;
    nn->tipo = tipo;
    nn->sig=NULL;
    if (cabeza == NULL)
        cabeza=nn;
    else{
        nn->sig = cabeza;
        cabeza = nn;
    }
}

int largoLista(){
    int i=0;
    struct nodoLista* temp=cabeza;
    if (cabeza!=NULL){
        do {
            i++;
            temp = temp->sig;
        }
        while(temp!=NULL);
    }
    return i;
}

void eliminarArticulo(int indice){
    struct nodoLista *act = cabeza, *ant;
    int cont = 0;
    if (indice >= 0 && indice <= largoLista()-1){
        if (cont == indice){
            act = act->sig;
            free(cabeza);
            cabeza = act;
        }
        else {
            while (cont != indice) {
                ant = act;
                act = act->sig;
                cont++;
            }
            ant->sig = act->sig;
            free(act);
        }
    } else
        printf("EL INDICE A ELIMINAR ES INVALIDO\n");
}

void imprimirNumeros(){
    struct nodoLista* act = cabeza;
    printf("********* Lista de Articulos *********\n");
    if (act == NULL)
        printf("Lista Vacia");
    else
        while(act!=NULL){
            if (act->tipo==0){
                printf("Numero: %s, Tipo: CELULAR\n", ((struct Celular*)act->mumeroX)->numero);
            }
            if (act->tipo==1) {
                printf("Numero: %s Tipo: TELEFONO\n", ((struct Telefono*)act->mumeroX)->numero);
            }
            if (act->tipo==2) {
                printf("Numero: %s Tipo: NUMERO INTERNACIONAL\n",((struct Internacional*)act->mumeroX)->numero);
            }
            act = act->sig;}
}

//------------------------ Logica para capturar numeros  -----------------------------------------
regex_t regex;
int reti;

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int EsCelular(char * stringy,  char * patronCR){
    char  * formatoNormal , * patronCelular;
    patronCelular = "[6-8][-)( ./0-9]*$";
    formatoNormal = concat(patronCR, patronCelular);   // Formato telefono cualquiera
    reti = regcomp(&regex, formatoNormal ,0);
/* regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}

int EsTelefono(char * stringy, char  * patronCR){

    char * auxpatron, * pt;
    auxpatron =  "[2][-)( ./0-9]*$";
    char  * formatoNormal;
    formatoNormal = concat(patronCR,auxpatron);   // Formato telefono cualquiera
    reti = regcomp(&regex, formatoNormal ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}

//    TELEFONOS NORMALES
int EsNormal(char * stringy){
    char  * formatoNormal;
    formatoNormal ="^[+)( ./0-9]*$";   // Formato telefono cualquiera
    reti = regcomp(&regex, formatoNormal ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}

//  FORMATO CR   +506
int EsNacional1(char * stringy){
    char  * formatoNacional2;
    formatoNacional2 ="^[+][:5:][:0:][:6:][-)( ./0-9]*$"; // Formato +506
    reti = regcomp(&regex, formatoNacional2 ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}

int EsNacional5(char * stringy){
    char  * formatoNacional2;
    formatoNacional2 ="^[(][:5:][:0:][:6:][-)( ./0-9]*$"; // Formato (506)
    reti = regcomp(&regex, formatoNacional2 ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}

int EsNacional2(char * stringy){
    char  * formatoNacionaL2;
    formatoNacionaL2 = "^[:5:][:0:][:6:][-)( ./0-9]*$"; // Formato 506
    reti = regcomp(&regex, formatoNacionaL2 ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}
//            FORMATO +(506)
int EsNacional3(char * stringy){
    char  * formatoNacional3;
    formatoNacional3 ="^[+][(][:5:][:0:][:6:][)][-)( ./0-9]*$"; // Formato +(506)
    reti = regcomp(&regex, formatoNacional3 ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}

//      FORMATO  (+506)
int EsNacional4(char * stringy){
    char  * fn6;
    fn6 ="^[(][+][:5:][:0:][:6:][)][-)( ./0-9]*$"; // Formato (+506)
    reti = regcomp(&regex, fn6 ,0);
/* Execute regular expression */
    reti = regexec(&regex, stringy, (size_t) NULL, 0, 0);
    if (!reti) {
        return 1;
    }
    return 0;
}
//returns the size of a character array using a pointer to the first element of the character array
int lenString(char *ptr)
{
    int offset = 0;
    int count = 0;
    while (*(ptr + offset) != '\0')
    {
        ++count;
        ++offset;
    }
    return count;
}

void reconoceFormato( char *stringy)
{
    char  * formatoNacional1;
    formatoNacional1 ="^[+][:5:][:0:][:6:]"; // Formato +506

    char  * formatoNacional1SegundoCaso;
    formatoNacional1SegundoCaso ="^[(][:5:][:0:][:6:][)/0-9]"; // Formato +506

    char  * formatoNacionaL2;
    formatoNacionaL2 = "^[:5:][:0:][:6:]"; // Formato 506

    char  * formatoNacional3;
    formatoNacional3 ="^[+][(][:5:][:0:][:6:][)]"; // Formato +(506)

    char  * formatoNacionalL4;
    formatoNacionalL4 ="^[(][+][:5:][:0:][:6:][)]"; // Formato (+506)

    int tam;
    tam = lenString(stringy);

    if (EsNormal(stringy) == 1) {

        if(tam == 8){
            if (EsCelular(stringy, "^") == 1)
            {
                insertarNumeroX(nuevoCelular((char *) stringy), CELULAR);

            }
            if (EsTelefono(stringy, "^") == 1)
            {
                insertarNumeroX(nuevoTelefono((char *) stringy), TELEFONO);

            }
        }

        if (EsNacional1(stringy) == 1) {

            if (EsCelular(stringy, formatoNacional1) == 1) {

                insertarNumeroX(nuevoCelular((char *) stringy), CELULAR);

            }
            if (EsTelefono(stringy, formatoNacional1) == 1) {

                insertarNumeroX(nuevoTelefono((char *) stringy), TELEFONO);
            }

        }
        if (EsNacional5(stringy) == 1)
        {
            if (EsCelular(stringy, formatoNacional1SegundoCaso) == 1) {

                insertarNumeroX(nuevoCelular((char *) stringy), CELULAR);

            }
            if (EsTelefono(stringy, formatoNacional1SegundoCaso) == 1) {

                insertarNumeroX(nuevoTelefono((char *) stringy), TELEFONO);
            }

        }
        if (EsNacional2(stringy) == 1) {
            if (EsCelular(stringy, formatoNacionaL2) == 1) {

                insertarNumeroX(nuevoCelular((char *) stringy), CELULAR);

            }
            if (EsTelefono(stringy, formatoNacionaL2) == 1) {

                insertarNumeroX(nuevoTelefono((char *) stringy), TELEFONO);
            }

        }
        if (EsNacional3(stringy) == 1) {

            if (EsCelular(stringy, formatoNacional3) == 1) {

                insertarNumeroX(nuevoCelular((char *) stringy), CELULAR);
            }
            if (EsTelefono(stringy, formatoNacional3) == 1) {

                insertarNumeroX(nuevoTelefono((char *) stringy), TELEFONO);
            }
        }
        if (EsNacional4(stringy) == 1) {

            if (EsCelular(stringy, formatoNacionalL4) == 1) {

                insertarNumeroX(nuevoCelular((char *) stringy), CELULAR);
            }
            if (EsTelefono(stringy, formatoNacionalL4) == 1) {

                insertarNumeroX(nuevoTelefono((char *) stringy), TELEFONO);
            }
        }
        if (EsNormal(stringy) == 1 && lenString(stringy) > 12 && EsNacional1(stringy) == 0 && EsNacional2(stringy) == 0 &&
            EsNacional3(stringy) == 0 && EsNacional4(stringy) == 0 && EsNacional5(stringy) == 0) {
            insertarNumeroX(nuevoInternacional(stringy), INTERNACIONAL);

        }
    }
}

void leePalabraPorPalabra(char * palabra){
    // Extract the first token
    char * token = strtok(palabra, " ");
    int tam;
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        tam = lenString(token);
        if (tam >= 8) {
            reconoceFormato(concat(token,""));
        }
        token = strtok(NULL, " \n");
    }
}
void abrirArchivo(){
    FILE  * fPointer;
    fPointer = fopen("DocumentoTexto.txt", "r");
    char singleLine[1000]; // Cantidad de lineas
    while (!feof(fPointer)){
        fgets(singleLine, 500, fPointer);
        leePalabraPorPalabra(singleLine); }
    fclose(fPointer);
}

int main() {
    abrirArchivo();
    imprimirNumeros();
    return  0;
}


