# Chess

## Működés:

A program, futtatásakor megérdezi hogy szeretnénk-e tesztett futtatni.
Amennyiben igen az '1' karaktert kell beírni. Ilyenkor minden koordinátára leteszteli az algoritmust.

Ha viszont egy adott kezdőpozícióra vagyunk kiváncsiak akkor a '0' karatert kell beírni. Ezt követően meg kell adni a kezdő poziciót(a számozás 1-el kezdődik)
a következő formában:"x y".
Pl.:5 7

## Függvények:

### int validate(int x,int y,int table)

  - A validate függvénynek át kell adni  x és y értékeket valamint a tábla egy adott pontját.
  - A függvény leellenörzi hogy x és y kissebek-e 8-nál.Ezen felül leelenörzi hogy a tábla adott pontján jártunk-e már

### int test(int all_steps[63][10][2],int k);

  - A test függvénynek át kell adni egy 3 dimenziós tömböt valamint egy integert.
  - Az integer azt jelzi hogy hányadik teszt fut le.
  - Az all_steps minden érintet koordinátát tartalmaz és leteszteli hogy mindegyik csak egyszer szerepel-e

### int show_board(int table[8][8],int x, int y);

  - A kiírja a tömbot
  - A jelenlegi poziciót pirossal jelöli

### int solve(int table[8][8],int moves[8][2],int temp_cor[8][2],int all_steps[63][10][2],int x,int y,int t);

  - Megoldja a feladatot
  - Megértéséhez olvassa el az "Algoritmus működése" részt

## Algoritmus működése:

Egy 2d tömbként ábrázolom a sakk táblát. '0'-val jelölöm azokat helyeket ahol még nem jártam. Ahova beléptem azt a mezőt átírom az adott kör számára, így
jól követhetó hogy melyik körben hova lépett.

Egy másik tömbön belül tároljuk a lépéseket amelyek szabályosak

Minden körben megállapítjuk hogy melyek lehetnek a következő lépések. Ezeket a "temp_cor" tömbben tároljuk.
Ezt követően megnézzük hogy ezekről a helyekről hova lehetne tovább lépni és ezt megszámoljuk a legkissebeket pedig eltároljuk.
A következő körben pedig a legkissebek közül az elsőt kiválasztjuk és odalépünk. 

Amennyiben nem lehet tovább lépni abban az esetben visszakeresükk azt a korábbi koordinátát ahol több lehetséges irányt tudtunk volna választani.
Mivel korábban az első minimumot választottuk most a soron következőt fogjuk. Innen pedig tovább fut a program az eddigiek alapján.

