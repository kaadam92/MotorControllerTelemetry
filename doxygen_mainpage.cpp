 /**
 * @mainpage
 * @tableofcontents
 *
 * @section Architektura Architektúra áttekintés
 *
 * Az alkalmazás feladata, hogy megjelenítse a TCP vagy soros kommunikáción keresztül érekző adatokat
 * illetve egy log fájlba elmentse azokat. A demonstrációs és tesztcélokat szolgáló szimulátort egy külön projektben valósítottuk meg.
 * Az alkalmazás az alábbi funkciókkal rendelkezik:
 *        - Az autóhoz a gombok segítségével lehet csatlkozni, illvet üzemkész állapotbe helyezni azt. A gombok alatt található slider
 *            segítségével sebesség alapjelet adhatunk a szimulázornak.
 *        - Az alkalmazás fő eleme a felül, jobb oldalt található megjelenítő rész. Itt három nézetet közül lehet váalsztani:
 *        
 *            -- A pillanatnyi paramétereket lehet megjeleníteni
 *            -- Grafikonon követhetjük a paraméterek alakulásást. (A sebesség alapjelét és a valós sebességét)
 *            -- A 12 cellás akkumlátor egyes cellefeszültségeinek alakulását követhetjük nyomon
 *            
 *        - Az alsó harmadban külnböző log üzeneteket olvashatunk.
 *
 *
 *
 * @section Usage A program használata
 *
 * Első lépésben mind a Simulator, mind a Telmetria szoftvert indítsuk el. Ezt követően a telemetria szoftverben a "Connenct" gomb seítségével
 * csatlakozhatunk a szimulátorhoz. Csatlakozás után a "Teszt" gomb segítségével elindíthatjuk az öntesztelő funkciót, melynek sikerességéről log üzenetek tájékoztatnak minket.
 * A "HV Enable" gomb segítségével engedélyezhetjük a nagyfeszültségű akkumlátor kimenetét. A sikeres állapotváltásta gomb zöldé válás jelzi. A "Drive Enable" gomb lenyomásával
 * engedélyezzük az ató hajtását. Ezen állapotban a slider segítségével adhatunk sebesség alapjelet.
 * 
 * @section buildup Az alkalmazás felépítése
 * 
 * Az alkalmazás felépítése az alábbi ábraán látható. A viszonylag kompakt méret tartása érdekében csak a saját osztályainkat ábárzoltuk, a Qt
 * osztályait nem.
 * 
 * ![](UML_main.png)
 * 
 * Az osztályok alapvetően három csoportra bonthatóak:
 * 		- Kommunikációval kapcsoaltos osztályok
 * 		- Adatfeldolgozással kapcsolatos osztályok
 * 		- Megjelenítéssel, grafikus felület menedzselésével kapcsolatos osztályok.
 *
 */
