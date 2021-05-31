# ProjetPIR


**Etapes du projet**
- Faire toutes les installations nécessaires (voir guide d'install docLyrat.txt) [Fait]    
- Récupérer les valeurs des échantillons du micro grâce à la LyraT pour les mettre dans une structure de données appropriée (Liste?) [En cours]    
	-Conversion des fichiers C++ en C [En cours]        
		-ES8388 [Fait]     
		-AudioDSP [En cours, à tester]      
- Appliquer un traitement sur ces échantillons de manière à obtenir les fréquences instantannées [Codé mais pas testé]     
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

