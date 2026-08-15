# Contribuer

Merci de votre intérêt pour **huffman-compressor**. Le projet est un outil en C de compression et décompression de fichiers par codage de Huffman, construit avec `make` (norme C89).

## Avant de commencer

- Recherchez dans les [issues existantes](https://github.com/Taza67/huffman-compressor/issues) pour éviter de faire un travail en double.
- Pour les changements importants ou structurels, ouvrez d'abord une issue.

## Environnement de développement

### Prérequis

- `gcc` (voir `Makefile` : options `-Wall -W -g -std=c89 -pedantic -O3`)
- `make`

### Cloner et compiler

```bash
git clone https://github.com/Taza67/huffman-compressor.git
cd huffman-compressor
make build
```

## Pull requests

1. Forkez le dépôt et créez une branche depuis `main`.
2. Faites des changements ciblés ; gardez les PR faciles à relire.
3. Vérifiez que `make build` se compile sans erreur ni avertissement.
4. Ouvrez une pull request avec une description claire et liez les issues concernées.

## Messages de commit

Suivez [Conventional Commits](https://www.conventionalcommits.org/).

- **Types :** `feat`, `fix`, `refactor`, `docs`, `test`, `chore`
- **Description :** à l'impératif, en minuscules, sans point final
- **Corps :** facultatif ; ligne vide après la description, puis des puces `-` — en minuscules sauf noms propres, à l'impératif, sans point final

## Organisation du code

| Fichier | Rôle |
|---------|------|
| `src/main.c` | Point d'entrée, vérifie la ligne de commande |
| `src/compression.c` | Compression des fichiers et dossiers |
| `src/decompression.c` | Décompression d'une archive |
| `src/arbre_huffman.c` | Construction de l'arbre de Huffman et des codes |
| `src/en_tete.c` | Écriture et lecture de l'entête de l'archive |
| `src/gestion_fichiers.c` | Vérification et parcours des fichiers et dossiers |
| `src/gestion_erreurs.c` | Validation des arguments et messages d'erreur |
| `src/allocation.c` | Allocation et libération mémoire |
| `src/mon_erreur.c` | Gestion des erreurs |

## Code de conduite

Ce projet suit le [Contributor Covenant](CODE_OF_CONDUCT.md). En y participant, vous acceptez de le respecter.