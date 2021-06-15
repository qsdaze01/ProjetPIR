# Lien installation #   

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/#step-4-set-up-the-environment-variables

# Conseils #      

- Suivre l'installation normalement jusqu'à step 6     

- Suivre le deuxième tuto sur le lien : https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html#example-output     

- Bien faire l'élévation de privilège : sudo usermod -a -G dialout $USER (ATTENTION : elle n'est effective qu'après un redémarrage de la session du PC)     

- Suivre step 7 normalement     

- Dans le menuconfig il faut bien vérifier le nombre de bauds que l'on veut utiliser (utile pour la suite)    

- Pour la step 8, avant de faire le flash il faut garder appuyé le bouton boot puis appuyer sur reset puis relacher reset puis relacher boot (voilà donc juste trouver ce truc ça m'a pris 1h30 mdrr)     

- Suivre step 10 normalement     

- Pour lancer le programme il est nécessaire d'appuyer sur 'reset'    

- Pour l'arrêter il faut faire 'ctrl' + 'alt GR' + ')'      


# A chaque redémarrage, faire les commandes #    

- alias get_idf='. $HOME/esp/esp-idf/export.sh'       
  
- get_idf       

- idf.py set-target esp32     


# Pour chaque upload #     

- idf.py -p /dev/ttyUSB0 flash   

- Garder appuyé le bouton boot puis appuyer sur reset puis relacher reset puis relacher boot     

- idf.py -p /dev/ttyUSB0 monitor     


## Autres infos utiles ##       
 
- Le port à mettre est /dev/ttyUSB0      
