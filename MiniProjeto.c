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
void readFile(char filename[200], char** grid, int* row, int* col);
void writeFile(char filenameout[200], char** grid, int row, int col);
void logFunc(char** game, int x, int y, int time, int logPos[625], int logCount, int row, int col);
void trigger(char** game, int x, int y, int logPos[100], int logCount, int row, int col);
char** generateMap(int row, int col);

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
    int logPos[100];
    int logCount = 0;
    // variavel de ajuda para opção show
    int count = 0;
    // Tempo de Explosão
    int time = 0;
    // Tamanho Maximo
    int row = DEFAULT;
	int col = DEFAULT;
	// Gerar Mapa
	char** game = generateMap(row, col);

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
                    readFile(filename, game, row, col);
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
                    //if (count > 0)
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
                            trigger(game, posx, posy, logPos, logCount, row, col);
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

                                if(count > 0){
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
                        printf("%d [%d, %d]\n", time, posx, posy);
                        logFunc(game, posx, posy, time, logPos, logCount, row, col);
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

void trigger(char** game, int x, int y, int logPos[625], int logCount, int row, int col)
{
    if (logCount > 0)
    {
        for (int i = 0; i < 98; i++)
        {
            logPos[i] = logPos[i + 2];
        }
        logCount--;
    }

    // Verifica os lados da bomba
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {

            // Posição da bomba inicial
            if ((i == 0 && j == 0) || (i != 0 && j != 0))
            {
                // continua
                continue;
            }
            // Verifica se está dentro Do mapa
            else if ((x + i < 0) || (x + i > row) || (y + j < 0) || (y + j > col))
            {
                // Vai para o else
                continue;
            }
            // Se está tudo certo rebenta as que estão a volta
            else
            {

                if (game[x + i][y + j] == ARMED)
                {
                    game[x + i][y + j] = DISARMED;
                    // Guarda a posição das adjacentes, x
                    logPos[logCount * 2] = x + i;
                    // Guarda a posição das adjacentes, y
                    logPos[logCount * 2 + 1] = y + j;
                    logCount++;
                }
            }
        }
    }

    // Verifica todas as diagonais a volta da bomba
    for (int i = -1; i < 2; i += 2)
    {
        for (int j = -1; j < 2; j += 2)
        {

            // Posição da bomba inicial
            if (i == 0 && j == 0)
            {
                // continua
                continue;
            }
            // Verifica se está dentro Do mapa
            else if ((x + i < 0) || (x + i > row) || (y + j < 0) || (y + j > col))
            {
                // Vai para o else
                continue;
            }
            // Se está tudo certo rebenta as que estão a volta
            else
            {
                if (game[x + i][y + j] == ARMED)
                {
                    game[x + i][y + j] = DISARMED;
                    // guarda a posição e das bombas explodidas diagonal , x
                    logPos[logCount * 2] = x + i;
                    // guarda a posição e das bombas explodidas diagonal , y
                    logPos[logCount * 2 + 1] = y + j;
                    logCount++;
                }
            }
        }
    }
    if (logCount)
    {
        trigger(game, logPos[0], logPos[1], logPos, logCount, row, col);
    }
}

void logFunc(char** game, int x, int y, int time, int logPos[625], int logCount, int row, int col)
{
    if (logCount > 0)
    {
        for (int i = 0; i < 98; i++)
        {
            logPos[i] = logPos[i + 2];
        }
        logCount--;
    }

    // Verifica os lados da bomba
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {

            // Posição da bomba inicial
            if ((i == 0 && j == 0) || (i != 0 && j != 0))
            {
                // continua
                continue;
            }
            // Verifica se está dentro Do mapa
            else if ((x + i < 0) || (x + i > row) || (y + j < 0) || (y + j > col))
            {
                // Vai para o else
                continue;
            }
            // Se está tudo certo rebenta as que estão a volta
            else
            {

                if (game[x + i][y + j] == ARMED)
                {
                    game[x + i][y + j] = DISARMED;
                    // Guarda a posição das adjacentes, x
                    logPos[logCount * 2] = x + i;
                    // Guarda a posição das adjacentes, y
                    logPos[logCount * 2 + 1] = y + j;
                    logCount++;
                    time += 10;
                    printf("%d [%d, %d]\n", time, x + i, y + j);
                }
            }
        }
    }

    // Verifica todas as diagonais a volta da bomba
    for (int i = -1; i < 2; i += 2)
    {
        for (int j = -1; j < 2; j += 2)
        {

            // Posição da bomba inicial
            if (i == 0 && j == 0)
            {
                // continua
                continue;
            }
            // Verifica se está dentro Do mapa
            else if ((x + i < 0) || (x + i > row) || (y + j < 0) || (y + j > col))
            {
                // Vai para o else
                continue;
            }
            // Se está tudo certo rebenta as que estão a volta
            else
            {
                if (game[x + i][y + j] == ARMED)
                {
                    game[x + i][y + j] = DISARMED;
                    // guarda a posição e das bombas explodidas diagonal , x
                    logPos[logCount * 2] = x + i;
                    // guarda a posição e das bombas explodidas diagonal , y
                    logPos[logCount * 2 + 1] = y + j;
                    logCount++;
                    time += 15;
                    printf("%d [%d, %d]\n", time, x + i, y + j);
                }
            }
        }
    }
    if (logCount)
    {
        logFunc(game, logPos[0], logPos[1], time, logPos, logCount, row, col);
    }
}

// Lê o ficheiro
void readFile(char filename[200], char** grid, int* row, int* col)
{
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
    }
    else
    {
        *row = 3;
        *col = 3;
        free(grid);
        grid = generateMap(*row, *col); //ir buscar valores a ficheiro!!

        turn = 0;
        chx = 0;
        chy = 0;
        hasx = 0;
        hasy = 0;

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
                            grid[chx][chy] = ARMED;

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
                            grid[chx][chy] = ARMED;

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
                        grid[chx][chy] = ARMED;
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
}

// cria um ficheiro novo
void writeFile(char filenameout[200], char** grid, int row, int col)
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
char** generateMap(int row, int col)
{
	// aloca um vector de vectores com tamanho nrows
	char** map = (char**)malloc(row * sizeof(char*));

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
