# Plan de validation — nanoDNS 13.60

**Langues :** [English (default)](TEST_PLAN.md) | Français

**Statut :** version candidate de développement. Un build et des tests logiciels verts ne garantissent pas la stabilité de l'extinction ou du réveil par la DualSense. Les tests console suivants restent à effectuer physiquement.

## 1. Tests automatisés

Exécuter `python3 -m unittest discover -s tests -v` et le test natif de correspondance des masques DNS. Vérifier les **124 règles** présentes dans le profil livré, l'exemple, la configuration générée et le tableau compilé en C.

Compiler l'ELF PS5 avec le SDK officiel `ps5-payload-dev/sdk` et exécuter également la compilation PS4 pour détecter les régressions. Vérifier que les artefacts existent et sont non vides. Ne pas publier de version présentée comme validée avant les tests console.

## 2. Préparation sécurisée

Sauvegarder l'ELF d'origine, `/data/nanodns/nanodns.ini`, les journaux et les sauvegardes importantes. Interdire temporairement l'accès WAN au niveau du routeur, IPv4 et IPv6, en préservant le FTP et le chargement local.

Configuration cible : PS5 13.60, WebKit Autoloader 0.7.1, Payload Manager, Kstuff Lite 1.11, ShadowMountPlus 1.7beta12, BFPilot 0.4.4 et ftpsrv 0.22. Vérifier l'absence de chargement double.

## 3. Matrice DNS

| Test | Résultat attendu |
| --- | --- |
| `ps5.np.playstation.net` A | Blocage local en `0.0.0.0`, aucun appel au DNS amont |
| `fus01.ps5.update.playstation.net` AAAA | Blocage sans adresse IPv6 |
| `feature.api.playstation.com` A | Bloqué même si une ancienne exception persiste dans l'INI |
| `gst.prod.dl.playstation.net` A | Bloqué même avec une ancienne exception |
| `nintendo.net`, `xboxlive.com`, `ea.com` A | Bloqués suivant les règles |
| Question multiple ou opcode non pris en charge | Rejet, sans retransmission non filtrée |
| `github.com` | Résolution autorisée |
| Réponse amont contenant un CNAME vers un domaine protégé | Rejet, retour SERVFAIL |
| Second lancement nanoDNS | Première instance conservée ; la nouvelle échoue à obtenir le port |
| Configuration absente ou invalide | Protection obligatoire intégrée conservée |

Tester avec des paquets DNS contrôlés et les journaux ; ne pas contacter volontairement les serveurs de mise à jour firmware.

## 4. Cycle de vie

1. Tester l'extinction et le démarrage à la manette **sans nanoDNS**, pour établir une référence.
2. Charger une seule instance nanoDNS, vérifier les DNS autorisés et interdits, puis tenter une extinction normale.
3. Depuis une console complètement éteinte, appuyer sur PS de la DualSense et vérifier si la console démarre.
4. Tester mode repos, reprise, contrôleur et continuité DNS.
5. Tester changement de jeu/application, fermeture et extinction.
6. Relancer nanoDNS dans Payload Manager sans `SIGKILL` ni écoute UDP partagée.
7. Contrôler l'absence de réparation du stockage, gel, crash ou régression réseau.

Conserver les dernières traces et logs système en les anonymisant.

## 5. Critère de publication

**Nécessaire :** CI PS5 verte, contrôles DNS verts, domaines interdits de la matrice non transmis à l'amont, domaines autorisés fonctionnels, arrêt/veille/reprise et réveil normaux sur console réelle.

**Blocage de publication :** extinction figée, réveil DualSense défectueux, réparation du stockage, fuite DNS ou build en échec.
