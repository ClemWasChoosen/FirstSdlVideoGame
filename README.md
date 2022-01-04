# Chevalier vs squelettes
Jeu réalisé par Emel Tatoglu et Clément Oberhauser dans le cadre de nos études Licence 2 Informatique 

## Téléchargement et lancement
  !!!!!
  Pour que le jeu puisse se lancer il faut impérativement avoir la bibliothèque SDL sur son pc 
  !!!!!
 
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
  Le but du jeu est de finir toutes les vagues de squelette avec au moins une demie vie. Losrqu'on rencontre un ennemi, une case à coté ou sur l'ennemi, le joueur perd une demie vie.
  
## Comment jouer
  Pour se déplacer : 
    - z : aller vers le haut
    - q : aller à gauche
    - s : aller vers le bas
    - d : aller vers la droite
    
 Pour attaquer : 
    - e : pour attaquer à droite
    - a : pour attaquer à gauche
    

