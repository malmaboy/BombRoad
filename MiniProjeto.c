# include <stdio.h>
# include <string.h>
# include <stdlib.h>


void menu();
void choices();
void readFile(filename);

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
		if(scanf("\n%s%s",&choice, &filename )){
			// compares the input with the menu options
			if(strcmp(choice,"read") == 0)
			{
				readFile(filename);
				
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
				printf("Inputs errados");
			}

		}
		else if(scanf("%s",&choice)){
			if(strcmp(choice,"quit") == 0)
			{
				exit(1);
			}
		}
		
			
		
			
	} while (i != 0);
}

// Lê o ficheiro
void readFile(char filename[200]){
	int ch;
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
		
		//Imprime tudo que está no ficheiro
		while ((ch = fgetc(file)) != EOF)
		{ 
			mineposition(ch);
			
		}
		
		fclose(file);
		
	}
	


}

int mineposition(int ch){
	int x1 = 0;
	int y2 = 0;

	

	int position[10][10];

	for( int x = 0; x < ch;x++){
		for(int y = 0; y < ch;y++){
			fscanf("%d",position[x1][y2]);
			
		}
                                                                   
	}
	
	printf("%d%d\n", position);

	return 0;
}

