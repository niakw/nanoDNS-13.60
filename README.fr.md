<div align="center">

# nanoDNS 13.60 — Runtime renforcé

### Des règles DNS obligatoires, un arrêt plus propre et un payload vérifiable.

**124 motifs protégés intégrés · Quad9 sécurisé · Tests natifs · Cycle de vie fiabilisé**

**Langues :** [English (default)](README.md) · Français

[**Installation française**](docs/INSTALL.fr.md) · [**Politique DNS**](docs/DNS_POLICY.fr.md) · [**Audit runtime**](docs/PS5_13_60_LIFECYCLE.fr.md) · [**Tests**](docs/TEST_PLAN.fr.md)

</div>

---

## Plus qu'un fichier de règles

Un fichier de blocklist peut être modifié ou contourné par une exception. Un payload mal géré peut également perturber l'arrêt ou le chargement en double.

**Ce fork de [nanoDNS par Drakmor](https://github.com/drakmor/nanoDNS)** intègre les **124 règles** de [niakw Console Blocklist](https://github.com/niakw/nanodns-console-blocklist) **dans le programme lui-même**. Elles sont vérifiées avant les exceptions utilisateur. Les noms autorisés continuent de passer par **Quad9 sécurisé**.

L'objectif est une protection DNS mieux définie et un fonctionnement plus stable, sans supprimer inutilement l'accès au Web.

## Ce qui change réellement

| Fonction | nanoDNS original | Blocklist seule | **Notre fork renforcé** |
| --- | --- | --- | --- |
| Règles livrées par défaut | **8** | **124** | **124 obligatoires compilées** |
| Exceptions par défaut | **6** | **0** | Ne peuvent pas neutraliser les motifs obligatoires |
| DNS amont | 3 fournisseurs | Quad9 sécurisé | **Quad9 sécurisé uniquement** |
| Questions DNS non standards | Comportement d'origine | Hérité | Refus sans retransmission non contrôlée |
| Réponses des résolveurs | Contrôles d'origine | Hérité | Vérifications supplémentaires des noms et alias |
| Moteur des masques | Récursif | Hérité | Itératif avec tests natifs |
| Lancement en double | Arrêt brutal de l'ancienne instance | Hérité | Écoute exclusive, sans arrêt brutal |
| Logs / extinction | Journal précédent écrasé | Hérité | Conservation, limite de taille et traces d'arrêt |
| Garantie d'absence totale de fuite IP | **Non** | **Non** | **Non** |
| Extinction et réveil validés sur console | Non établi | Sans objet | **À confirmer sur matériel** |

Ces chiffres concernent **les réglages initiaux** de la version d'origine, qui sait également charger une blocklist personnalisée.

## Fonctionnement et Quad9

Les 124 motifs obligatoires sont évalués avant toute exception. Pour les noms interdits, les requêtes A reçoivent `0.0.0.0` et les AAAA aucune adresse. Les requêtes autorisées sont envoyées à **`9.9.9.9` puis `149.112.112.112`**, deux adresses du **même service sécurisé Quad9**. Le transfert amont du payload utilise toujours de l'UDP non chiffré.

## Tu utilises déjà le nanoDNS 0.4 officiel ?

**N'utilise pas Update sur l'ancienne entrée du catalogue.** Notre dépôt indépendant exige une **migration manuelle** : sauvegarde l'ELF et l'INI, désactive l'autoload d'origine, redémarre proprement, importe notre `nanodns.elf` comme **payload local**, remplace **séparément** `/data/nanodns/nanodns.ini` par FTP et n'active que la nouvelle entrée. Les deux DNS de la console restent `127.0.0.1`.

[**Guide complet de migration depuis la version officielle**](docs/INSTALL.fr.md#migration-depuis-le-nanodns-04-officiel-de-drakmor) · [English upgrade guide](docs/INSTALL.md#upgrade-from-drakmors-original-nanodns-04) · [Fichiers de la préversion](https://github.com/niakw/nanoDNS-13.60/releases/tag/v0.4-13.60.1-beta.1)

## Fiabilité et installation

Le fork supprime les offsets internes fragiles et les `SIGKILL` destinés à remplacer une ancienne instance, impose une écoute UDP exclusive, nettoie les ressources réseau lors d'un arrêt signalé et conserve le journal précédent. Il ajoute également des tests de cohérence de configuration et des tests natifs.

Avant installation, **isoler le WAN au niveau du routeur, IPv4 et IPv6**, sauvegarder l'ELF et la configuration, copier le [`nanodns.ini`](nanodns.ini) et régler **les deux DNS console sur `127.0.0.1`**. Le payload ne remplace pas automatiquement un INI existant.

Lire le [guide français](docs/INSTALL.fr.md) ou le [guide principal anglais](docs/INSTALL.md). Appliquer ensuite la [matrice de validation](docs/TEST_PLAN.fr.md).

## Peut-on supprimer le fork ?

**Pas avant validation sur matériel.** Un build vert ne prouve pas le bon arrêt, le réveil à la manette ou l'absence de réparation du stockage. Même après ces essais, revenir au binaire original fait perdre les **règles compilées obligatoires** et les corrections du runtime. Une archive conservée est préférable à une suppression définitive.

## Limites

Aucun DNS local ne peut bloquer toutes les IP directes, les DNS alternatifs ou chiffrés, les caches et les communications avant chargement. Une interdiction stricte du WAN exige un pare-feu externe. Voir [sécurité](SECURITY.fr.md).

## Crédits

Code original : [Drakmor](https://github.com/drakmor/nanoDNS). Règles : [niakw Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). Intégration : [niakw](https://github.com/niakw/nanoDNS-13.60). Licence [GPL-3.0](LICENSE), projet communautaire indépendant.

---

**Des protections mesurables. Des limites documentées.**
