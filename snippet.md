# A tapasztalatokat összefoglaló snippet házi beadáshoz

A fejlesztés során több akadályba, nehézségbe és furcsaságba is ütköztünk, ezeket hivatott összefoglalni ez a kis leírás.

## A Qt Creator sajátosságai

A Qt Creator bár egy elsőre igen purítán felületnek tűnik, egy meglehetősen jól átgondolt felületet ad a fejlesztéshez. Néhány anomália azonban itt is akad, bár ezek lehet nem általános jellegőek:

  * Amikor furcsa fordítási hiábt kapunk, nem értjük, ohgy miről szól, és rá kattintva memóriatartalom nyilik meg, akkor a megoldás jó eséllyel a kézi *qmake* futtatás lesz a megoldás
  * A QML fájlok nem mentődnek el automatikusan build-kor, erre jó eséllyel van beállítás, de elsőre furcsa lehet.
  * A QML-ben eszközölt módosítások nem mindig jelennek meg fordítás után az UI-on, ellenben ha a grafikus szerkesztővel egy kicsit bizgetünk a felületen, akkor már igen.
  * Ha több példányban futtatjuk a Qt Creatort, akkor csak az egyik ablak használhatja a debug konzolt

### QML-ben automatikusan generálódó függvénynevek

Amikor QML-ben létrehozunk egy modult, és azt példányosítjuk, akkor a modul signaljai megjelennek a felső rétegen is, pl a "valami" nevű signalból a példányosítás helyén lesz "onValami" nevű függvényhívás. Konrét példát találunk a SimpleTelemetryVisualiser-ben.

```javascript
    signal resetCommand;
    signal accelerateCommand;
    signal stopCommand;
```

Ezek a signalok jönnek létre a MainForm modlban, melyet a main.qml fájlban példányosítunk.

```javascript
    MainForm {
        id: mainFormControl
        anchors.fill: parent

        // Az eseménykezelőkben tovább hívjuk az itteni signalokat a C++ oldal felé.
        onResetCommand: {
            resetCpp();
        }
        onAccelerateCommand: {
            accelerateCommandCpp();
        }
        onStopCommand: {
            stopCommandCpp();
        }
    }
}
```

Itt pedig láthatóak a létrejövő függvényhívások a kész modulban. Érdekesség, hogy a modulban található signal első betűje automatikusan naggyá válzotik a függvényeknél, a többi karakter viszont case-sensitive, azaz a konkrét példát szemlélve, a *stopCommand* és a StopCommand* között nincs különbség, a *stopCommand* és a *stopcommand* viszont két különböző signal. Az, hogy ezek a függvénynevek, hogyan jönnek létre a signalokból, a szerzők előtt nem ismert, lézetésüket azonban tényként elfogadják.

### QML vs .ui

A Qt két gyökeresen eltérő módszerrel segíti grafikus felhasználói felületek gyors összeállítását. Az egyik az áltlaunk is tanult QML, mely javascript szerű leírással némi funkcionalitás megvalósításának is teret enged. Ez sok dolog elegáns megvalósítását biztosítja, hátrány azonban, hogy igen kevés előre gyártott elemből tudunk építkezni, nekünk kell megírni sok mindent. (Erre abszolút elemi példa, hogy nincsen pl. kör QML-ben, a megoldás az, hogy négyszöget csinál az amber, melynek a sarkai oldalhoszz/2 sugárral lekerekít.) Természetesen hatalmas potenciál van ebben a koncepcióban, azonban nagyon sok gyakorlást és rutint igényel, hogy az ember el tudja dönteni megfelelő módon, hogy mi az, amit QML-ben és mi az, amit C++-ban érdemes megvalósítani. A mi házi feladatunkban is valószínűleg sok olyan megoldás van, ami egy rutinos Qt programozó számára nevetségesen undorító, összetákolt munka, és tud rá sokkal elegánsabb és praktikusabb megoldást.

Ezzel szemben a .ui egyszerű, xml alapú leírást biztosít, a messziről induló kezdő Qt felhsználó számára jobban átlátható, és nem ró a két oldal közti szeparációs terheket a felhasználóra. Sokkal több beépített elemből válogathatunk, ezekt ráadásul C++-ból is könnyebb elérni.

Összegezve tehát azt mondanám, hogy nagyon jó a QML, de rutint igényel, ezzel szemben a *.ui* könnyebben átlátható első ránézésre , így kezdő felhsználók számára gyorsabb lehet.

### Library-k használata QML-ben

A legtöbb UI modul, melyet le tudunk tölteni internetről, a .ui stílusú leírást támogatja. Szerencsére ez nem akadályozza meg, hogy haszánljuk őket QML alatt is. Mi a [QCustomPlot](http://www.qcustomplot.com/index.php/introduction) nevű libraryt használtuk fel a a házi feladatunk során, amely nagyon igényes, lejes körő adatvizualizációt támogató csomag.

Ahhoz, hogy fel tudujuk használni QML-ben létre kell hoznunk egy a modul menedzselő C++ objektumot. Ezek után ezt az objektumot be kell regisztálni QML objektumként.

```c
qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
```

Ha ezzel is kész vagyunk, akkor már csak példányosítani kell QML oldalon.

```javascript
  CustomPlotItem {
      objectName: "customPlot"
      id: customPlot
      anchors.fill: parent
      Component.onCompleted: initCustomPlot()
      }
```

Innentől kezdve *customPlot* néven meg tudjuk találni C++ oldalról.

### Hogyan érjünk el QML objektumokat C++ oldalról?

Erre láthattunk példát a KontrolKupac mintaprojektben

```c
QQuickItem* MainWindowCppSide::findItemByName(const QString& name)
{
    Q_ASSERT(mainWindowObject != nullptr);
    if (mainWindowObject->objectName() == name)
    {
        return mainWindowObject;
    }
    return findItemByName(mainWindowObject->children(), name);
}

QQuickItem* MainWindowCppSide::findItemByName(QObject *rootObject, const QString& name)
{
    Q_ASSERT(rootObject != nullptr);
    if (rootObject->objectName() == name)
    {
        return (QQuickItem*)rootObject;
    }
    return findItemByName(rootObject->children(), name);
}

QQuickItem* MainWindowCppSide::findItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = findItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}
```

Ez meglehetősen hosszú, ráadásul saját magunknak megírni nem is feltétlennül kellemes. E helyett használhatunk beépített függvényt:

```c
 auto mainWindowPtr = rootObject->findChild<QObject*>("MainWindow");
 eventhandler.setMainWindowPtr(mainWindowPtr);
```

Ebben a kódrészletben használjuk a Qt által biztosított findChild függvényt, majd átadjuk az EventHandler osztályunknak a pointert az ablakra, hogy el tudjuk érni innen is a tartalmát.
## A szoftver futtatása más számítógépen
A fejlesztés utolsó fázisának nevezhető az ún. deployment, ami tulajdonképpen az elkészült szoftver használatra bocsájtása. Windows rendszeren ez annyit jelent, hogy a felhasználó számára biztosítjuk a futtatható bináris állományt (.exe) és az esetleges dinamikusan linkelt könyvtárakat (.dll).

### Dinamikus linkelés

Ez a módszer tűnik a legegyszerűbb megoldásnak: a release módon fordított alkalmazásunkhoz tartozó .exe fájlt kimásoljuk egy mappába és mellette elhelyezzük a szükséges .dll könyvtárakat. A kérdés csak az, hogy honnan lehet megtudni a szükséges fájlok listáját.

Első megközelítésben megpróbáljuk lefuttatni a programunkat a célrendszeren és a windows hibaüzenetek alapján levadásszuk a hiányolt .dll fájlt. Általában a "--QT DIR--\Qt5.5.1\5.5\mingw492_32\bin" mappában találhatóak. Ez a folyamat időigényes lehet, ha sok fájlt kell megtalálni, illetve a windows hibaüzenetek nem minden esetben írják ki a hiányzó fájl nevét, ekkor zsákutszába kerülünk, nem tudjuk mire lenne szükség.



### Statikus linkelés


Qt szoftverek esetén a felhasznált modulokt mennyiségétől függően viszonylag sok dll fájl szükséges a működéshez, ezért kíváncsiak voltunk, hogy van-e lehetőség egyetlen .exe fájlba, statikusan linkelni a könyvtárakat.


