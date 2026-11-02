
Pour cette seconde partie du TP, nous avons décidé de revoir notre façon de penser pour la réalisation de notre jeu.

1. Une liste chaînée généralisée (DataGame)
Tout d'abord, nous avons fait le choix d'une liste chaînée généralisée. Pourquoi ce choix ? Comme nous souhaitions manipuler différents types d'éléments, nous nous sommes dit, d'un commun accord, qu'il serait plus judicieux de généraliser notre liste chaînée au lieu d'en réécrire une pour chaque type. Cette structure générique est donc DataGame.(Nous avons par conséquent dû régénéraliser toutes les fonctions liées à DataGame.)

2. Nos structures de données classiques
Nous avons ensuite créé nos premières structures de base :

Object : pour gérer les objets (comme les potions, etc.).

Entité : pour tous les personnages du jeu.

Equipe : pour regrouper jusqu'à 6 entités et stocker le nom de l'équipe.

Joueur : pour stocker les caractéristiques du joueur.

3. Le rôle de la structure Object et du type
La structure Object est composée d'un entier nb_element, d'une chaîne de caractères nm_object et d'un champ de type. Le type que nous avons défini ici permet de savoir s'il s'agit d'un objet, d'une entité, etc., grâce à l'énumération TypeElement.

Cela nous permet de passer d'une liste chaînée générique (void \*) à une manipulation typée avec précision. C'est particulièrement utile pour la comparaison de types lorsqu'il s'agit de rechercher ou d'identifier un élément spécifique au sein de la liste.