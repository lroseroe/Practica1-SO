#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *name_entry;
    GtkWidget *publ_entry;
    GtkWidget *result_list; //Para mostrar resultados en una lista
} searchWidgets;


static void showError(GtkWindow *parent, const char *message){
    GtkAlertDialog *dialog;
    dialog = gtk_alert_dialog_new("%s", message);
    gtk_alert_dialog_show(dialog, parent);
}

static void search_cb(GtkButton *btn, gpointer user_data){
    searchWidgets *widgets = user_data;
    GtkWidget *row;
    GtkWidget *name_lbl;

    const char *name_ent = gtk_editable_get_text(GTK_EDITABLE(widgets->name_entry));
    const char *publ_ent = gtk_editable_get_text(GTK_EDITABLE(widgets->publ_entry));

    char *name = g_strdup(name_ent); //Hacemos una copia mutable
    g_strstrip(name);
    char *publ = g_strdup(publ_ent);
    g_strstrip(publ);

    if(strlen(name) == 0 && strlen(publ) == 0){
        showError(GTK_WINDOW(widgets -> window), "Ingrese al menos un criterio de búsqueda");
    }

    if(strlen(name) > 0){

        //Realizar busqueda por nombre
        
        name_lbl = gtk_label_new("Test");
        row = gtk_list_box_row_new();

        gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), name_lbl);
        gtk_list_box_append(GTK_LIST_BOX(widgets -> result_list), row);

    } else if(strlen(publ) > 0){

        //Realizar busqueda por distribuidora
    }

    g_print("%li\n",strlen(name));
    g_print("%li\n",strlen(publ));

    g_print("Nombre: %s\n", name);
    g_print("Distribuidora: %s\n", publ);

    //Liberar memoria 
    g_free(name);
    g_free(publ);
}

static void activate(GtkApplication *app){
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *search_box;
    GtkWidget *name_entry; //Para buscar por nombre
    GtkWidget *publ_entry; //Para buscar por distribuidora
    GtkWidget *search_btn; //Ejecutar la busqueda
    GtkWidget *paned; //Para dividir la ventana
    GtkWidget *result_list; //Mostrar resultados encontrados
    GtkWidget *details_box; //Mostrar detalles de un resultado
    GtkWidget *details_scroll;

    GtkWidget *name_lbl;
    GtkWidget *release_date_lbl;
    GtkWidget *background_image_lbl;
    GtkWidget *rating_lbl;
    GtkWidget *ratings_count_lbl;
    GtkWidget *added_lbl;
    GtkWidget *playtime_lbl;
    GtkWidget *reviews_count_lbl;
    GtkWidget *platforms_lbl;
    GtkWidget *stores_lbl;
    GtkWidget *developers_lbl;
    GtkWidget *genres_lbl;
    GtkWidget *publishers_lbl;
    GtkWidget *website_lbl;
    GtkWidget *description_lbl;

    searchWidgets *s_widgets = g_malloc(sizeof(searchWidgets));

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Sistema de Búsqueda");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 500);

    main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous (GTK_BOX (main_box), FALSE);
    gtk_window_set_child (GTK_WINDOW (window), main_box);
    
    search_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    // ----- Widgets de search_box ---------
    name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Ingrese el nombre del juego");

    publ_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(publ_entry), "Ingrese la distribuidora del juego");
    
    search_btn = gtk_button_new_with_label("Buscar");

    s_widgets -> window = window;
    s_widgets -> name_entry = name_entry;
    s_widgets -> publ_entry = publ_entry;

    g_signal_connect (search_btn, "clicked", G_CALLBACK (search_cb), s_widgets);

    gtk_box_append(GTK_BOX(search_box), name_entry);
    gtk_box_append(GTK_BOX(search_box), publ_entry);
    gtk_box_append(GTK_BOX(search_box), search_btn);

    // Widgets de paned
    result_list = gtk_list_box_new();
    s_widgets -> result_list = result_list;

    details_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    details_scroll = gtk_scrolled_window_new();
    gtk_widget_set_hexpand(details_scroll, TRUE);
    gtk_widget_set_vexpand(details_scroll, TRUE);

    //Ajustar margenes
    gtk_widget_set_margin_start(details_box, 12);
    gtk_widget_set_margin_end(details_box, 12);
    gtk_widget_set_margin_top(details_box, 12);
    gtk_widget_set_margin_bottom(details_box, 12);


    name_lbl = gtk_label_new("Nombre: ");
    release_date_lbl = gtk_label_new("Fecha de lanzamiento: ");
    background_image_lbl = gtk_label_new("Imagen de fondo: ");
    rating_lbl = gtk_label_new("Calificación: ");
    ratings_count_lbl = gtk_label_new("Cantidad de calificaciones: ");
    added_lbl = gtk_label_new("Cantidad de jugadores: ");
    playtime_lbl = gtk_label_new("Duración (Horas): ");
    reviews_count_lbl = gtk_label_new("Cantidad de reseñas: ");
    platforms_lbl = gtk_label_new("Plataformas: ");
    stores_lbl = gtk_label_new("Tiendas: ");
    developers_lbl = gtk_label_new("Desarrolladores: ");
    genres_lbl = gtk_label_new("Genero: ");
    publishers_lbl = gtk_label_new("Distribuidores: ");
    website_lbl = gtk_label_new("Sitio web: ");
    description_lbl = gtk_label_new("Descripción: ");

    gtk_box_append(GTK_BOX(details_box), name_lbl);
    gtk_box_append(GTK_BOX(details_box), release_date_lbl);
    gtk_box_append(GTK_BOX(details_box), background_image_lbl);
    gtk_box_append(GTK_BOX(details_box), rating_lbl);
    gtk_box_append(GTK_BOX(details_box), ratings_count_lbl);
    gtk_box_append(GTK_BOX(details_box), added_lbl);
    gtk_box_append(GTK_BOX(details_box), playtime_lbl);
    gtk_box_append(GTK_BOX(details_box), reviews_count_lbl);
    gtk_box_append(GTK_BOX(details_box), platforms_lbl);
    gtk_box_append(GTK_BOX(details_box), stores_lbl);
    gtk_box_append(GTK_BOX(details_box), developers_lbl);
    gtk_box_append(GTK_BOX(details_box), genres_lbl);
    gtk_box_append(GTK_BOX(details_box), publishers_lbl);
    gtk_box_append(GTK_BOX(details_box), website_lbl);
    gtk_box_append(GTK_BOX(details_box), description_lbl);

    gtk_widget_set_halign(name_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(name_lbl), 0.0);
    gtk_widget_set_halign(release_date_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(release_date_lbl), 0.0);
    gtk_widget_set_halign(background_image_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(background_image_lbl), 0.0);
    gtk_widget_set_halign(rating_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(rating_lbl), 0.0);
    gtk_widget_set_halign(ratings_count_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(ratings_count_lbl), 0.0);
    gtk_widget_set_halign(added_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(added_lbl), 0.0);
    gtk_widget_set_halign(playtime_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(playtime_lbl), 0.0);
    gtk_widget_set_halign(reviews_count_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(reviews_count_lbl), 0.0);
    gtk_widget_set_halign(platforms_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(platforms_lbl), 0.0);
    gtk_widget_set_halign(stores_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(stores_lbl), 0.0);
    gtk_widget_set_halign(developers_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(developers_lbl), 0.0);
    gtk_widget_set_halign(genres_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(genres_lbl), 0.0);
    gtk_widget_set_halign(publishers_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(publishers_lbl), 0.0);
    gtk_widget_set_halign(website_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(website_lbl), 0.0);
    gtk_widget_set_halign(description_lbl, GTK_ALIGN_START);
    gtk_label_set_xalign(GTK_LABEL(description_lbl), 0.0);
    
    gtk_paned_set_start_child(GTK_PANED(paned), result_list);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(details_scroll), details_box);
    gtk_paned_set_end_child(GTK_PANED(paned), details_scroll);

    gtk_box_append(GTK_BOX(main_box), search_box);
    gtk_box_append(GTK_BOX(main_box), paned);
    gtk_window_present(GTK_WINDOW (window));

}


int main(int argc, char **argv){
    GtkApplication *app;
    int status;

    app = gtk_application_new ("ui.gtk.practica", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref(app); //Liberar app

    return status;
}



