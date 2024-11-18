# Simulation de la production de centrales hydroélectriques


### Tâche 1: (`test-utils`)

Dans le dossier `src/utils`, on trouve deux modules implémentant des structures
de données de base: `string_array` et `treemap`. Bien que ces modules semblent
bien fonctionner en apparence, ils ne sont pas accompagnés d'une couverture de
tests suffisante pour qu'on ait pleinement confiance en leur fonctionnement.

Votre première tâche consistera à enrichir le cadre de tests de ces deux
modules à l'aide de la bibliothèque `libtap`. Vos modifications devront être
enregistrés sur une branche nommée `test-utils`, basée sur le *commit* le plus
récent de la branche `master`.

Vous devrez notamment apporter les changements suivants:

* Enrichir le fichier `test_treemap.c` afin d'offrir une meilleure couverture
  de tests du module `treemap`
* Créer un nouveau fichier `test_string_array.c` dans lequel vous placerez des
  tests pour le module `string_array`
* Bien organiser le contenu des fichiers `test_treemap.c` et
  `test_string_array.c` pour en faciliter leur maintenance
* Mettre à jour le fichier `CMakeLists.txt` afin que le nouveau module de test
  puisse être inclus dans les tests, notamment pour l'intégration continue

### Tâche 2: (`memory-leak`)

En l'état actuel, le programme entraîne des fuites de mémoire lorsqu'il est
invoqué dans certaines situations. À l'aide de l'outil
[Valgrind](https://valgrind.org/), identifiez les sources de ces fuites et
apportez les correctifs nécessaires.

Vos modifications devront être sauvegardées sur une branche nommée
`memory-leak`, basée sur le *commit* le plus récent de votre branche
`test-utils`. Vous devez vous assurer qu'il n'y a pas de fuites mémoire
introduites autant dans les modules internes que dans les exécutables de test.

Vous devrez notamment apporter les changements suivants:

* Corriger toutes les fuites mémoire ou les accès mémoires interdits
* Ajouter des cibles personnalisées de la forme `exec_valgrind_test_*` à l'aide
  de la fonction `add_custom_target` dans le fichier `CMakeLists.txt` qui
  permet d'invoquer Valgrind sur chacun des exécutables de test
* Ajouter une cible `test-valgrind` similaire à `test-unit` à l'aide de la
  fonction `add_custom_target` qui permet d'invoquer toutes les cibles de la
  forme `exec_valgrind_test_*`
* Ajouter quelques tests Bats qui invoquent Valgrind sur l'exécutable principal
* Ajuster le fichier `.gitlab-ci.yml` afin d'ajouter une étape `test-valgrind`
  à l'intégration continue

*Suggestions*:

* Commencez par invoquer Valgrind sur les exécutables de test
* Ensuite, invoquez Valgrind sur des exécutions de l'exécutable principal
* Explorez les options de Valgrind (`man valgrind`), notamment `--leak-check`
  et `--error-exitcode`

### Tâche 3: (`dot-output`)

Lorsqu'on construit un scénario, il est difficile de naviguer à travers le
document JSON le représentant. Afin d'améliorer l'expérience d'utilisation,
votre troisième tâche consistera à ajouter une option `-t [json|dot]` à la
sous-commande `simprod scenario` qui permet de choisir le format en sortie, les
deux choix possibles étant `json` (le format par défaut) et `dot` (le format
reconnu par Graphviz).

Plus précisément, vous devriez produire un graphe orienté respectant les
critères suivants:

* Il y a un noeud qui représente la ligne du temps (`timeline`), avec son
  nombre de pas de temps et les durées de ses pas de temps futurs
* Pour chaque lien de transport (`link`), on a un noeud qui représente ce lien,
  avec son identifiant
* Pour chaque centrale (`plant`), on a un noeud qui représente la centrale,
  avec son identifiant et ses puissances minimales/maximales pour chaque pas de
  temps
* Pour chaque zone (`zone`), on a un noeud qui représente la zone, avec son
  identifiant et la demande électrique prévue, pour chaque pas de temps
* Pour chaque centrale (`plant`), il existe un arc (une flèche) de cette
  centrale vers la zone à laquelle elle appartient
* Pour chaque lien de transport (`link`), il existe un arc (une flèche) de sa
  zone source vers le lien, et du lien vers sa zone cible
* Il n'y a pas de lien entre la ligne du temps et les autres composantes du
  scénario

Des exemples de fichiers au format DOT et au format PNG sont disponibles dans
le répertoire [`images`](./images) du présent répertoire. Vous n'êtes pas tenus
de respecter exactement le même style graphique que dans ces exemples, mais on
devrait minimalement respecter les contraintes de style suivantes:

* Les 4 types de noeuds (`link`, `plant`, `timeline`, `zone`) devraient avoir
  une apparence qui permet de les distinguer facilement au niveau visuel
* Les flèches doivent être orientées dans la bonne direction
* Les relations entre centrale et zone doivent être représentées par une flèche
  qui identifie la relation *faire partie de* plutôt qu'une simple flèche

Afin de vous donner confiance que vos modifications ont été bien implémentées,
vous devez également fournir des tests unitaires et des tests fonctionnels
illustrant la nouvelle fonctionnalité.

### Tâche 4: (`improve-json-errors`) **Déplacée au TP3**

**Note**: la tâche 4 a été déplacée dans le 3e travail pratique. Vous n'avez
donc pas à la compléter dans ce 2e travail pratique. La grille de correction
plus bas a été modifiée en conséquence.



## Tests automatiques

Actuellement, on peut invoquer différents tests unitaires et fonctionnels:

```sh
# Tests unitaires
$ make test
$ make test-unit
# Tests fonctionnaires
$ make test-bats
```

Lorsque vous apporterez des modifications au programme, vous devez vous assurer
que celles-ci ne brisent pas les suites de tests (autrement dit, il s'agit de
**tests de régression** et vous devez en tenir compte dans vos modifications).
Il se peut que vous ayez besoin d'ajuster certains tests dans certains cas, ou
d'en ajouter de nouveaux.

