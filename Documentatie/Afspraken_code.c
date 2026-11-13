// Ik weet overigens niet of elke @ hier ook een daadwerkelijk doxygen ding is...


// Sowieso een goed ding, alle lokale dingen gaan altijd in je .c bestand
// Alle niet-lokale dingen, zoals API functies voor laag 3, moeten we definiëren in het bijbehorende .h bestand
// Dus stel laag 2 wil functies aanroepen van laag 3, dan moet laag 3 alle functies die aan te roepen zijn in het .h bestand van laag 3 hebben staan
// In laag 2 heb je dan een #include ".h bestand van laag 3" nodig

/** ==================================================================================== */
/** @file Afspraken_code.c                                                               */
/** @author K.vijlbrief, A.Kamphuis of C.Fletcher                                        */
/** @date datum van wanneer je het bestand voor het laatst hebt aangepast                */
/** @version versiebeheer, moeten we misschien nog even wat over bedenken hoe dit moet   */
/**                                                                                      */
/** @brief Leg hier uit wat je code doet, en schrijf het kort op                         */
/** @attention kan er eventueel ook in                                                   */
/** ==================================================================================== */


// Volgorde van source opbouw, van boven naar beneden is:
// #include <library-header>
// #include "user-header"
// #define-statements
// externe variabelen (extern int page_nr;)
// globale variabelen
// User functies
// Main functie (moet altijd onderaan)


// Voor elke include, houd de volgende volgorde aan:
#include <Alle libraries die je gebruikt die globale dingen zijn, zoals math.h of wat dan ook>
#include "main.h" // Include in elk bestand altijd main.h hierin staan de debug defines en alles voor het gehele programma
#include "het .h bestand van dit .c bestand"

// Defines altijd lokaal doen als andere bestanden er niks mee gaan doen
// Als andere bestanden er wat mee gaan doen, stop dan de defines in een .h bestand
#define DEBUG_LAYER_1 1
#define DEBUG_LAYER_2 1
#define DEBUG_LAYER_3 1

// Alle variabelen en structnamen zijn altijd lowercase
int druif = 0;
int grape = 0;


// Dit is ongeveer hoe ver ik kom met een struct maken
typedef struct command_type
{
    char type[20];
    int x;
    char color[20];
} command;

// Alle functies beginnen altijd eerst met welke laag ze beginnen (Dus, API, naam voor laag 2, naam voor laag 1), daarna de functie en daarna het onderwerp, dus:
// De naam van de laag staat altijd in hoofdletters, de rest van de text staat in kleine letters

// Dit is dus voor text schrijven, wederom alle variabelen in lowercase
int API_draw_text (int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved);
// Dit is maybe een idee voor die switch case
int LAAG2_exec_functies(struct command *c);
// Dit is dan maybe een idee voor het ontvangen van de UART
int LAAG3_receive_char(int *uart_handle);



// Voorbeeld comment voor een functie, dit is een voorbeeld van een externe functie die laag 2 moet gebruiken, dus deze comment zou in een .h bestand belanden
/**
    @brief Schrijft text op het scherm via een aantal parameters
    @param x_lup de x positie waarop de text moet beginnen
    @param y_lup de y positie waarop de text moet beginnen
    @param color de kleur van de tekst die op het scherm getoond word
    @param text pointer naar de tekst die op het scherm moet laten zien worden
    @param fontname pointer naar de naam van het font dat getoond moet worden
    @param fontsize de grootte van het font/de text die getoond wordt
    @param fontstyle style van het gekozen font, dus bold, italic, etc.
    @param reserved reserved bit, wordt niet gebruikt
    @return de variabele err_code, 0 als de functie correct is uitgevoerd, iets anders als er een fout is opgetreden tijdens het uitvoeren
 */
int API_draw_text (int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved);


// Nog een dingetje, als er globale functies zijn, zoals basically alle API functies, dan is het het handigst als de doxygen documentatie in het .h bestand staat
// Als er puur interne functies zijn die andere lagen niet gebruiken, kan de doxygen documentatie gewoon in het bestand zelf