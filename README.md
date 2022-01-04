# Chevalier vs squelettes
&ensp; Jeu réalisé par Emel Tatoglu et Clément Oberhauser dans le cadre de nos études Licence 2 Informatique  
Lien GitHub : (https://github.com/ClemWasChoosen/FirstSdlVideoGame)

## Téléchargement et lancement
  !!!!! Pour que le jeu puisse se lancer il faut impérativement avoir la bibliothèque SDL sur son pc !!!!!
 
 Pour installer le jeu : 
```
 $ git clone https://github.com/ClemWasChoosen/FirstSdlVideoGame.git
 $ cd FirstSdlVideoGame
 $ make
 $ ./main
```

Si le jeu s'arrête et que vous voulez rejouer :

```
 //Ligne suivante inutile si vous êtes déjà dans le dossier
 $ cd FirstSdlVideoGame
 $ make mrproper
 $ make
 $ ./main
 ```

## But du jeu
 &ensp; Le but du jeu est de finir toutes les vagues de squelette avec au moins une demie vie. Losrqu'on rencontre un ennemi, une case à coté ou sur l'ennemi, le joueur perd une demie vie. Le nombre de vague est lié au nombre d'ennemi dans le jeu (augementer d'une vague = +1 ennemi), pour changer le nombre d'ennemi, il faut aller dans le fichier constants.h et changer la valeur de 
 
 ```
 #define NBZOMBIES 2
 ```
  et changer le deux en nombre d'enemie final que l'on veut
  
## Comment jouer
  Pour se déplacer :   
   &ensp; - z : aller vers le haut  
   &ensp; - q : aller à gauche  
   &ensp; - s : aller vers le bas  
   &ensp; - d : aller vers la droite  
    
 Pour attaquer :  
   &ensp; - e : pour attaquer à droite  
   &ensp; - a : pour attaquer à gauche  
   
   Pour quitter le jeu :  
  &ensp; - cliquer sur la croix  
  &ensp; - gagner ou perdre  
  
  Pour mettre le jeu en pause:  
  &ensp; - cliquer sur l'écran (click gauche, pour relancer cliquer)

