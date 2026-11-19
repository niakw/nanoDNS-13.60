# Plan de validation — firmware 13.60

**Langues :** [English (default)](TEST_PLAN.md) | Français

**Statut : Release GitHub standard ; premier test utilisateur positif sur firmware 13.60, autres vérifications en attente.** Un build seul ne prouve ni une extinction correcte, ni un réveil à la manette, ni une reprise de veille fiable.

## Compte rendu de test sur console — 19 novembre 2026

**Firmware 13.60 : test utilisateur réussi pour le fonctionnement de base.** Le testeur a installé notre bêta et indique que le précédent problème d'extinction et de rallumage **ne s'est pas reproduit** lors de l'essai réalisé.

Deux générations de journaux transmises (`nanodns.log` et `nanodns.log.previous`) confirment :

- Version `NanoDNS v0.4-13.60.1`, 124 règles chargées, aucune exception et les deux adresses Quad9.
- Écoute IPv4 sur `127.0.0.1:53` et IPv6 sur `[::1]:53`.
- **23 requêtes A** au total, toutes bloquées localement avec `0.0.0.0` par `mandatory-console-blocklist`. Aucune requête amont n'est visible dans ces fichiers.
- Aucune trace finale `shutdown: complete`. L'extinction et le rallumage corrects sont **rapportés par le testeur**, non prouvés par ce marqueur de journal.

| Console / firmware | Vérification |
| --- | --- |
| Génération actuelle, firmware 13.60 | **TEST UTILISATEUR RÉUSSI : démarrage, filtrage DNS A, essai d'extinction/rallumage** |
| Génération actuelle, tous les autres firmwares | **NON VALIDÉ PAR TEST UTILISATEUR** |
| Binaire de génération précédente, tous firmwares | **NON VALIDÉ PAR TEST UTILISATEUR** |

**Vérifications encore nécessaires sur 13.60 :** résolution d'un nom autorisé via Quad9, AAAA, DNS alternatifs, veille/reprise, cycles répétés d'arrêt/rallumage et stabilité prolongée. Une CI verte n'est jamais une validation matérielle. Un essai d'arrêt réussi n'établit pas définitivement la cause racine du problème initial.



## 1. Vérifications automatiques

- `python3 -m unittest discover -s tests -v` : cohérence des 124 règles obligatoires, absence d'exceptions par défaut, correspondance entre INI et code, adresses Quad9 et tests natifs.
- Compiler l'ELF avec le SDK compatible, vérifier sa présence et sa taille, puis vérifier aussi la compilation secondaire.
- Contrôler le commit `main` actuel, pas uniquement un ancien build vert.

## 2. Préparation réseau

Sauvegarder l'ELF d'origine, `/data/nanodns/nanodns.ini`, les journaux et les sauvegardes utiles. Bloquer le WAN au niveau du routeur/pare-feu en IPv4 et IPv6 tout en conservant le LAN/FTP et un chargeur local.

Vérifier qu'un seul mécanisme d'autoload est actif et qu'une seule instance nanoDNS est chargée. Transférer explicitement les 124 règles : le payload n'écrase pas les INI existants.

## 3. Matrice DNS

| Scénario | Résultat attendu |
| --- | --- |
| Requête A vers un nom protégé de l'INI | `0.0.0.0` en local, aucune transmission amont |
| Requête AAAA vers le même nom | Aucune adresse IPv6, aucune transmission amont |
| Domaine historiquement exempté mais présent parmi les motifs obligatoires | Bloqué malgré une ancienne exception |
| Autres domaines de services ou d'éditeurs protégés par l'INI | Bloqués conformément aux motifs |
| Plusieurs questions, classe ou opcode non pris en charge | Rejet, aucune retransmission non contrôlée |
| Domaine autorisé comme `github.com` | Résolution via Quad9 si WAN volontairement activé |
| CNAME amont dirigé vers un nom protégé | Rejet et absence de relais vers le client |
| Double lancement du payload | Le premier écouteur demeure, le second ne récupère pas le port 53 |
| Fichier INI absent ou invalide | Liste obligatoire compilée toujours appliquée |
| Signal d'arrêt supporté | Sockets et pool réseau libérés proprement |

Choisir les domaines bloqués **directement dans le fichier INI**, sans lancer volontairement de requête de mise à jour système. Préserver des journaux anonymisés.

## 4. Tests sur console

1. Tester extinction et démarrage à la manette **sans nanoDNS** comme référence.
2. Charger une seule instance, utiliser normalement le système et l'éteindre.
3. Depuis un état complètement éteint, tenter le démarrage via la manette.
4. Tester veille, reprise, manette et continuité DNS.
5. Répéter après des changements d'applications.
6. Surveiller gel, messages de réparation du stockage, avertissements système et absence de trace de fermeture.
7. En cas de défaut, revenir à l'ELF et à l'INI précédents.

## 5. Critères de qualification matérielle complémentaire

**Obligatoire :** builds du dernier commit et CI sécurité verts, blocage démontré des requêtes connues, résolution des noms autorisés et extinction/veille/réveil reproductibles sur matériel.

**Bloquant :** anomalie d'extinction, réparation du stockage, requête connue retransmise, régression réseau, terminaison inattendue ou CI rouge. La garantie d'absence totale de trafic WAN reste du ressort du pare-feu externe.
