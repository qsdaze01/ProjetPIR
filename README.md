# ProjetPIR


**Etapes du projet**
- Faire toutes les installations nécessaires (voir guide d'install docLyrat.txt)
- Enregistrer un fichier au format .wav grâce à la LyraT, dans un premier temps un son monophonique
- Récupérer les valeurs des échantillons du wav grâce à la LyraT pour les mettre dans une structure de données appropriée (Liste?)
- Appliquer un traitement sur ces échantillons de manière à obtenir les fréquences instantannées
- Produire un graphique des fréquences instantanées en fonction du temps et l'exporter

**Objectif final :**
Obtenir un graphique des fréquences en fonction du temps

**Objectifs Radar :**
- Retranscrire ce graphe sous la forme d'une partition de musique
- Gérer des fichiers avec des sons polyphoniques

**Contraintes**
- Utiliser la librairie idf et non adf
- Développer pour l'environnement LyraT


**Notes pour Gaspard**  
Pour utiliser la librairie <math.h> en C, il faut dans le Makefile rajouter -lm à la fin des lignes de gcc