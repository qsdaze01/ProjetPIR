#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct wavfile //définit la structure de l entete d un wave
{
    char        id[4];          // doit contenir "RIFF"
    int         totallength;        // taille totale du fichier moins 8 bytes
    char        wavefmt[8];     // doit etre "WAVEfmt "
    int         format;             // 16 pour le format PCM
    short       pcm;              // 1 for PCM format
    short       channels;         // nombre de channels
    int         frequency;          // frequence d echantillonage
    int         bytes_per_second;   // nombre de bytes par secondes
    short       bytes_by_capture;
    short       bits_per_sample;  // nombre de bytes par echantillon
    char        data[4];        // doit contenir "data"
    int         bytes_in_data;      // nombre de bytes de la partie data
};

int main(){
	
	int i=0;
    int nbech=0; //nombre d echantillons extraits du fichier audio
    char fichieraudio[100];
    //char fichierdat[100];

    /*---------------------selection du fichier audio-------------------------------*/
    printf ("entrer le nom du fichier audio a extraire en data :\n");
    scanf("%s", fichieraudio);
    printf ("nom du fichier : %s\n", fichieraudio);
    //sprintf (fichierdat,"%s.dat", fichieraudio);
    /*--------------fin de selection du fichier audio-------------------------------*/

    /*---------------------ouverture du wave----------------------------------------*/
    FILE *wav = fopen(fichieraudio,"rb"); //ouverture du fichier wave
    struct wavfile header; //creation du header

    if ( wav == NULL )
    {
        printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
        printf("ne pas oublier l'extention .wav\n");
        exit(1);
    }
    /*---------------------fin de ouverture du wave---------------------------------*/

    /*---------------------lecture de l entete et enregistrement dans header--------*/
    //initialise le header par l'entete du fichier wave
    //verifie que le fichier posséde un entete compatible
    if ( fread(&header,sizeof(header),1,wav) < 1 )
    {
        printf("\nne peut pas lire le header\n");
        exit(1);
    }
    if (    header.id[0] != 'R'|| header.id[1] != 'I'|| header.id[2] != 'F'|| header.id[3] != 'F' )
    {
        printf("\nerreur le fichier n'est pas un format wave valide\n");
        exit(1);
    }
    if (header.channels!=1)
    {
        printf("\nerreur : le fichier n'est pas mono\n");
        exit(1);
    }
    /*----------------fin de lecture de l entete et enregistrement dans header-------*/

    /*-------------------------determiner la taille des tableaux---------------------*/
    nbech=(header.bytes_in_data/header.bytes_by_capture);
    /*------------------fin de determiner la taille des tableaux---------------------*/

    /*---------------------creation des tableaux dynamiques--------------------------*/
    float *data=NULL; //tableau de l'onde temporelle
    data=malloc( (nbech) * sizeof(float));
    if (data == NULL)
    {
        exit(0);
    }

    /*---------------------fin de creation des tableaux dynamiques-------------------*/
    
	/*---------------------initialisation des tableaux dynamiques--------------------*/
    for(i=0; i<nbech; i++)
    {
        data[i]=0;
    }
    /*---------------------fin de initialisation des tableaux dynamiques-------------*/

    /*---------------------remplissage du tableau tab avec les echantillons----------*/
    i=0;
    short value=0;
    FILE *data_Et_Temps=fopen("son_Et_Temps.dat","w"); //fichier data des echantillons
    FILE *dat=fopen("son.dat", "w");
//    FILE *dat2=fopen("fabs_son.dat","w");//fichier.dat des valeurs absolues des echantillons
    //FILE *dat3=fopen(fichierdat,"w");
    while( fread(&value,(header.bits_per_sample)/8,1,wav) )
    {
        //lecture des echantillons et enregistrement dans le tableau
        data[i]=value;
        i++;
    }
    printf("\nnombre d'echantillons lus : %d\n",i);
    for (i=0; i<nbech; i++)
    {
        fprintf(data_Et_Temps,"%lf %lf\n", data[i], (1.*i/header.frequency));
        fprintf(dat,"%lf \n", data[i]);

        //permet de sauvegarder le tableau dans le fichier data.dat pour vérification manuelle des données
        //fprintf(dat2,"%lf %lf\n", fabs(data[i]), (1.*i/header.frequency));
        //fprintf(dat3,"%lf %lf\n", 20*log10(fabs(data[i])), (1.*i/header.frequency));

    }
    /*-----------------fin de remplissage du tableau avec les echantillons-----------*/

     /*---------------------liberation de la memoire----------------------------------*/
    //liberation de la ram des malloc

    free(data);
    data = NULL;
    fclose(wav);
    fclose(data_Et_Temps);
    fclose(dat);
    /*---------------------fin de liberation de la memoire---------------------------*/

	return 0;
}






/* FILE * fichierWav;

	fichierWav = fopen("11_11.wav","r");

	char buffer[10000];

	fgets(buffer, 10000, fichierWav);
	printf("Données : %s \n", buffer);

	fclose(fichierWav);*/