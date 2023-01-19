# Option's Pricer
## Fonctionnalités du programme

## Critique des problèmes rencontrés et des solutions adoptées



## Architecture du programme
### Les classes
Nous avons une classe abstraite nommée *option*. Nous avons définis trois paires de classes qui héritent de cette interface *option* :
- **Options européennes** : une classe *european_call* et une classe *european_put*,
- **Options américaines** : une classe *american_call* et une classe *american_put*,
- **Options asiatiques** : une classe *asian_call* et une classe *asian_put*.

Nous avons une classe *asset* pour les actifs financiers et une classe *dividends*. Nous utilisons une composition : une des variables membres de *asset* est de type *dividends*.

### Les fonctions disponibles
