# Historique des modifications

**Langues :** [English (default)](CHANGELOG.md) | Français

## 0.4-13.60.1 — version de développement (19 novembre 2026)

### Fiabilité des processus
- Suppression du scan système dépendant d'offsets internes et des remplacements d'instances par `SIGKILL`.
- Conservation de l'étiquette d'origine des processus pour Payload Manager.
- Exigence d'une écoute IPv4 UDP exclusive et libération des ressources en cas d'échec.
- Sortie sur `SIGINT` / `SIGTERM` avec étapes de nettoyage journalisées.
- Délais monotones selon disponibilité et traitement limité des anciens paquets réseau.
- Conservation du journal précédent et taille maximale pour les logs actifs.

### Politique DNS et sécurité
- Intégration avec crédits de la [liste de blocage multi-consoles](https://github.com/niakw/nanodns-console-blocklist) : 124 règles, aucune exception par défaut.
- Compilation des règles obligatoires dans le binaire et application prioritaire sur toute exception utilisateur.
- Rejet des questions DNS non prises en charge sans retransmission non filtrée.
- Contrôle des identifiants/questions des réponses amont et refus de certains alias vers des domaines protégés.
- Synchronisation de la configuration générée, du profil livré et des tests de cohérence.
- Remplacement du moteur de correspondance récursif par une version itérative, testée nativement.

### Documentation et intégration continue
- Documentation de sécurité, d'architecture du cycle de vie, d'installation, de tests et de provenance.
- Conservation des compilations SDK PS5/PS4 et ajout de validations automatiques de la politique DNS.
- Anglais par défaut et traductions françaises séparées.

**Limite :** un build CI réussi n'est pas une preuve de correction du réveil par DualSense ou de la stabilité de l'extinction sur console réelle.
