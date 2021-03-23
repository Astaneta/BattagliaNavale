#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creaCampoGioco(int matrice[10][10]);
void stampaCampoGiocoNemico(int matrice[10][10]);
void stampaCampoGiocoAlleato(int matrice[10][10]);
int numeroRandom10();
int numeroRandom2();
int numeroRandom4();
void creaNave(int matrice[10][10], int, int);
void richiediMossa(int matrice[10][10], int campo[10][10], int*);
void controlloVariabili(int, int, int*);
void creaNaviAlleate(int matrice[10][10], int, int);
void intelligenzaArtificiale(int [10][10], int*); // Parolone

int secondaNave = 0, terzaNave = 0, quartaNave = 0, quintaNave = 0;
const int MANCATO = 88;
const int COLPITO = 178;
const int ACQUA = 0;
const int NAVE1 = 97;
const int NAVE2 = 98;
const int NAVE3 = 99;
const int NAVE4 = 100;
const int NAVE5 = 101;

int main()
{
    srand(time(NULL));
    int i, j, inizio = numeroRandom2(), scelta; // Variabili di conteggio
    int naviAllAff = 0;
    int primaNave = 0;
    int end = 1; // Variabile per decidere quando il gioco è finito
    int livelloGioco[10][10] = {}; //Creo il campo da gioco e lo setto a zero
    int posizioneNaviNemiche[10][10] = {}; // Creo una matrice dove inserire le navi nemiche
    int posizioneNaviAlleate[10][10] = {}; // Creo una matrice dove inserire le navi alleate
    //int grigliaIA[10][10] = {};
    for ( i = 0; i < 10; i++) // Setto la matrice delle navi alleate a 95 (ossia vuota, come l'acqua) in modo da poterla poi riempire con le navi alleate
    {
        for (j = 0; j < 10; j++)
        {
            posizioneNaviAlleate[i][j] = ACQUA;
        }
    }
    for ( i = 0; i < 10; i++) // Setto la matrice delle navi nemiche a 95 (ossia vuota, come l'acqua) in modo da poterla poi riempire con le navi alleate
    {
        for (j = 0; j < 10; j++)
        {
            posizioneNaviNemiche[i][j] = ACQUA;
        }
    }
    creaCampoGioco(livelloGioco); // Si limita a settare la matrice con il numero 95 che indica l'acqua.
    creaNave(posizioneNaviNemiche, 5, NAVE1); // Ogni nave creata ha un numero unico (in terzo parametro) per identificarla e un numero che ne indica la lunghezza
    creaNave(posizioneNaviNemiche, 4, NAVE2);
    creaNave(posizioneNaviNemiche, 3, NAVE3);
    creaNave(posizioneNaviNemiche, 3, NAVE4);
    creaNave(posizioneNaviNemiche, 2, NAVE5);
    stampaCampoGiocoAlleato(posizioneNaviAlleate);
    creaNaviAlleate(posizioneNaviAlleate, 5, NAVE1);
    stampaCampoGiocoAlleato(posizioneNaviAlleate);
    creaNaviAlleate(posizioneNaviAlleate, 4, NAVE2);
    stampaCampoGiocoAlleato(posizioneNaviAlleate);
    creaNaviAlleate(posizioneNaviAlleate, 3, NAVE3);
    stampaCampoGiocoAlleato(posizioneNaviAlleate);
    creaNaviAlleate(posizioneNaviAlleate, 3, NAVE4);
    stampaCampoGiocoAlleato(posizioneNaviAlleate);
    creaNaviAlleate(posizioneNaviAlleate, 2, NAVE5);
    stampaCampoGiocoAlleato(posizioneNaviAlleate);
    printf("\n\n");

    printf("Per decidere chi inizia, scegli testa o croce\n");
    printf("1. Testa\n2. Croce\n");
    scanf("%d", &scelta);
    scelta -= 1;
    if (scelta == inizio)
    {
        printf("Inizia il giocatiore\n\n");
        do //Si inizializza il gioco
        {
            printf("\n\n\n\n\n\n\nNuovo turno!");
            printf("\n\n\n");
            stampaCampoGiocoNemico(livelloGioco);
            richiediMossa(posizioneNaviNemiche, livelloGioco, &primaNave);
            controlloVariabili(primaNave, naviAllAff, &end);
            if (end == 0)
            {
                break;
            }
            printf("\n\n");
            intelligenzaArtificiale(posizioneNaviAlleate, &naviAllAff);
            stampaCampoGiocoAlleato(posizioneNaviAlleate);
            controlloVariabili(primaNave, naviAllAff, &end);
        }while (end != 0);
    }
    else
    {
        printf("Inizia il computer\n\n");
        do //Si inizializza il gioco
        {
            printf("\n\n\n\n\n\n\nNuovo turno!");
            printf("\n\n\n");
            intelligenzaArtificiale(posizioneNaviAlleate, &naviAllAff);
            stampaCampoGiocoAlleato(posizioneNaviAlleate);
            controlloVariabili(primaNave, naviAllAff, &end);
            if (end == 0)
            {
                break;
            }
            printf("\n\n");
            stampaCampoGiocoNemico(livelloGioco);
            richiediMossa(posizioneNaviNemiche, livelloGioco, &primaNave);
            controlloVariabili(primaNave, naviAllAff, &end);
        }while (end != 0);
    }


    return 0;

}

void creaCampoGioco(int matrice[10][10]) // Tecnicamente il campo è stampato
{
    int i, j;
    for (i = 0; i < 10; i++)               //Inizializzo la matrice e la setto a 0
    {
        for (j = 0; j < 10; j++)
        {
            matrice[i][j] = ACQUA;
        }
    }
}

void stampaCampoGiocoNemico(int matrice[10][10])
{
    int i, j;
    printf("  \t");
    for (i = 1; i < 11; i++)
    {
        printf("%d\t", i);
    }
    printf("\n\n");
    for (i = 0; i < 10; i++)
    {
        printf("%2d\t", i+1);
        for (j = 0; j < 10; j++)
        {
            printf("%c\t", matrice[i][j]);
        }
        printf("\n\n");
    }
}

int numeroRandom10()
{
    return rand() % 10;
}

int numeroRandom2()
{
    return rand() % 2;
}

int numeroRandom4()
{
    return rand() % 4;
}
void creaNave(int matrice[10][10], int n, int m)
{
    int i, j, k = 1;
    int check = 0, direzione = numeroRandom2();
    int libOri = 0;
    do
    {
        i = numeroRandom10();
        j = numeroRandom10();
        if (matrice[i][j] == ACQUA)
        {
            if (direzione == 0)
            {
                for (k = 0; k < n; k++)
                {
                    if (j + n > 10 || matrice[i][j+k] != ACQUA)
                    {
                        libOri = 1;
                    }
                }
                if (libOri == 0)
                {
                    for (k = 0; k < n; k++)
                    {
                        matrice[i][j+k] = m;
                        check = 1;
                    }
                }
                else if (libOri == 1)
                {
                    for (k = 0; k < n; k++)
                    {
                        if(j - n < 0 || matrice[i][j-k] != ACQUA)
                        {
                            libOri = 2;
                        }
                    }
                    if (libOri == 1)
                    {
                        for (k = 0; k < n; k++)
                        {
                            matrice[i][j-k] = m;
                            check = 1;
                        }
                    }
                }
            }

            if (direzione == 1)
            {
                for (k = 0; k < n; k++)
                {
                    if (i + n > 10 || matrice[i+k][j] != ACQUA)
                    {
                        libOri = 1;
                    }
                }
                if (libOri == 0)
                {
                    for (k = 0; k < n; k++)
                    {
                        matrice[i+k][j] =m;
                        check = 1;
                    }
                }
                else if (libOri == 1)
                {
                    for (k = 0; k < n; k++)
                    {
                        if(i - n < 0 || matrice[i-k][j] != ACQUA)
                        {
                            libOri = 2;
                        }
                    }
                    if (libOri == 1)
                    {
                        for (k = 0; k < n; k++)
                        {
                            matrice[i-k][j] = m;
                            check = 1;
                        }
                    }
                }
            }
        }

    } while (check == 0);
}

void richiediMossa(int matrice[10][10], int campo[10][10], int *primaNave)
{
    int i, j, check = 0;
    int end = 0;
    do
    {
        printf("\nInserisci le coordinate dove vuoi colpire, con numeri INTERI da 1 a 10");
        do
        {
            printf("\nInserisci la riga: ");
            scanf("%d", &i);
            if (i >= 1 && i <= 10)
            {
                check = 1;
            }
            else
            {
                printf("Il valore non e' compreso fra 1 e 10");
                check = 0;
            }
        } while (check == 0);
        do
        {
            printf("Inserisci ora la colonna: ");
            scanf("%d", &j);
             if (j >= 1 && j <= 10)
            {
                check = 1;
            }
            else
            {
                printf("Il valore non e' compreso fra 1 e 10\n");
                check = 0;
            }
        } while (check == 0);

        if (matrice[i-1][j-1] != ACQUA && matrice[i-1][j-1] != COLPITO && matrice[i-1][j-1] != MANCATO)
        {
            if (matrice[i-1][j-1] == NAVE1)
            {
                *primaNave += 1;
            }
            else if (matrice[i-1][j-1] == NAVE2)
            {
                secondaNave++;
            }
            else if (matrice[i-1][j-1] == NAVE3)
            {
                terzaNave++;
            }
            else if (matrice[i-1][j-1] == NAVE4)
            {
                quartaNave++;
            }
            else if (matrice[i-1][j-1] == NAVE5)
            {
                quintaNave++;
            }
            printf("\nHai colpito la nave!\n");
            campo[i-1][j-1] = COLPITO;
            matrice[i-1][j-1] = COLPITO;
            end = 1;
        }
        else if(matrice[i-1][j-1] == COLPITO || matrice[i-1][j-1] == MANCATO)
        {
            printf("\nArtigliere, cosa combini? Hai già sparato a queste coordinate! Non puoi sparare di nuovo\n\n");
        }
        else if(matrice[i-1][j-1] == ACQUA)
        {
            printf("\nArtigliere, aggiusta la mira. Hai colpito l'acqua\n\n");
            campo[i-1][j-1] = MANCATO;
            matrice[i-1][j-1] = MANCATO;
            end = 1;
        }
    }while (end == 0);
}

void controlloVariabili(int primaNave, int aff, int *end)
{
    static int naviNemAff = 0;
    int primaNaveAff = 0, secondaNaveAff = 0, terzaNaveAff = 0, quartaNaveAff = 0, quintaNaveAff = 0;
    if (primaNave == 5)
    {
        primaNaveAff = 1;
        naviNemAff += 1;
        primaNave = 0;
    }
    if (secondaNave == 4)
    {
        secondaNaveAff = 1;
        naviNemAff += 1;
        secondaNave = 0;
    }
    if (terzaNave == 3)
    {
        terzaNaveAff = 1;
        naviNemAff += 1;
        terzaNave = 0;
    }
    if (quartaNave == 3)
    {
        quartaNaveAff = 1;
        naviNemAff += 1;
        quartaNave = 0;
    }
    if (quintaNave == 2)
    {
        quintaNaveAff = 1;
        naviNemAff += 1;
        quintaNave = 0;
    }
    if (primaNaveAff == 1)
    {
        printf("\Hai affondato la nave da 5\n");
    }
    if (secondaNaveAff == 1)
    {
        printf("\Hai affondato la nave da 4\n");
    }
    if (terzaNaveAff == 1)
    {
        printf("\Hai affondato la nave da 3\n");
    }
    if (quartaNaveAff == 1)
    {
        printf("\Hai affondato la nave da 3\n");
    }
    if (quintaNaveAff == 1)
    {
        printf("\Hai affondato la nave da 2\n");
    }
    if (aff >= 1 && aff <= 5)
    {
        printf("\nIl nemico ha affondato %d navi\n", aff);
        if (aff == 5)
        {
            printf("\n\n\nHai perso!!!");
            *end = 0;
        }
    }
    else if (naviNemAff == 5)
    {
        printf("\nHai affondato tutte le navi nemiche. Hai vinto!");
        *end = 0;
    }
}

void creaNaviAlleate(int matrice[10][10], int n, int m)
{
    int x, y; //Creo gli assi con le variabili da inserire per posizionare le navi
    int direzione, i; // Indica la direzione, orizzontale o verticale
    int libero; // Variabile per verificare se una nave può essere inserita in tale direzione
    printf("Devi posizionare le navi. Al momento stai posizionando la nave da %d posti\n", n); // n identifica la lunghezza della nave
    do
    {
        libero = 1; // Setto la variabile ad 1, in modo che verrà ricaricata nel caso il ciclo do riparta
        printf("Inserisci la coordinata x di dove vuoi inserirla: ");
        scanf("%d", &x);
        while (x < 1 || x > 10)
        {
            printf("Il valore inserito non e' compreso fra 1 e 10. Inseriscilo di nuovo: ");
            scanf("%d", &x);
        }
        x--;
        printf("Inserisci la coordinata y di dove vuoi inserirla: ");
        scanf("%d", &y);
        while (y < 1 || y > 10)
        {
            printf("Il valore inserito non e' compreso fra 1 e 10. Inseriscilo di nuovo: ");
            scanf("%d", &y);
        }
        y--;
        if (matrice[x][y] == ACQUA)
        {
            printf("Scegli se posizionare la nave in orizzontale o in verticale\n");
            printf("1. Orizzontale\n2. Verticale\n");
            scanf("%d", &direzione);
            while (direzione != 1 && direzione != 2)
            {
                    printf("La scelta non e' valida. Inserirla di nuovo: ");
                    scanf("%d", &direzione);
            }

            if(direzione == 1)
                {
                    for (i = 0; i < n; i++)
                    {
                        if (y+i > 9 || matrice[x][y+i] != ACQUA)
                        {
                            libero = 0;
                        }
                    }
                    if (libero == 1)
                    {
                        for (i = 0; i < n; i++)
                        {
                            matrice[x][y+i] = m;
                        }
                        printf("Nave creata con successo\n");
                    }
                    else
                    {
                        printf("La nave non puo' essere inserita in orizzontale in queste coordinate\n");
                    }
                }
            else
            {
                for (i = 0; i < n; i++)
                    {
                        if (x+i > 9 || matrice[x+i][y] != ACQUA)
                        {
                            libero = 0;
                        }
                    }
                    if (libero == 1)
                    {
                        for (i = 0; i < n; i++)
                        {
                            matrice[x+i][y] = m;
                        }
                        printf("Nave creata con successo\n");
                    }
                    else
                    {
                        printf("La nave non puo' essere inserita in orizzontale in queste coordinate\n");
                    }
            }
        }
        else if(matrice[x][y] != ACQUA)
        {
            printf("\nLa casella gia' e' occupata. Selezionarne un'altra\n");
        }
    } while (matrice[x][y] != m);

}

void stampaCampoGiocoAlleato(int matrice[10][10])
{
    int i, j;
    printf("  \t");
    for (i = 1; i < 11; i++)
    {
        printf("%d\t", i);
    }
    printf("\n\n");
    for (i = 0; i < 10; i++)
    {
        printf("%2d\t", i+1);
        for (j = 0; j < 10; j++)
        {
            printf("%c\t", matrice[i][j]);
        }
        printf("\n\n");
    }
}

void intelligenzaArtificiale(int matrice[10][10], int* aff)
{
    int x, y, check = 0;
    static int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5; // Coordinate delle singole nave;
    static int navePrima = 0, naveSeconda = 0, naveTerza = 0, naveQuarta = 0, naveQuinta = 0;
    static int affondata = 0;
    static int i = 0;
    static int j = 0;
    static int k = 1;
    static int ultimaMossa = 0; // Setto l'ultima mossa come "neutro"
    static int ripetutaAlto = 0, ripetutaBasso = 0, ripetutaSinistra = 0, ripetutaDestra = 0;
    static int direzione, invertire = 0;
    do
    {
        x = numeroRandom10();
        y = numeroRandom10();
        //x = 4;
        //y = 5;
        if (ultimaMossa == 0) // If dove l'ultimo colpo è andato a vuoto
        {
            if (matrice[x][y] == ACQUA)
            {
                matrice[x][y] = MANCATO;
                ultimaMossa = 0;
                check = 1;
            }
            else if (matrice[x][y] == NAVE1 || matrice[x][y] == NAVE2 || matrice[x][y] == NAVE3 || matrice[x][y] == NAVE4 || matrice[x][y] == NAVE5)
            {
                i = x;
                j = y;
                if (matrice[x][y] == NAVE1)
                {
                    navePrima += 1;
                    if (navePrima == 1)
                    {
                        x1 = i;
                        y1 = j;
                    }
                    else if (navePrima == 5)
                    {
                        affondata = 1;
                        *aff += 1;
                        navePrima = 0;
                    }
                }
                else if (matrice[x][y] == NAVE2)
                {
                    naveSeconda += 1;
                    if (naveSeconda == 1)
                    {
                        x2 = i;
                        y2 = j;
                    }
                    else if (naveSeconda == 4)
                    {
                        affondata = 1;
                        *aff += 1;
                        naveSeconda = 0;
                    }
                }
                else if (matrice[x][y] == NAVE3)
                {
                    naveTerza += 1;
                    if (naveTerza == 1)
                    {
                        x3 = i;
                        y3 = j;
                    }
                    else if (naveTerza == 3)
                    {
                        affondata = 1;
                        *aff += 1;
                        naveTerza = 0;
                    }
                }
                else if (matrice[x][y] == NAVE4)
                {
                    naveQuarta += 1;
                    if (naveQuarta == 1)
                    {
                        x4 = i;
                        y4 = j;
                    }
                    else if (naveQuarta == 3)
                    {
                        affondata = 1;
                        *aff += 1;
                        naveQuarta = 0;
                    }
                }
                else if (matrice[x][y] == NAVE5)
                {
                    naveQuinta += 1;
                    if (naveQuinta == 1)
                    {
                        x5 = i;
                        y5 = j;
                    }
                    else if (naveQuinta == 2)
                    {
                        affondata = 1;
                        *aff += 1;
                        naveQuinta = 0;
                    }
                }
                matrice[x][y] = COLPITO;
                ultimaMossa = 1;
                direzione = 0;
                check = 1;
            }
        }
        else if (ultimaMossa == 1)
        {
            //0. In basso
            //1. In alto
            //2. A sinistra
            //3. A destra
            if (direzione == 0)
            {
                if (invertire == 0) // Se sta andando verso l'alto per la prima volta
                {
                    if (i-k < 0 || matrice[i-k][j] == COLPITO || matrice[i-k][j] == MANCATO) // Primo caso. Sono al bordo griglia od ho già colpito in tali diagonali
                    {
                        invertire = 1;
                        k = 1; // k viene riportato al numero base. Non c'è il check perché non ho potuto colpire, quindi l'if riparte di nuovo
                    }
                    else if (matrice[i-k][j] != ACQUA && matrice[i-k][j] != COLPITO && matrice[i-k][j] != MANCATO) // Sono andato in alto e ho colpito
                    {
                        if (matrice[i-k][j] == NAVE1)
                        {
                            navePrima += 1;
                            if (navePrima == 1)
                            {
                                x1 = i-k;
                                y1 = j;
                            }
                            else if (navePrima == 5)
                            {
                                affondata = 1;
                                *aff += 1;
                                navePrima = 0;
                            }
                        }
                        else if (matrice[i-k][j] == NAVE2)
                        {
                            naveSeconda += 1;
                            if (naveSeconda == 1)
                            {
                                x2 = i-k;
                                y2 = j;
                            }
                            else if (naveSeconda == 4)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveSeconda = 0;
                            }
                        }
                        else if (matrice[i-k][j] == NAVE3)
                        {
                            naveTerza += 1;
                            if (naveTerza == 1)
                            {
                                x3 = i-k;
                                y3 = j;
                            }
                            else if (naveTerza == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveTerza = 0;
                            }
                        }
                        else if (matrice[i-k][j] == NAVE4)
                        {
                            naveQuarta += 1;
                            if (naveQuarta == 1)
                            {
                                x4 = i-k;
                                y4 = j;
                            }
                            else if (naveQuarta == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuarta = 0;
                            }
                        }
                        else if (matrice[i-k][j] == NAVE5)
                        {
                            naveQuinta += 1;
                            if (naveQuinta == 1)
                            {
                                x5 = i-k;
                                y5 = j;
                            }
                            else if (naveQuinta == 2)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuinta = 0;
                            }
                        }
                        matrice[i-k][j] = COLPITO;
                        k++;
                        if (affondata == 1)
                        {
                            if (navePrima != 5 && navePrima != 0)
                            {
                                i = x1;
                                j = y1;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveSeconda != 4 && naveSeconda != 0)
                            {
                                i = x2;
                                j = y2;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveTerza != 3 && naveTerza != 0)
                            {
                                i = x3;
                                j = y3;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuarta != 3 && naveQuarta != 0)
                            {
                                i = x4;
                                j = y4;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuinta != 2 && naveQuinta != 0)
                            {
                                i = x5;
                                j = y5;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else
                            {
                                ultimaMossa = 0;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                        }
                        check = 1;

                    }
                    else if (matrice[i-k][j] == ACQUA)
                    {
                        matrice[i-k][j] = MANCATO;
                        invertire = 1;
                        k = 1;
                        check = 1;
                    }
                }
                else if (invertire == 1) // Prima alto, poi basso
                {
                    if (i+k >= 10 || matrice[i+k][j] == COLPITO || matrice[i+k][j] == MANCATO)
                    {
                        invertire = 2;
                        k = 1;
                    }
                    else if (matrice[i+k][j] != ACQUA && matrice[i+k][j] != COLPITO && matrice[i+k][j] != MANCATO)
                    {
                        if (matrice[i+k][j] == NAVE1)
                        {
                            navePrima += 1;
                            if (navePrima == 1)
                            {
                                x1 = i+k;
                                y1 = j;
                            }
                            else if (navePrima == 5)
                            {
                                affondata = 1;
                                *aff += 1;
                                navePrima = 0;
                            }
                        }
                        else if (matrice[i+k][j] == NAVE2)
                        {
                            naveSeconda += 1;
                            if (naveSeconda == 1)
                            {
                                x2 = i+k;
                                y2 = j;
                            }
                            else if (naveSeconda == 4)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveSeconda = 0;
                            }
                        }
                        else if (matrice[i+k][j] == NAVE3)
                        {
                            naveTerza += 1;
                            if (naveTerza == 1)
                            {
                                x3 = i+k;
                                y3 = j;
                            }
                            else if (naveTerza == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveTerza = 0;
                            }
                        }
                        else if (matrice[i+k][j] == NAVE4)
                        {
                            naveQuarta += 1;
                            if (naveQuarta == 1)
                            {
                                x4 = i+k;
                                y4 = j;
                            }
                            else if (naveQuarta == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuarta = 0;
                            }
                        }
                        else if (matrice[i+k][j] == NAVE5)
                        {
                            naveQuinta += 1;
                            if (naveQuinta == 1)
                            {
                                x5 = i+k;
                                y5 = j;
                            }
                            else if (naveQuinta == 2)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuinta = 0;
                            }
                        }
                        matrice[i+k][j] = COLPITO;
                        k++;
                        if (affondata == 1)
                        {
                            if (navePrima != 5 && navePrima != 0)
                            {
                                i = x1;
                                j = y1;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveSeconda != 4 && naveSeconda != 0)
                            {
                                i = x2;
                                j = y2;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveTerza != 3 && naveTerza != 0)
                            {
                                i = x3;
                                j = y3;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuarta != 3 && naveQuarta != 0)
                            {
                                i = x4;
                                j = y4;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuinta != 2 && naveQuinta != 0)
                            {
                                i = x5;
                                j = y5;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else
                            {
                                ultimaMossa = 0;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                        }
                        check = 1;
                    }


                    else if (matrice[i+k][j] == ACQUA)
                    {
                        matrice[i+k][j] = MANCATO;
                        invertire = 2;
                        k = 1;
                        check = 1;
                    }

                }
                else if (invertire == 2) // Prima alto, dopo in basso, poi destra
                {
                    if (j+k >= 10 || matrice[i][j+k] == COLPITO || matrice[i][j+k] == MANCATO)
                    {
                        invertire = 3;
                        k = 1;
                    }
                    else if (matrice[i][j+k] != ACQUA && matrice[i][j+k] != COLPITO && matrice[i][j+k] != MANCATO)
                    {
                        if (matrice[i][j+k] == NAVE1)
                        {
                            navePrima += 1;
                            if (navePrima == 1)
                            {
                                x1 = i;
                                y1 = j+k;
                            }
                            else if (navePrima == 5)
                            {
                                affondata = 1;
                                *aff += 1;
                                navePrima = 0;
                            }
                        }
                        else if (matrice[i][j+k] == NAVE2)
                        {
                            naveSeconda += 1;
                            if (naveSeconda == 1)
                            {
                                x2 = i;
                                y2 = j+k;
                            }
                            else if (naveSeconda == 4)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveSeconda = 0;
                            }
                        }
                        else if (matrice[i][j+k] == NAVE3)
                        {
                            naveTerza += 1;
                            if (naveTerza == 1)
                            {
                                x3 = i;
                                y3 = j+k;
                            }
                            else if (naveTerza == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveTerza = 0;
                            }
                        }
                        else if (matrice[i][j+k] == NAVE4)
                        {
                            naveQuarta += 1;
                            if (naveQuarta == 1)
                            {
                                x4 = i;
                                y4 = j+k;
                            }
                            else if (naveQuarta == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuarta = 0;
                            }
                        }
                        else if (matrice[i][j+k] == NAVE5)
                        {
                            naveQuinta += 1;
                            if (naveQuinta == 1)
                            {
                                x5 = i;
                                y5 = j+k;
                            }
                            else if (naveQuinta == 2)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuinta = 0;
                            }
                        }
                        matrice[i][j+k] = COLPITO;
                        k++;
                        if (affondata == 1)
                        {
                            if (navePrima != 5 && navePrima != 0)
                            {
                                i = x1;
                                j = y1;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveSeconda != 4 && naveSeconda != 0)
                            {
                                i = x2;
                                j = y2;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveTerza != 3 && naveTerza != 0)
                            {
                                i = x3;
                                j = y3;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuarta != 3 && naveQuarta != 0)
                            {
                                i = x4;
                                j = y4;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuinta != 2 && naveQuinta != 0)
                            {
                                i = x5;
                                j = y5;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else
                            {
                                ultimaMossa = 0;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                        }
                        check = 1;
                    }


                    else if (matrice[i][j+k] == ACQUA)
                    {
                        matrice[i][j+k] = MANCATO;
                        invertire = 3;
                        k = 1;
                        check = 1;
                    }
                }
                else if (invertire == 3) // Prima in alto, dopo in basso, dopo a destra e ora a sinistra
                {
                    if (j-k < 0 || matrice[i][j-k] == COLPITO || matrice[i][j-k] == MANCATO)
                    {
                        invertire = 0;
                        ultimaMossa = 0;
                        direzione = 0;
                    }
                    else if (matrice[i][j-k] != ACQUA && matrice[i][j-k] != COLPITO && matrice[i][j-k] != MANCATO)
                    {
                        if (matrice[i][j-k] == NAVE1)
                        {
                            navePrima += 1;
                            if (navePrima == 1)
                            {
                                x1 = i;
                                y1 = j-k;
                            }
                            else if (navePrima == 5)
                            {
                                affondata = 1;
                                *aff += 1;
                                navePrima = 0;
                            }
                        }
                        else if (matrice[i][j-k] == NAVE2)
                        {
                            naveSeconda += 1;
                            if (naveSeconda == 1)
                            {
                                x2 = i;
                                y2 = j-k;
                            }
                            else if (naveSeconda == 4)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveSeconda = 0;
                            }
                        }
                        else if (matrice[i][j-k] == NAVE3)
                        {
                            naveTerza += 1;
                            if (naveTerza == 1)
                            {
                                x3 = i;
                                y3 = j-k;
                            }
                            else if (naveTerza == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveTerza = 0;
                            }
                        }
                        else if (matrice[i][j-k] == NAVE4)
                        {
                            naveQuarta += 1;
                            if (naveQuarta == 1)
                            {
                                x4 = i;
                                y4 = j-k;
                            }
                            else if (naveQuarta == 3)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuarta = 0;
                            }
                        }
                        else if (matrice[i][j-k] == NAVE5)
                        {
                            naveQuinta += 1;
                            if (naveQuinta == 1)
                            {
                                x5 = i;
                                y5 = j-k;
                            }
                            else if (naveQuinta == 2)
                            {
                                affondata = 1;
                                *aff += 1;
                                naveQuinta = 0;
                            }
                        }
                        matrice[i][j-k] = COLPITO;
                        k++;
                        if (affondata == 1)
                        {
                            if (navePrima != 5 && navePrima != 0)
                            {
                                i = x1;
                                j = y1;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveSeconda != 4 && naveSeconda != 0)
                            {
                                i = x2;
                                j = y2;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveTerza != 3 && naveTerza != 0)
                            {
                                i = x3;
                                j = y3;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuarta != 3 && naveQuarta != 0)
                            {
                                i = x4;
                                j = y4;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else if (naveQuinta != 2 && naveQuinta != 0)
                            {
                                i = x5;
                                j = y5;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                            else
                            {
                                ultimaMossa = 0;
                                invertire = 0;
                                affondata = 0;
                                k = 1;
                            }
                        }
                        check = 1;
                    }


                    else if (matrice[i][j-k] == ACQUA)
                    {
                        matrice[i][j-k] = MANCATO;
                        invertire = 0;
                        ultimaMossa = 0;
                        direzione = 0;
                        k = 1;
                        check = 1;
                    }
                }
            }
        }
    }while (check == 0);
}
