# Game Of Life 

Projekt został wykonany w ramach przedmiotu Języki i Metody Programowania 2 na Politechnice Warszawskiej. Jest to implementacja klasycznej "Gry w życie" Johna Conwaya.

## Instalacja

Po pobraniu kodu źródłowego należy w folderze głównym projektu użyć polecenia make. W jej wyniku powstaną 2 katalogi: bin, obj. W folderze bin znajdować się będą pliki wykonywalne.

## Wersje

Po wykonania kroku instalacji powstaną 2 pliki wykonywalne. Oba rozwiązania korzystają z zasad sąsiedztwa Moore'a.

- **moore**
  - traktuje planszę jako zamknięty obiekt
  - pola poza planszą traktowane są jako pola nieaktywne
- **tormoore** 
  - traktuje planszę jako torus
  - pola poza planszą są polami krawędziowymi z drugiej strony planszy

## Użycie

Użycie programu jest identyczne zarówno dla wersji moore jak i tormoore. Przedstawione poniżej przykłady będą bazować na wersji moore.

By użyć programu należy uruchomić go z odpowiednimi argumentami.

Uruchomienie programu bez parametrów bądź z parametrami niepoprawnymi poskutkuje wyświetleniem instrukcji użytkowania.

### Argumenty

Podstawowym argumentem jest ten mówiący o początkowym stanie planszy. Można go przedstawić w jeden z dwóch sposobów:

- Możemy podać plik z zapisaną planszą: **./moore -m path-to-file**
- Możemy podać rozmiary planszy, zostanie wtedy utworzona losowa plansza o zadanych rozmiarach: **./moore -r [rows]x[columns]**

Po użyciu jedynie podstawowych argumentów automatycznie zostaną utworzone zarówno pliki BMP(z kolejnymi numerami generacji planszy) jak i plik GIF (life.gif).

Dodatkowe argumenty:

- **-i**
  - mówi o ilości iteracji symulacji.
  - **Domyślna Wartość:** 100
- **-d**
  - pozwala na wskazanie nazwy podkatalogu (znajdującego się w katalogu result), do którego zostaną zapisane pliki wynikowe
  - **Domyslna Wartość:** life
    - W przypadku gdy katalog life już istnieje, katalogiem do którego zostanie zapisany będzie life* z pierwszą niezajętą liczbą.
- **-o**
  - pozwala na wskazanie pliku, z jaką zostanie zapisana ostatnia generacja symulacji.
  - **Domyślna Wartość:** data/lastgen/map
- **--gif**
  - tworzy wynikowy plik GIF
- **--bmp**
  - tworzy wynikowe pliki BMP

### Przykłady

#### Przykład 1

Znajdując się w folderze głównym projektu

```bash
./bin/moore -r 100x100 --gif
```

Za pomocą powyższego polecenia zostanie przeprowadzona symulacja Gry W Życie w wersji moore z losową mapą o rozmiarze 100x100 oraz zostanie wygenerowany plik GIF przedstawiający całą symulację.

## Instrukcja

Instrukcja zarówno dla wersji moore jak i tormoore jest analogiczna, dlatego przedstawiona została tutaj tylko wersja moore.

```text
NAME
   ./bin/moore - simulation of Conway's Game of Life

SYNOPSIS
   ./bin/moore [ -m map-file | -r [rows]x[columns] ] [options]

DESCRIPTION
   ./bin/moore plays Conway's Game of Life. There are ways of playing the game:
       1. Insert properly formated text file (after '-m' option).
          File should have two integer values seperated by space
          in the first row: number of rows and numer of columns.
          Directly underneath should be table with values {0, 1}.
          Table should have number of rows equal to that in the first
          line. Each line should consist of number of values equal to
          the one at the top of the file.
       2. Insert bmp file (after '-m' option).
          Currently only 1 bit per pixel (bpp) files are accepted.
       3. Insert number of rows and columns separated by 'x'.
          When that kind of string appears after '-r' option, program
          generates random map of given dimensions and plays on that map.

   There are availible two versions of program:
       1. moore - bahaves as if outside map borders all cells were dead
       2. tormoore - behaves as if map was surface of torus

OPTIONS
   -i number-of-generations,   by default it is 100
   -d name-of-directory,       directory, where BMP files are stored,
                               by default it is 'life'
   -o name-of-output-file      file, where the last generation is saved
                               in the map-file format,
                               by default it is 'data/lastgens/map'
   --bmp                       with this non-argument option passed,
                               program creates bmp file
   --gif                       with this non-argument option passed,
                               program creates gif file

AUTHORS
   Jakub Maciejewski, Michal Ziober, Sebastian Gorka,
   students of Warsaw University of Technology.
   This program is JIMP2 coursework.
```

## Authors

Jakub Maciejewski, Michał Ziober, Sebastian Górka.

