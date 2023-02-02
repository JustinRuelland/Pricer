# Option's Pricer
Plan :
- I. Introduction
- II. Architecture du programme
- III. Fonctionnalité du programme
- IV. Critique des problèmes rencontrés et des solutions adoptées
- V. Méthodologie de pricing
 
## I. Introduction
### But du programme
Dans le cadre du modèle de Black-Scholes :
- calcul du prix d'options :
  - européennes sur sous-jacent avec ou sans dividendes (utilisation des formules explicites du modèle de *Black-Scholes-Merton*),
  - américaines (par la méthode de *Longstaff & Schwartz*),
  - asiatiques (par méthode de *Monte-Carlo*),
- affichage de la stratégie de réplication d'options (européennes sur sous-jacent avec ou sans dividendes - utilisation de la parité call-put)

Les formules mathématiques utilisées sont explicitées à la fin du README.
### Conventions et hypothèses
Quelques hypothèses importantes optées pour notre programme ;
- *r* : le taux sans risque est constant,
- aucun affichage du programme ne présente une unité pour les prix : le programme donne de bons résultats tant que tous les prix sont utilisés avec la même devise.

## II. Architecture du programme
### Vue d'ensemble de l'architecture: Diagramme de classes UML
Choix de représentation :
- les Getter et Setter pour chaque attribut des classes sont bien définis dans le code, nous ne les écrivons pas dans le diagramme de classe. 
- Pareil pour le constructeur par défaut, par copie et le destructeur

![Diagramme de classe UML](https://github.com/louisgeist/Pricer/blob/main/DiagramUML_v2.png)

Légende du diagramme de classe UML:
- La flèche indique un héritage. La classe mère de l'héritage est pointée par la flèche.
- Les traits avec un losange indiquent :
  - pour un losange noir : une relation de composition (Le losange est du côté de l'objet qui est composé par l'autre objet. Comme c'est une relation de composition, la destruction de l'objet composé détruit l'objet composant.)
  - pour un losange creux : une relation d'agrégation (le losange est du côté de l'objet agrégat. Comme c'est une relation d'agrégation, la destruction de l'objet agrégat ne détruit pas l'objet agrégé.)

### Classe asset
Nous avons une classe **asset** pour les actifs financiers.
Les variables membres de la classe *asset* sont :
- AssetName : un pointeur vers une chaîne de caractères qui désigne le nom de l'actif,
- CurrentTime : la date à laquelle est évaluée l'actif,
- SpotPrice : le prix spot de l'actif,
- Volatility : la volatilité de l'action,
- r : le taux sans risque (c'est un membre statique de la classe, car il doit être le même pour tous les asset),
- Dividends : les dividendes futurs de l'actif, qui est un objet de la classe dividend.

La classe **dividend** est une classe agrégée à la classe *asset*.
Ses variables membres sont :
- Type : un entier dans $\{0,1,2\}$ qui indique le type de dividendes :
  - $0$ : signifie qu'il n'y a pas de dividendes,
  - $1$ : désigne des dividendes à date de paiements discrets,
  - $2$ : désigne des dividendes à paiements continus.
- Rate : le taux des dévidendes
- Periods : la période entre deux paiements (pertinent que pour un dividende de type 1)
- Next : durée jusqu'au prochain paiement (pertinent que pour un dividende de type 1)


### Classe option
La classe *option* est une classe abstraite. Ses attributs sont :
- K : le *strike* de l'option,
- sigma : la *volatilité* du sous-jacent,
- ptr_underlying : pointeur vers un objet de la classe *asset*.

Nous avons défini trois paires de classes qui héritent de cette interface *option* :
- **Options européennes** : 
  - une classe *european_call*, 
  - une classe *european_put*,
- **Options américaines** : 
  - une classe *american_call*,
  - une classe *american_put*,
- **Options asiatiques** : 
  - une classe *asian_call*,
  - une classe *asian_put*.

## III. Fonctionnalités du programme
### Fonctions
Les fonctions suivantes ont été implémentées pour toutes les classes du programme.

#### Constructeurs et destructeurs
Les constructeurs :
- default constructor,
- copy constructor,
- constructor with arguments.

#### Fonctions membres
Les fonctions membres classiques :
- les *Getters*,
- les *Setters*,

#### Fonctions non-membres
Nous avons surchargé les opérateurs de iostream ">>" et "<<" pour les classes *option* et *asset*.

### Fonctions spécifiques aux classes
#### Classe asset
- asset estimation
- asset actulalisation

**JR**

#### Classe option
Les fonctions membres spécifiques sont toutes des fonction purement virtuelles, qui  :
- type() :  qui retourne (en string) le type de l'option (european put, asian call, etc...  : c'est-à-dire le nom de la classe fille)
- price() : qui retourne le prix actuel de l'option ainsi définie.
- replication() : qui affiche comment répliquer l'option (Nous ne savons pas répliquer des options autres qu'européennes, donc nous avons renvoyé un message d'avertissement pour les autres options.)


## IV. Critique des problèmes rencontrés et des solutions adoptées
### Organisation d'un programme de grande ambition
La classe option (et ce qui en hérite), d'un côté, et la classe asset (et la classe dividend ), d'un autre, ont été codé par deux personnes. Nous avions réalisé des rendez-vous réguliers pour se mettre d'accord comment coder et aborder le programme, mais lorsqu'il était venu d'utiliser la classe asset dans la classe option (afin de valoriser des options sur sous-jacents avec dividendes), nous nous sommes rendu compte de petites spécificités à nos deux manières de coder que nous n'avions pas anticipées. 

Forts de cette expérience, nous en concluons que nous devrons pour un prochain projet de programmation, davantage nous mettre d'accord sur les fonctionnalités de chacune des classes, notamment sur les types des arguments et le type renvoyé des fonctions. Une idée aussi serait d'essayer de réaliser un diagramme de classes avant le début du codage en ajoutant les appels de fonctions entre classes.

Par exemple, nous trouvons une limite importante de notre projet dans le manque de dynamisme temporel du pricing d'options. Nous entendons par là que si le prix d'un asset est actualisé à une nouvelle date (avec la fonction assset_actualization(t,S)), la méthode .price() de la classe option va prendre en compte le nouveau prix de l'asset, mais pas du changement de la date actuelle ("Current"). Par exemple, nous considérons une option émise avec une maturité de deux ans. Nous apprenons à bout d'un an que le prix du sous-jacent est $S'$ . Dans notre programme, nous entrons alors le code suivant :
```C++
double new_current_time = 1;

mon_asset.asset_actualization(new_current_time,S');
mon_option.price();
```
On s'attendrait à obtenir la nouvelle valeur de l'option en $t=1ans$ avec pour prix du sous-jacent $S'$ . Cependant, ces deux lignes renvoient le prix de l'option avec prix du sous-jacent $S'$ mais avec une maturité de 2 ans encore.
Pour corriger cela, il faut alors entrer la syntaxe suivante :
```C++
double new_current_time = 1;

mon_asset.asset_actualization(new_current_time,S');
double old_T = mon_option.get_T();
mon_option.set_T(old_T - new_current_time);
mon_option.price();
```
On remarque que cette solution n'est pas robuste à une deuxième actualisation du temps.


### Modification d'un attribut d'une classe attribut
**JR**
Problème :

Solution : création de la fonction membre de asset `get_alias_dividend` un "getter" non standard. Le getter n'est pas de type `const`. Cela permet alors depuis l'asset accéder à dividend.

### Problème du "destructeur timide"
Nous avons fait face à un bug très étrange sur notre programme. L'exécution du programme affichait un "segmentation fault" et nous ne comprenions pas comment une telle erreur avait lieu. Le problème provenait d'un destructeur que nous avons désigné comme "timide", car il n'était pas trouvé par notre compilateur ; le compilateur essayait donc de créer son destructeur, mais comme on manipulait un pointeur dont la mémoire était allouée dynamiquement, cela menait à une erreur.

En effet, nous avons rapidement identifié que le programme essayait de détruire deux fois le même pointeur. En effet, à l'aide de "cout<<"Destruction dans european call"<<endl;" et de "cout<<"avant"<<endl;" et "cout<<"après"<<endl;" dans le destructeur non trivial de asset (cf ligne 98 de asset.cpp) qui supprime la mémoire allouée au pointeur AssetName. La destruction (en fin de programme) d'un objet de la classe european_call appelait le destructeur de european_call dans un premier temps, puis appelait le destructeur de option. Cependant, le programme ne semblait pas trouver le destructeur de european_call que nous avons écrit et définissait donc le sien qui amenait à la double destruction du même pointeur.

Le constructeur non trouvé par notre programme était :
```C++
european_call::~european_call() {};
```
Le debugage consistait simplement à
1. modifier le constructeur de la façon suivante (ajout d'un retour à la ligne): 
```C++
european_call::~european_call() {
};
```
2. make run à nouveau le main ; nous n'avons alors plus le "segmentation fault".
3. Et nous pouvions supprimer le retour à la ligne, pour revenir à :
```C++
european_call::~european_call() {};
```
4. make run à nouveau le main qui n'affiche plus de "segementation fault" (alors qu'à l'oeil nu, le c'est exactement le même destructeur qu'au début...).

NB : puisque le bug avait lieu pour chacune des classes filles (european_call, european_put, asian_call, asian_put...), nous avons pu clairement identifier cette manipulation qui permet de debug (et l'avons même enregistré en vidéo...).

Nous ne savons à l'heure actuelle pas ce que nous devons retenir pour ne pas reproduire le bug (Le bug provenait peut être du compilateur que j'utilise ?). Toutefois, cela m'a appris à identifier efficacement l'origine d'un problème (avec les std::cout) et comprendre l'appel des destructeurs et constructeurs pour des classes héritées. Cette expérience nous a enfin montré que la définition de nos destructeurs non triviaux était un point très important, pour qu'ils ne soient pas implémentés automatiquement par le compilateur.


## V. Méthodologie de pricing
### Notations
On note de manière classique dans le cadre d'un modèle Black-Scholes :
- K : le *strike* de l'option,
- S : le *spot price* du sous-jacent,
- r : le taux sans risque,
- sigma : la volatilité du sous-jacent,
- T : la maturité de l'option.

Pour les options avec dividendes :
- On note le prix d'une option call européenne de maturité $T$ et de strike $K$ sur un sous-jacent de volatilité $\sigma$ et de prix spot $S$ : $c(S,\sigma,T,K)$,
- $\delta$ : le taux de dividendes.
- $n$ : [pour des lump payments] nombre de détachements de dividendes durant la détention de l'option

### Formules utilisées
#### European options
- European sans dividendes
  - call : formule de Black-Scholes : $c=SN(d_{1})-e^{-rT}N(d_{2})$
    - où : $N(.)$ est la fonction de répartition de $\mathcal{N}(0,1)$
  - put : call-put parity : $c-p=S_{T}-e^{-rT}K$

- European continuous dividend :
  - call : $c_{continuous}=c(e^{-\delta T}S_{0},\sigma,T,K)$
  - put : $c_{continuous}-p_{continuous}=e^{-\delta T}S_{0}-e^{-rT}K$
  - Remarque : dans le code, j'ai nommé S_hat $=e^{-\delta T}S_{0}$

- European lump payment dividend : 
  - call : $c_{lump_payments}=c((1-\delta)^{n}S_{0},\sigma,T,K)$
  - put : $c_{lump_payments}-p_{lump_payments}=(1-\delta)^{n}S_{0}-e^{-rT}K$
  - Remarque : dans le code, j'ai nommé S_hat $=e^{-\delta T}S_{0}$


#### Asian options
On note $\bar{S}= \frac{1}{T}\int\limits_{0}^{T}S_{t}dt$
  - call : $V_{T}=(\bar{S}-K)^{+}$
  - put : $V_{T}=(\bar{S}-K)^{-}$


#### American
**JR**
