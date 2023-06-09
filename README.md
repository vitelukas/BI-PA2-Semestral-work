# BI-PA2-Semestral-work -- Pacman

Implementujte hru Pacman. Hlavní postava Pacman se snaží sesbírat všechny mince na herním plánu. Během toho se musí vyhýbat všem duchům, kteří se mu v tomto snaží zabránit. Pokud se hráči podaří sesbírat všechny mince, postupuje na další úroveň (jiný herní plán a/nebo obtížnost).

## Hra musí splňovat následující funkcionality:

* Hra musí dodržovat základní pravidla (př. nelze vykročit z mapy, …).
* Implementujte alespoň následující herní mechaniky:
  * mince (zvýší skóre),
  * třešně (umožní lovit duchy),
  * teleporty (umožní hráči se teleportovat z jednoho místa na jiné).
* Implementujte alespoň 3 různé druhy chování duchů (umělé inteligence). Druh chování musí jít nastavit pro každého ducha zvlášť.
* Stav hry musí být znázorněn vizuálně (př. pokud duchové jsou zranitelní, jsou reprezentováni jiným znakem nebo jsou jinak vykreslení, …).
* Hra musí být konfigurovatelná ze souboru:
  * lze načítat mapy (př. bludiště, startovní pozice duchů, druhy chování duchů, pozice bonusů, …)
  * definice obtížnosti (př. rychlost duchů, délka jednotlivých módů hry jako je lov duchů, pravděpodobnost na bonusy, …)
* Hra umožňuje zobrazovat tabulku nejlepších hráčů.

## Kde lze využít polymorfismus? (doporučené)

* druhy chování duchů: pronásledování, prchání, predikce pohybu, hlídkování v sektoru, …
* efekty bonusů: mince (body), třešnička (změna módu), srdíčko (život navíc), teleport (přemístění hráče), …
* mód hry: standardní (duchové chodí dle svých běžných strategií), zběsilý (duchové pronásledují hráče), nezranitelný (duchové jsou pomalejší, dají se zabít), …
* rozdělení postav na hracím plánu: hráč, duch
* uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), …

## Další informace:

* Není nutné implementovat přesnou kopii hry Pac Man, zamyslete se, jakým způsobem můžete základní požadavky rozšířit a udělat hru zajímavější. Nápady na rozšíření: náhodné generování bonusů nebo herních úrovní, nové druhy bonusů, klíče a dveře, zasazení do příběhu.
* Poznámka 29.4.2023: Není nutné implementovat hru real-time, hra může být i tahová.  
https://cs.wikipedia.org/wiki/Pac-Man  
http://programujte.com/clanek/2011010500-chovani-duchu-ve-hre-pac-man-cast-1/  
http://programujte.com/clanek/2011010900-chovani-duchu-ve-hre-pac-man-cast-2/  


## Specifikace

 Vytvoříme jednoduchou hru Pacman. Hra poběží v terminálovém rozhraní za pomocí knihovny *ncurses* a bude se ovládat pomocí vstupu z klávesnice, od klienta.

 Na začátku se program "přesune" z 'main' do třidy 'CMainMenu', která již bude umožňovat vizualizaci vstupu v výstupu a jakousi navigaci v programu.
 Po spuštění programu třída 'CMainMenu' hráči ukáže základní menu, které bude hráči umožňovat:
  * spustit novou hru
  * vybrat si obtížnost hry(z 3 možných variant):
      * easy - duchové chodí náhodně po mapě a hráče si nevšímají
      * medium - duchové pronásledují hráče
      * hard - duchové jsou rychlejší a mód *lov duchů* trvá kratší dobu
  * zobrazit tabulku nejlepších hráčů
      * ta bude uložena v souboru, do kterého se postupně budou přidávat jednotlivé záznamy, po dohrání hry hráčem
      * tabulka bude zpracovávaná pomocí třídy 'CLeaderBoard' 
  * ukončit hru

    Poté, co hráč samotnou hru spustí, se o hru bude starat třída 'CGame'. Ta načte herní mapu (reprezentovanou třídou 'CMap') a další entity, které se na mapě nachází (jako například Pacman, který reprezentuje hráčovu postavičku, duchové, body (== mince), reprezentované například tečkami/puntíky, které Pacman sbírá, a další). Mapa bude uložena v kofiguračním souboru a kterou si hráč bude moct upravit podle sebe. Mapa bude reprezentována pomocí ASCII znaků, které se v interpretované podobě budou zobrazovat v herním okně a budou tak tvořit mapu hry.

    "Živé objekty" budou ve hře implementovány v podobě třídy 'CEntity'. Z této třídy bude dědit třída 'CPlayer' a třídy pro duchy 'CGhost_1', 'CGhost_2' a 'CGhost_3'.

    Hra bude mít v podstatě stejné principy, jako klasický Pacman.
    * Cílem hry bude posbírat všechny body, které se na mapě nachází(čehož se docílí pohybem po mapě a následné kolizi Pacmana s těmito body).
    * Na mapě se také budou nacházet 2 teleporty, které může hráč využít pro přemístění po mapě a případně tak uniknout duchům.
    * V tom se Pacmanovi ale snaží zabránit duchové, kteří Pacmana po mapě pronásledují. Pokud dojde ke kolizi ducha a Pacmana, hráč ztrácí jeden život. 
    * Hráč má dohromady životy 3. Jestliže hráč ztratí všechny 3 životy, tak prohrál a hra pro  něj končí. Na konci hry hráč zadá své jméno, které se poté zapíše i s jeho aktuálním skóre do tabulky nejlepších hráčů.
    * Po dohrání hry se hráč opět vrátí do základního menu a vše jede od znova.

## Polymorfismus

   Polymorfismus bude ve hře využit například v chování jednotlivých duchů, kdy každý bude mít v základu podobné chování, ale u každého ze tří duchů se bude mírně lišit.
   * 1.duch bude náhodně chodit po mapě a nebude si všímat hráče
   * 2.duch bude hráče pronásledovat
   * 3.duch bude nějak zjednodušeně předvídat hráčův pohyb

   Polymorfismus využiji ale i v obecném pohybu entit po mapě, kdy každá entita se bude nějak pohybovat, takže bude de facto výchazet ze stejném třídy, ale způsob pohybu se bude lišit pro každou entitu. Pacman se bude   pohybovat pomocí vstupu od hráče a duchové se budou pohybovat pomocí žejednodušeného AI.

   Polymorfismus by se případně dal využít i v uživatelském rozhraní, ale upřímně si ještě zatím nejsem 100% jistý, jakým způsobem budu uživatelské rozhraní zpracovávat.
