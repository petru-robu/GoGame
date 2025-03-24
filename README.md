# Go Game
An implementation of the Game of Go, done in C++ using the SFML library. The application simulates the go rules and applies them to the board. The game can be played locally by two players or against an AI integrated in the application.

## Implementation details
The application is structured in the follwing sections: frontend, backend and AI integration.

### Frontend
The frontend was done using the [SFML library](https://www.sfml-dev.org/), a very useful tool for creating GUI in C++.
The application makes use of some classes that deal with the visual aspect of the game: 
- First of all, there is a menu system implemented. This is done by implementing an interface and down casting diffrent types of menus depending on the current state of the game.
- Second of all, SFML only provides acces to various components of the PC, graphics, audio, network, etc. So, I implemented UI elements, like labels, buttons, sliders and more.

### Backend
The backend is the most intricate part of the implementation. I decided to go with the following when implementing the game logic:
- The backend consists of a grid of Intersections. Every intersection is of a certain type (WHITE, BLACK, WHITE_LIBERTY, BLACK_LIBERTY or EMPTY).
- For efficiency and not recomputing the state of the board every move, there are groups of stones, which reference intersections. In a group of stones we have a set of pieces and a set of liberties. Also, every intersection references a group of stones as well (may be null, if an intersection is not part of a group). When th groups become connected, they are merged. For further optimization, the groups merge by size(merge the smaller group to the bigger one). 

### AI Integration

## Compilation instructions
The project is configured via [CMake](https://cmake.org/).
0. Necessary libraries on linux (assuming debian installation).
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

1. Configuration
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# or ./scripts/cmake.sh configure

# On Windows with GCC:
# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

2. Compilation
```sh
cmake --build build --config Debug --parallel 6
# or ./scripts/cmake.sh build
```

3. Installation (optional)
```sh
cmake --install build --config Debug --prefix install_dir
# or ./scripts/cmake.sh install
```

## Tasks
### Tema 0:

- [X] Nume proiect (poate fi schimbat ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

### Tema 1:

#### Cerințe
- [X] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [X] constructori de inițializare cu parametri pentru fiecare clasă
- [X] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor (clasa Game)
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<` (clasa BackendBoard)
- [X] cât mai multe `const` (unde este cazul) și funcții `private` (clasa Label, const la getters)
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [X] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [X] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect
- [X] tag de `git`: de exemplu `v0.1`
- [X] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions

### Tema 2:

#### Cerințe
- [X] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [X] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [X] STL
- [X] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [X] minim 75-80% din codul propriu să fie C++
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`

### Tema 3:

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] minim 85% din codul propriu să fie C++
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`

## Resources

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- [Robot-Crush Font](https://www.dafont.com/robot-crush.font)
- [Shuriken Font](https://www.dafont.com/the-last-shuriken.font)
- [Arial Font](https://font.download/font/arial)
