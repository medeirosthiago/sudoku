#include <stdio.h>
#include <time.h>
#define PADRAO 9

int sudoku[PADRAO][PADRAO];
int matExemplo[PADRAO][PADRAO] = { 
							{6, 9, 8, 5, 2, 4, 1, 3, 7 },
							{2, 7, 4, 3, 9, 1, 5, 6, 8 },
							{5, 1, 3, 8, 6, 7, 4, 9, 2 },
							{4, 8, 7, 6, 1, 3, 2, 5, 9 },
							{9, 3, 6, 7, 5, 2, 8, 4, 1 },
							{1, 2, 5, 4, 8, 9, 3, 7, 6 },
							{3, 6, 9, 1, 4, 8, 7, 2, 5 },
							{7, 5, 1, 2, 3, 6, 9, 8, 4 },
							{8, 4, 2, 9, 7, 5, 6, 1, 3 } 
						};

void inicializar()
{
	int i, j;
	
	for(i = 0; i < PADRAO; i++) {
		for(j = 0; j < PADRAO; j++)	{
			sudoku[i][j] = matExemplo[i][j];
		}
	}	
}

void imprimeSudokuCompleto()
{
	int i, j;

	printf("+--------+--------+--------+\n");
	
	for(i = 0; i < PADRAO; i++) {
		for(j = 0; j < PADRAO; j++) {
			printf(" %d ", sudoku[i][j]);
		}
		printf("\n");
	}

	printf("+--------+--------+--------+\n");
}

void geraArquivoeImprimeSudoku()
{	
	int i, j, aux = 0;

	char sudokuTemp[PADRAO][PADRAO];

	FILE *arq1;
	arq1 = fopen("sudoku_modelo.txt", "r");

	if(arq1 == NULL)
			printf("Problemas na CRIACAO do arquivo\n");

	for(i = 0; i < PADRAO; i++)
		for(j = 0; j < PADRAO; j++)
			fscanf(arq1, "%c", &sudokuTemp[i][j]);


	for(i = 0; i < PADRAO; i++)	{
		do {
			j = rand() % 9;
			sudokuTemp[i][j] = ' ';

			j = rand() % 9;
			sudokuTemp[i][j] = ' ';

			j = rand() % 9;
			sudokuTemp[i][j] = ' ';

			j = rand() % 9;
			sudokuTemp[i][j] = ' ';

			j = rand() % 9;
			sudokuTemp[i][j] = ' ';

			j = rand() % 9;
			sudokuTemp[i][j] = ' ';

			aux++;
		} while (aux < 5);
	}

	printf("+--------+--------+--------+\n");

	for(i = 0; i < PADRAO; i++) {
		for(j = 0; j < PADRAO; j++) {
			printf(" %c ", sudokuTemp[i][j]);
		}
		printf("\n");
	}

	printf("+--------+--------+--------+\n");

	fclose(arq1);

	FILE *arq2;
	arq2 = fopen("sudoku.txt", "w");

	if(arq2 == NULL)
			printf("Problemas na CRIACAO do arquivo\n");

	fprintf(arq2, "+--------+--------+--------+\n", sudokuTemp[i][j]);

	for(i = 0; i < PADRAO; i++)
		for(j = 0; j < PADRAO; j++) {
			if(j == 8)
			 	fprintf(arq2, " %c \n", sudokuTemp[i][j]);
			else 
				fprintf(arq2, " %c ", sudokuTemp[i][j]);
		}

	fprintf(arq2, "+--------+--------+--------+\n", sudokuTemp[i][j]);

	fclose(arq2);
}

void geraArquivoSudokuCompleto()
{
	FILE *arq;
	int sudokuTemp[PADRAO][PADRAO];
	int i, j, result;

	for(i = 0; i < PADRAO; i++)
		for(j = 0; j < PADRAO; j++)
			sudokuTemp[i][j] = sudoku[i][j];
	
	arq = fopen("sudoku_solucao.txt", "w");

	if(arq == NULL)
			printf("Problemas na CRIACAO do arquivo\n");

	fprintf(arq, "+--------+--------+--------+\n", sudokuTemp[i][j]);

	for(i = 0; i < PADRAO; i++) {
		for(j = 0; j < PADRAO; j++) {
			if(j == 8)
			 	fprintf(arq, " %d \n", sudokuTemp[i][j]);
			else 
				fprintf(arq, " %d ", sudokuTemp[i][j]);
		}
	}

	fprintf(arq, "+--------+--------+--------+\n", sudokuTemp[i][j]);
	
	fclose(arq);
}

void geraArquivoSudokuModelo()
{
	FILE *arq;
	int sudokuTemp[PADRAO][PADRAO];
	int i, j, result;

	for(i = 0; i < PADRAO; i++)
		for(j = 0; j < PADRAO; j++)
			sudokuTemp[i][j] = sudoku[i][j];
	
	arq = fopen("sudoku_modelo.txt", "w");

	if(arq == NULL)
			printf("Problemas na CRIACAO do arquivo\n");
	
	
	for(i = 0; i < PADRAO; i++)
		for(j = 0; j < PADRAO; j++)
				fprintf(arq, "%d", sudokuTemp[i][j]);		
	
	fclose(arq);	
}


void trocaLinhaPeq(int linha1, int linha2)
{
	int j, tempL;

	for(j = 0; j < PADRAO; j++) {
		tempL = sudoku[linha1][j];
		
		sudoku[linha1][j] = sudoku[linha2][j];
		sudoku[linha2][j] = tempL;
	}
}

void trocaLinhaGrande(int lgrande1, int lgrande2)
{	
	if(lgrande1 > 2 || lgrande2 > 2)
		printf("ERRO LINHA GRANDE");
	else {
		trocaLinhaPeq(lgrande1 * 3, lgrande2 * 3);
		trocaLinhaPeq(lgrande1 * 3 + 1, lgrande2 * 3 + 1);
		trocaLinhaPeq(lgrande1 * 3 + 2, lgrande2 * 3 + 2);
	}
}

void trocaColunaPeq(int col1, int col2)
{
	int i, tempC;	
	
	for(i = 0; i < PADRAO; i++) {
		tempC = sudoku[i][col1];
		
		sudoku[i][col1] = sudoku[i][col2];
		sudoku[i][col2] = tempC;
	}
}

void trocaColunaGrande(int cgrande1, int cgrande2)
{	
	if(cgrande1 > 2 || cgrande2 > 2)
		printf("ERRO COLUNA GRANDE");
	else {
		trocaColunaPeq(cgrande1 * 3, cgrande2 * 3);
		trocaColunaPeq(cgrande1 * 3 + 1, cgrande2 * 3 + 1);
		trocaColunaPeq(cgrande1 * 3 + 2, cgrande2 * 3 + 2);
	}
}

void giraVertical()
{
	int i, j, tempV;
	
	for(i = 0; i < PADRAO; i++)	{
		for(j = 0; j < PADRAO/2; j++) {
			tempV = sudoku[i][j];
			
			sudoku[i][j] = sudoku[i][8 - j];
			sudoku[i][8 - j] = tempV;
		}
	}
}

void giraHorizontal()
{
	int i, j, tempH;
	
	for(i = 0; i < PADRAO/2; i++) {
		for(j = 0; j < PADRAO; j++)	{
			tempH = sudoku[i][j];
			
			sudoku[i][j] = sudoku[8 - i][j];
			sudoku[8 - i][j] = tempH;
		}
	}
}

void trocaColLinha()
{
	int i, j, temptrocaColLinha;
	
	for(i = 0; i < PADRAO; i++) {
		for(j = i; j < PADRAO; j++)	{
			temptrocaColLinha = sudoku[i][j];
			
			sudoku[i][j] = sudoku[j][i];
			sudoku[j][i] = temptrocaColLinha;
		}
	}
}

void inverteMatriz()
{
	int i, j;
	int sudokuTemp[PADRAO][PADRAO];
	
	for(i = 0; i < PADRAO; i++)	{
		for(j = 0; j < PADRAO; j++)	{
			sudokuTemp[i][j] = sudoku[i][j];			
		}
	}
	
	for(i = 0; i < PADRAO; i++)	{
		for(j = 0; j < PADRAO; j++) {
			sudoku[i][j] = sudokuTemp[j][i];
		}
	}
	
}

void inverteMatriz2()
{
	giraVertical();
	inverteMatriz();
}

void substitui(int a, int b)
{
	int i, j;
	for(i = 0; i < PADRAO; i++)	{
		for(j = 0; j < PADRAO; j++)	{
			if(sudoku[i][j] == a)
			sudoku[i][j] = b;
			
			else if(sudoku[i][j] == b)
			sudoku[i][j] =a;
		}
	}
}

void geraSudoku()
{
	inicializar();
	srand(time(NULL));
	
	int embaralha, i, bloco;
	
	for(i = 0; i < 10; i++) {
		
		embaralha = rand() % 10;
		bloco = rand() % 3;
		
		switch(embaralha) {
		case 0: 
			switch(bloco) {
				case 0:
					trocaLinhaPeq(rand() % 3, rand() % 3);
					break;
					
				case 1:
					trocaLinhaPeq((rand() % 3) + 3, (rand() % 3) + 3);
					break;
					
				case 2: 
					trocaLinhaPeq((rand() % 3) + 6, (rand() % 3) + 6);
					break;
					
			}
			break;
		case 1: 
			trocaLinhaGrande((rand() % 3), (rand() % 3));
			break;
			
		case 2: 
			switch(bloco) {
				case 0:
					trocaColunaPeq((rand() % 3), (rand() % 3));
					break;
					
				case 1:
					trocaColunaPeq((rand() % 3) + 3, (rand() % 3) + 3);
					break;
					
				case 2: 
					trocaColunaPeq((rand() % 3) + 6, (rand() % 3) + 6);
					break;
				}
			break;
		case 3: 
			trocaColunaGrande((rand() % 3), (rand() % 3));
			break;
			
		case 4: 
			giraVertical();			
			break;
			
		case 5: 
			giraHorizontal();
			break;
			
		case 6: 
			trocaColLinha();
			break;
			
		case 7: 
			inverteMatriz();
			break;
			
		case 8: 
			inverteMatriz2();
			break;
			
		case 9: 
			substitui((rand() % 9) + 1, (rand()  % 9)+ 1);
			break;
		}
	}
}

int main()
{

	system("clear");

	puts("\n");
	puts("--------------------------------------------------");
	puts("--------------------- SUDOKU ---------------------");
	puts("--------------------------------------------------");
	puts("Thiago Medeiros");
	puts("\n");
	
	char op;

	do {

		puts("Entre com uma opção:");
		puts("1. Gerar sudoku (arquivo será criado automaticamente).");
		puts("2. Solução sudoku (arquivo será criado automaticamente).");
		puts("\n");
		puts("---");		
		puts("'X' - SAIR\n");
	

		__fpurge(stdin);
		scanf("%c", &op);

			switch(op) {
				case '1':
					system("clear");
					geraSudoku();
					geraArquivoSudokuModelo();
					geraArquivoeImprimeSudoku();
					break;

				case '2':
					system("clear");
					imprimeSudokuCompleto();
					geraArquivoSudokuCompleto();
					break;

				case 'X':
					return 0;

				case 'x':
					return 0;

				default:
					system("clear");
					puts("ERRO: Opção inválida.\n");
					break;
			}

	} while(op != 0);

	return 0;
}
