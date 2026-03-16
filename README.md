# Práctica 1 - Comunicación de Procesos
## Integrantes
Juan Thomas Contreras Pinzón \
Luisa María Rosero Espinosa

## Introducción
Este proyecto consiste en un buscador de videojuegos implementado con dos procesos no emparentados: Interfaz gráfica (Cliente) y Buscador por criterios (Servidor). Para la comunicación entre procesos se utilizaron _tuberías con nombre_, ademàs de la _liberìa GTK_ para la GUI y una estructura tipo _HashMap_ para el buscador principal.

## Dataset 
El dataset utilizado fue tomado de: https://huggingface.co/datasets/atalaydenknalbant/rawg-games-dataset 

Cabe aclarar que este dataset originalmente tiene 55 columnas y 890k videojuegos diferentes registrados, sin embargo, para propósitos de este práctica, al encontrar un resultado unicamente mostramos los 15 campos más relevantes descritos a continuación: 

| Campo | Descripción |
|-----  |  ---------- |
| name  | Titulo oficial del juego |
| released | Fecha de lanzamiento del juego, en el formato YYYY-MM-DD |
| background_image | URL de la principal imagen promocional del juego |
| rating  | Puntaje agregado basado en las reseñas de los jugadores |
| ratings_count  | Cantidad de calificaciones recibidas de jugadores |
| added | Cantidad de usuarios de RAWG que han agregado el juego a su biblioteca |
| playtime  | Estimado del promedio de tiempo (en horas) que los jugadores han pasado en el juego |
| reviews_count  | Cantidad de reseñas que tiene el juego |
| platforms  | Conjunto de plataformas que indica en que sistemas el juego está disponible (PC, PlayStation, Xbox, etc) |
| stores  | Conjunto de tiendas donde se puede obtener el juego (Steam, PlayStation store, etc) |
| developers  | Individuos o compañias responsables de la creación del juego |
| genres  | Lista de generos que categorizan al juego (Action, Adventure, RPG, etc) |
| website  | URL del sitio web oficial del juego |
| description  | Narrativa detallada del juego, ofreciendo información sobre el gameplay, trama, mecánicas y contexto general |

## Criterios de Búsqueda
Considerando el dataset utilizado, utilizamos dos criterios de bùsqueda,
### Name
Es claro que en nuestro caso, el nombre es el criterio de búsqueda más utilizado en buscadores reales, pues es único e identificable para cada juego en el dataset. 

### Publisher
Nótese que un juego puede tener varias distribuidoras y una distribuidora ser responsable por varios juegos, sin embargo, tras estudiar el dataset encontramos que un juego generalmente tiene una sola distribuidora, y en caso de tener más, la primera que aparece en el campo es la más reconocida. Teniendo en cuenta lo anterior, decidimos utilizar a la distribuidora principal de un juego como otro criterio de búsqueda relevante.

Nota. Tanto para el criterio de _Name_ como para _Publisher_ aceptamos cadenas con mayúsculas/minúsculas, espacios y caracteres especiales; siempre y cuando consten de 1 a 256 caracteres.

## Ejemplos 
A continuación se presentan algunos ejemplos de uso:

<img width="2008" height="1270" alt="Image" src="https://github.com/user-attachments/assets/549e0b43-16fd-423d-9753-e33ae6942196" />

<img width="2008" height="1270" alt="Image" src="https://github.com/user-attachments/assets/b71fe1dd-df7a-4d60-b101-39c8de16a4dd" />

<img width="2008" height="1270" alt="Image" src="https://github.com/user-attachments/assets/956860dd-61e5-498a-a781-48ecc241360b" />
