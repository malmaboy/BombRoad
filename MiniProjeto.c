# include <stdio.h>
# include <string.h>
# include <stdlib.h>

void menu();
void choices();
void readFile();

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



	do
	{
		printf(">");
		gets(choice);
			
			// compares the input with the menu options
			if (strcmp(choice,"read") == 0)
			{
				readFile();
				
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
			}
			else if(strcmp(choice,"sos") == 0)
			{
				menu();
			}
			else 
			{
				printf("Inputs errados");
			}
	} while (i != 0);
}

// Lê o ficheiro
void readFile(){
	int ch;
	//Apontador para o ficheiro 
	FILE *file;
	// nome do ficheiro
	char filename[200];
	// localização do ficheiro
	gets(filename);

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
			putchar(ch);
		}
		
		fclose(file);
		
	}
	


}

