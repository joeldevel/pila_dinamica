#include "pila.h"
#include "testing.h"
#include<stdio.h>

/* Pruebas para una pila vacía. */
static void prueba_pila_vacia(void) {

    printf("INICIO DE PRUEBAS CREAR PILA VACIA\n");

    pila_t *pila = pila_crear();
    print_test("Prueba pila vacía: ", pila_esta_vacia(pila));
    pila_destruir(pila);
}

/* Pruebas para tope pila vacía es inválido. */
static void prueba_pila_ver_tope_creada_es_invalido(void) {

    printf("INICIO DE PRUEBAS VER TOPE EN PILA VACÍA ES INVÁLIDO\n");

    pila_t *pila = pila_crear();
    print_test("Prueba pila ver tope en pila recién creada es inválido: ", pila_ver_tope(pila)==NULL);
    pila_destruir(pila);
}

/* Pruebas para apilar un elemento. */
static void prueba_apilar_un_elemento(void) {

    printf("INICIO DE PRUEBAS APILAR UN ELEMENTO\n");

    pila_t *pila = pila_crear();
  
    char elemento = 'A';

    bool ok = pila_apilar(pila, &elemento);
    print_test("Se puede apilar un elemento", ok);

    int tope = *(char*)pila_ver_tope(pila);
    printf("lo que vuelve de pila_ver_tope= %c\n", tope );

    pila_destruir(pila);
}

/* Pruebas para apilar pocos elementos. */
static void prueba_apilar_pocos_elementos(void) {

    printf("INICIO DE PRUEBAS APILAR POCOS ELEMENTOS\n");

    pila_t *pila = pila_crear();
    char elementos[] = {'A','b','c', 'F','X'};
    int tam = 5;
    bool ok = true;
    for(int i=0; i < tam; i++) {
        pila_apilar(pila, &elementos[i]);
        ok &= (elementos[i]==*(char*)pila_ver_tope(pila));
    }

    print_test("se pudieron apilar todos los elementos", ok);

    pila_destruir(pila);
}

/*Se pueden desapilar los elementos y se cumple FIFO*/
static void prueba_pila_desapilar(void) {

    printf("INICIO DE PRUEBAS DESAPILAR\n");

    pila_t *pila = pila_crear();
    int valores[] = {11,22,33,44,55,66,77,88,99};
    int tam = 9;
    for (int i = 0; i < tam; i++) {
        pila_apilar(pila, &valores[i]);
    }

    bool ok = true;
    for (int i = 0; i < tam; i++) {
      ok &= (valores[tam-i-1]==*(int*)pila_desapilar(pila));
    }
    print_test("se pudieron desapilar todos los elementos", ok);

    pila_destruir(pila);
}

/* Pruebas de la pila al trabajar con un volumen grande de elementos */
static void prueba_pila_volumen(void) {

    printf("INICIO DE PRUEBAS VOLUMEN\n");

    pila_t *pila = pila_crear();

    int tam = 1000;
    int el[tam];
    for (int i = 0; i< tam; i++) {
      el[i] = i;
    }
    bool ok = true;
    for (int i = 0; i < tam; i++) {
        // Si algun elemento no se pudo guardar correctamente, ok sera false
        ok &= pila_apilar(pila, &el[i]);
    }
    print_test("se pudieron apilar todos los elementos", ok);

    // desapilarlos
    ok = true;
    for (int i = 0; i < tam; i++) {
        ok &= (tam-i-1==*(int*)pila_desapilar(pila));
    }
    print_test("se pudieron desapilar todos los elementos", ok);

    pila_destruir(pila);
}
static void prueba_pila_desapilar_vacia_es_invalido(void) {

    printf("INICIO DE PRUEBAS DESAPILAR PILA VACÍA ES INVÁLIDO\n");

    pila_t *pila = pila_crear();
    print_test("Prueba pila vacía: ", pila_esta_vacia(pila));
    print_test("Prueba desapilar vacía es inválido", pila_desapilar(pila)==NULL);
    pila_destruir(pila);
}

static void prueba_pila_desapilar_despues_de_apilar_y_desapilar_es_invalido(void) {

    printf("INICIO DE PRUEBAS DESAPILAR DESPUES DE DESAPILAR INVÁLIDO\n");

    pila_t *pila = pila_crear();
    int valores[] = {11,22,33,44,55,66,77,88,99};
    int cant_valores = 9;
    for(int i = 0; i< cant_valores; i++) {
        pila_apilar(pila, &valores[i]);
    }
    for( int i = 0; i< cant_valores;i++) {
        pila_desapilar(pila);
    }
    print_test("Prueba desapilar despues de apilar y vaciar es inválido", pila_desapilar(pila)==NULL);

    pila_destruir(pila);
}


static void prueba_pila_ver_tope_despues_de_apilar_y_desapilar_es_invalido(void) {

    printf("INICIO DE PRUEBAS VER TOPE DESPUES DE DESAPILAR INVÁLIDO\n");

    pila_t *pila = pila_crear();
    int valores[] = {11,22,33,44,55,66,77,88,99};
    int cant_valores = 9;
    for(int i = 0; i< cant_valores; i++) {
      pila_apilar(pila, &valores[i]);
    }
    for( int i = 0; i< cant_valores;i++) {
        pila_desapilar(pila);
    }
    print_test("Prueba ver tope despues de apilar y vaciar es invalido", pila_desapilar(pila)==NULL);

    pila_destruir(pila);
}

/* Se puede apilar NULL */
static void prueba_pila_apilar_null() {

    printf("INICIO DE PRUEBAS APILAR NULL ES VÁLIDO\n");

    pila_t *pila = pila_crear();
    print_test("Prueba se puede apilar NULL", pila_apilar(pila, NULL));
    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_apilar_un_elemento();
    prueba_pila_ver_tope_creada_es_invalido();
    prueba_apilar_pocos_elementos();
    prueba_pila_desapilar();
    prueba_pila_volumen();
    prueba_pila_desapilar_vacia_es_invalido();
    prueba_pila_desapilar_despues_de_apilar_y_desapilar_es_invalido();
    prueba_pila_ver_tope_despues_de_apilar_y_desapilar_es_invalido();
    prueba_pila_apilar_null();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
