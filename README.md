<a id="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url]
[![License][license-shield]][license-url]
[![C][c-shield]][c-url]

<div align="center">

<h3 align="center">huffman-compressor</h3>

  <p align="center">
    Compression Huffman en C — un fichier, plusieurs fichiers, ou un dossier complet. Un arbre de Huffman construit à partir des occurrences, produisant des codes binaires de longueur variable.
    <br />
    <br />
    <a href="https://github.com/Taza67/huffman-compressor/issues/new?labels=bug">Report Bug</a>
    &middot;
    <a href="https://github.com/Taza67/huffman-compressor/issues/new?labels=enhancement">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

## About The Project

`huffman-compressor` est un outil en ligne de commande qui compresse un ou plusieurs fichiers — y compris des dossiers entiers, parcourus récursivement — dans une archive unique, puis les restaure.

L'outil construit un arbre de Huffman à partir des occurrences de chaque caractère et écrit des codes binaires de longueur variable dans le fichier compressé.

### Built With

* [C](https://fr.wikipedia.org/wiki/C_(langage)) C89
* [Make](https://fr.wikipedia.org/wiki/Make)

<p align="right"><a href="#readme-top" title="Retour en haut">↑</a></p>

## Getting Started

### Prerequisites

* `gcc`
* `make`

### Installation

```bash
git clone https://github.com/Taza67/huffman-compressor.git
cd huffman-compressor
make build
```

<p align="right"><a href="#readme-top" title="Retour en haut">↑</a></p>

## Usage

Afficher l'aide :

```sh
./huffman-compressor -h
```

Compresser un ou plusieurs fichiers, ou un dossier, dans une archive :

```sh
./huffman-compressor -c archive.huf fichier.txt
./huffman-compressor -c archive.huf dossier/
```

Décompresser une archive (dans le dossier courant, ou un dossier cible) :

```sh
./huffman-compressor -d archive.huf
./huffman-compressor -d archive.huf dossier_cible
```

<p align="right"><a href="#readme-top" title="Retour en haut">↑</a></p>

## Contributing

Voir [CONTRIBUTING.md](CONTRIBUTING.md). Veuillez lire [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) avant de participer.

<p align="right"><a href="#readme-top" title="Retour en haut">↑</a></p>

## License

Distribué sous la licence MIT. Voir [LICENSE](LICENSE) pour plus d'informations.

<p align="right"><a href="#readme-top" title="Retour en haut">↑</a></p>

## Contact

Taza67 - [tazaakil67@gmail.com](mailto:tazaakil67@gmail.com)

Lien du projet : [https://github.com/Taza67/huffman-compressor](https://github.com/Taza67/huffman-compressor)

<p align="right"><a href="#readme-top" title="Retour en haut">↑</a></p>

<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/Taza67/huffman-compressor.svg
[contributors-url]: https://github.com/Taza67/huffman-compressor/graphs/contributors
[issues-shield]: https://img.shields.io/github/issues/Taza67/huffman-compressor.svg
[issues-url]: https://github.com/Taza67/huffman-compressor/issues
[license-shield]: https://img.shields.io/badge/License-MIT-blue.svg
[license-url]: https://github.com/Taza67/huffman-compressor/blob/main/LICENSE
[c-shield]: https://img.shields.io/badge/C89-00599C.svg?logo=c&logoColor=white
[c-url]: https://fr.wikipedia.org/wiki/C_(langage)