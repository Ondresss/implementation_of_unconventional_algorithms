# REAME CZ
Požadavky a závislosti

Pro sestavení projektu potřebujete:

    Kompilátor: GCC 14+ nebo Clang (podpora standardu C++26)

    Sestavovací systém: CMake 3.20+

    Knihovny:

        Armadillo (Lineární algebra)

        mlpack (Strojové učení)

        raylib (Grafika a vstup)

Instalace závislostí (Debian/Ubuntu/Kali)
Bash

sudo apt update
sudo apt install cmake g++ libarmadillo-dev libmlpack-dev libraylib-dev

Kompilace a spuštění

Projekt využívá CMake pro snadnou konfiguraci. Sestavení provedete následovně:
Bash

# 1. Vytvoření sestavovacího adresáře
mkdir build && cd build

# 2. Konfigurace projektu
cmake ..

# 3. Kompilace
make

# 4. Spuštění programu
./PoleBalancingProblem
Technické detaily
CMake Konfigurace

Projekt je v základu nastaven s AddressSanitizerem (-fsanitize=address), který pomáhá odhalovat chyby při práci s pamětí (vhodné pro vývoj).
CMake

target_compile_options(PoleBalancingProblem PRIVATE -fsanitize=address -fsanitize=undefined)

Struktura kódu

    Agent.cpp/h: Jádro AI. Obsahuje Q-tabulku a architekturu neuronové sítě (mlpack::FFN).

    PoleBalancingProblem.cpp/h: Fyzikální model CartPole a integrační smyčka pro raylib.

    Discretizer.h: Logika pro převod spojitých hodnot (pozice, úhel) na indexy v Q-tabulce.

    main.cpp: Hlavní řídicí logika (přepínání mezi tréninkem a vizualizací).

Parametry simulace

    Limit úhlu: ±12∘ (cca 0.21 rad)

    Limit pozice: ±2.4 metrů

    Akce: Vlevo (Backward) / Vpravo (Forward)


sudo apt update
sudo apt install cmake g++ libarmadillo-dev libmlpack-dev libraylib-dev

2. Manuální instalace (Git Clone)

Raylib
Bash

git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=OFF
make
sudo make install

Armadillo (vyžaduje cmake a LAPACK/BLAS)
Bash

sudo apt install liblapack-dev libblas-dev
git clone https://gitlab.com/conradsnicta/armadillo-code.git armadillo
cd armadillo
mkdir build && cd build
cmake ..
make
sudo make install

mlpack
Bash

git clone https://github.com/mlpack/mlpack.git mlpack
cd mlpack
mkdir build && cd build
cmake .. -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_TESTS=OFF
make
sudo make install

Kompilace Projektu

Jakmile máš závislosti nainstalované, sestav samotnou aplikaci:

    Stáhni projekt:
    Bash

git clone <url-tveho-projektu>
cd PoleBalancingProblem

Sestav projekt:
Bash

mkdir build && cd build
cmake ..
make

