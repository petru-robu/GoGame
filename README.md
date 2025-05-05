# Go Game
An implementation of the Game of Go, done in C++ using the SFML library. The application simulates the go rules and applies them to the board. The game can be played locally by two players. In the future, the application should support playing on a server and playing against an AI agent.

## Implementation details
The application is structured in the follwing sections: **frontend** and **backend**.

### Frontend
The frontend was done using the [SFML library](https://www.sfml-dev.org/), a very useful tool for creating GUI in C++.
The application makes use of some classes that deal with the visual aspect of the game: 

#### UI Design
The UI consists of *Label* and *Button* objects. Labels are understood as *drawable* elements and buttons are *labels* that are *clickable*.<br>
*IDrawable* and *IClickable* interfaces are interfaces for drawable elements and clickable elements, respectively.
  ```
  class IDrawable
  {
  public:
      IDrawable(sf::RenderWindow& window): window(window){}
      virtual void Render() = 0;
      virtual ~IDrawable() = default;
  };
  
  class IClickable
  {
  public:
      virtual void HandleClick(const std::optional<sf::Event> &event) = 0;
      virtual bool WasClicked() const = 0;
  };

  class Label: public IDrawable
  class Button: public Label, public IClickable
  ```
#### Visual Board Design
An importand part of the application is the frontend for the board. The board is created by overlapping two grids, as in GO, we place on intersections, not in cells. So, there is a grid of cells, and then lines of the board are drew over the grid. The *VisualBoard* object is also an *IDrawable*. The *VisualBoard* consists also of two *std::vectors* of *Pieces* and *Liberties*, where *Piece* is a template *Cell* object with *sf::CircleShape* as type and *Liberty* with *sf::RectangleShape* as type, like below:
```
template <typename DT>
class Cell : public IDrawable
{};
class Piece: public Cell<sf::CircleShape>
{};
class Liberty: public Cell<sf::RectangleShape>
{};

class VisualBoard: public IDrawable
{
private:
    BackendBoard backend_board;
    std::vector<std::vector<Piece>> piece_grid;
    std::vector<std::vector<Liberty>> liberty_grid;

public:
    void manageHovers(sf::Vector2i mouse_pos);
    void manageMouseClick(sf::Vector2i mouse_pos, CellType& turn);
};
```
#### Resource Manager
Resource managers are very useful when designing a frontend. The *Resource Manager* class manages the loading of fonts, textures and sounds.
```
class ResourceManager
{
private:
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
public:
    static ResourceManager& getInstance();
    std::shared_ptr<sf::Font> getFont(const std::string& path);
    std::shared_ptr<sf::Texture> getTexture(const std::string& path);
};
```
Also, for being consistent with a theme, I created a namespace with the colors for the application.
```
namespace Colors
{
    const sf::Color RED      = sf::Color(255, 0, 0, 255);
    const sf::Color BUTTON_COLOR = sf::Color(255, 174, 0);
    const sf::Color BOARD_BACKGROUND_COLOR = sf::Color(252, 144, 3);
    const sf::Color PIECE_HOVER_COLOR = sf::Color(255, 0, 0, 100);
    const sf::Color LIBERTY_COLOR = sf::Color(255, 234, 0);
}
```
#### Error Handling
Error handling is essential for both frontend and backend. There is an exception hierarchy built in. My application is susceptible to these types of errors in most part:
```
class GameException : public std::exception 
{
protected:
    std::string message;
public:
    explicit GameException(const std::string& msg);
    const char* what() const noexcept override;
};
class ResourceLoadException : public GameException
class InvalidMoveException : public GameException 
```
An exception may be thrown like this in *backend_board*:
```
if(hasFriendlyGroup && !friendlyGroupAlive && !hasEmptyNeighbour && enemy_capture_cnt == 0)
{
    //This move is suicide (do not allow)
    //revert changes
    for(auto grp:groups_of_covered_liberty)
        grp->addLiberty(curr_inter);
    throw InvalidMoveException("Suicide move!");
}
```
And caught like this in *visual_board*:
```
try
{
    backend_board.addStone(cx, cy, turn);        
}
catch (const InvalidMoveException& e)
{
    //invalid move
    std::cout<<e.what()<<"\n";
}
```


### Backend
The backend is the most intricate part of the implementation. I decided to go with the following when implementing the game logic: <br>
The *BackendBoard* is the heart of the application. The board is a matrix of *intersections*. Through the backend_board object we also maintain the group of stones as a std::set of *Groups*. 
-  An Intersection can be of a certain type (WHITE, BLACK or LIBERTY)
-  An Intersection points to multiple Groups it belongs to.
-  A Group can be of a certain type (WHITE or BLACK).
-  A Group consists of two sets of intersection. One set represent the stones of the group, and the other, it's liberties. 

```
class Group;
class Intersection
{
private:
    std::pair<int, int> coords;
    CellType type;
    std::set<Group*> groups;
};  

class Group
{
private:
    CellType group_type;
    std::set<Intersection*> stones;
    std::set<Intersection*> liberties;
public:
    Group();
    void extend(const Group* group);
};

class BackendBoard
{
private:
    std::vector<std::vector<Intersection>> board_matrix;
    std::set<Group*> white_groups;
    std::set<Group*> black_groups;
public:
    void addStone(int cx, int cy, CellType type);
};
```
When adding a stone or modifying the board's current configuration, the groups are adjusted dynamically. This is a tricky process split into multiple parts: adding a stone, managing group merges, managing captures, managing suicide situations and managing the [Ko rule](https://www.pandanet.co.jp/English/learning_go/learning_go_8.html). The Ko rule is implemented using [Zobrist Hashing](https://en.wikipedia.org/wiki/Zobrist_hashing) for efficient computation of past moves.

## Compilation instructions
The project is configured via [CMake](https://cmake.org/). <br>
Necessary libraries on linux (assuming debian installation).
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

## Future Improvements
Some features to be added to the application:
- Playing against a computer: KataGO agent.
- Playing on a server.
- Move History. Create an efficient system for keeping a history of moves. 

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
- [X] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [X] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [X] apelarea constructorului din clasa de bază din constructori din derivate
  - [X] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [X] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [X] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [X] smart pointers (recomandat, opțional)
- [X] excepții
  - [X] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [X] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [X] funcții și atribute `static`
- [X] STL
- [X] cât mai multe `const`
- [X] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [X] minim 75-80% din codul propriu să fie C++
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [X] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`

### Tema 3:

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [X] o clasă șablon cu sens; minim **2 instanțieri**
  - [X] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] minim 85% din codul propriu să fie C++
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`

## Resources

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- [Robot-Crush Font](https://www.dafont.com/robot-crush.font)
- [Shuriken Font](https://www.dafont.com/the-last-shuriken.font)
- [Arial Font](https://font.download/font/arial)
