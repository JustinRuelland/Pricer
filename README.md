# Option's Pricer
## Fonctionnalités du programme

## Critique des problèmes rencontrés et des solutions adoptées



## Architecture du programme
### Les classes
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

### Les fonctions disponibles
#### classe option
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

## Les notations
On note de manière classique dans le cadre d'un modèle Black-Scholes :
- K : le *strike* de l'option,
- S : le *spot price* du sous-jacent,
- r : le taux sans risque,
- sigma ($\sigma$) : la volatilité du sous-jacent,
- T : la maturité de l'option.
