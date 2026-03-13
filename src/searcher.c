#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"
#include "search_name.h"
#include "search_publisher.h"

int fd_query, fd_response;

int main(){
    int r, count;
    Query query;
    OffsetList offsets;
    Videojuego temp;   // <-- un solo buffer temporal

    offsets.positions = NULL;
    offsets.size = 0;

    r = mkfifo("/tmp/fifo_query", 0666);
    if(r < 0 && errno != EEXIST){
        perror("Error creando fifo_query");
        exit(1);
    }

    r = mkfifo("/tmp/fifo_response", 0666);
    if(r < 0 && errno != EEXIST){
        perror("Error creando fifo_response");
        exit(1);
    }

    fd_query = open("/tmp/fifo_query", O_RDONLY);
    if(fd_query < 0){
        perror("Error abriendo fifo_query");
        exit(-1);
    }

    fd_response = open("/tmp/fifo_response", O_WRONLY);
    if(fd_response < 0){
        perror("Error abriendo fifo_response");
        exit(-1);
    }

    FILE *fcsv = fopen(CSV_FILE, "r");
    uint32_t *dir_name = cargarDirectorioName(DIR_NAME_FILE);
    FILE *fidx_name = fopen(IDX_NAME_FILE, "rb");

    uint32_t *dir_publ = cargarDirectorioPublisher(DIR_PUBL_FILE);
    FILE *fidx_publ = fopen(IDX_PUBL_FILE, "rb");

    if(!fidx_name || !fidx_publ || !fcsv){
        perror("fopen");
        free(dir_name);
        free(dir_publ);
        if(fidx_name) fclose(fidx_name);
        if(fidx_publ) fclose(fidx_publ);
        if(fcsv) fclose(fcsv);
        return 1;
    }

    while(1){
        r = read(fd_query, &query, sizeof(query));

        if(r == 0){
            printf("Terminando proceso de búsqueda...\n");
            break;
        }

        if(r < 0){
            perror("Error leyendo fifo_query");
            exit(-1);
        }

        normalizarCadena(query.criteria);

        if(query.type == 0){
            offsets = buscarEnIndiceName(query.criteria, dir_name, fidx_name);
        } else if(query.type == 1){
            offsets = buscarEnIndicePublisher(query.criteria, dir_publ, fidx_publ);
        } else {
            offsets.positions = NULL;
            offsets.size = 0;
        }

        count = offsets.size;
        if(count > MAX_RESULTS) count = MAX_RESULTS;

        writeFull(fd_response, &count, sizeof(int));

        for(int i = 0; i < count; i++){
            temp = getRegisterFromCSV(offsets.positions[i], fcsv);
            writeFull(fd_response, &temp, sizeof(Videojuego));
        }

        if(offsets.positions){
            free(offsets.positions);
            offsets.positions = NULL;
            offsets.size = 0;
        }
    }

    free(dir_name);
    free(dir_publ);
    fclose(fidx_name);
    fclose(fidx_publ);
    fclose(fcsv);
    close(fd_query);
    close(fd_response);

    return 0;
}