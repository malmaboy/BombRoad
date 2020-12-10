# include <stdio.h>
# include <string.h>

void menu();
void choices();

int main(){
	menu();
	choices();
}	

/// Imprime o menu
/// Verifica a escolha do utilizador 
void menu(){
	puts("+-----------------------------------------------------");
	puts("|reads <filename> - read input file");
	puts("|show - show the mine map");
	puts("|trigger <x> <y> - trigger mine at <x> <y>");
	puts("|plant <x> <y> - place armed mine at <x> <y>");
	puts("|export <filename> - save file with current map");
	puts("|quit - exit program");
	puts("+-----------------------------------------------------");
}

void choices(){

	char choice[20];
	int i = 0;



	do
	{
		printf(">");
		gets(choice);
			
			// verifica se as strings são iguais
			if (strcmp(choice,"read") == 0)
			{
				i = 1;
				
			}
			if(strcmp(choice,"show") == 0)
			{
				i = 2;
			}
			if(strcmp(choice,"trigger") == 0)
			{
				i = 3;
			}
			if(strcmp(choice,"plant") == 0)
			{
				i = 4;
			}
			if(strcmp(choice,"export") == 0)
			{
				i = 5;
			}
			if(strcmp(choice,"quit") == 0){
				i = 6;
			}
			


		switch (i)
		{
			case 1: // read
				printf("hello");
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6: // quit
				break;
		default:
			break;
		}
	} while (i != 6);
	
}

