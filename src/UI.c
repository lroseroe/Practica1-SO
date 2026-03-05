#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "UI.h"

#define MAX_STRING_LEN 100

bool strEmpty(char *str){
    while(*str){ //Recorrer char por char en memoria hasta que se encuentre NULL
        if(!isspace(*str)){
            return false;
        }
        str++;
    }
    return true;
}

int strToLower(char *str){
    char *c;
    c = str; //Para no perder el inicio
    while(*c){ //Recorrer char por char en memoria hasta que se encuentre NULL
        *c = tolower(*c);
        c++;
    }
    return 0;
}

int menuPrincipal(){
    int opcion, c;
    bool nombreEmpty, devEmpty;

    char *nombre = (char *) malloc(sizeof(char) * MAX_STRING_LEN);
    if(nombre == NULL){
        perror("Error alocando memoria para nombre");
        exit(-1);
    }
    char *dev = (char *) malloc(sizeof(char) * MAX_STRING_LEN);
    if(dev == NULL){
        perror("Error alocando memoria para dev");
        exit(-1);
    }
    
    bool running = true;
    while(running){
        printf("\nBienvenido. ");
        printf("\n1. Buscar juego por nombre");
        printf("\n2. Buscar juegos por desarrollador");
        printf("\n3. Realizar búsqueda ");
        printf("\n4. Salir");

        printf("\nIngrese la acción que desee realizar: ");
        scanf("%i", &opcion); 
        /*Nota. scanf() deja un \n en el buffer al terminar de leer,
        es necesario consumirlo para evitar problemas con fgets()*/

        switch(opcion){
            case 1:
                printf("Para dejarlo vacío -> ENTER");
                printf("\nIngrese el nombre del juego: ");
                while ((c = getchar()) != '\n' && c != EOF); //Limpiar buffer
                fgets(nombre, MAX_STRING_LEN, stdin); //Leer nombre
                nombre[strcspn(nombre, "\n")] = '\0'; //Quitar salto de linea al final

                printf("\nTest: %s", nombre);
                
                break;
            case 2:
                printf("Para dejarlo vacío -> ENTER");
                printf("\nIngrese el desarrollador: ");
                while ((c = getchar()) != '\n' && c != EOF); //Limpiar buffer
                fgets(dev, MAX_STRING_LEN, stdin); //Leer dev
                dev[strcspn(dev, "\n")] = '\0'; //Quitar salto de linea al final

                printf("\nTest: %s", dev);
                
                break;
            case 3: 
                nombreEmpty = strEmpty(nombre);
                devEmpty = strEmpty(dev);
                if(nombreEmpty && devEmpty){
                    printf("Ingrese al menos un criterio de búsqueda.\n");
                }

                //Convertir a minuscula para más facilidad buscando
                if(!nombreEmpty){
                    strToLower(nombre);
                    printf("\nNombre: %s", nombre);
                }

                if(!devEmpty){
                    strToLower(dev);
                    printf("\nDesarrollador: %s", nombre);
                }

                //Buscar en HashMap y mostrar resultados en pantalla 
                
                break;
            case 4:
                printf("Programa terminado\n");
                running = false;
                break;
            default:
                break;
        }
    }
    
    //Liberar memoria
    free(nombre);
    free(dev);


    return 0;
}