# Option's Pricer
## General information
2nd year project at ENSAE Paris. The aim of the project was to exploit the object-oriented programming features of C++. (Classes, Encapsulation, Inheritance and Polymorphism - Pointers and References).

Grade : *comming soon*

Topic : option pricing under the Black-Scholes model. (see more below and in the file *report_FR.pdf*)

Contributors : 
- Justin Ruelland
- Louis Geist

## Features
In the framework of the Black-Scholes model, this project performs : 
- the pricing of :
  - European options on the underlying with or without dividends (using the explicit Black-Scholes formula),
  - American options (by the method of *Longstaff and Schwartz*),
  - Asian options (by the method of *Monte-Carlo*),
- the display of the replication strategy of options (European on underlying with or without dividends - use of the call-put parity)

## Class diagram
![Diagramme de classe UML](https://github.com/louisgeist/Pricer/blob/main/DiagramUML_v3.png)
