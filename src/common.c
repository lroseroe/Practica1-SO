#include "common.h"
#include <ctype.h>
#include <string.h>

/* Hash djb2 para strings */
unsigned long hashString(const char *str, unsigned long B){
    unsigned long hash = 5381;
    int c;

    while((c = (unsigned char)*str++)){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % B;
}

/* Normalización de cadenas para que las búsquedas sean consistentes */
void normalizarCadena(char *s){
    if(s == NULL) return;

    /* quitar fin de línea */
    s[strcspn(s, "\r\n")] = '\0';

    /* quitar espacios iniciales */
    char *inicio = s;
    while(*inicio && isspace((unsigned char)*inicio)) inicio++;

    if(inicio != s){
        memmove(s, inicio, strlen(inicio) + 1);
    }

    /* quitar espacios finales */
    int n = (int)strlen(s);
    while(n > 0 && isspace((unsigned char)s[n - 1])){
        s[n - 1] = '\0';
        n--;
    }

    /* pasar a minúsculas */
    for(int i = 0; s[i]; i++){
        s[i] = (char)tolower((unsigned char)s[i]);
    }

    /* quitar comillas exteriores */
    n = (int)strlen(s);
    if(n >= 2 && s[0] == '"' && s[n - 1] == '"'){
        memmove(s, s + 1, n - 2);
        s[n - 2] = '\0';
    }
}

/* Extrae la columna indicada de una línea CSV.
   Respeta comillas dobles para no cortar mal si hay comas dentro del campo. */
int extraerCampoCSV(const char *linea, int indiceCampo, char *salida, size_t maxSalida){
    int campoActual = 0;
    int dentroComillas = 0;
    size_t j = 0;

    for(size_t i = 0; linea[i] != '\0'; i++){
        char c = linea[i];

        if(c == '"'){
            dentroComillas = !dentroComillas;
        }
        else if(c == ',' && !dentroComillas){
            if(campoActual == indiceCampo){
                salida[j] = '\0';
                return 1;
            }
            campoActual++;
            j = 0;
        }
        else{
            if(campoActual == indiceCampo){
                if(j + 1 < maxSalida){
                    salida[j++] = c;
                }
            }
        }
    }

    if(campoActual == indiceCampo){
        salida[j] = '\0';
        return 1;
    }

    return 0;
}

/* Divide el campo publishers usando '|' como separador.
   Guarda cada publisher en publishers[i].
   Devuelve cuántos publishers encontró. */
int dividirPublishers(const char *campo, char publishers[][MAX_PUBLISHER], int maxPublishers){
    if(campo == NULL || campo[0] == '\0') return 0;

    int count = 0;
    int j = 0;

    for(size_t i = 0; ; i++){
        char c = campo[i];

        if(c == '|' || c == '\0'){
            if(j > 0 && count < maxPublishers){
                publishers[count][j] = '\0';
                normalizarCadena(publishers[count]);

                if(publishers[count][0] != '\0'){
                    count++;
                }
            }

            j = 0;

            if(c == '\0'){
                break;
            }
        }
        else{
            if(count < maxPublishers && j < MAX_PUBLISHER - 1){
                publishers[count][j++] = c;
            }
        }
    }

    return count;
}