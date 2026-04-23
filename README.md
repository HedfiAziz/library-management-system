# 📚 Système de Gestion de Bibliothèque en C

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c)
![Platform](https://img.shields.io/badge/Platform-Console-4D4D4D?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-2ea44f?style=for-the-badge)

Une application console robuste et complète pour gérer une bibliothèque, ses livres, ses adhérents et ses emprunts. Ce projet met en avant des algorithmes de tri, la manipulation de matrices et une **gestion ultra-sécurisée des saisies utilisateur**.

---

## ✨ Fonctionnalités Principales

Ce projet est divisé en trois modules puissants, accessibles via un menu interactif :

### 📖 1. Gestion de la Bibliothèque
* **Inventaire complet :** Ajout, suppression et modification du stock de livres.
* **Moteur de recherche :** Retrouvez instantanément un livre par son titre.
* **Filtrage intelligent :** Affichage exclusif des livres actuellement disponibles en rayon.
* *Inclus par défaut : des classiques comme "Le Petit Prince", "1984", ou "Les Misérables".*

### 🤝 2. Gestion des Emprunts
* **Système de prêt sécurisé :** Limite de 7 livres maximum par adhérent.
* **Traçabilité des dates :** Enregistrement des dates d'emprunt et de retour prévue.
* **Détection des retards :** Algorithme de comparaison de dates pour cibler les emprunts non rendus à temps.
* **Historique :** Consultation des emprunts actifs par CIN ou recherche par date de retour.

### 📊 3. Statistiques Avancées
* **Top Livres :** Détection du livre le plus emprunté (globalement ou sur une période donnée).
* **Top Adhérents :** Identification du lecteur le plus actif.
* **Audit d'inventaire :** Liste des livres "oubliés" qui n'ont jamais été empruntés.
* **Vue globale :** Résumé du nombre total de livres, d'adhérents uniques et de transactions.

---

## 🛡️ Points Forts Techniques (Sous le capot)

Ce projet n'est pas qu'un simple CRUD, il intègre des mécaniques de programmation avancées :

* **Anti-Crash (Contrôle de Saisie) :** Utilisation de fonctions personnalisées (`vider_buffer`, `saisir_entier`) garantissant que si l'utilisateur tape des lettres au lieu de chiffres, le programme ne plante jamais.
* **Gestion des Matrices :** Utilisation d'une matrice 2D complexe `m[100][9]` pour stocker toutes les métadonnées des emprunts (CIN, ID Livre, Dates, État).
* **Vérification Logique :** Impossible d'emprunter un livre en rupture de stock, et impossible de saisir une date de retour antérieure à la date d'emprunt.

---

## 🚀 Comment lancer le projet ?

### Prérequis
Vous avez besoin d'un compilateur C (comme `gcc`) installé sur votre machine.

### Compilation et Exécution
Ouvrez votre terminal et tapez les commandes suivantes :

```bash
# 1. Cloner le dépôt
git clone [https://github.com/HedfiAziz/library-management-system.git](https://github.com/HedfiAziz/library-management-system.git)

# 2. Se rendre dans le dossier
cd library-management-system

# 3. Compiler le code source
gcc "Gestion d une bibliotheque.c" -o library_app

# 4. Lancer l'application
./library_app


👨‍💻 Développé par
Hedfi Ahmed Aziz * GitHub: @HedfiAziz
