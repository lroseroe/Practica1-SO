#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "GUI.h"

#define MAX_LINE_LEN 8192

//NOTA. Esto lo debe hacer el proceso de búsqueda

void splitLineIntoArray(char *str, char arr[][MAX_STRING_LEN], int n){ // A|B|C -> [A, B, C]
    char *token = strtok(str, "|");
    for(int i = 0; i < n && token != NULL; i++){
        strncpy(arr[i], token, MAX_STRING_LEN - 1);
        arr[i][MAX_STRING_LEN - 1] = '\0';

        token = strtok(NULL, "|");
    }
}       

struct videojuego *getRegisterFromCSV(long position){
    int r, len;
    bool in_quotes = false; //Para evitar errores parseando el CSV
    char line[MAX_LINE_LEN], value[MAX_STRING_LEN];
    struct videojuego *vjuego;
    
    vjuego = malloc(sizeof(struct videojuego));
    if(vjuego == NULL){
        perror("Error alocando memoria para vjuego");
        exit(-1);
    }

    FILE *file;
    file = fopen("dataset/rawg-games-dataset.csv", "r");
    if(file == NULL){
        perror("Error abriendo el archivo");
        exit(-1);
    }

    //SEEK_SET para que cuente los byts indicados por position desde el inicio del csv
    r = fseek(file, position, SEEK_SET); 
    if(r != 0){
        perror("Error en fseek()");
        exit(-1);
    }
    
    fgets(line, MAX_LINE_LEN, file); 

    int col = 0;
    int start = 0;
    int end = 0;

    for(int i = 0; line[i] != '\0'; i++){
        if(line[i] == '"'){ 
            in_quotes = !in_quotes; 
            continue;
        } 
        if(line[i] == ',' && !in_quotes){
            end = i; 

            if(line[start] == '"'){
                start++;
            }

            if(line[end - 1] == '"'){
                end--;
            }

            len = end - start;
            strncpy(value, &line[start], len);
            value[len] = '\0';

            switch(col){
                case 2: //name
                    strcpy(vjuego->name, value);
                    break;
                case 3: //release_date
                    strcpy(vjuego->release_date, value);
                    break;
                case 4: //background_image
                    strcpy(vjuego->background_image, value);
                    break;
                case 5: //rating
                    vjuego->rating = atof(value);
                    break;
                case 7: //ratings_count
                    vjuego->ratings_count = atoi(value);
                    break;
                case 9: //added
                    vjuego->added = atoi(value);
                    break;
                case 10: //playtime
                    vjuego->playtime = atoi(value);
                    break;
                case 13: //reviews_count
                    vjuego->reviews_count = atoi(value);
                    break;
                case 16: //platforms
                    splitLineIntoArray(value, vjuego->platforms, 10);
                    break;
                case 17: //stores
                    splitLineIntoArray(value, vjuego->stores, 10);
                    break;
                case 18: //developers
                    splitLineIntoArray(value, vjuego->developers, 10);
                    break;
                case 19: //genres
                    splitLineIntoArray(value, vjuego->genres, 5);
                    break;
                case 21: //publishers
                    splitLineIntoArray(value, vjuego->publishers, 5);
                    break;
                case 32: //website
                    strcpy(vjuego->website, value);
                    break;
                case 41: //description
                    strcpy(vjuego->description, value);
                    break;
            }

            col ++;
            start = i + 1;
        }

    }

    fclose(file);
    return vjuego;
}