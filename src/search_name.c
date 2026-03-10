#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Carga el directorio de buckets en memoria */
static uint32_t *cargarDirectorio(const char *rutaDir){
    FILE *f = fopen(rutaDir, "rb");
    if(!f){
        perror("fopen dir");
        exit(EXIT_FAILURE);
    }

    uint32_t *dir = (uint32_t*)malloc(NUM_BUCKETS * sizeof(uint32_t));
    if(!dir){
        perror("malloc dir");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    size_t leidos = fread(dir, sizeof(uint32_t), NUM_BUCKETS, f);
    fclose(f);

    if(leidos != NUM_BUCKETS){
        fprintf(stderr, "Error leyendo directorio.\n");
        free(dir);
        exit(EXIT_FAILURE);
    }

    return dir;
}

/* Imprime registros del CSV usando sus offsets */
static void imprimirRegistrosCSV(FILE *fcsv, uint32_t *offsets, uint32_t n){
    char linea[MAX_LINEA];

    for(uint32_t i = 0; i < n; i++){
        if(fseek(fcsv, offsets[i], SEEK_SET) != 0){
            perror("fseek csv");
            continue;
        }

        if(fgets(linea, sizeof(linea), fcsv)){
            printf("%s", linea);
        }
    }
}

/* Busca una consulta dentro del índice binario por name */
static void buscarEnIndice(const char *query, const uint32_t *dir, FILE *fidx, FILE *fcsv){
    unsigned long bucket = hashString(query, NUM_BUCKETS);
    uint32_t pos = dir[bucket];

    while(pos != INVALID_OFFSET){
        if(fseek(fidx, pos, SEEK_SET) != 0){
            perror("fseek index");
            return;
        }

        DiskEntryHeader h;
        if(fread(&h, sizeof(DiskEntryHeader), 1, fidx) != 1){
            fprintf(stderr, "Error leyendo cabecera del índice.\n");
            return;
        }

        char *key = (char*)malloc(h.keyLen + 1);
        if(!key){
            perror("malloc key");
            return;
        }

        if(fread(key, sizeof(char), h.keyLen, fidx) != h.keyLen){
            free(key);
            fprintf(stderr, "Error leyendo key.\n");
            return;
        }
        key[h.keyLen] = '\0';

        if(strcmp(key, query) == 0){
            uint32_t *offsets = (uint32_t*)malloc(h.countOffsets * sizeof(uint32_t));
            if(!offsets){
                perror("malloc offsets");
                free(key);
                return;
            }

            if(fread(offsets, sizeof(uint32_t), h.countOffsets, fidx) != h.countOffsets){
                fprintf(stderr, "Error leyendo offsets.\n");
                free(offsets);
                free(key);
                return;
            }

            imprimirRegistrosCSV(fcsv, offsets, h.countOffsets);

            free(offsets);
            free(key);
            return;
        }

        free(key);
        pos = h.nextEntry;
    }

    printf("NA\n");
}

int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr, "Uso: %s <rawg-games-dataset.csv> <name_dir.bin> <name_index.bin>\n", argv[0]);
        return 1;
    }

    uint32_t *dir = cargarDirectorio(argv[2]);

    FILE *fidx = fopen(argv[3], "rb");
    FILE *fcsv = fopen(argv[1], "r");

    if(!fidx || !fcsv){
        perror("fopen");
        free(dir);
        if(fidx) fclose(fidx);
        if(fcsv) fclose(fcsv);
        return 1;
    }

    char consulta[MAX_NAME];
    printf("Ingrese name: ");
    if(!fgets(consulta, sizeof(consulta), stdin)){
        free(dir);
        fclose(fidx);
        fclose(fcsv);
        return 1;
    }

    normalizarCadena(consulta);
    buscarEnIndice(consulta, dir, fidx, fcsv);

    free(dir);
    fclose(fidx);
    fclose(fcsv);
    return 0;
}