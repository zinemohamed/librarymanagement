#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void interfaceDynamique() {
    int i;
    for (i = 0; i <= 8; i++) {
        Sleep(200);
        system("cls");

        textcolor(15);
        gotoxy(10, 1 + i);
        cprintf("  |||||  |||||  ||||| |||||| ||||||  ||||  |||  || |||  ||  ||||  |||||| |||||  |||||");
        gotoxy(10, 2 + i);
        cprintf(" ||      ||    ||       ||     ||   ||  || |||| || |||| || ||  ||   ||   ||  || ||   ");
        gotoxy(10, 3 + i);
        cprintf(" ||  ||| |||||  ||||    ||     ||   ||  || || | || || | || ||||||   ||   |||||  |||||");
        gotoxy(10, 4 + i);
        cprintf(" ||  |   ||        ||   ||     ||   ||  || || |||| || |||| ||  ||   ||   ||  || ||   ");
        gotoxy(10, 5 + i);
        cprintf(" |||||   ||||| |||||    ||   ||||||  ||||  ||  ||| ||  ||| ||  || |||||| ||  || |||||");

        gotoxy(5, 24 - i);
        cprintf("                                                                          \\ ");
        gotoxy(5, 25 - i);
        cprintf("||||   |||||     |||||  |||||| |||||  ||    ||||||  ||||  |||||| ||  || |||||  ||||   ||  || |||||");
        gotoxy(5, 26 - i);
        cprintf("|| ||  ||        ||  ||   ||   ||  || ||      ||   ||  ||   ||   ||  || ||    ||  ||  ||  || ||");
        gotoxy(5, 27 - i);
        cprintf("||  || |||||     |||||    ||   |||||  ||      ||   ||  ||   ||   |||||| ||||| ||  ||  ||  || |||||");
        gotoxy(5, 28 - i);
        cprintf("|| ||  ||        ||  ||   ||   ||  || ||      ||   ||  ||   ||   ||  || ||    || |||  ||  || ||");
        gotoxy(5, 29 - i);
        cprintf("||||   |||||     |||||  |||||| |||||  ||||| ||||||  ||||    ||   ||  || |||||  ||| ||  ||||  |||||");
    }
    textcolor(11);
    //gotoxy(3, 2);cprintf("MIAGE CASA");
    gotoxy(3, 28);cprintf("Annee Academique: 2022/2023");
    gotoxy(55, 2);cprintf("Realiser par: Mohamed Zine");
    //gotoxy(65, 28);cprintf("Encadrer par: MR. EL OUAFI Abderahmane");
}

void barreProg() {
    int i;
    textcolor(11);
    gotoxy(40, 16);
    cprintf("[");
    gotoxy(66, 16);
    cprintf("]");
    for (i = 1; i <= 25; i++) {
        Sleep(200);
        textcolor(14);
        gotoxy(47, 14);
        cprintf("Chargement...");
        gotoxy(40 + i, 16);
        cprintf("|");
        gotoxy(69, 16);
        cprintf("%d %%", i * 4);
    }
}

struct Livre {
    char titre[100];
    char auteur[100];
};

void ajouterLivre() {
    FILE* fichier;
    struct Livre livre;

    clrscr();
    textcolor(14);
    gotoxy(47, 10);cprintf("=== Ajouter un livre ===");

    textcolor(15);
    gotoxy(47, 12);cprintf("Titre du livre : ");
    fflush(stdin);
    fgets(livre.titre, sizeof(livre.titre), stdin);
    livre.titre[strcspn(livre.titre, "\n")] = '\0';

    gotoxy(47, 14);cprintf("Auteur du livre : ");
    fflush(stdin);
    fgets(livre.auteur, sizeof(livre.auteur), stdin);
    livre.auteur[strcspn(livre.auteur, "\n")] = '\0';

    fichier = fopen("biblio.txt", "a");
    if (fichier == NULL) {
        textcolor(4);
        gotoxy(47, 22);cprintf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "%s;%s\n", livre.titre, livre.auteur);
    fclose(fichier);

    textcolor(10);
    gotoxy(47, 20);cprintf("Livre ajouté: %s par %s\n", livre.titre, livre.auteur);

    printf("\nAppuyez sur une touche pour continuer...");
    getch();
}

void supprimerLivre() {
    FILE* fichier;
    FILE* fichierTemp;
    char ligne[200];
    char titre[100];
    int trouve = 0;
    int compteur = 0;

    clrscr();

    textcolor(14);
    gotoxy(47, 10);cprintf("=== Supprimer un livre ===");

    fichier = fopen("biblio.txt", "r");
    if (fichier == NULL) {
        textcolor(4);
        gotoxy(10, 12);
        cprintf("Aucun livre enregistré.\n");
        return;
    }

    // Affichage de la liste des livres à gauche en gris
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* titre = strtok(ligne, ";");
        char* auteur = strtok(NULL, "\n");

        gotoxy(10, 15 + compteur * 4);cprintf("------------");
        gotoxy(10, 14 + compteur * 4);
        textcolor(8);
        cprintf("Livre %d:", compteur + 1);
        gotoxy(10, 15 + compteur * 4);
        cprintf("------------");
        gotoxy(10, 16 + compteur * 4);
        cprintf("Titre: %s", titre);
        gotoxy(10, 17 + compteur * 4);
        cprintf("Auteur: %s", auteur);
        gotoxy(10, 18 + compteur * 4);
        cprintf("------------");

        compteur++;
    }

    fclose(fichier);

    // Affichage de la fonction de suppression à droite en jaune
    textcolor(14);
    gotoxy(50, 10);cprintf("=== Suppression ===");

    textcolor(15);
    gotoxy(47,12);cprintf("Titre du livre a supprimer : ");
    fflush(stdin);
    fgets(titre, sizeof(titre), stdin);
    titre[strcspn(titre, "\n")] = '\0';

    fichier = fopen("biblio.txt", "r");
    if (fichier == NULL) {
        textcolor(4);
        gotoxy(50, 14);cprintf("Aucun livre enregistre.\n");
        return;
    }

    fichierTemp = fopen("biblio_temp.txt", "w");
    if (fichierTemp == NULL) {
        textcolor(4);
        gotoxy(50, 14);cprintf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char* ligneTitre = strtok(ligne, ";");
        char* ligneAuteur = strtok(NULL, "\n");

        if (strcmp(ligneTitre, titre) != 0) {
            fprintf(fichierTemp, "%s;%s\n", ligneTitre, ligneAuteur);
        } else {
            trouve = 1;
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove("biblio.txt");
    rename("biblio_temp.txt", "biblio.txt");

    if (trouve) {
        textcolor(10);
        gotoxy(50, 14);cprintf("Livre supprime avec succès.\n");
    } else {
        textcolor(4);
        gotoxy(50, 14);cprintf("Aucun livre avec ce titre n'a ete trouve.\n");
    }
}

void modifierLivre() {
    FILE* fichier;
    FILE* fichierTemp;
    char ligne[200];
    char titre[100];
    int trouve = 0;
    int compteur = 0;

    clrscr();
    textcolor(14);
    gotoxy(47, 10);
    cprintf("=== Modifier un livre ===");

    fichier = fopen("biblio.txt", "r");
    if (fichier == NULL) {
        textcolor(4);
        gotoxy(47, 14);
        cprintf("Aucun livre enregistré.\n");
        return;
    }

    // Affichage de la liste des livres à gauche en gris
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* titre = strtok(ligne, ";");
        char* auteur = strtok(NULL, "\n");

        textcolor(8);  // Couleur gris
        gotoxy(10, 12 + compteur * 3);
        cprintf("Livre %d:", compteur + 1);
        gotoxy(10, 13 + compteur * 3);
        cprintf("------------");
        gotoxy(10, 14 + compteur * 3);
        cprintf("Titre: %s", titre);
        gotoxy(10, 15 + compteur * 3);
        cprintf("Auteur: %s", auteur);
        gotoxy(10, 16 + compteur * 3);
        cprintf("------------");

        compteur++;
    }

    fclose(fichier);

    // Affichage de la fonction de modification à droite en jaune
    textcolor(14);
    gotoxy(50, 10);
    cprintf("=== Modification ===");

    textcolor(15);
    gotoxy(47, 12);
    cprintf("Titre du livre à modifier : ");
    fflush(stdin);
    fgets(titre, sizeof(titre), stdin);
    titre[strcspn(titre, "\n")] = '\0';

    fichier = fopen("biblio.txt", "r");
    if (fichier == NULL) {
        textcolor(4);
        gotoxy(50, 14);
        cprintf("Aucun livre enregistré.\n");
        return;
    }

    fichierTemp = fopen("biblio_temp.txt", "w");
    if (fichierTemp == NULL) {
        textcolor(4);
        gotoxy(50, 14);
        cprintf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char* ligneTitre = strtok(ligne, ";");
        char* ligneAuteur = strtok(NULL, "\n");

        if (strcmp(ligneTitre, titre) == 0) {
            struct Livre livre;

            clrscr();
            textcolor(14);
            gotoxy(47, 10);
            cprintf("=== Modifier un livre ===");

            textcolor(15);
            gotoxy(47, 12);
            cprintf("Titre du livre : ");
            fflush(stdin);
            fgets(livre.titre, sizeof(livre.titre), stdin);
            livre.titre[strcspn(livre.titre, "\n")] = '\0';

            gotoxy(47, 14);
            cprintf("Auteur du livre : ");
            fflush(stdin);
            fgets(livre.auteur, sizeof(livre.auteur), stdin);
            livre.auteur[strcspn(livre.auteur, "\n")] = '\0';

            fprintf(fichierTemp, "%s;%s\n", livre.titre, livre.auteur);
            trouve = 1;
        } else {
            fprintf(fichierTemp, "%s;%s\n", ligneTitre, ligneAuteur);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove("biblio.txt");
    rename("biblio_temp.txt", "biblio.txt");

    if (trouve) {
        textcolor(10);
        gotoxy(47, 14);
        cprintf("Livre modifié avec succès.\n");
    } else {
        textcolor(4);
        gotoxy(47, 14);
        cprintf("Aucun livre avec ce titre n'a été trouvé.\n");
    }

    printf("\nAppuyez sur une touche pour continuer...");
    getch();
}

void afficherLivres() {
    FILE* fichier;
    char ligne[200];
    int compteur = 0;
    int nombreLivres = 0;
    clrscr();

    textcolor(14);
    gotoxy(47, 10);cprintf("======= Liste des livres =======");

    fichier = fopen("biblio.txt", "r");
    if (fichier == NULL) {
        textcolor(4);gotoxy(47, 12);cprintf("Aucun livre enregistre.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* titre = strtok(ligne, ";");
        char* auteur = strtok(NULL, "\n");

        textcolor(2);
        gotoxy(47, 14 + compteur * 4);cprintf("Livre %d:", compteur + 1);
        textcolor(14);
        gotoxy(47, 15 + compteur * 4);cprintf("------------");
        textcolor(15);
        gotoxy(47, 16 + compteur * 4);cprintf("Titre: %s", titre);
        gotoxy(47, 17 + compteur * 4);cprintf("Auteur: %s", auteur);
        textcolor(14);
        gotoxy(47, 18 + compteur * 4);cprintf("------------");

        compteur++;
        nombreLivres++; // Incrémente le nombre de livres à chaque itération
    }

    fclose(fichier);

    textcolor(8);
    gotoxy(47, 12 );cprintf("Nombre de livres enregistres : %d", nombreLivres);

    // Attente de l'entrée de l'utilisateur jusqu'à ce qu'il appuie sur une touche spécifique
    while (1) {
        if (kbhit()) { // Vérifie si une touche est enfoncée
            char key = getch(); // Récupère la touche enfoncée par l'utilisateur
            if (key == 'q' || key == 'Q') { // Si l'utilisateur appuie sur la touche 'q' ou 'Q'
                clrscr(); // Efface l'écran
                return; // Retourne à l'étape précédente (dans ce cas, la fonction gererBibliotheque())
            }
        }
    }
}

void gererBibliotheque() {
    int choix;

    clrscr();
    textcolor(14);
    gotoxy(47, 10);
    cprintf("======= Menu =======");

    while (1) {
        textcolor(15);
        gotoxy(47, 12);cprintf("1. Ajouter un livre");
        gotoxy(47, 13);cprintf("2. Voir la liste des livres");
        gotoxy(47, 14);cprintf("3. Supprimer un livre");
        gotoxy(47, 15);cprintf("4. Modifier un livre");
        gotoxy(47, 16);cprintf("5. Quitter");
        gotoxy(47, 18);cprintf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                clrscr();
                ajouterLivre();
                break;
            case 2:
                clrscr();
                afficherLivres();
                break;
            case 3:
                supprimerLivre();
                break;
            case 4:
                modifierLivre();
                break;
            case 5:
                textcolor(10);
                gotoxy(47, 21);cprintf("Au revoir !");
                exit(0);
                break;
            default:
                textcolor(4);
                gotoxy(47, 23);cprintf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        clrscr(); // Efface l'écran
        textcolor(14);
        gotoxy(47, 10);
        cprintf("======= Menu =======");
    }
}

void interfaceMenu() {
    int choix;
    clrscr();

    clrscr();
    gotoxy(47, 9);
    cprintf("\n======= Menu =======\n");

    while (1) {
        textcolor(15);
        gotoxy(47, 12);
        cprintf("1. Gerer la bibliotheque\n");
        gotoxy(47, 13);
        cprintf("2. Quitter\n");
        gotoxy(47, 15);
        cprintf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                gererBibliotheque();
                break;
            case 2:
                textcolor(10);
                gotoxy(47, 18);
                cprintf("Au revoir !");
                exit(0);
                break;
            default:
                textcolor(4);
                gotoxy(47, 20);
                cprintf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
    }
}


int main() {
    interfaceDynamique();
    getch();
    clrscr();
    barreProg();
    getch();
    clrscr();
    interfaceMenu();

    return 0;
}
