# C++ Calculator Versie 1

Dit projectje zorgt er voor dat je eenvoudige rekenopdrachten kunt laten uitvoeren. Deze opdrachten voer je in
op de command-line na het starten van het programma. Denk aan:

* 1+1
* 3*5
* 6.3+2.7
* 100000/2
* 5-5

Let op

1. de invoer van getallen met een decimale component ('cijfers achter de komma' ) ingevoerd moeten worden met
   een punt als decimaal scheidingsteken (en dus niet een komma).
2. er wordt geen prompt gegeven ('voer een getal in') om het testen te vereenvoudigen (hierover later meer)

# Bouwen van het project

Deze CMakeLists.txt is bedoeld om een eenvoudig C++-project genaamd CppCalculator te configureren en te compileren.
Hieronder leggen we stap voor stap uit wat elk commando doet.

## Minimale CMake-versie

```text 
cmake_minimum_required(VERSION 3.30)
```

Dit geeft aan dat CMake versie 3.30 of hoger nodig is om dit project te kunnen bouwen. Als een oudere versie van CMake
wordt gebruikt, kan het zijn dat bepaalde functies niet werken.

## Projectnaam instellen

```text
   project(CppCalculator)
```

Hiermee wordt het project CppCalculator genoemd. Dit helpt bij het organiseren van de bestanden en instellingen binnen
CMake.

## C++-standaard instellen

```text
   set(CMAKE_CXX_STANDARD 20)
```

Dit vertelt de compiler om C++20 te gebruiken, wat nodig is als het project functies uit deze standaard gebruikt.

## Compiler- en linkeropties instellen

```text
   set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
```

Deze regel zorgen ervoor dat de gegenereerde uitvoerbare bestanden statisch worden gelinkt. Dit betekent dat de
standaard C++-bibliotheken worden opgenomen in het programma zelf, zodat het kan draaien op systemen zonder extra
afhankelijkheden. Doe je dit niet dan werkt het waarschijnlijk alleen in je IDE en wordt testen lastig.

## De uitvoerbare applicatie maken

```text
   add_executable(CppCalculator main.cpp)
```

Dit commando vertelt CMake om een uitvoerbaar bestand CppCalculator te maken uit het bronbestand main.cpp. Zorg ervoor
dat main.cpp zich in dezelfde map bevindt als deze CMakeLists.txt, anders moet je het juiste pad opgeven.

# Hoe compileer je dit project?

Als het goed is moet een moderne IDE je `CMakeLists.txt` herkennen en zorgen dat je vanuit je IDE kunt builden.

# Testen van het project

## Handmatig testen
Je kunt het programma uiteindelijk draaien in een terminal van de IDE of in een losse Powershell of cmd.exe command-prompt.

Na het opstarten kun je dus rekenopdrachten invoeren. Druk daarna op enter en je krijgt je antwoord. Bijvoorbeeld:
```text
1+1
1+1=2
```

Het *netjes* stoppen van het programma doe je door middel van de toetscombinatie voor EOT (*End of transmission*). Op 
Windows is dat `CTRL+Z` en op Mac/Linux is dat `CTRL+D`. Het programma krijgt dan de kans om zichzelf netjes af te sluiten
en resources vrij te geven. Dit in tegenstelling tot het gebruik van `CTRL+C` waarbij een SIGINT (Signal Interrupt) wordt
gestuurd en het programma in wezen afgebroken wordt. 

## Bulk testen

Je kunt ook meerdere berekeningen in een tekstbestand zetten en dat gebruiken om je programma te testen. We gebruiken
hiervoor *Input/Output redirection*.

```shell
 > cppcalculator < input.txt
 1+1
 1+1=2
 1+2
 1+2=3
 >
```
Etcetera.

We kunnen ook de output van deze test opvangen in een bestand.

```shell
 > cppcalculator < input.txt > output.txt
 > 
```

Als we van tevoren de output die we willen zien (op basis van de input) hebben vastgelegd in een bestand, dan kunnen we
eenvoudig de daadwerkelijke output vergelijken met de gewenste output. We definiëren een bestand `output-check.txt` 
en nemen daar de gewenste output in op. 

Bijvoorbeeld:

Het bestand `input.txt` bevat:

```text
1+1
2+2
4-4
5*5
```

Het bestand `output-check.txt` bevat 
```text
1+1=2
2+2=4
4-4=8
5*5=25
```

**Let op**: de output van het programma kan variëren afhankelijk van de instelling van `cout` met spaties en
decimale komma.

We starten het programma 

```shell
 > cppcalculator < input.txt > output.txt
 > 
```

Het bestand `output.txt` zou dan moeten bevatten:
```text
1+1=2
2+2=4
4-4=8
5*5=25
```

Daarna vergelijken we de inhoud van het bestand `output.txt` met `output-check.txt`. Dat kan bijvoorbeeld in je IDE, maar
ook dat is te automatiseren met het programma `fc` (Windows cmd) of `diff` (Mac/Linux). 

In het project zit een Powershell script dat deze zaken in één keer regelt. Daarnaast geeft het ook informatie over
de snelheid van het uitvoeren van alle berekeningen.

## Automatisch testen en conclusies trekken

Het bestand `run-test.ps1` bevat een set met Windows *Powershell* instructies om de calculator te testen met een input-file, de output
op te vangen en deze te vergelijken met een referentie output. 

```powershell
echo "Running tests"
$stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
Start-Process -FilePath .\cmake-build-release\CppCalculator -RedirectStandardInput "test-input.txt" -RedirectStandardOutput "test-output.txt" -NoNewWindow -Wait
$stopwatch.Stop()
$stopwatch.ElapsedMilliseconds

echo "Comparing output"
cmd /c fc /L test-output.txt test-output-check.txt > diff.txt
if ($?) {
    Write-Host "De bestanden zijn identiek."
    exit 0
} else {
    Write-Host "Er zijn verschillen gevonden!"
    exit 1
}
```

*Verklaring*

Het eerste gedeelte bevat het opzetten van een stopwatch om de doorlooptijd in milliseconden te kunnen meten. Door middel
van het Powershell commando `Start-Process` wordt het programma (`build release`!) opgestart. Er worden command line
parameters meegegeven om de input en output te sturen/op te vangen. 

Daarna wordt het programma `fc` gedraaid. Dit is een niet-powershell commando en daarom wordt het voorag gegaan door
`cmd /c` zodat het gestart wordt binnen `CMD.EXE`. De uitvoering van `fc` zorgt ervoor dat de exit-code op nul wordt
gezet als er geen verschillen zijn, of op niet-nul wordt gezet bij detectie van verschillen.

Het laatste deel (`if`-statement) rapporteert op basis van de vergelijking of er verschillen waren. ALs deze er zijn
dan kun je die nalezen in het bestand `diff.txt`.
