

Pour cette seconde partie du TP, nous avons décider de revoir notre façon de penser pour la réalisation de notre jeu.

Tous d'abord, une liste chaîne généralisé. Pourquoi ce choix ? Comme nous souhaitions avoir plusieurs liste chainée de plusieurs type différents, nous nous sommes dit , d'un accord à un désarcord, qui serait judicieux de généralisé notre liste chainé au lieu d'en définir une pour chaque type.Cette liste chaine est donc DataGame
(Nous avons donc du regénéraliser tous les fonctions de DataGame.)

Nous avons ensuite créer nos premières structure classique : 
Objet : Comme les potions ect...
Entite : tous les personnages du jeux
Equipe : regroupe 6 entite et donne nom equipe
Joueur : les caractéristiques du joueur


Cette liste chaine est la structure Object, elle est composé d'un entier : **nb_element**, d'une chaine de caractères : **nm_object** et d'un "type".


Le "type" que nous avons defini ici permettra de saovir si ol s'agit d'un object, d'une entite ect... grace a l'enumeration TpeElement.Cela nous permet de passer d'une liste chainne général a une liste chainee avec un type precis.Cela est tres utile pour le la comparaison de type lorsqu'il faut trouver un element dans une liste chaine




