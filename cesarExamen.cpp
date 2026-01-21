//  examenMayo23
/*
 *
 *
  César Mata Rodríguez
 *
 *
 */
//  Created by  on 29/05/2023.
//  Copyright © 2023 . All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//**************** TIPOS DE DATOS ****************************
struct datosEmpleado{
    char dni[10];
    int año;
    double sueldo;
};

struct nodoEmpleado{
    struct datosEmpleado infoEmpleado;
    struct nodoEmpleado *siguiente;
    struct nodoEmpleado *anterior;
};

struct listaEmpleados{
    struct nodoEmpleado *primero;
    struct nodoEmpleado *ultimo;
};

struct datosHotel{
    int codigo;
    char ciudad[20];
    int numeroEstrellas;
};

struct nodoHotel{
    struct datosHotel infoHotel;
    struct listaEmpleados listaEmpleados;
    struct nodoHotel *siguiente;
    struct nodoHotel *anterior;
};
struct listaHoteles{
    struct nodoHotel *primero;
    struct nodoHotel *ultimo;
};
//************************************************************

//**************** FUNCIONES CODIFICADAS**********************
void introducirInfoHotel(struct datosHotel *);
void addNodoHotel(struct listaHoteles *);
int menu(void);
void addEmpleado(struct nodoHotel *pri);
void addNodoEmpleado(struct listaEmpleados *lista);
struct nodoHotel * buscar(struct nodoHotel *pri, int codigo);
struct nodoEmpleado * buscarEmpleado(struct nodoEmpleado *primero, char dni[]);
void addNodoHotel(struct listaHoteles *lista);
void eliminarEmpleado (struct listaHoteles *lista);
void FicheroBinario (struct listaHoteles *lista);

//************************************************************

int main() {
    struct listaHoteles listaHoteles;
    listaHoteles.primero = listaHoteles.ultimo = NULL;
    int opc;
    do{
        opc = menu();
        switch (opc) {
            case 1:addNodoHotel(&listaHoteles);
                break;
            case 2:
                addEmpleado(listaHoteles.primero);
                break;
            case 3:
                eliminarEmpleado(&listaHoteles);
                break;
            case 4:

                break;

            default:
                break;
        }
    }while (opc!=0);

    return 0;
}

int menu(){
    int opc;
    do{
        printf("\n\t\t\tMENU");
        printf("\n\t1.Añadir un hotel");
        printf("\n\t2.Contratar un empleado");
        printf("\n\t3.Rescindir contrato");
        printf("\n\t4.Registar empleados de la cadena");
        printf("\n\n\t0.SALIR");
        printf("\n\nIntroduce una opción: ");scanf("%d",&opc);
    }while(opc<0 || opc>4);
    return opc;
}

void introducirInfoHotel(struct datosHotel *hotel){
    printf("\n\t Información del hotel");
    printf("\n\t Codigo: ");scanf("%d",&hotel->codigo);
    printf("\n\t Ciudad: ");fpurge(stdin);scanf("%s",hotel->ciudad);
    printf("\n\t Numero Estrellas: ");scanf("%d",&hotel->numeroEstrellas);
}

void addNodoHotel(struct listaHoteles *lista){
    struct nodoHotel *nuevo;

    nuevo = (struct nodoHotel *)malloc(sizeof(struct nodoHotel));

    if (nuevo == NULL){
        printf("\n ERROR de memoria");
        return;
    }
    introducirInfoHotel(&nuevo->infoHotel);
    nuevo->listaEmpleados.primero = nuevo->listaEmpleados.ultimo = NULL;

    if (lista->primero == NULL){
        lista->primero = nuevo;
    }
    else{
        lista->ultimo->siguiente = nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = lista->ultimo;
    lista->ultimo = nuevo;
}



struct nodoHotel * buscar(struct nodoHotel *pri, int codigo) {
    struct nodoHotel *recorre;
    recorre = pri;

    while (recorre != NULL && recorre->infoHotel.codigo != codigo) {
        recorre = recorre->siguiente;
    }
    return recorre;

}

struct nodoEmpleado *buscarEmpleado(struct nodoEmpleado *primero, char dni[]) {
    struct nodoEmpleado *recorre;
    recorre = primero;

    while (recorre != NULL && strcmp(recorre->infoEmpleado.dni,dni)!=0) {
        recorre = recorre->siguiente;
    }
    return recorre;

}

void addEmpleado(struct nodoHotel *pri) {
    int codigo;
    struct nodoHotel *hotelBuscado;

    printf("\n Introduce el codigo del hotel: ");
    scanf("%d",&codigo);

    hotelBuscado = buscar(pri,codigo);
    if (hotelBuscado == NULL) {
        printf("\n El hotel no existe");
        return;
    }

    addNodoEmpleado(&hotelBuscado->listaEmpleados);

}
void addNodoEmpleado(struct listaEmpleados *lista) {
    char dni[10];
    struct nodoEmpleado *nuevo, *buscado;

    printf("\n Introduce el dni del empleado: ");
    fflush(stdin);
    scanf("%s", dni);
    buscado = buscarEmpleado(lista->primero, dni);
    if (buscado != NULL) {
        printf("el empleado ya esta trabajando");
    }

    nuevo = (struct nodoEmpleado *)malloc(sizeof(struct nodoEmpleado));

    if (nuevo == NULL) {
        printf("\n ERROR de memoria");
        return;
    }


    strcpy(nuevo->infoEmpleado.dni, dni);
    printf("\n Introduce el sueldo: ");
    scanf("%f", &nuevo->infoEmpleado.sueldo);
    printf("\n Introduce el anno de entrada: ");
    scanf("%f", &nuevo->infoEmpleado.año);


    if (lista->primero == NULL) {
        lista->ultimo = nuevo;
    }
    else {
        lista->primero->anterior = nuevo;
    }
    nuevo->siguiente = lista->primero;
    nuevo->anterior = NULL;
    lista->primero = nuevo;

}


void eliminarEmpleado(struct listaHoteles *listaHoteles) {
    int codigo;
    char dni[10];
    struct nodoHotel *hotel;
    struct nodoEmpleado *empleadoBuscado;
    int fechaActuald;
    int fechaActualm;
    int fechaActuala;
    int diferencia;
    FILE *Texto;
    Texto = fopen("rescindir.txt","w");

    if(Texto == NULL){
        printf("\n Error con el fichero: ");
        return;
    }

    printf("\n Introduce el codigo del hotel: ");
    scanf("%d", &codigo);

    hotel = buscar(listaHoteles->primero,codigo);
    if (hotel == NULL) {
        printf("\n El hotel no existe");
        return;
    }


    printf("\n Introduce el dni del empleado del que se quiere rescindir el contrato: ");
    fflush(stdin);
    scanf("%s", dni);

    empleadoBuscado = buscarEmpleado(hotel->listaEmpleados.primero, dni);
    if (empleadoBuscado == NULL) {
        printf("\n no existe ese empleado");
        return;
    }


    printf("\n Introduce el dia: ");
    scanf("%d", &fechaActuald);

    printf("\n Introduce el mes: ");
    scanf("%d", &fechaActualm);

    printf("\n Introduce el anno: ");
    scanf("%d", &fechaActuala);



    fprintf(Texto," Fecha: %d/%d/%d",fechaActuald,fechaActualm,fechaActuala);
    fprintf(Texto," DNI: %s",empleadoBuscado->infoEmpleado.dni);
    fprintf(Texto," Codigo Hotel : %d",hotel->infoHotel.codigo);
    fprintf(Texto," Antiguedad (ano desde que lleva en el hotel) : %d",empleadoBuscado->infoEmpleado.año);


    if (empleadoBuscado == hotel->listaEmpleados.primero && empleadoBuscado == hotel->listaEmpleados.ultimo) {

        hotel->listaEmpleados.primero = NULL;
        hotel->listaEmpleados.ultimo = NULL;
    }
    else if (empleadoBuscado == hotel->listaEmpleados.ultimo) {

        hotel->listaEmpleados.ultimo = hotel->listaEmpleados.ultimo->anterior;
        hotel->listaEmpleados.ultimo->siguiente = NULL;
    }
    else if (empleadoBuscado == hotel->listaEmpleados.primero) {

        hotel->listaEmpleados.primero = empleadoBuscado->siguiente;
        hotel->listaEmpleados.primero->anterior = empleadoBuscado->siguiente;
    }
    else {

        empleadoBuscado->siguiente->anterior = empleadoBuscado->anterior;
        empleadoBuscado->anterior->siguiente= empleadoBuscado->siguiente;
    }
    free(empleadoBuscado);
    fclose(Texto);
}

void FicheroBinario (struct listaHoteles *lista){
    struct nodoHotel *recorre;
    struct nodoEmpleado *recorreE;
    FILE *f;
    int  contador = 0;

    f = fopen("listar.bin","wb");

    if(f == NULL){
        printf("\n Error con el fichero: ");
        return;
    }

    while (recorre != NULL ) {
        fwrite(&recorre->infoHotel.codigo,sizeof (struct nodoHotel),1,f);

        while (recorreE != NULL ){
            fwrite(&recorreE,sizeof (struct nodoHotel),1,f);
            contador = contador +1;
        }
    }

}












