# nanoDNS 13.60 — fork de fiabilisation et sécurité DNS

**Langues :** [English (default)](README.md) | Français

Ce dépôt adapte [nanoDNS de Drakmor](https://github.com/drakmor/nanoDNS) à une utilisation contrôlée sur **PS5 firmware 13.60**, avec une liste obligatoire de **124 règles DNS** issue de [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist).

**Statut :** compilation PS5/PS4 et contrôles automatisés nécessaires, mais un build vert ne prouve pas la stabilité de l’extinction, du mode repos ou du réveil avec la DualSense. Ne remplace pas ton payload officiel tant que le [protocole console](docs/TEST_PLAN.fr.md) n’est pas validé.

## Améliorations apportées

- Suppression du scan des processus fondé sur des offsets internes et de leur terminaison brutale par `SIGKILL`.
- Conservation du nom `nanodns.elf` afin de rester compatible avec Payload Manager.
- Sortie plus propre sur `SIGINT` / `SIGTERM`, nettoyage des sockets et des ressources SceNet, avec étapes journalisées.
- Un seul propriétaire du port DNS UDP 53 ; refus de démarrer si l'écoute IPv4 nécessaire échoue.
- Délais monotones lorsqu'ils sont disponibles et limites de traitement des paquets obsolètes.
- Configuration initiale, exemple et `nanodns.ini` alignés sur la liste de 124 règles sans exception.
- **Règles de blocage intégrées au binaire** et appliquées avant toute exception utilisateur, notamment pour les domaines Sony/PlayStation.
- Rejet des questions DNS inhabituelles non contrôlées et validation des réponses amont, y compris certains alias de domaines interdits.
- Tests Python de cohérence et tests natifs des masques DNS, avec compilation PS4/PS5 par GitHub Actions.
- Sauvegarde du journal précédent et plafonnement de la taille des logs.

## DNS amont Quad9 uniquement

Le profil livré, les valeurs générées et les valeurs de secours intégrées utilisent **`9.9.9.9` puis `149.112.112.112`**, deux adresses du [service sécurisé Quad9](https://quad9.net/fr/service/service-addresses-and-features/). Aucun relais Cloudflare dans les valeurs par défaut ; le filtrage Quad9 complète la blocklist locale sans la remplacer.

**Attention :** le payload ne remplace pas un `nanodns.ini` déjà présent sur la console. Il faut donc copier le nouveau profil pour activer ces DNS amont. Le trafic DNS amont de nanoDNS utilise de l'UDP non chiffré.

## Installation

Lire le [guide d'installation sécurisé en français](docs/INSTALL.fr.md). Isoler d'abord l'accès Internet **au niveau du routeur**, conserver la possibilité de charger le jailbreak hors ligne, sauvegarder l'ELF et la configuration, puis copier [`nanodns.ini`](nanodns.ini) dans `/data/nanodns/nanodns.ini`.

Configurer **les deux DNS** de la PS5 sur `127.0.0.1` (pas de DNS public secondaire), et démarrer une seule instance via Payload Manager. Vérifier les requêtes bloquées dans le journal de la session, les résolutions autorisées et le comportement d'arrêt/réveil.

Le nouveau binaire **ne remplace jamais automatiquement un `nanodns.ini` existant**. Une ancienne configuration ne peut cependant pas contourner les 124 règles obligatoires compilées.

## Documentation française

- [Installation](docs/INSTALL.fr.md)
- [Politique DNS et règles](docs/DNS_POLICY.fr.md)
- [Audit du cycle de vie PS5 13.60](docs/PS5_13_60_LIFECYCLE.fr.md)
- [Tests de validation et critères de publication](docs/TEST_PLAN.fr.md)
- [Sécurité et limites](SECURITY.fr.md)
- [Crédits et provenance](docs/CREDITS.fr.md)
- [Historique des modifications](CHANGELOG.fr.md)

## Limites essentielles

**nanoDNS n'est pas un pare-feu.** Il ne bloque ni les connexions directes aux IP, ni les DNS alternatifs ou chiffrés, ni les communications avant son lancement, ni les noms encore inconnus de la liste. Pour interdire strictement les connexions WAN, appliquer le filtrage sur la box/routeur, IPv4 **et** IPv6.

Le réveil via la touche PS de la DualSense est géré lorsque la console est éteinte : un payload qui tourne après le démarrage ne peut pas le forcer directement. Corriger une mauvaise extinction pourrait aider, mais cela reste à vérifier sur console.

**Crédits :** code original de [Drakmor](https://github.com/drakmor/nanoDNS), règles de [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist), intégration indépendante de [niakw](https://github.com/niakw). Licence [GPL-3.0](LICENSE) conservée. Aucun lien officiel avec Sony ou Drakmor.
