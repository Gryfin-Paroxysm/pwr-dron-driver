#define ROTATE_SPEED 30

/*
 * Najpierw wczytujemy opis sceny, a potem dzialamy
 */

Scene xml/scena.xml
Pause 800 // Czas podany jest w milisekundach

/* 
 * Przykładowy zestaw poleceń
 */

Fly 2 1 30 // Start niezbyt szybki
Fly 0 0 0 // A zatrzymujemy
Rotate ROTATE_SPEED 40
Fly 0 0 0
Rotate 30 60
Fly 0 0 0
Fly 3 0.5 3
Fly 1 -0.7 4
