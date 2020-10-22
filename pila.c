#include "pila.h"
#include<stdio.h>
#include <stdlib.h>

#define MIN_PILA 4 // el minimo que la pila al ser creada
#define FACTOR_INC_PILA 2 // duplicar la pila cuando llena

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ..
pila_t *pila_crear(void) {
    // crear un puntero struct en heap
    pila_t *pila = malloc( sizeof(pila_t) );
    // si no lo pudo crear retornar null
    if (!pila) return NULL;
    // si todo ok sigo
    // crear un puntero generico en heap de size puntero generico
    // * minimo size de la pila
    void *datos = malloc( sizeof(void*) * MIN_PILA);
    // si no se puede retornar null
    if( !datos) {
      printf("no se pudo hacer malloc datos\n");
      return NULL;
    }
    pila->datos = datos;
    pila->cantidad = 0;
    pila->capacidad = MIN_PILA;
    // printf("pila->datos: %p\n", pila->datos);
    // printf("pila->capacidad: %d\n", pila->capacidad);
    // printf("pila->cantidad: %d\n", pila->cantidad);

    // todo ok, retorno la pila, que vive el el heap
    return pila;
}

void pila_destruir(pila_t *pila) {
    // borro los datos de la pila primero
  free(pila->datos);
  // luego la pila
  free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {

    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor) {
    // solamente contemplado el caso de tudo bom
    // printf("apilando %d\n",  (int)valor);
    // pongo el el arreglo de datos el valor en la posicion
    //  cantidad (inicialmente = 0) e incremento la cantidad
    if( pila->cantidad == pila->capacidad) {
      // intentar el realloc
      void *datos_nuevo = realloc(pila->datos, pila->cantidad *FACTOR_INC_PILA * sizeof(void*));

      // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
      // En toda otra situación significa que falló el realloc.
      if ( datos_nuevo == NULL) {
          return false;
      }
      // poner los datos en la pila
      pila->datos = datos_nuevo;
      // actualizar cantidad
      pila->capacidad = pila->cantidad* FACTOR_INC_PILA;
    }
    // agregar el dato
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    // printf("pila en cantidad %d\n",  (int)pila->datos[0]);
    printf("pila->capacidad: %d\n", pila->capacidad);
    printf("pila->cantidad: %d\n", pila->cantidad);

  return true;
}

void *pila_ver_tope(const pila_t *pila) {
    // pila vacia
    if(pila_esta_vacia(pila) ) return NULL;
    // lo jodido de esta funcion es el return
    // paso a puntero generico la direcion del dato[tope]
    // ojo al piojo!
    // printf("cantidad es %d\n", (int)pila->cantidad);
    // printf("tope de pila: %d\n", (int)pila->datos[pila->cantidad-1]);
  return (void *)&pila->datos[pila->cantidad-1];
}

void *pila_desapilar(pila_t *pila) {
    if(pila->cantidad == 0) return NULL;
    /*
    if(pila->cantidad == 1) {
        pila->cantidad = 0;
        return (void *)&pila->datos[0];
    }
    pila->cantidad--;
    */
    if( (pila->capacidad > MIN_PILA*4) && (pila->cantidad <= pila->capacidad/4)) {
      // realloc para abajo
      void *datos_nuevo = realloc(pila->datos, (pila->capacidad / 2) * sizeof(void*));

      // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
      // En toda otra situación significa que falló el realloc.
      // if ( datos_nuevo == NULL) {
      //     return false;
      // }
      // poner los datos en la pila
      pila->datos = datos_nuevo;
      // actualizar cantidad
      pila->capacidad = pila->capacidad/2;
    }
      // actualizar capacidad
    // }
    // Aguantaaa Maradona!
    return (void *)&pila->datos[--pila->cantidad];
}
/*
int main() {
    pila_t *pi = pila_crear();
    //free(pi->datos);
    //free(pi);
    // pruebo de poner un elemento en la pila, debo pasarle un puntero
   // void* v = malloc( sizeof(void *)*1 );
   // v = (int*)8897;
   // printf("v=%d , &v= %p\n", (int)v, &v);
    pila_apilar(pi,(int*)3323);
    pila_apilar(pi, (int*)2172);

    // void *  eltope = malloc(sizeof(void*));
    // ojo con esto, pila_ver_tope me devuelve una direccion de
    // un puntero generico, (int *) lo transforma en un puntero a entero
    // y * antes del (int *) desreferencia la direccion del tope
    // y lo guardo en eltope
    int eltope = *(int *)pila_ver_tope(pi);
    // muestro el tope como un entero comun y corriente
    printf("al tope esta: %d\n",eltope);
    if( pila_esta_vacia( pi ) ) printf("La pila esta vacia\n");
    else printf("La pIla NO esta vacia\n");

    printf("------------------desapilar--------\n");
    int saco_elemento = *(int *)pila_desapilar(pi);
    printf("elemento sacado: %d\n",saco_elemento);

    if( pila_esta_vacia( pi ) ) printf("La pila esta vacia\n");
    else printf("La pIla NO esta vacia\n");

    eltope = *(int *)pila_ver_tope(pi);
    // muestro el tope como un entero comun y corriente
    printf("al tope esta: %d\n",eltope);


    pila_destruir( pi );
  return 0;
}
*/
