#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

/* Cantidad de buckets del hash.
   65536 = 2^16, buen balance entre memoria y colisiones */
#define NUM_BUCKETS 65536UL

/* Valor especial para indicar que un bucket no tiene entradas */
#define INVALID_OFFSET 0xFFFFFFFFU

/* Tamaño máximo de línea leída del CSV */
#define MAX_LINEA 65536

/* Tamaño máximo esperado para el campo name */
#define MAX_NAME 2048

/* Tamaño máximo esperado para el campo publisher */
#define MAX_PUBLISHER 2048

/* Columna del CSV donde está "name" */
#define COL_NAME 2

/* Columna del CSV donde está "publishers" */
#define COL_PUBLISHERS 21

/* Vector dinámico de offsets.
   Reemplaza la lista enlazada de offsets para ahorrar memoria
   y facilitar escritura binaria. */
typedef struct OffsetVec {
    uint32_t *data;
    uint32_t size;
    uint32_t capacity;
} OffsetVec;

/* Nodo temporal del hashmap usado SOLO durante la construcción
   del índice. */
typedef struct BuildNode {
    char *key;                 /* name normalizado */
    OffsetVec offsets;         /* offsets del CSV para esta llave */
    struct BuildNode *next;    /* chaining para colisiones */
} BuildNode;

/* Cabecera de cada entrada guardada en el archivo binario.
   Después de esta cabecera, se escriben:
   - la llave (key)
   - el arreglo de offsets */
typedef struct {
    uint32_t nextEntry;      /* posición de la siguiente entrada del bucket en el archivo */
    uint32_t keyLen;         /* longitud de la llave */
    uint32_t countOffsets;   /* cantidad de offsets asociados */
} DiskEntryHeader;

/* Función hash para strings */
unsigned long hashString(const char *str, unsigned long B);

/* Normaliza una cadena:
   - quita \r y \n
   - quita espacios al inicio y al final
   - pasa a minúsculas
   - quita comillas externas */
void normalizarCadena(char *s);

/* Extrae un campo del CSV respetando comillas.
   Devuelve 1 si pudo extraer el campo, 0 si no. */
int extraerCampoCSV(const char *linea, int indiceCampo, char *salida, size_t maxSalida);

/* Procesa el campo publishers y llama callback por cada publisher encontrado */
void procesarPublishers(const char *campo, void (*callback)(const char*, uint32_t, void*), uint32_t offset, void *ctx);

int dividirPublishers(const char *campo, char publishers[][MAX_PUBLISHER], int maxPublishers);

#endif