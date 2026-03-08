#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "UI.h"
#include "CSV.h"

/*------------ Manipular strings -------------- */

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

int printStringArray(char arr[][MAX_STRING_LEN], int n){
    for(int i = 0; i < n; i++){
        if(arr[i][0] == '\0') break;

        if(i == n - 1 || arr[i + 1][0] == '\0'){
            printf("%s", arr[i]);
        }else {
            printf("%s, ", arr[i]);
        }
    }
    printf("\n");

    return 0;
}

void mostrarRegistro(void *juego){
    struct videojuego *vjuego;
    vjuego = juego;

    printf("- Nombre: %s\n", vjuego -> name);
    printf("- Fecha de lanzamiento: %s\n", vjuego -> release_date);
    printf("- Imagen de fondo: %s\n", vjuego -> background_image);
    printf("- Calificación: %.2f\n", vjuego -> rating);
    printf("- Cantidad de calificaciones: %i\n", vjuego -> ratings_count);
    printf("- Cantidad de jugadores: %i\n", vjuego -> added);
    printf("- Duración (Horas): %i\n", vjuego -> playtime);
    printf("- Cantidad de reseñas: %i\n", vjuego -> reviews_count);
    printf("- Plataformas: ");
    printStringArray(vjuego -> platforms, 10);
    printf("- Tiendas: ");
    printStringArray(vjuego -> stores, 10);
    printf("- Desarrolladores: ");
    printStringArray(vjuego -> developers, 10);
    printf("- Géneros: ");
    printStringArray(vjuego -> genres, 5);
    printf("- Distribuidores: ");
    printStringArray(vjuego -> publishers, 5);
    printf("- Sitio web: %s\n", vjuego -> website);
    printf("- Descripción: %s\n", vjuego -> description);

}

int menuPrincipal(){
    int c;
    bool nombreEmpty, distrEmpty;
    char option, confirm;
    char nombre_copy[MAX_STRING_LEN];
    char distr_copy[MAX_STRING_LEN];
    struct videojuego *juego;

    char *nombre = (char *) malloc(sizeof(char) * MAX_STRING_LEN);
    if(nombre == NULL){
        perror("Error alocando memoria para nombre");
        exit(-1);
    }
    char *distr = (char *) malloc(sizeof(char) * MAX_STRING_LEN);
    if(distr == NULL){
        perror("Error alocando memoria para distr");
        exit(-1);
    }

    nombre[0] = '\0';
    distr[0] = '\0';
    
    bool running = true;

    while(running){
        do {
            printf("\n> Bienvenido. Ingrese una opción de 1 a 4 <");
            printf("\n1. Buscar juego por nombre");
            printf("\n2. Buscar juegos por desarrollador");
            printf("\n3. Realizar búsqueda ");
            printf("\n4. Salir");

            printf("\n------- Barra de búsqueda -------");
            printf("\nNombre: %s", nombre_copy);
            printf("\nDistribuidora: %s", distr_copy);
            printf("\n---------------------------------");

            printf("\n >>> Ingrese la opción que desee: ");
            scanf(" %c", &option); 
            /*Nota. scanf() deja un \n en el buffer al terminar de leer,
            es necesario consumirlo para evitar problemas con fgets()*/

        } while (option != '1' && option != '2' && option != '3' && option != '4');

        switch(option){
            case '1':
                printf("Para dejarlo vacío -> ENTER");
                printf("\nIngrese el nombre del juego: ");
                while ((c = getchar()) != '\n' && c != EOF); //Limpiar buffer
                fgets(nombre, MAX_STRING_LEN, stdin); //Leer nombre
                nombre[strcspn(nombre, "\n")] = '\0'; //Quitar salto de linea al final
                strcpy(nombre_copy, nombre); 
                
                break;
            case '2':
                printf("Para dejarlo vacío -> ENTER");
                printf("\nIngrese el desarrollador: ");
                while ((c = getchar()) != '\n' && c != EOF); //Limpiar buffer
                fgets(distr, MAX_STRING_LEN, stdin); //Leer distr
                distr[strcspn(distr, "\n")] = '\0'; //Quitar salto de linea al final
                strcpy(distr_copy, distr);

                break;
            case '3': 
                nombreEmpty = strEmpty(nombre);
                distrEmpty = strEmpty(distr);
                if(nombreEmpty && distrEmpty){
                    printf(">>> ¡Ingrese al menos un criterio de búsqueda! <<<\n");
                }

                //Convertir a minuscula para más facilidad buscando
                if(!nombreEmpty){
                    strToLower(nombre);

                    //Buscar por nombre

                } else if(!distrEmpty){ 
                    strToLower(distr);

                    //Si no hay nombre, buscar por desarrollador

                }

                //TEST
                FILE *test = fopen("dataset/rawg-games-dataset.csv", "r");
                char line[8192];
                fgets(line, 8192, test); 

                juego = getRegisterFromCSV(ftell(test)); 
                mostrarRegistro((void *) juego);
                
                while (confirm != 's' && confirm != 'n'){
                    printf("\n¿Desea volver al menú principal? s/n : ");
                    scanf(" %c", &confirm);
                    confirm = tolower(confirm);
                }

                if(confirm == 'n'){
                    running = false;
                }

                break;
            case '4':
                printf("Programa terminado\n");
                running = false;
                break;
        }
    }
    
    //Liberar memoria
    free(nombre);
    free(distr);
    free(juego);

    return 0;
}