# Option's Pricer
### But
But du programme : Dans le cadre du modèle de Black-Scholes :
- calcul du prix d'options (européennes, américaines et asiatiques sur sous-jacents sans dividendes ; )
- affichage de la stratégies de réplication (pour des options européennes)

### Hypothèses
Laisser cette partie ?
- *r* : le taux sans risque est constant,
- aucun affichage du programme ne présente une unité pour les prix : le programme donne de bons résultats tant que tous les prix sont utilisés avec la même devise.
## Architecture du programme
### Classe option
Nous avons une classe abstraite nommée *option*. Nous avons définis trois paires de classes qui héritent de cette interface *option* :
- **Options européennes** : 
  - une classe *european_call*, 
  - une classe *european_put*,
- **Options américaines** : 
  - une classe *american_call*,
  - une classe *american_put*,
- **Options asiatiques** : 
  - une classe *asian_call*,
  - une classe *asian_put*.

Nous avons une classe *asset* pour les actifs financiers et une classe *dividends*. Nous utilisons une composition : une des variables membres de *asset* est de type *dividends*.

### Classe asset
***A venir - @JR***

## Fonctionnalités du programme
### Fonctions et variables membres
#### Classe option
##### Variables membres
- K : le *strike* de l'option,
- S : le *spot price* du sous-jacent,
- r : le taux sans risque,
- sigma : la volatilité du sous-jacent,
- T : la maturité de l'option.
- ptr_underlying : pointeur vers un objet de la classe "*asset*"

La variable *r* est un membre *statique* de la classe, car il doit être le même pour toutes les options, car c'est une caractéristique du marché et non de l'option seule.
##### Constructeurs et destructeurs
Les constructeurs :
- default constructor
- copy constructor
- constructor with arguments (K,S,T et sigma)

Le destructeur par défaut n'a pas besoin d'être redéfini, car on n'alloue pas de mémoire avec l'opérator new.

##### Fonctions membres
Les fonctions membres classiques :
- les *Getters* :
  - get_K
  - get_S
  - get_r
  - get_sigma
  - get_T
- les *Setters* :
  - set_K
  - set_S
  - set_r
  - set_sigma
  - set_T

Les fonctions membres spécifiques, qui sont toutes des fonction purement virtuelles, sont :
- type() :  qui retourne (en string) le type de l'option (european put, asian call, etc...  : c'est-à-dire le nom de la classe fille)
- price() : qui retourne le prix actuel de l'option ainsi définie.
- replication() : qui affiche comment répliquer l'option (Nous ne savons pas répliquer des options autres qu'européennes, donc nous avons renvoyé un message d'*erreur*.)

##### Fonctions non-membres
Nous avons surchargé les opérateurs de iostream ">>" et "<<" pour toutes les options.

## Critique des problèmes rencontrés et des solutions adoptées
La classe option (et ce qui en hérite) et la classe asset (et notamment la classe dividendes ) ont été codé par deux personnes différentes. Nous avions réalisé des rendez-vous réguliers pour ce mettre d'accord comment coder et aborder le programme, mais lorsqu'il était venu d'utiliser la classe asset dans la classe option (afin de valoriser des options sur sous-jacents avec dividendes), nous nous sommes rendus comptes de petites spécificités à nos deux manières de coder que nous n'avions pas anticipées. 

Fort de cette expérience, nous en concluoons que nous devrons pour un prochain projet de programmation, davantage nous mettre d'accord sur les fonctionnalités de chacune des classes, notamment sur les types des arguments et le type renvoyé des fonctions.


## Les notations
On note de manière classique dans le cadre d'un modèle Black-Scholes :
- K : le *strike* de l'option,
- S : le *spot price* du sous-jacent,
- r : le taux sans risque,
- sigma : la volatilité du sous-jacent,
- T : la maturité de l'option.
