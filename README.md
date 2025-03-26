# Drone_1_Axe
                                  Stabilisateur de Drone sur un Axe
1. Description Générale

Le projet consiste à concevoir un système de stabilisation sur un seul axe pour simuler un drone. Celui-ci repose sur une tige, avec deux hélices montées sur un axe pivotant. L'objectif est de contrôler l'orientation de l'axe à l'aide d'un potentiomètre et d'une carte électronique basée sur une STM32 G431. Un écran permettra d'afficher les informations pertinentes en temps réel tel que l’angle d’inclinaison de l’axe, l’énergie utilisée par les moteurs, les vitesses de moteurs, la vitesse de rotation de l’axe etc…

2. Interface Utilisateur

L’utilisateur voit :

•	Un dispositif physique composé d'une base fixe assez lourd pour supporter une tige verticale.
•	Un axe pivotant monté sur cette tige, avec deux hélices placées aux extrémités.
•	Ces deux hélices tourneront dans le sens inverse afin d’annuler toute possibilité de rotation dans un autre axe.
•	Un potentiomètre permettant d'interagir avec le système, envoyant les informations à la carte stm32.
•	Un écran affichant des informations telles que l'angle d'inclinaison, la vitesse des hélices, l'état du système (stabilisation active ou non), et d'éventuelles alertes.

Ce que peut faire l'utilisateur

•	Modifier l'angle de l'axe : L’utilisateur peut appuyer sur l’axe pivotant afin de le déstabiliser et regarder la stabilisation instantanée de cet axe.
•	Activer/désactiver le mode de stabilisation : L'utilisateur peut choisir de laisser le système compenser automatiquement l'inclinaison ou tester une configuration manuelle.
•	Observer les données en temps réel : L'écran affiche les informations cruciales, permettant à l'utilisateur d'analyser le comportement du système.

Effets des actions de l'utilisateur

•	Un changement du potentiomètre entraîne une modification des commandes envoyées aux moteurs des hélices.
•	Lorsque la stabilisation est activée, le système ajuste automatiquement la puissance des hélices pour maintenir l'axe en équilibre.
•	Une mauvaise manipulation ou une panne peut provoquer des oscillations ou une instabilité du système, ce qui sera indiqué sur l'écran.

4. Objectifs du Projet

Objectif Final
Concevoir un système capable de stabiliser l'axe sur un seul degré de liberté (à l'horizontale) en régulant la vitesse des hélices grâce à un contrôleur embarqué.

Étapes de Développement

1.	Choix des composants nécessaires
	Sélection des moteurs, hélices, capteurs et autres composants électroniques.

2.	Soudure du PCB
a.	Montage et soudure des composants essentiels (alimentation, écran, microcontrôleur).
b.	Préparation des connexions pour le potentiomètre et les moteurs.

3.	Conception Mécanique
a.	Choisir une structure stable et adaptée au projet, base assez lourde et axe léger.
b.	Intégrer les hélices et assurer un montage permettant un mouvement fluide et sans secousse.

4.	Code sur STM32
a.	Programmer la STM32 pour réguler la vitesse des hélices en fonction de l'angle de l'axe.
b.	Implémenter un algorithme de stabilisation (PID ou autre méthode adaptée).

5.	Tests et Ajustements
a.	Tester la réponse du système à différentes perturbations.
b.	Optimiser les paramètres pour assurer une réaction rapide et efficace.

6.	Finalisation et Démonstration
a.	Rendre le système fonctionnel et prêt à être présenté.
b.	Documenter le fonctionnement et les performances du stabilisateur.

Conclusion
Ce projet vise à démontrer la faisabilité d'un système de stabilisation sur un axe à l'aide d'un microcontrôleur et d'un retour utilisateur simple. Il peut être étendu à des applications plus complexes, comme la stabilisation d'un drone complet ou d'autres dispositifs de contrôle d'attitude.
