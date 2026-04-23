#include <stdio.h>
#include <string.h>

// ================= VARIABLES GLOBALES =================
int T_NLivre[100] = {101, 102, 103, 104, 105};
int T_Nbr_exp[100] = {7, 5, 3, 10, 4};
char T_Titre[100][100] = {
    "Le_Petit_Prince",
    "1984_Orwell",
    "Les_Miserables",
    "Harry_Potter_1",
    "L_etranger_Camus"
};
int nb = 5;

// Matrice emprunts (0:CIN, 1:Livre, 2-4:DateEmp, 5-7:DateRet, 8:Etat)
int m[100][9];
int nbe = 0;

// ================= OUTILS DE CONTROLE DE SAISIE =================

// Fonction pour vider la mémoire tampon (évite les bugs si on tape des lettres)
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Outil 1 : Force la saisie d'un entier entre min et max
int saisir_entier(int min, int max, char* message) {
    int val;
    int retour;
    do {
        printf("%s", message);
        retour = scanf("%d", &val);
        vider_buffer(); // Nettoie après la saisie

        if (retour != 1 || val < min || val > max) {
            printf("ERREUR : Veuillez entrer un nombre entre %d et %d.\n", min, max);
        }
    } while (retour != 1 || val < min || val > max);
    return val;
}

// Outil 2 : Force la saisie d'un entier positif simple (pour CIN, ID...)
int saisir_positif(char* message) {
    int val;
    int retour;
    do {
        printf("%s", message);
        retour = scanf("%d", &val);
        vider_buffer();
        if (retour != 1 || val < 0) {
            printf("ERREUR : Veuillez entrer un nombre positif.\n");
        }
    } while (retour != 1 || val < 0);
    return val;
}

// Outil 3 : Saisie sécurisée d'une date
void saisir_date(int *j, int *m, int *a, char* message) {
    printf("%s\n", message);
    *a = saisir_entier(2020, 2030, " - Annee (2020-2030) : ");
    *m = saisir_entier(1, 12,      " - Mois (1-12) : ");

    // Petit calcul simple pour les jours (30 ou 31)
    int max_j = 31;
    if (*m == 4 || *m == 6 || *m == 9 || *m == 11) max_j = 30;
    if (*m == 2) max_j = 29; // On simplifie Février à 29 max

    *j = saisir_entier(1, max_j,   " - Jour : ");
}

// Prototypes
void gst_bib();
void gst_emp();
void stat();
int comparer_dates(int j1, int m1, int a1, int j2, int m2, int a2);

// ================= MAIN =================
int main() {
    int choix;
    do {
        printf("\n=============================================================\n");
        printf("||      MENU PRINCIPAL - CONTROLE TOTAL ACTIVE              ||\n");
        printf("=============================================================\n");
        printf("1. GESTION DE LA BIBLIOTHEQUE\n");
        printf("2. GESTION DES EMPRUNTS\n");
        printf("3. STATISTIQUES\n");
        printf("4. QUITTER L'APPLICATION\n");
        printf("-------------------------------------------------------------\n");

        // Utilisation de notre super fonction de saisie
        choix = saisir_entier(1, 4, "Votre choix (1-4) : ");

        switch (choix) {
            case 1: gst_bib(); break;
            case 2: gst_emp(); break;
            case 3: stat(); break;
            case 4: printf("Au revoir !\n"); break;
        }
    } while (choix != 4);
    return 0;
}

// ================= PARTIE 1 : GESTION BIBLIOTHEQUE =================
void gst_bib() {
    int choix, i, num, nbeX, trouve;
    char titre[100];

    do {
        printf("\n=== GESTION DE LA BIBLIOTHEQUE ===\n");
        printf("1. AFFICHER TOUS LES LIVRES\n");
        printf("2. AJOUTER UN LIVRE\n");
        printf("3. SUPPRIMER UN LIVRE\n");
        printf("4. MODIFIER LE STOCK\n");
        printf("5. RECHERCHER UN LIVRE\n");
        printf("6. AFFICHER DISPONIBLES\n");
        printf("7. RETOUR MENU PRINCIPAL\n");

        choix = saisir_entier(1, 7, "Choix : ");

        switch(choix) {
            case 1:
                printf("\n--- LISTE DES LIVRES ---\n");
                for(i=0; i<nb; i++) printf("No: %d | Titre: %s | Stock: %d\n", T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
                break;

            case 2:
                num = saisir_positif("Numero du nouveau livre : ");

                // Vérifier si l'ID existe déjà (Contrôle supplémentaire)
                int existe = 0;
                for(i=0; i<nb; i++) if(T_NLivre[i] == num) existe = 1;

                if(existe) {
                    printf("ERREUR : Ce numero de livre existe deja !\n");
                } else {
                    printf("Titre du livre (sans espaces) : ");
                    scanf("%s", titre); vider_buffer();
                    nbeX = saisir_positif("Nombre d'exemplaires : ");

                    T_NLivre[nb] = num;
                    strcpy(T_Titre[nb], titre);
                    T_Nbr_exp[nb] = nbeX;
                    nb++;
                    printf("succes !\n");
                }
                break;

            case 3:
                num = saisir_positif("Numero du livre a supprimer : ");
                trouve = -1;
                for(i=0; i<nb; i++) if(T_NLivre[i] == num) trouve = i;

                if(trouve != -1) {
                    int emprunte = 0;
                    for(i=0; i<nbe; i++) if(m[i][1] == num && m[i][8] == 0) emprunte = 1;

                    if(emprunte) printf("Impossible: Livre en cours d'emprunt.\n");
                    else {
                        for(i=trouve; i<nb-1; i++) {
                            T_NLivre[i] = T_NLivre[i+1];
                            T_Nbr_exp[i] = T_Nbr_exp[i+1];
                            strcpy(T_Titre[i], T_Titre[i+1]);
                        }
                        nb--;
                        printf("Livre supprime.\n");
                    }
                } else printf("Livre introuvable.\n");
                break;

            case 4:
                num = saisir_positif("Numero du livre a modifier : ");
                trouve = 0;
                for(i=0; i<nb; i++) {
                    if(T_NLivre[i] == num) {
                        T_Nbr_exp[i] = saisir_positif("Nouveau stock : ");
                        printf("Stock modifie.\n");
                        trouve = 1;
                    }
                }
                if(!trouve) printf("Livre introuvable.\n");
                break;

            case 5:
                printf("Titre a chercher : "); scanf("%s", titre); vider_buffer();
                for(i=0; i<nb; i++) {
                    if(strstr(T_Titre[i], titre) != NULL)
                        printf("Trouve: %d | %s | Stock: %d\n", T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
                }
                break;

            case 6:
                for(i=0; i<nb; i++) if(T_Nbr_exp[i] > 0) printf("%s (Stock: %d)\n", T_Titre[i], T_Nbr_exp[i]);
                break;
        }
    } while(choix != 7);
}

// ================= PARTIE 2 : GESTION EMPRUNTS =================
void gst_emp() {
    int choix, i, j, cin, numLivre;
    int jc, mc, ac;
    int jd, md, ad, jf, mf, af;

    do {
        printf("\n=== GESTION DES EMPRUNTS ===\n");
        printf("1. AJOUTER UN EMPRUNT\n");
        printf("2. CONSULTER PAR ADHERENT\n");
        printf("3. RETOUR D'UN LIVRE\n");
        printf("4. LISTE EMPRUNTS EN COURS\n");
        printf("5. VERIFIER LES RETARDS\n");
        printf("6. CHERCHER PAR DATE RETOUR\n");
        printf("7. SUPPRIMER PAR PERIODE\n");
        printf("8. RETOUR MENU PRINCIPAL\n");

        choix = saisir_entier(1, 8, "Choix : ");

        switch(choix) {
            case 1:
                cin = saisir_positif("CIN Adherent : ");
                int compte = 0;
                for(i=0; i<nbe; i++) if(m[i][0] == cin && m[i][8] == 0) compte++;
                if(compte >= 7) { printf("Erreur: Max 7 livres atteints.\n"); break; }

                numLivre = saisir_positif("Numero Livre : ");
                int idx = -1;
                for(i=0; i<nb; i++) if(T_NLivre[i] == numLivre) idx = i;

                if(idx != -1 && T_Nbr_exp[idx] > 0) {
                    m[nbe][0] = cin;
                    m[nbe][1] = numLivre;

                    saisir_date(&m[nbe][2], &m[nbe][3], &m[nbe][4], "--- DATE EMPRUNT ---");
                    saisir_date(&m[nbe][5], &m[nbe][6], &m[nbe][7], "--- DATE RETOUR PREVUE ---");

                    // Controle: Date retour doit etre >= Date emprunt
                    if(comparer_dates(m[nbe][5], m[nbe][6], m[nbe][7], m[nbe][2], m[nbe][3], m[nbe][4]) == -1) {
                         printf("ERREUR: La date retour est avant la date d'emprunt !\n");
                    } else {
                        m[nbe][8] = 0;
                        T_Nbr_exp[idx]--;
                        nbe++;
                        printf("Emprunt valide.\n");
                    }
                } else {
                    printf("Livre non disponible ou inexistant.\n");
                }
                break;

            case 2:
                cin = saisir_positif("CIN Adherent : ");
                for(i=0; i<nbe; i++) {
                    if(m[i][0] == cin) {
                        printf("- Livre %d | %s\n", m[i][1], m[i][8]==0 ? "En cours" : "Rendu");
                    }
                }
                break;

            case 3:
                cin = saisir_positif("CIN : ");
                numLivre = saisir_positif("Livre : ");
                int found = 0;
                for(i=0; i<nbe; i++) {
                    if(m[i][0] == cin && m[i][1] == numLivre && m[i][8] == 0) {
                        m[i][8] = 1;
                        for(j=0; j<nb; j++) if(T_NLivre[j] == numLivre) T_Nbr_exp[j]++;
                        printf("Retour enregistre.\n");
                        found = 1;
                        break;
                    }
                }
                if(!found) printf("Aucun emprunt actif trouve.\n");
                break;

            case 4:
                printf("\n--- EMPRUNTS EN COURS ---\n");
                for(i=0; i<nbe; i++) {
                    if(m[i][8] == 0)
                        printf("CIN %d | Livre %d | Retour: %d/%d/%d\n", m[i][0], m[i][1], m[i][5], m[i][6], m[i][7]);
                }
                break;

            case 5:
                saisir_date(&jc, &mc, &ac, "Entrez la date d'aujourd'hui :");
                for(i=0; i<nbe; i++) {
                    if(m[i][8] == 0) {
                        if(comparer_dates(m[i][5], m[i][6], m[i][7], jc, mc, ac) == -1) {
                             printf("RETARD: CIN %d | Livre %d\n", m[i][0], m[i][1]);
                        }
                    }
                }
                break;

            case 6:
                saisir_date(&jd, &md, &ad, "Date de retour cherchee :");
                for(i=0; i<nbe; i++) {
                    if(m[i][5] == jd && m[i][6] == md && m[i][7] == ad)
                        printf("Emprunt CIN %d | Livre %d\n", m[i][0], m[i][1]);
                }
                break;

            case 7:
                saisir_date(&jd, &md, &ad, "Date debut :");
                saisir_date(&jf, &mf, &af, "Date fin :");
                int initial = nbe;
                for(i=0; i<nbe; ) {
                    if(comparer_dates(m[i][2], m[i][3], m[i][4], jd, md, ad) >= 0 &&
                       comparer_dates(m[i][2], m[i][3], m[i][4], jf, mf, af) <= 0) {
                        for(j=i; j<nbe-1; j++) for(int k=0; k<9; k++) m[j][k] = m[j+1][k];
                        nbe--;
                    } else i++;
                }
                printf("%d suppressions.\n", initial - nbe);
                break;
        }
    } while(choix != 8);
}

// ================= PARTIE 3 : STATISTIQUES =================
void stat() {
    int choix, i, j;
    int j1, m1, a1, j2, m2, a2;

    do {
        printf("\n=== STATISTIQUES ===\n");
        printf("1. TOTAUX\n");
        printf("2. TOP LIVRE GLOBAL\n");
        printf("3. JAMIS EMPRUNTES\n");
        printf("4. TOP LIVRE PERIODIQUE\n");
        printf("5. TOP EMPRUNTEUR\n");
        printf("6. RETOUR\n");

        choix = saisir_entier(1, 6, "Choix : ");

        switch(choix) {
            case 1:
                { // Accolades necessaires pour declarer variables dans un case
                    int nbAdh = 0;
                    int tabCin[100];
                    for(i=0; i<nbe; i++) {
                        int vu = 0;
                        for(j=0; j<nbAdh; j++) if(tabCin[j] == m[i][0]) vu = 1;
                        if(!vu) { tabCin[nbAdh] = m[i][0]; nbAdh++; }
                    }
                    printf("Total Livres: %d | Adherents: %d | Emprunts: %d\n", nb, nbAdh, nbe);
                }
                break;

            case 2:
                {
                    int maxF = -1, idMax = -1;
                    for(i=0; i<nb; i++) {
                        int count = 0;
                        for(j=0; j<nbe; j++) if(m[j][1] == T_NLivre[i]) count++;
                        if(count > maxF) { maxF = count; idMax = i; }
                    }
                    if(maxF > 0) printf("Top Livre: %s (%d fois)\n", T_Titre[idMax], maxF);
                    else printf("Aucune donnee.\n");
                }
                break;

            case 3:
                printf("Jamais empruntes :\n");
                for(i=0; i<nb; i++) {
                    int vu = 0;
                    for(j=0; j<nbe; j++) if(m[j][1] == T_NLivre[i]) vu = 1;
                    if(!vu) printf("- %s\n", T_Titre[i]);
                }
                break;

            case 4:
                saisir_date(&j1, &m1, &a1, "Debut :");
                saisir_date(&j2, &m2, &a2, "Fin :");
                {
                    int maxF = -1, idMax = -1;
                    for(i=0; i<nb; i++) {
                        int count = 0;
                        for(j=0; j<nbe; j++) {
                            if(m[j][1] == T_NLivre[i] &&
                               comparer_dates(m[j][2], m[j][3], m[j][4], j1, m1, a1) >= 0 &&
                               comparer_dates(m[j][2], m[j][3], m[j][4], j2, m2, a2) <= 0) {
                                count++;
                            }
                        }
                        if(count > maxF) { maxF = count; idMax = i; }
                    }
                    if(maxF > 0) printf("Top Livre periode: %s (%d fois)\n", T_Titre[idMax], maxF);
                }
                break;

            case 5:
                {
                    int maxEmp = -1, cinMax = -1;
                    for(i=0; i<nbe; i++) {
                        int cinActuel = m[i][0];
                        int count = 0;
                        for(j=0; j<nbe; j++) if(m[j][0] == cinActuel) count++;
                        if(count > maxEmp) { maxEmp = count; cinMax = cinActuel; }
                    }
                    if(cinMax != -1) printf("Top Adherent: CIN %d (%d emprunts)\n", cinMax, maxEmp);
                }
                break;
        }
    } while(choix != 6);
}

int comparer_dates(int j1, int m1, int a1, int j2, int m2, int a2) {
    if (a1 < a2) return -1;
    if (a1 > a2) return 1;
    if (m1 < m2) return -1;
    if (m1 > m2) return 1;
    if (j1 < j2) return -1;
    if (j1 > j2) return 1;
    return 0;
}
