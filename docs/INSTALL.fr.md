# Installation sécurisée — console 13.60

1. **Isole le WAN** pour la console au niveau de la box/du pare-feu (IPv4 **et** IPv6), tout en conservant le réseau local nécessaire au chargement du jailbreak, au FTP et aux tests. Ne dépends pas d'un DNS public pour protéger le tout premier démarrage.
2. **Sauvegarde** ton `nanodns.elf` d'origine, `/data/nanodns/nanodns.ini`, `/data/nanodns/nanodns.log` et les sauvegardes de jeux importantes.
3. Transfère le [profil complet de 124 règles](../nanodns.ini) vers `/data/nanodns/nanodns.ini` : le payload ne remplace jamais automatiquement un fichier existant. Vérifie `124 rule(s), 0 exception(s)`.
4. Dans les DNS primaire **et secondaire** de la console, utilise `127.0.0.1`. Aucun DNS public secondaire. Garde `bind=127.0.0.1` et `bind6=::1` dans la configuration.
5. Charge ton WebKit Autoloader puis **Payload Manager**, avec **une seule instance** de chaque payload. Ne mélange pas deux autoloads indépendants.
6. Déploie un ELF uniquement après le build console vert. Vérifie dans le nouveau log `listening on 127.0.0.1:53`, les blocages platform services A et AAAA, et la résolution d'un nom autorisé tel que `github.com`.
7. Applique [le protocole de tests console](TEST_PLAN.md) : arrêt normal, démarrage DualSense, veille/reprise, relance, doublon. En cas d'échec, restaure les fichiers précédents.

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
