#include "pila.h"
#include "testing.h"
#include<stdio.h>

static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();
    // print_test( ... pila_esta_vacia(pila) ... );
    print_test("Prueba pila vacía: ", pila_esta_vacia(pila));
    pila_destruir(pila);
}
// lo mismo que la de arriba?
static void prueba_pila_ver_tope_creada_es_invalido(void) {
    pila_t *pila = pila_crear();
    print_test("Prueba pila ver tope en pila recien creada es invalido: ", pila_ver_tope(pila)==NULL);
    pila_destruir(pila);
}
static void prueba_apilar_pocos_elementos(void) {
    pila_t *pila = pila_crear();
    for(int i=0; i< 10; i++) {
      pila_apilar(pila, (char *)'j');
      print_test("tope de pila = j: ", ('j'==*(char *)pila_ver_tope(pila)));
      pila_apilar(pila, (int *)219);
      print_test("tope de pila = 219: ", (219==*(int*)pila_ver_tope(pila)));

    }
    pila_destruir(pila);
}
static void prueba_pila_desapilar(void) {
  pila_t *pila = pila_crear();
  int valores[] = {11,22,33,44,55,66,77,88,99};
  int cant_valores = 9;
  for(int i = 0; i< cant_valores; i++) {
    pila_apilar(pila, (int*)valores[i]);
  }
  for( int i = 0; i< cant_valores;i++) {
    print_test("desapilando: ",(valores[cant_valores-i-1]==*(int*)pila_desapilar(pila)));
  }
  pila_destruir(pila);
}
static void prueba_pila_volumen(void) {
  pila_t *pila = pila_crear();
  /* Pruebo guardar en todas las posiciones */
  int tam = 10;
  int i;
  bool ok = true;
  for (i = 0; i < tam; i++) {
      // Si algun elemento no se pudo guardar correctamente, ok sera false
      ok &= pila_apilar(pila, (int*)i);
  }
  print_test("se pudieron apilar todos los elementos", ok);

  // desapilarlos
  for( int i = 0; i< tam;i++) {
    printf("%d\n", i);
    print_test("desapilando: ",(tam-i-1==*(int*)pila_desapilar(pila)));
  }
  // print_test("se pudieron desapilar todos los elementos", ok);

  // print_test("no se puede apilarun elemento en vec_vol[tam]", !vector_guardar(vec_vol, tam, 10));


  pila_destruir(pila);
}
static void prueba_pila_desapilar_vacia_es_invalido(void) {
  pila_t *pila = pila_crear();
  print_test("Prueba pila vacía: ", pila_esta_vacia(pila));
  print_test("Prueba desapilar vacia es invalido", pila_desapilar(pila)==NULL);
  pila_destruir(pila);
}

static void prueba_pila_desapilar_despues_de_apilar_y_desapilar_es_invalido(  void){
  pila_t *pila = pila_crear();
  int valores[] = {11,22,33,44,55,66,77,88,99};
  int cant_valores = 9;
  for(int i = 0; i< cant_valores; i++) {
    pila_apilar(pila, (int*)valores[i]);
  }
  for( int i = 0; i< cant_valores;i++) {
    print_test("desapilando: ",(valores[cant_valores-i-1]==*(int*)pila_desapilar(pila)));
  }
  print_test("Prueba desapilar despues de apilar y vaciar es invalido", pila_desapilar(pila)==NULL);

  pila_destruir(pila);
}
static void prueba_pila_ver_tope_despues_de_apilar_y_desapilar_es_invalido(  void){
  pila_t *pila = pila_crear();
  int valores[] = {11,22,33,44,55,66,77,88,99};
  int cant_valores = 9;
  for(int i = 0; i< cant_valores; i++) {
    pila_apilar(pila, (int*)valores[i]);
  }
  for( int i = 0; i< cant_valores;i++) {
    print_test("desapilando: ",(valores[cant_valores-i-1]==*(int*)pila_desapilar(pila)));
  }
  print_test("Prueba ver tope despues de apilar y vaciar es invalido", pila_desapilar(pila)==NULL);

  pila_destruir(pila);
}
void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_ver_tope_creada_es_invalido();
    prueba_apilar_pocos_elementos();
    prueba_pila_desapilar();
    prueba_pila_volumen();
    prueba_pila_desapilar_vacia_es_invalido();
    prueba_pila_desapilar_despues_de_apilar_y_desapilar_es_invalido();
    prueba_pila_ver_tope_despues_de_apilar_y_desapilar_es_invalido();
    // ...
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
