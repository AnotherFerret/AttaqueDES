Compilation : 

Commande "make"

Execution : 

Lancer le script avec la commande ./script
Le fichier "chiffres" doit contenir tous les messages fautés en hexadecimal, un par ligne ( les miens y sont par défaut ).
Le script lance par défaut le programme avec argv[2] = "878CF693C87EC079" qui correspond au chiffré sans faute qui m'est associé.
Cet argument ainsi que le fichier "chiffres" doivent être mis à jour pour utiliser le script avec un autre message.
Le script va alors lancer le programme pour chaque ligne du fichier "chiffre" afin de comparer les différences et trouver les clés potentielles.

Sorties : 
Le programme écrira dans le dossier "output" les valeurs de clés possible pour chaque chiffré fauté, par S-box.
( La comparaison pour retrouver la clé de 48 bits se fait manuellement pour le moment, elle sera automatisée si le temps imparti me le permet ) 

Une fois le script terminé, lancer le programme avec la ligne suivante pour obtenir la clé complète sur le terminal : 

./a.out "votre clé de taille 48 bits" "Le message clair en hexadécimal" "Le message chiffré sans faute en hexadécimal"

( Pour mes messages : 

./a.out "010110001001001010001101000110000000010100011000" "DF 51 8C EC BF 61 E3 D9" "87 8C F6 93 C8 7E C0 79"

) 
