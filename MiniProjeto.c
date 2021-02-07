#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// tamanho do array
#define MAX 25
// sem mina
#define EMPTY '_'
// mina armada
#define ARMED '.'
// mina desarmada
#define DISARMED '*'

void menu();
void choices(char game[][MAX]);
void readFile(char filename[200], char game[][MAX]);
void writeFile(char filenameout[200], char game[][MAX]);
void logFunc(char game[][MAX], int x, int y, int time, int logPos[625], int logCount);
void trigger(char game[][MAX], int x, int y, int logPos[100], int logCount, int count, int xdim, int ydim);
void saveLog(int x, int y, int _logPos[], int _logCount, int time);
void saveTrigger(int x, int y, int _logPos[], int _logCount);

// Main
int main()
{
    char map[MAX][MAX];
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            map[i][j] = EMPTY;
        }
    }
    menu();
    choices(map);
}

/// Imprime o menu
void menu()
{
    puts("+-----------------------------------------------------");
    puts("read <filename> - read input file");
    puts("show - show the mine map");
    puts("trigger <x> <y> - trigger mine at <x> <y>");
    puts("log <x> <y> - trigger mine at <x> <y>");
    puts("plant <x> <y> - place armed mine at <x> <y>");
    puts("export <filename> - save file with current map");
    puts("quit                - exit program");
    puts("sos - show menu");
    puts("+-----------------------------------------------------");
}

// Verifica a escolha do utilizador
void choices(char game[][MAX])
{
    int i = 1;
    // nome da escolha
    char choice[20];
    // nome do ficheiro
    char filename[200];
    // nome do ficheiro para fazer export
    char filenameout[200];
    // lista de posições para rebentar
    int logPos[100];
    // variavel de ajuda para opção show
    int count = 0;
    // Tempo de Explosão
    int time = 0;
    int checkRead = 0;

    int xdim, ydim;

    do
    {
        printf(">");
        // verifica a escolha do menu
        if (scanf("\n%s", choice))
        {
            // lê a escolha e o path do ficheiro
            if (strcmp(choice, "read") == 0)
            {
                if (scanf("%s", filename))
                {
                    checkRead = 1;
                    char ch;
                    // Variavel que recebe a posição x
                    int chx;
                    int hasx;
                    // Variavel que recebe a posição y
                    int chy;
                    int hasy;
                    // Variaveis que vão receber as posições do array
                    int currentNum;
                    int turn;
                    int corrupted = 0;

                    //Apontador para o ficheiro
                    FILE *file;

                    //Abre o ficheiro
                    file = fopen(filename, "r");

                    // Verifica se o ficheiro é valido
                    if (file == NULL)
                    {
                        fputs("Error opening file\n", stdout);
                        choices(game);
                    }
                    else
                    {
                        // Se o ficheiro for valido lê as posições que estão ficheiro
                        // e aplica no array

                        turn = 0;
                        chx = 0;
                        chy = 0;
                        hasx = 0;
                        hasy = 0;

                        fscanf(file, "%d %d", &xdim, &ydim);

                        // recebe as posições das minas
                        while (1)
                        {
                            if (fscanf(file, "%c", &ch) != EOF)
                            {
                                currentNum = ch - 48;

                                if ((ch != ' ') && (ch != '\n') && (ch != '\t'))
                                {
                                    if ((currentNum < 0) || (currentNum > 9))
                                    {
                                        fputs("File is corrupted\n", stdout);
                                        corrupted = 1;
                                        break;
                                    }
                                }

                                if (turn == 0)
                                {
                                    if (ch == '\n')
                                    {
                                        if (hasx && !corrupted)
                                        {
                                            fputs("File is corrupted\n", stdout);
                                            corrupted = 1;
                                            break;
                                        }
                                        else
                                        {
                                            continue;
                                        }
                                    }

                                    else if ((ch == ' ') || (ch == '\t'))
                                    {
                                        if (hasx)
                                        {
                                            turn = 1;
                                        }
                                        else
                                        {
                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        if (chx == 0)
                                        {
                                            chx = ch - 48;
                                            hasx = 1;
                                        }

                                        else
                                        {
                                            chx *= 10;
                                            chx += ch - 48;
                                            hasx = 1;

                                            if (chx >= 25)
                                            {
                                                hasx = 0;
                                                hasy = 0;

                                                if (!corrupted)
                                                {
                                                    fputs("File is corrupted\n", stdout);
                                                    corrupted = 1;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }

                                else if (turn == 1)
                                {
                                    if ((ch == ' ') || (ch == '\t'))
                                    {
                                        if (hasy)
                                        {
                                            game[chx][chy] = ARMED;

                                            turn = 0;
                                            chx = 0;
                                            chy = 0;
                                            hasx = 0;
                                            hasy = 0;
                                        }
                                        else
                                        {
                                            continue;
                                        }
                                    }
                                    else if (ch == '\n')
                                    {
                                        if (hasy)
                                        {
                                            game[chx][chy] = ARMED;

                                            turn = 0;
                                            chx = 0;
                                            chy = 0;
                                            hasx = 0;
                                            hasy = 0;
                                        }

                                        else if (!corrupted)
                                        {
                                            fputs("File is corrupted\n", stdout);
                                            corrupted = 1;
                                            break;
                                        }

                                        turn = 0;
                                        chx = 0;
                                        chy = 0;
                                        hasx = 0;
                                        hasy = 0;
                                    }
                                    else
                                    {
                                        if (chy == 0)
                                        {
                                            chy = ch - 48;
                                            hasy = 1;
                                        }

                                        else
                                        {
                                            chy *= 10;
                                            chy += ch - 48;
                                            hasy = 1;

                                            if (chy >= 25)
                                            {
                                                hasx = 0;
                                                hasy = 0;

                                                if (!corrupted)
                                                {
                                                    fputs("File is corrupted\n", stdout);
                                                    corrupted = 1;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (turn == 0)
                                {
                                    if (hasx && !corrupted)
                                    {
                                        fputs("File is corrupted6\n", stdout);
                                        corrupted = 1;
                                        break;
                                    }
                                }
                                else if (turn == 1)
                                {
                                    if (hasy)
                                    {
                                        game[chx][chy] = ARMED;
                                    }
                                    else
                                    {
                                        if (!corrupted)
                                        {
                                            fputs("File is corrupted7\n", stdout);
                                            corrupted = 1;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                    // Fecha o ficheiro
                    fclose(file);
                    count = 1;
                }
            }
            // Imprime o mapa
            else if (strcmp(choice, "show") == 0)
            {
                if (checkRead == 0)
                {

                    for (int i = 0; i < MAX; i++)
                    {
                        for (int j = 0; j < MAX; j++)
                        {
                            if (game[i][j] == EMPTY)
                                printf("_");
                            else if ((game[i][j]) == (ARMED))
                                printf(".");
                            else if ((game[i][j]) == (DISARMED))
                                printf("*");
                        }
                        if (count > 0)
                            printf("\n");
                    }
                }
                else if (checkRead == 1)
                {
                    for (int i = 0; i < xdim; i++)
                    {
                        for (int j = 0; j < ydim; j++)
                        {
                            if (game[i][j] == EMPTY)
                                printf("_");
                            else if ((game[i][j]) == (ARMED))
                                printf(".");
                            else if ((game[i][j]) == (DISARMED))
                                printf("*");
                        }
                        if (count > 0)
                            printf("\n");
                    }
                }
            }
            // Recebe coordenas x e y e põe as minas em estado "off"
            else if (strcmp(choice, "trigger") == 0)
            {
                int posx, posy;
                int logCount = 0;
                scanf("%d%d", &posx, &posy);
                count = 1;
                if (checkRead == 0)
                {
                    if ((posx >= 0 && posx <= MAX) && (posy >= 0 && posy < MAX))
                    {
                        // Verifica se existem números negativos
                        if (posx < 0 || posx >= MAX)
                        {
                            fputs("Invalid input\n", stdout);
                        }
                        else if (posy < 0 || posy >= MAX)
                        {
                            fputs("Invalid input\n", stdout);
                        }
                        else
                        {

                            if (game[posx][posy] == ARMED)
                            {
                                game[posx][posy] = DISARMED;
                                for (int i = 0; i < MAX; i++)
                                {

                                    for (int j = 0; j < MAX; j++)
                                    {
                                        if (game[i][j] == EMPTY)
                                            printf("_");
                                        else if ((game[i][j]) == (ARMED))
                                            printf(".");
                                        else if ((game[i][j]) == (DISARMED))
                                            printf("*");
                                    }

                                    if (count > 0)
                                    {
                                        printf("\n");
                                    }
                                    count = 0;
                                }
                            }
                            else
                            {
                                fputs("No mine at specified coordinate\n", stdout);
                            }
                        }
                    }
                    else
                    {
                        fputs("Invalid coordinate\n", stdout);
                    }
                }
                if (checkRead == 1)
                {
                    if ((posx >= 0 && posx <= xdim) && (posy >= 0 && posy < ydim))
                    {
                        // Verifica se existem números negativos
                        if (posx < 0 || posx >= xdim)
                        {
                            fputs("Invalid input\n", stdout);
                        }
                        else if (posy < 0 || posy >= ydim)
                        {
                            fputs("Invalid input\n", stdout);
                        }
                        else
                        {
                            if (game[posx][posy] == DISARMED)
                            {
                                for (int i = 0; i < xdim; i++)
                                {

                                    for (int j = 0; j < ydim; j++)
                                    {
                                        if (game[i][j] == EMPTY)
                                            printf("_");
                                        else if ((game[i][j]) == (ARMED))
                                            printf(".");
                                        else if ((game[i][j]) == (DISARMED))
                                            printf("*");
                                    }

                                    if (count > 0)
                                    {
                                        printf("\n");
                                    }
                                }
                                trigger(game, posx, posy, logPos, logCount, count, xdim, ydim);
                            }
                            else
                            {
                                fputs("No mine at specified coordinate\n",stdout);
                            }
                        }
                    }
                    else
                    {
                        fputs("Invalid coordinate\n", stdout);
                    }
                }
            }
            // recebe coordenadas x e y e põe uma mina em estado "armed"
            else if (strcmp(choice, "plant") == 0)
            {
                int posx, posy;
                scanf("%d%d", &posx, &posy);
                if (checkRead == 0)
                {
                    if ((posx >= 0 && posx < MAX) && (posy >= 0 && posy < MAX))
                    {
                        count++;
                        for (int i = 0; i < MAX; i++)
                        {
                            for (int j = 0; j < MAX; j++)
                            {
                                if ((game[i][j] == DISARMED) && (game[i][j] == game[posx][posy]))
                                {
                                    game[posx][posy] = ARMED;
                                }
                                if ((game[i][j] == ARMED) && (game[i][j] == game[posx][posy]))
                                {
                                    game[posx][posy] = ARMED;
                                }
                                if ((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy]))
                                {
                                    game[posx][posy] = ARMED;
                                }
                            }
                        }
                    }
                }
                if (checkRead == 1)
                {
                    if ((posx >= 0 && posx < xdim) && (posy >= 0 && posy < ydim))
                    {
                        count++;
                        for (int i = 0; i < xdim; i++)
                        {
                            for (int j = 0; j < ydim; j++)
                            {
                                if ((game[i][j] == DISARMED) && (game[i][j] == game[posx][posy]))
                                {
                                    game[posx][posy] = ARMED;
                                }
                                if ((game[i][j] == ARMED) && (game[i][j] == game[posx][posy]))
                                {
                                    game[posx][posy] = ARMED;
                                }
                                if ((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy]))
                                {
                                    game[posx][posy] = ARMED;
                                }
                            }
                        }
                    }
                }
                else
                {
                    fputs("Invalid coordinate\n", stdout);
                }
            }

            // Exporta as posições das bombas para outro ficheiro
            else if (strcmp(choice, "export") == 0)
            {
                if (scanf("%s", filenameout))
                {
                    writeFile(filenameout, game);
                }
            }
            // Fecha a aplicação
            else if (strcmp(choice, "quit") == 0)
            {
                exit(1);
            }
            // Imprime o menu
            else if (strcmp(choice, "sos") == 0)
            {
                menu();
            }
            else if (strcmp(choice, "log") == 0)
            {
                int posx, posy;

                scanf("%d%d", &posx, &posy);
                if (checkRead == 0)
                {
                    if ((posx >= 0) && (posx < MAX) && (posy >= 0) && (posy < MAX) && (game[posx][posy] == ARMED))
                    {
                        game[posx][posy] = DISARMED;
                        printf("%d [%d, %d]\n", time, posx, posy);
                        logFunc(game, posx, posy, time, logPos, 0);
                    }
                }
                if (checkRead == 1)
                {
                    if ((posx >= 0) && (posx < xdim) && (posy >= 0) && (posy < ydim) && (game[posx][posy] == ARMED))
                    {
                        game[posx][posy] = DISARMED;
                        printf("%d [%d, %d]\n", time, posx, posy);
                        logFunc(game, posx, posy, time, logPos, 0);
                    }
                }
            }
            else
            {
                fputs("Invalid input\n", stdout);
            }
        }

    } while (i != 0);
}

void trigger(char game[][MAX], int x, int y, int logPos[625], int logCount, int count, int xdim, int ydim)
{
    // Se houver log vai limpar as posições
    if (logCount > 0)
    {
        logCount--;

        for (int i = 0; i < 98; i++)
        {
            logPos[i] = logPos[i + 2];
        }
    }

    // Verifica a direita
    if (game[x][y + 1] == ARMED)
    {
        game[x][y + 1] = DISARMED;
        saveTrigger(x, y + 1, logPos, logCount);
        logCount++;
        // Show
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica a esquerda
    if (game[x][y - 1] == ARMED)
    {
        game[x][y - 1] = DISARMED;
        saveTrigger(x, y - 1, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica em baixo
    if (game[x - 1][y] == ARMED)
    {
        game[x - 1][y] = DISARMED;

        saveTrigger(x - 1, y, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica em cima
    if (game[x + 1][y] == ARMED)
    {
        game[x + 1][y] = DISARMED;
        saveTrigger(x + 1, y, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica na diagonal esquerda em cima
    if (game[x - 1][y - 1] == ARMED)
    {
        game[x - 1][y - 1] = DISARMED;
        saveTrigger(x - 1, y - 1, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica na diagonal esquerda em baixo
    if (game[x + 1][y - 1] == ARMED)
    {
        game[x + 1][y - 1] = DISARMED;
        saveTrigger(x + 1, y - 1, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica na diagonal direita em cima
    if (game[x + 1][y + 1] == ARMED)
    {
        game[x + 1][y + 1] = DISARMED;
        saveTrigger(x + 1, y + 1, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }
    // Verifica na diagonal direita em baixo
    if (game[x + 1][y - 1] == ARMED)
    {
        game[x + 1][y - 1] = DISARMED;
        saveTrigger(x + 1, y - 1, logPos, logCount);
        logCount++;
        for (int i = 0; i < xdim; i++)
        {

            for (int j = 0; j < ydim; j++)
            {
                if (game[i][j] == EMPTY)
                    printf("_");
                else if ((game[i][j]) == (ARMED))
                    printf(".");
                else if ((game[i][j]) == (DISARMED))
                    printf("*");
            }
            if (count > 0)
            {
                printf("\n");
            }
        }
    }

    if (logCount > 0)
    {
        trigger(game, logPos[0], logPos[1], logPos, logCount, count, xdim, ydim);
    }
}

void saveTrigger(int x, int y, int _logPos[], int _logCount)
{
    // Guarda o x e y, e imprime
    // para nao guardar um em cima do outro
    _logPos[_logCount * 2] = x;
    _logPos[_logCount * 2 + 1] = y;
}

void logFunc(char game[][MAX], int x, int y, int time, int logPos[625], int logCount)
{
    // Se houver log vai limpar as posições
    if (logCount > 0)
    {
        logCount--;

        for (int i = 0; i < 98; i++)
        {
            logPos[i] = logPos[i + 2];
        }
    }

    // Verifica a direita
    if (game[x][y + 1] == ARMED)
    {
        game[x][y + 1] = DISARMED;
        time += 10;
        saveLog(x, y + 1, logPos, logCount, time);
        logCount++;
    }
    // Verifica a esquerda
    if (game[x][y - 1] == ARMED)
    {
        game[x][y - 1] = DISARMED;
        time += 10;
        saveLog(x, y - 1, logPos, logCount, time);
        logCount++;
    }
    // Verifica em baixo
    if (game[x - 1][y] == ARMED)
    {
        game[x - 1][y] = DISARMED;
        time += 10;
        saveLog(x - 1, y, logPos, logCount, time);
        logCount++;
    }
    // Verifica em cima
    if (game[x + 1][y] == ARMED)
    {
        game[x + 1][y] = DISARMED;
        time += 10;
        saveLog(x + 1, y, logPos, logCount, time);
        logCount++;
    }
    // Verifica na diagonal esquerda em cima
    if (game[x - 1][y - 1] == ARMED)
    {
        game[x - 1][y - 1] = DISARMED;
        time += 15;
        saveLog(x - 1, y - 1, logPos, logCount, time);
        logCount++;
    }
    // Verifica na diagonal esquerda em baixo
    if (game[x + 1][y - 1] == ARMED)
    {
        game[x + 1][y - 1] = DISARMED;
        time += 15;
        saveLog(x + 1, y - 1, logPos, logCount, time);
        logCount++;
    }
    // Verifica na diagonal direita em cima
    if (game[x + 1][y + 1] == ARMED)
    {
        game[x + 1][y + 1] = DISARMED;
        time += 15;
        saveLog(x + 1, y + 1, logPos, logCount, time);
        logCount++;
    }
    // Verifica na diagonal direita em baixo
    if (game[x + 1][y - 1] == ARMED)
    {
        game[x + 1][y - 1] = DISARMED;
        time += 15;
        saveLog(x + 1, y - 1, logPos, logCount, time);
        logCount++;
    }

    if (logCount > 0)
    {
        logFunc(game, logPos[0], logPos[1], time, logPos, logCount);
    }
}

// Guarda as posições para depois limpar
void saveLog(int x, int y, int _logPos[], int _logCount, int time)
{
    // Guarda o x e y, e imprime
    // para nao guardar um em cima do outro
    _logPos[_logCount * 2] = x;
    _logPos[_logCount * 2 + 1] = y;
    printf("%d [%d, %d]\n", time, x, y);
}

// cria um ficheiro novo
void writeFile(char filenameout[200], char game[][MAX])
{

    // Apontador para o ficheiro
    FILE *file;
    // variaveis da grelha
    int i, j;

    //abre o ficheiro em modo escrita
    file = fopen(filenameout, "w");
    // Verifica se o ficheiro é null
    if (file == NULL)
    {
        fputs("Error opening the file\n", stdout);
        choices(game);
    }
    // Abre a grelha

    // Verifica se há bombas armadas no array
    // E verifica se há bombas desarmadas no array
    else
    {
        for (i = 0; i < MAX; i++)
        {
            for (j = 0; j < MAX; j++)
            {
                // Bombas armadas no array(posições)
                if (game[i][j] == ARMED)
                {
                    // Escreve no ficheiro as posições das bombas armadas
                    fprintf(file, "%d %d\n", i, j);
                }
                // Bombas desarmadas no array(posições)
                if (game[i][j] == DISARMED)
                {
                    // Escreve no ficheiro as posições das bombas desarmadas
                    fprintf(file, "%d %d\n", i, j);
                }
            }
        }
        // Fecha o ficheiro
        fclose(file);
    }
}
