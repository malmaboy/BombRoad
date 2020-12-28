#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// tamanho do array
#define MAX 25
// sem mina
#define EMPTY '_'
// mina armada
#define ARMED '.'
// mina desarmada
#define DISARMED '*'

void menu();
void choices();
void readFile(char filename[200], char grid[][MAX]);
void show(char empty[][MAX], char armed[][MAX]);
void writeFile(char filenameout[200], char grid[][MAX]);

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
    puts("read <filename>     - read input file");
    puts("show                - show the mine map");
    puts("trigger <x> <y>     - trigger mine at <x> <y>");
    puts("plant <x> <y>       - place armed mine at <x> <y>");
    puts("export <filename>   - save file with current map");
    puts("quit                - exit program");
    puts("+-----------------------------------------------------");
}

// Verifica a escolha do utlizador
void choices()
{
    int i = 1;
    // nome da escolha
    char choice[20];
    // nome do ficheiro 
    char filename[200];
    // nome do ficheiro para fazer export
    char filenameout[200];
    // array 
    char game[MAX][MAX];
    // variavel de ajuda para opção show
    int count = 0;


    do
    {
        printf("\n>");
        // lê a escolha e o path do ficheiro
        if (scanf("\n%s", &choice))
        {
            // compares the input with the menu options
            if (strcmp(choice, "read") == 0)
            {
                if (scanf("%s", &filename))
                {
                    readFile(filename, game);
                    count++;
                }
            }
            else if (strcmp(choice, "show") == 0)
            {
                for (int i = 0; i < MAX; i++){

                    for (int j = 0; j < MAX; j++){
                        if(count <= 0){
                            game[i][j] = EMPTY;
                            
                        }
                        else
                        {
                            game[i][j];

                        }
                        
                    printf("%c", game[i][j]);
                }
        }
            }
            // Recebe coordenas x e y e põe as minas em estado "off"
            else if (strcmp(choice, "trigger") == 0)
            {
                int posx, posy;
                int count1 = 0;
                scanf("%d%d", &posx, &posy);
                if(posx != NULL || posy != NULL){
                    if((posx >= 0 && posx <= MAX)  && (posy >= 0 && posy < MAX)){
                        

                        for(int i = 0; i < MAX; i++){
                            for (int j = 0; j < MAX; j++)
                            {
                                if((game[i][j] == ARMED) && (game[i][j] == game[posx][posy])){ 
                                    game[posx][posy] = DISARMED;
                                }
                                else if((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy])){
                                    count1 = 1;
                                }
                                




                            }
                        }
                        if(count1 == 1){
                            fputs("No mine at specified coordinate", stderr);
                            count1 == 0;
                        }
                    }
                    else
                    {
                        fputs("Invalid coordinate.",stderr);
                    }
                    
                }
                
                else
                {
                    fputs("Invalid coordinate.",stderr);
                    printf("%d%d", posx, posy);
                }
                
                


            }
            // recebe coordenadas x e y e põe uma mina em estado "armed"
            else if (strcmp(choice, "plant") == 0)
            {
                int posx, posy;
                scanf("%d%d", &posx, &posy);
                if(posx != NULL || posy != NULL){
                    if((posx >= 0 && posx <= MAX)  && (posy >= 0 && posy < MAX)){

                        for(int i = 0; i < MAX; i++)
                        {
                            for (int j = 0; j < MAX; j++)
                            {
                                if((game[i][j] == DISARMED) && (game[i][j] == game[posx][posy])){ 
                                    game[posx][posy] = ARMED;
                                }
                                if((game[i][j] == ARMED) && (game[i][j] == game[posx][posy])){ 
                                    game[posx][posy] = ARMED;
                                }
                                if((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy])){
                                game[posx][posy] = EMPTY;
                                }
                            }
                        }
                    }
                    else
                    {
                        fputs("Invalid coordinate.",stderr);
                    }
                    
                }
                else
                {
                    fputs("Invalid coordinate.",stderr);
                }
                

            }
            // Exporta as posições das bombas para outro ficheiro
            else if (strcmp(choice, "export") == 0)
            {
                if(scanf("%s", &filenameout)){
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
            else
            {
                fputs("Invalid input.", stderr);
            }
        }

    } while (i != 0);
}

// Lê o ficheiro
void readFile(char filename[200], char grid[][MAX])
{
    // Variavel que recebe a posição x
    int chx;
    // Variavel que recebe a posição y
    int chy;
    // Variaveis que vão receber as posições do array
	int i, j;

    //Apontador para o ficheiro
    FILE *file;

    //Abre o ficheiro
    file = fopen(filename, "r");


    // Verifica se o ficheiro é valido
    if (filename == NULL)
    {
        fputs("Error opening file\n", stderr);
    }
    else
    {
        // Se o ficheiro for valido lê as posições que estão ficheiro 
        // e aplica no array 
        for (i = 0; i < MAX; i++)
        {
            for ( j = 0; j < MAX; j++)
            {
                grid[i][j] = EMPTY;
            }
        }

        // recebe as posições das minas e imprime-as
        while (fscanf(file, "%d %d", &chx, &chy) != EOF)
        {
            if(chx != NULL || chy != NULL){
                grid[chx][chy] = ARMED;

            }
            // Caso exista uma posição x ou y null retorna o erro
            else
            {
                fputs("File is corrupted.\n", stderr);
            }
            
        }
        // Fecha o ficheiro
        fclose(file);
    }

	
}

// cria um ficheiro novo
void writeFile(char filenameout[200], char grid[][MAX]){

    // Apontador para o ficheiro
    FILE *file;
    // int para ler o caracteres
    int chx, chy;
    // variaveis da grelha
    int i,j;

    //abre o ficheiro em modo escrita
    file = fopen(filenameout, "w");
    // Verifica se o ficheiro é null
    if(file == NULL){
        fputs("Error opening the file.\n", stderr);
    }
    // Abre a grelha 
    // Verifica se há bombas armadas no array
    // E verifica se há bombas desarmadas no array
    else
    {
        for(i = 0; i < MAX; i++){
            for (j = 0; j < MAX; j++)
            {
                // Bombas armadas no array(posições)
                if(grid[i][j] == ARMED){
                    // Escreve no ficheiro as posições das bombas armadas
                    fprintf(file, "%d %d\n", i,j);
                }
                // Bombas desarmadas no array(posições)
                if (grid[i][j] == DISARMED)
                {
                    // Escreve no ficheiro as posições das bombas desarmadas
                    fprintf(file, "%d %d\n", i,j);
                    
                }
                
            }

        }
        // Fecha o ficheiro
        fclose(file);
    }

    
}

