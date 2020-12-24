# include <stdio.h>
# include <string.h>
# include <stdlib.h>
#define MAX 25


void menu();
void choices();
void readFile(filename);
int grelha();

int main(){
	menu();
	choices();
	
}	

/// Imprime o menu
/// Verifica a escolha do utilizador 
void menu(){
	puts("+-----------------------------------------------------");
	puts("read <filename>     - read input file");
	puts("show                - show the mine map");
	puts("trigger <x> <y>     - trigger mine at <x> <y>");
	puts("plant <x> <y>       - place armed mine at <x> <y>");
	puts("export <filename>   - save file with current map");
	puts("quit                - exit program");
	puts("+-----------------------------------------------------");
}

void choices(){

	char choice[20];
	int i = 1;
	char filename[200];
	
	do
	{
		printf("\n>");
		// lê a escolha e o path do ficheiro
		///scanf("%s%s",choice, filename );
		if(scanf("\n%s",&choice)){
			// compares the input with the menu options
			if(strcmp(choice,"read") == 0)
			{
				if(scanf("%s", &filename)){
					readFile(filename);

				}
			
				
				
			}
			else if(strcmp(choice,"show") == 0)
			{
				//printmap()
			}
			else if(strcmp(choice,"trigger") == 0)
			{
			}
			else if(strcmp(choice,"plant") == 0)
			{
			}
			else if(strcmp(choice,"export") == 0)
			{

			}
			else if(strcmp(choice,"quit") == 0)
			{
				exit(1);
			}
			else if(strcmp(choice,"sos") == 0)
			{
				menu();
			}
			else
			{
				printf("Inputs errados.\n");
			}

		}
		
		
			
		
			
	} while (i != 0);
}

// Lê o ficheiro
void readFile(char filename[200]){
	int *chx;
	int *chy;
	int x;
	
	//Apontador para o ficheiro 
	FILE *file;

	// nome do ficheiro
	// localização do ficheiro

	//Abre o ficheiro
	file = fopen(filename,"r");

	// Verifica se o ficheiro é valido

	if(filename == NULL){
		printf("Impossivel abrir o ficheiro %s", filename);
	}
	else
	{
		x = grelha();
		//Imprime tudo que está no ficheiro
		while (fscanf(file,"%d %d",&chx, &chy)!= EOF)
		{ 
			printf("x%dy%d\n", chx, chy);

			x [chx][chy] = 1;
			


		}
		
		fclose(file);
		
	}
	
	return 0;

}


// faz a grelha
int grelha(){

	int me[MAX][MAX];

	
	int i = 0;
	int j = 0;

	for (i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++){
			me[i][j] = 0;
			printf("%d", me[i][j]);
			 
		}
	}



	return me;
}


