# Installation sécurisée — console 13.60

**Langues :** [English (default)](INSTALL.md) | Français

## Migration depuis le nanoDNS 0.4 officiel de Drakmor

**C'est une migration manuelle, pas une mise à jour du dépôt d'origine.** Les deux dépôts GitHub sont indépendants. Le bouton **Update** de l'ancienne entrée nanoDNS du catalogue risque de réinstaller le payload officiel plutôt que notre version.

1. **Téléchargement et sauvegarde :** récupère `nanodns.elf` et `nanodns.ini` depuis la [préversion 13.60](https://github.com/niakw/nanoDNS-13.60/releases/tag/v0.4-13.60.1-beta.1). Copie sur ton Mac l'ancien ELF 0.4, ton `/data/nanodns/nanodns.ini` et `/data/nanodns/nanodns.log`. Maintiens le blocage WAN sur le routeur (IPv4 et IPv6), mais conserve les accès locaux FTP/loader.
2. **Désactivation de l'ancienne version :** dans **Payload Manager**, désactive l'autoload du nanoDNS officiel. Si un autre chargeur lance directement nanoDNS, désactive aussi cette entrée. Ne touche pas aux autres payloads.
3. **Extinction puis redémarrage propres :** relance le chargeur local et Payload Manager après avoir rallumé la console. Ne remplace pas un ELF en cours d'exécution, ne force pas la fermeture de l'ancien processus avec `SIGKILL` et ne charge jamais les deux versions simultanément.
4. **Import du nouveau binaire en local :** utilise l'import de payload local de Payload Manager avec le nouveau `nanodns.elf`. Sélectionne **l'entrée locale importée**, et non celle du catalogue officiel. Ne modifie pas au hasard les fichiers internes du gestionnaire.
5. **Remplacement séparé du fichier de règles :** en FTP, copie le nouveau `nanodns.ini` à l'emplacement **`/data/nanodns/nanodns.ini`**. Le nouvel ELF **n'écrase pas** la configuration existante : un changement d'ELF seul ne remplace pas les anciens DNS ou exceptions du fichier.
6. **DNS de la console :** renseigne `127.0.0.1` dans **les deux champs DNS**. Seul `[upstream]` dans l'INI doit contenir `server=9.9.9.9` et `server=149.112.112.112`, avec **zéro exception active**. Ne renseigne pas Quad9 directement comme DNS de la console.
7. **Un seul autoload :** lance le nouveau payload, vérifie son fonctionnement, puis active uniquement son **entrée locale** au démarrage. L'ancienne entrée du catalogue reste désactivée. Un doublon peut refuser le port DNS UDP 53 : c'est volontaire.
8. **Validation :** contrôle le nouveau `/data/nanodns/nanodns.log` : `124 rule(s)`, `0 exception(s)`, écoute locale et réponses bloquées. Si tu autorises volontairement certaines connexions, vérifie un domaine autorisé comme `github.com`. Termine par [les tests d'extinction, de réveil à la manette et de veille/reprise](TEST_PLAN.fr.md).

**Retour arrière :** désactive l'autoload du nouvel ELF, éteins normalement, restaure l'ancien `nanodns.elf` via Payload Manager et l'ancien `nanodns.ini` par FTP, puis réactive **uniquement l'entrée officielle**. Conserve les journaux utiles au diagnostic.

**Limite de sécurité :** nanoDNS n'est pas un pare-feu. IP directes, caches, autres DNS, DNS chiffrés ou TCP, trafic avant chargement et domaines inconnus exigent un filtrage externe. Un build vert ne prouve pas la résolution des problèmes d'extinction.

## Première installation : contrôle rapide

1. **Isole le WAN** pour la console au niveau de la box/du pare-feu (IPv4 **et** IPv6), tout en conservant le réseau local nécessaire au chargement du jailbreak, au FTP et aux tests. Ne dépends pas d'un DNS public pour protéger le tout premier démarrage.
2. **Sauvegarde** ton `nanodns.elf` d'origine, `/data/nanodns/nanodns.ini`, `/data/nanodns/nanodns.log` et les sauvegardes de jeux importantes.
3. Transfère le [profil complet de 124 règles](../nanodns.ini) vers `/data/nanodns/nanodns.ini` : le payload ne remplace jamais automatiquement un fichier existant. Vérifie `124 rule(s), 0 exception(s)`.
4. Dans les DNS primaire **et secondaire** de la console, utilise `127.0.0.1`. Aucun DNS public secondaire. Garde `bind=127.0.0.1` et `bind6=::1` dans la configuration.
5. Charge ton WebKit Autoloader puis **Payload Manager**, avec **une seule instance** de chaque payload. Ne mélange pas deux autoloads indépendants.
6. Déploie un ELF uniquement après le build console vert. Vérifie dans le nouveau log `listening on 127.0.0.1:53`, le blocage des domaines protégés en A et AAAA, et la résolution d'un nom autorisé tel que `github.com`.
7. Applique [le protocole de tests console](TEST_PLAN.md) : arrêt normal, démarrage à la manette, veille/reprise, relance, doublon. En cas d'échec, restaure les fichiers précédents.

## DNS amont Quad9

La configuration distribuée utilise exclusivement les deux adresses du service sécurisé Quad9 pour les domaines **autorisés** :

```ini
[upstream]
server=9.9.9.9
server=149.112.112.112
timeout_ms=1500
```

Ces adresses **ne doivent pas être configurées dans les paramètres réseau de la console** : les deux champs DNS de la console restent `127.0.0.1`. Un ancien fichier `nanodns.ini` doit être remplacé manuellement.

**Important :** nanoDNS est un filtre DNS sélectif, pas un pare-feu. Il ne bloque pas les adresses IP directes, les DNS alternatifs, le DoH, les connexions avant activation du payload ni les domaines inconnus. Pour une absence stricte de fuite réseau, garde le blocage WAN externe.

**Crédits :** payload original [drakmor/nanoDNS](https://github.com/drakmor/nanoDNS), configuration [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist). Fork indépendant GPL-3.0.
