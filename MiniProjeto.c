#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// tamanho do array
#define DEFAULT 25
// sem mina
#define EMPTY '_'
// mina armada
#define ARMED '.'
// mina desarmada
#define DISARMED '*'

void menu();
void choices();
void writeFile(char filenameout[200], char **grid, int row, int col);
void logFunc(char **game, int x, int y, int time, int logPos[625], int logCount, int xdim, int ydim);
void trigger(char **game, int x, int y, int logPos[625], int logCount, int count, int xdim, int ydim);
char **generateMap(int row, int col);
void saveTrigger(int x, int y, int _logPos[], int _logCount);
void saveLog(int x, int y, int _logPos[], int _logCount, int time);

// Main
int main()
{
    menu();
    choices();
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
void choices()
{
    int i = 1;
    // nome da escolha
    char choice[20];
    // nome do ficheiro
    char filename[200];
    // nome do ficheiro para fazer export
    char filenameout[200];
    // lista de posições para rebentar
    int logPos[256];
    int logCount = 0;
    // variavel de ajuda para opção show
    int count = 0;
    // Tempo de Explosão
    // Tamanho Maximo
    int row = DEFAULT;
    int col = DEFAULT;
    int xdim, ydim;
    //int checkRead = 0;
    // Gerar Mapa
    char **game = generateMap(row, col);

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
                    //checkRead = 1;
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
                        continue;
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
                        game = generateMap(xdim, ydim);
                        row = xdim;
                        col = ydim;

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
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        if (game[i][j] == EMPTY)
                            printf("_");
                        else if ((game[i][j]) == (ARMED))
                            printf(".");
                        else if ((game[i][j]) == (DISARMED))
                            printf("*");
                    }

                    printf("\n");
                }
            }
            // Recebe coordenas x e y e põe as minas em estado "off"
            else if (strcmp(choice, "trigger") == 0)
            {
                int posx, posy;
                scanf("%d%d", &posx, &posy);
                if ((posx >= 0 && posx <= row) && (posy >= 0 && posy < row))
                {
                    // Verifica se existem números negativos
                    if (posx < 0 || posx >= col)
                    {
                        fputs("Invalid input\n", stdout);
                    }
                    else if (posy < 0 || posy >= col)
                    {
                        fputs("Invalid input\n", stdout);
                    }
                    else
                    {
                        if (game[posx][posy] == ARMED)
                        {
                            game[posx][posy] = DISARMED;
                            trigger(game, posx, posy, logPos, logCount, count, row, col);
                            for (int i = 0; i < row; i++)
                            {
                                for (int j = 0; j < col; j++)
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
            // recebe coordenadas x e y e põe uma mina em estado "armed"
            else if (strcmp(choice, "plant") == 0)
            {
                int posx, posy;
                scanf("%d%d", &posx, &posy);

                if ((posx >= 0 && posx < row) && (posy >= 0 && posy < row))
                {
                    count++;
                    for (int i = 0; i < col; i++)
                    {
                        for (int j = 0; j < col; j++)
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
                    writeFile(filenameout, game, row, col);
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

                // Verifica se existem números negativos
                if (posx < 0 || posx >= row)
                {
                    fputs("Invalid input\n", stdout);
                }
                else if (posy < 0 || posy >= row)
                {
                    fputs("Invalid input\n", stdout);
                }
                else
                {
                    if (game[posx][posy] == ARMED)
                    {
                        game[posx][posy] = DISARMED;
                        printf("%d [%d, %d]\n", 0, posx, posy);
                        logFunc(game, posx, posy, 0, logPos, logCount, xdim, ydim);
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

void trigger(char **game, int x, int y, int logPos[625], int logCount, int count, int xdim, int ydim)
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

void logFunc(char **game, int x, int y, int time, int logPos[], int logCount, int xdim, int ydim)
{
    // Se houver log vai limpar as posições
    if (logCount > 0)
    {
        logCount--;

        for (int i = 0; i < 253; i++)
        {
            logPos[i] = logPos[i + 3];
        }
    }

    // Verifica a direita
    if ((y + 1 < ydim) && (game[x][y + 1] == ARMED))
    {
        game[x][y + 1] = DISARMED;
        saveLog(x, y + 1, logPos, logCount, time + 10);
        logCount++;
    }
    // Verifica a esquerda
    if ((y - 1 >= 0) && (game[x][y - 1] == ARMED))
    {
        game[x][y - 1] = DISARMED;
        saveLog(x, y - 1, logPos, logCount, time + 10);
        logCount++;
    }
    // Verifica em baixo
    if ((x - 1 >= 0) && (game[x - 1][y] == ARMED))
    {
        game[x - 1][y] = DISARMED;
        saveLog(x - 1, y, logPos, logCount, time + 10);
        logCount++;
    }
    // Verifica em cima
    if ((x + 1 < xdim) && (game[x + 1][y] == ARMED))
    {
        game[x + 1][y] = DISARMED;
        saveLog(x + 1, y, logPos, logCount, time + 10);
        logCount++;
    }
    // Verifica na diagonal esquerda em cima
    if ((x - 1 >= 0) && (y - 1 >= 0) && (game[x - 1][y - 1] == ARMED))
    {
        game[x - 1][y - 1] = DISARMED;
        saveLog(x - 1, y - 1, logPos, logCount, time + 15);
        logCount++;
    }
    // Verifica na diagonal esquerda em baixo
    if ((x + 1 < xdim) && (y - 1 >= 0) && (game[x + 1][y - 1] == ARMED))
    {
        game[x + 1][y - 1] = DISARMED;
        saveLog(x + 1, y - 1, logPos, logCount, time + 15);
        logCount++;
    }
    // Verifica na diagonal direita em cima
    if ((x + 1 < xdim) && (y + 1 < ydim) && (game[x + 1][y + 1] == ARMED))
    {
        game[x + 1][y + 1] = DISARMED;
        saveLog(x + 1, y + 1, logPos, logCount, time + 15);
        logCount++;
    }
    // Verifica na diagonal direita em baixo
    if ((x + 1 < xdim) && (y - 1 >= 0) && (game[x + 1][y - 1] == ARMED))
    {
        game[x + 1][y - 1] = DISARMED;
        saveLog(x + 1, y - 1, logPos, logCount, time + 15);
        logCount++;
    }

    if (logCount > 0)
    {
        logFunc(game, logPos[0], logPos[1], logPos[2], logPos, logCount, xdim, ydim);
    }
}

// Guarda as posições para depois limpar
void saveLog(int x, int y, int _logPos[], int _logCount, int time)
{
    // Guarda o x e y, e imprime
    // para nao guardar um em cima do outro
    _logPos[_logCount * 3] = x;
    _logPos[_logCount * 3 + 1] = y;
    // Guardar o time
    _logPos[_logCount * 3 + 2] = time;
    printf("%d [%d, %d]\n", time, x, y);
}

// cria um ficheiro novo
void writeFile(char filenameout[200], char **grid, int row, int col)
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
    }
    // Abre a grelha

    // Verifica se há bombas armadas no array
    // E verifica se há bombas desarmadas no array
    else
    {
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                // Bombas armadas no array(posições)
                if (grid[i][j] == ARMED)
                {
                    // Escreve no ficheiro as posições das bombas armadas
                    fprintf(file, "%d %d\n", i, j);
                }
                // Bombas desarmadas no array(posições)
                if (grid[i][j] == DISARMED)
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

// Gerar Mapa
char **generateMap(int row, int col)
{
    // aloca um vector de vectores com tamanho nrows
    char **map = (char **)malloc(row * sizeof(char *));

    if (map == NULL)
    {
        puts("Error: Out of Memory");
        exit(1);
    }
    // para cada elemento do vector, aloca um vector com tamanho ncols
    for (int i = 0; i < row; i++)
    {
        map[i] = malloc(col * sizeof(char));
        if (map[i] == NULL)
        {
            puts("Error: Out of Memory");
            exit(1);
        }
    }
    // a partir daqui pode aceder aos elementos da matriz da forma habitual map[x][y]
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            map[i][j] = EMPTY;
        }
    }

    return map;
}
