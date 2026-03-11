#ifndef GUI_H //Si no se ha definido la libreria...
#define GUI_H //Se define

#define MAX_STRING_LEN 370
#define MAX_LINK_LEN 1024
#define MAX_TEXT_LEN 4096

struct videojuego {
    char name[MAX_STRING_LEN]; // 2
    char release_date[15]; //Formato YYYY-MM-DD 3
    char background_image[MAX_LINK_LEN]; // 4
    float rating; // 5 
    int ratings_count; // 7
    int added; // 9 
    int playtime; // 10
    int reviews_count; //13
    char platforms[10][MAX_STRING_LEN]; //16
    char stores[10][MAX_STRING_LEN]; //17
    char developers[5][MAX_STRING_LEN]; //18
    char genres[5][MAX_STRING_LEN]; //19
    char publishers[5][MAX_STRING_LEN]; //21
    char website[MAX_LINK_LEN]; //32
    char description[MAX_TEXT_LEN]; //41
};



#endif