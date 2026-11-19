# Historique des modifications

**Langues :** [English (default)](CHANGELOG.md) | Français

## 0.4-13.60.2 — Release standard, tests matériels à refaire (19 novembre 2026)

- Suppression de la course `stat()` / `fopen("w")` lors de la création du `nanodns.ini` : ouverture atomique `O_CREAT | O_EXCL | O_NOFOLLOW`, permissions initiales restreintes, aucun écrasement du fichier existant.
- Ouverture du fichier INI existant sans suivre les liens symboliques et validation du type fichier ordinaire. Si le chargement échoue, maintien des règles intégrées obligatoires.
- Droits minimaux `contents: read` dans les workflows classiques de compilation, suppression des publications automatiques concurrentes, publication centralisée conservée.
- Correction de la configuration Dependabot pour le suivi hebdomadaire des GitHub Actions.
- Guides anglais/français d'accessibilité, de contribution, de conduite et d'issues adaptés au projet.

**Limite de validation :** la Release 0.4-13.60.2 contient de **nouveaux binaires** avec le correctif de sécurité et les PR CI fusionnées, mais n'a **pas encore été retestée par utilisateur**. Le test 13.60 positif concernait le binaire 0.4-13.60.1. Les autres firmwares et le binaire secondaire restent non validés.

## 0.4-13.60.1 — Release GitHub standard ; premier test utilisateur positif sur 13.60 (19 novembre 2026)

### Fiabilité des processus
- Suppression du scan système dépendant d'offsets internes et des remplacements d'instances par `SIGKILL`.
- Conservation de l'étiquette d'origine des processus pour Payload Manager.
- Exigence d'une écoute IPv4 UDP exclusive et libération des ressources en cas d'échec.
- Sortie sur `SIGINT` / `SIGTERM` avec étapes de nettoyage journalisées.
- Délais monotones selon disponibilité et traitement limité des anciens paquets réseau.
- Conservation du journal précédent et taille maximale pour les logs actifs.

### Politique DNS et sécurité

- DNS amont désormais uniquement Quad9 : `9.9.9.9` et `149.112.112.112`, sans résolveur supplémentaire dans les valeurs par défaut. Conservation des 124 règles / zéro exception.
- Intégration avec crédits de la [liste de blocage multi-consoles](https://github.com/niakw/nanodns-console-blocklist) : 124 règles, aucune exception par défaut.
- Compilation des règles obligatoires dans le binaire et application prioritaire sur toute exception utilisateur.
- Rejet des questions DNS non prises en charge sans retransmission non filtrée.
- Contrôle des identifiants/questions des réponses amont et refus de certains alias vers des domaines protégés.
- Synchronisation de la configuration générée, du profil livré et des tests de cohérence.
- Remplacement du moteur de correspondance récursif par une version itérative, testée nativement.

### Documentation et intégration continue
- Documentation de sécurité, d'architecture du cycle de vie, d'installation, de tests et de provenance.
- Conservation des compilations SDK console/console et ajout de validations automatiques de la politique DNS.
- Anglais par défaut et traductions françaises séparées.

**Validation :** un premier essai utilisateur sur firmware 13.60 a confirmé le démarrage, les blocages DNS de type A et l'extinction/rallumage sans reproduction du problème. La veille/reprise, les essais répétés, la résolution autorisée et les autres firmwares restent non validés. Un build CI vert ne remplace jamais les tests matériels.
