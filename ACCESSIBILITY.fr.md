# Accessibilité et contributions inclusives

**Langues :** [English (default)](ACCESSIBILITY.md) | Français

nanoDNS est un payload DNS natif en arrière-plan, sans interface graphique propre. Ses interfaces publiques sont la documentation, les téléchargements, les guides d'installation, les journaux et les formulaires GitHub. Nous voulons rendre ces ressources compréhensibles et utilisables par le plus grand nombre.

## Documentation et téléchargements

- Guides en texte/Markdown, avec titres et liens explicites, sans instructions uniquement visuelles.
- Chemins absolus copiables et procédure claire pour remplacer l'ancien autoload de Payload Manager.
- Documentation principale en anglais, traduction française des guides importants. Les signalements sont acceptés dans les deux langues.
- Journaux texte lisibles ; **anonymiser** noms d'hôtes et informations réseau avant partage.

## Ce qui est vérifié — et ce qui ne l'est pas

**Aucun audit formel d'accessibilité n'a été réalisé** et aucune conformité WCAG n'est revendiquée. L'interface de GitHub et celle de Payload Manager sont externes au projet. Un test utilisateur du fonctionnement DNS de base et de l'extinction/rallumage sur firmware 13.60 est positif ; les autres firmwares et le binaire de génération précédente restent **non validés par utilisateur**. Cela ne constitue pas un audit d'accessibilité.

## Signaler une difficulté

Ouvre une [issue de documentation ou d'accessibilité](https://github.com/niakw/nanoDNS-13.60/issues/new/choose) en indiquant, si possible :

- Ce que tu voulais faire (trouver le ZIP, suivre une étape d'installation, comprendre un message).
- La page publique ou son titre et le comportement rencontré.
- Ton environnement ou ton aide technique **seulement si tu souhaites le communiquer** ; aucune capture n'est exigée.
- Une suggestion de formulation ou de présentation plus accessible.

Ne publie pas de données personnelles, de logs DNS non anonymisés ou d'identifiants de console. Aucun délai de réponse automatique n'est garanti.

## Participer

Privilégie les titres bien structurés, des liens explicites, des équivalents textuels pour les schémas et des exemples copiables. Une modification destinée aux utilisateurs doit conserver la cohérence anglais/français. Voir [les contributions](CONTRIBUTING.fr.md), [la sécurité](SECURITY.fr.md) et [les tests](docs/TEST_PLAN.fr.md).
