# Travail pratique 3: Simulation de la production de centrales hydroélectriques (suite)

Dans ce troisième travail pratique, vous devez poursuivre votre développement
de l'application `simprod`, entamé lors du [deuxième travail
pratique](./sujet-tp2.md).

Le travail doit être réalisé **seul**. Il doit être remis au plus tard le **29
décembre 2023** à **23h59**.  À partir de minuit, une pénalité de **2% par
heure** de retard sera appliquée.

## Objectifs spécifiques

Les principaux objectifs visés sont les suivants :

* Se **familiariser** avec un logiciel développé en C par quelqu'un d'autre
* Apprendre à utiliser des **bibliothèques tierces** à l'intérieur d'un
  programme C, en consultant la documentation disponible
* Organiser le développement des modifications à l'aide de **branches**
* Soumettre les **modifications** en utilisant des **requêtes d'intégration**
  (*merge requests*)
* **Documenter** convenablement des requêtes d'intégration à l'aide du format
  Markdown
* S'assurer que les modifications apportées sont adéquates en proposant ou en
  mettant à jour un **cadre de tests** qui montre que les modifications
  n'entraînent pas de régression

## Description du travail

Rendez-vous sur
[https://gitlab.info.uqam.ca/inf3135-aut2023/inf3135-aut2023-tp3](https://gitlab.info.uqam.ca/inf3135-aut2023/inf3135-aut2023-tp2),
où se trouve le simulateur de production hydroélectrique. Avant-même de créer
une copie (*fork*), prenez le temps de bien vous familiariser avec les
modifications apportées depuis le deuxième travail pratique. Ne négligez pas
cette étape importante.

Votre travail consiste à compléter les tâches ci-bas. Bien que ce ne soit pas
obligatoire, il est recommandé de les implémenter dans l'ordre présenté.

### Tâche 1: (`improve-style`)

Dans l'état actuel, le code peut être amélioré. Il peut y avoir des erreurs
typographiques ou d'orthographe, des *docstrings* manquantes, un style pas
toujours uniforme, des fonctions plus longues que nécessaires ou mal nommées.

Dans cette première tâche, vous devez apporter des modifications aux différents
modules du programme qui permettent globalement d'améliorer le style et la
documentation. Vous devez minimalement couvrir chacun des éléments suivants:

* Compléter de la documentation manquante ou corriger de la documentation
  erronée. Il peut s'agir des *docstrings* ou encore du fichier `README.md`
* Améliorer le style du code dans au moins un module
* Améliorer au moins deux fonctions en les factorisant

Il est important qu'aucune de vos modifications ne modifie le fonctionnement du
programme.

### Tâche 2: (`cli-parsing`)

Le traitement des arguments fournis en ligne de commande à l'application
`simprod` est actuellement géré de façon manuelle, ce qui est pénible et peut
mener à commettre des erreurs. Afin d'améliorer la situation, on vous demande
d'introduire la bibliothèque
[Getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html) ou la
bibliothèque [Argparse](https://github.com/cofyc/argparse) afin d'effectuer le
traitement (les deux bibliothèques sont acceptables, à vous de choisir celle
que vous préférez). En particulier, après les avoir introduites, on s'attend
à ce que toutes les commandes suivantes fonctionnent:

```sh
$ ./simprod scenario examples/scenario.json -t dot
$ ./simprod scenario -t dot examples/scenario.json
$ ./simprod scenario examples/scenario.json -t json
$ ./simprod scenario -t json examples/scenario.json
```

### Tâche 3: (`improve-json-errors`)

Lorsqu'on charge des fichiers JSON représentant un scénario ou un plan, le
programme vérifie si le format est respecté et un message d'erreur est affiché
en conséquence. Or, le message d'erreur ne donne pas toujours un contexte
suffisant pour retracer la source de l'erreur. Aussi, dans certains cas, il est
possible qu'on rencontre des erreurs de segmentation ou des comportement
indéfinis, car on n'a pas suffisamment validé les entrées.

Votre troisième tâche consistera à améliorer la rétroaction fournie en cas
d'erreur, en indiquant la ligne à laquelle se trouve l'erreur, ainsi qu'un
chemin identifiant la partie du document concernée. Vous devrez également vous
assurer qu'aucune erreur de segmentation ne peut survenir, peu importe le
fichier JSON fourni en entrée.

### Dépendance/indépendance entre les tâches

Il est important de bien diviser les branches et les *commits* selon les tâches
auxquelles ils se rapportent. Assurez-vous que la « topologie » de vos
contributions reflète clairement les dépendances ou l'indépendance des
branches.

## Soumettre une contribution

Comme pour le deuxième travail pratique, un objectif de ce travail pratique est
de soumettre vos modifications en utilisant les mécanismes offerts par le
logiciel de contrôle de versions Git et les plateformes de développement
collaboratif telles que GitLab. Plus précisément, vous devrez utiliser une
*requête d'intégration* (en anglais, *merge request*, aussi parfois appelée
*pull request*). Pour cela, vous devrez créer une branche pour chacune des
tâches demandées. Afin de simplifier la correction, il est important de
respecter **exactement** la nomenclature suggérée (`improve-style`,
`cli-parsing`, et `improve-json-errors`).

Dans un premier temps, vous devez répliquer (en anglais *fork*) le programme de
base disponible. Assurez-vous de bien faire une copie **privée** (sinon les
autres étudiantes et étudiants du groupe pourront voir votre solution et vous
serez alors responsable s'il y a plagiat). Ensuite, vous devrez donner accès
à votre projet en mode *Maintainer* aux utilisateurs `blondin_al` et `dogny_g`.

Supposons que vous avez complété la branche `improve-style` sur votre dépôt
local et que vous souhaitez la partager. Alors il vous suffit de pousser la
branche `improve-style` sur votre propre dépôt puis de créer une requête
d'intégration de la branche `improve-style` à la branche `master` (toujours
dans votre dépôt). Il est recommandé de vous inspirer de la requête d'exemple
[du TP2 de l'automne
2017](https://gitlab.com/ablondin/inf3135-aut2017-tp2/merge_requests/1) pour un
exemple de requête bien rédigée.

Notez qu'il est possible en tout de temps de mettre à jour le titre et la
description d'une requête d'intégration. Il est aussi possible de mettre à jour
la branche correspondante. Ainsi, n'hésitez pas à faire des essais et à adapter
le tout au fur et à mesure que vous avancez dans votre projet.

**Attention!** Dans votre travail, il est important de **ne pas** fusionner de
branche lors de la remise de votre travail, car vous devez attendre que vos
modifications soient validées par quelqu'un d'autre, en l'occurrence, votre
enseignant. En pratique, on fait une requête d'intégration d'une branche de
notre dépôt personnel (`origin`) vers le dépôt principal (`upstream`).
Cependant, dans ce contexte académique, la requête doit être faite
à l'intérieur de votre dépôt privé, pour vous assurer que personne d'autre ne
puisse consulter votre code. Ainsi, toutes vos requêtes se feront d'une branche
vers la branche `master` de votre propre dépôt.

## Tests automatiques

Actuellement, on peut invoquer différents tests unitaires et fonctionnels:

```sh
# Tests unitaires
$ make test
$ make test-unit
# Tests de gestion de la mémoire
$ make test-valgrind
# Tests fonctionnaires
$ make test-bats
```

Lorsque vous apporterez des modifications au programme, vous devez vous assurer
que celles-ci ne brisent pas les suites de tests (autrement dit, il s'agit de
**tests de régression** et vous devez en tenir compte dans vos modifications).
Il se peut que vous ayez besoin d'ajuster certains tests dans certains cas, ou
d'en ajouter de nouveaux.

## Contraintes

Afin d'éviter des pénalités, il est important de respecter les contraintes
suivantes:

- Votre projet doit être un clone (*fork*) privé du projet
  <https://gitlab.com/inf3135-aut2023/inf3135-aut2023-tp3>. L'adjectif
  *privé* est très important si vous ne voulez pas que d'autres étudiants
  accèdent à votre solution!
- Vos tâches doivent se trouver sur des branches nommées **exactement**
  `improve-style`, `cli-parsing` et `improve-json-errors`
- **Aucune requête d'intégration** ne doit être faite vers le dépôt public
  (sans quoi les autres étudiants pourront voir vos modifications!)
- **Aucune requête d'intégration** ne doit être fusionnée sur la branche
  `master` (ou tout autre branche), car elle doit d'abord être validée par
  quelqu'un d'autre (l'enseignant ou le correcteur) avant d'être intégrée,
  étape qui sera effectué seulement lors de la correction de votre travail
- **Aucune variable globale** (à l'exception des constantes) n'est permise
- Votre programme doit **compiler** sans **erreur** et sans **avertissement**
  lorsqu'on entre ``make all``.

Advenant le non-respect d'une ou plusieurs de ces contraintes, une pénalité
pouvant aller jusqu'à **50%** de la note totale pourrait être appliquée.

## Remise

Votre travail doit être remis au plus tard le **29 décembre 2023** à **23h59**.
À partir de minuit, une pénalité de **2% par heure** de retard sera appliquée.

La remise se fait **obligatoirement** par l'intermédiaire de la plateforme
[GitLab du département](https://gitlab.info.uqam.ca/). **Aucune remise par
courriel ne sera acceptée** (le travail sera considéré comme non remis).

## Barème

Pour chacune des trois tâches, les critères suivants seront pris en compte
dans l'évaluation:

**Documentation du code source**

* Les *docstrings* respectent le standard Javadoc
* La documentation est bien formatée et bien aérée
* Le format est cohérent avec les autres *docstrings* déjà présentes dans le
  projet
* La *docstring* ne contient pas d'erreurs d'orthographe

**Qualité de la requête d'intégration (*merge request*)**

* Le titre de la requête est significatif
* La description de la modification apportée est claire, concise et précise. En
  particulier, elle respecte le format Markdown et l'exploite à son maximum.
* Le comportement du programme avant modification est décrit
* Le comportement du programme après modification est décrit
* La branche de la requête est basée sur le *commit* le plus récent de la
  branche `master`, ou d'une autre branche si elle en dépend
* La branche ne contient que des *commits* pertinents
* Les *commits* sont atomiques
* Les messages de *commits* sont significatifs et ont un format cohérent avec
  les messages rédigés par les autres développeurs
* La requête ne contient pas d'erreurs d'orthographe et de grammaire

**Qualité du changement de code**

* Le code modifié est lisible, clair et concis
* Le code est bien aéré, de façon cohérente avec le style de programmation déjà
  existant
* Il utilise au maximum les fonctionnalités déjà présentes
* Il est bien factorisé
* La solution n'est pas inutilement complexe

**Fonctionnalité**

* Les modifications apportées répondent à ce qui est demandé
* Les modifications ne brisent pas les tests déjà présents
* S'il y a lieu, des tests sont ajoutés pour illustrer le fait que les
  nouvelles fonctionnalités ont été correctement implémentées
* Dans le cas d'une refactorisation ou d'une amélioration de style, le
  comportement du programme demeure inchangé

La pondération pour chacune des tâches est distribuée comme suit:

| Tâche                          | Documentation | Requête   |   Code    | Fonctionnalité |  Total    |
| ------------------------------ | ------------- | --------- | --------- | -------------- | --------- |
| Tâche 1: `improve-style`       |      5        |     5     |     5     |       5        |    20     |
| Tâche 2: `cli-parsing`         |      5        |     5     |    15     |      15        |    40     |
| Tâche 3: `improve-json-errors` |      5        |     5     |    15     |      15        |    40     |
| **Total**                      |   **15**      |  **15**   |  **35**   |    **35**      | **100**   |
