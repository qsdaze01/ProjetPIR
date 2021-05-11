#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Yin.h"

void init_buffer(float* buffer, int taille){

	for(int i = 0; i < taille; i++){
		buffer[i] = 0.0;
	}
}

void recup_echantillon(float* buffer, int pointeur){

	buffer[pointeur] = 0.0; //Méthode de Luc

}

int test_fin(){
	//Je ne sais pas encore comment faire cette méthode donc là elle sert à rien pour l'instant

	return(0);

}
void moyennage(float* donnees, float* res, int taille, int pointeur){
	float somme = 0;
	for(int i = 0; i < taille; i++){
		somme += donnees[i];
	}

	res[pointeur] = somme/((float)(taille));
}

void app_main(void){
    
	int finished = 0;
	int pointeur = 0;
	int pointeurRes = 0;
	Yin yin;
	float pitch;

	/*			Initialisation des buffers 			*/
	float bufferEntree[265];
	float bufferSortie[265];
	float bufferRes[1000]; //Mettre une autre taille, c'est pas la bonne

	init_buffer(bufferEntree, 265);
	init_buffer(bufferSortie, 265);

	while(finished == 0){

		/*		Récupération des échantillons			*/
		recup_echantillon(bufferEntree, pointeur);
		

		/*					Traitement					*/
		Yin_init(&yin, 265, 0.08); //Je ne comprends pourquoi mais si on prend une confidence en dessous de 0.08 ça ne fonctionne plus
		pitch = Yin_getPitch(&yin, bufferEntree); // Changer le type du buffer d'entrée en float
		//buffer_length++;

		
		/*			Ajout des sorties au buffer 		*/
		bufferSortie[pointeur] = pitch;

		
		/*					Moyennage					*/
		moyennage(bufferSortie, bufferRes, 265, pointeurRes);
		pointeurRes += 1;

		
		/* 			Mise à jour du buffer 				*/
		if(pointeur == 264){
			pointeur = 0;
		}else{
			pointeur += 1;
		}


		/*					Test de fin	 				*/
		finished = test_fin();

	}

}
