//SENAC Santo Amaro - Engenharia de Computação 
//Linguagem de Programacao
//Rafael Fortunatti Simoes - 1 Semestre Noturno
//Projeto Preliminar

//Codificação e decodificação atraves de File IO

#include <stdio.h>

#define MAX_IN 25

//Global declaration dos ponteiros de arquivos
FILE *file_ptr_in;
FILE *file_ptr_out;

//Protótipos
void func_code ();
void func_decode ();
void capture_files_ptrs ();
int chck_hex_condition (int base, int exp);
int func_hextodec (char arr_hex[]);

int main () {
	
	int menu_option = 0;
	char chck_continue;
	//Garanto que os ponteiros nao contem lixo
	file_ptr_in = NULL;
	file_ptr_out = NULL;
	
	printf ("Coder/Decoder v1.0\n");
	
	//Laco primario de execucao
	while (0 == 0) {
		menu_option = 0;
		chck_continue = '0';
		while (menu_option < 1 || menu_option > 2) {
			printf ("\nEntre com a opcao desejada:\n1 - Codificar\n2 - Decodificar\n");
			scanf ("%d", &menu_option);
		}
		
		if (menu_option == 1) {
			capture_files_ptrs ();
			func_code ();
			//Finalizo o buffer de IO e reseto os ponteiros
			fclose (file_ptr_out);
			fclose (file_ptr_in);
			file_ptr_in = NULL;
			file_ptr_out = NULL;
			printf ("\nOPERACAO EFETUADA COM SUCESSO!\n");
		}
		
		if (menu_option == 2) {
			capture_files_ptrs ();
			func_decode ();
			//Finalizo o buffer de IO e reseto os ponteiros
			fclose (file_ptr_out);
			fclose (file_ptr_in);
			file_ptr_in = NULL;
			file_ptr_out = NULL;
			printf ("\nOPERACAO EFETUADA COM SUCESSO!\n");
		}
		
		do {
			printf ("\nDeseja efetuar outra operacao? (s/n)");
			chck_continue = getc (stdin);
			if (chck_continue == 's')
				break;
			if (chck_continue == 'n')
				return 0;
			}while (chck_continue != 'n' || chck_continue != 's');
	}
				
}

//Funcao que solicita, captura e atribui o nome dos arquivos aos ponteiros
//correspondentes
void capture_files_ptrs () {

	char file_name_in[100], file_name_out[100];
	
	while (file_ptr_in == NULL) {
		printf ("Entre com o nome do arquivo de entrada: ");
		scanf ("%s", file_name_in);
		file_ptr_in = fopen (file_name_in, "r");
		if (file_ptr_in != NULL) {
			break;
		}
		printf ("\nERRO! Tente novamente!\n");
	}
	
	printf ("\n");
	
	while (file_ptr_out == NULL) {
		printf ("Entre com o nome do arquivo de saida: ");
		scanf ("%s", file_name_out);
		file_ptr_out = fopen (file_name_out, "w");
		if (file_ptr_out != NULL) {
			break;
		}
		printf ("\nERRO! Tente novamente!\n");
	}
}


void func_code () {

	char vec_caracIn[MAX_IN], aux_char;
	int lines_qnt = 0, count_line, j;
	//Capturo a quantidade de linhas no arquivo
	fscanf (file_ptr_in, "%d", &lines_qnt);
	fgetc (file_ptr_in);
	fprintf (file_ptr_out, "%d\n", lines_qnt);
	
	//A codificacao utiliza a conversao nativa da funcao fprintf,
	//portanto necessito capturar cada caractere individualmente
	//e imprimi-lo no arquivo de saida com o parametro "%X".
	
	for(count_line = 0; count_line < lines_qnt; count_line++) {
        //Verificacao da ultima linha que precisa ser tratada de forma diferenciada
		if (count_line == lines_qnt - 1) {
            do {
                aux_char = fgetc (file_ptr_in);
				if (aux_char == EOF)
					break;
				fprintf (file_ptr_out, "%X", aux_char);
            }while (aux_char != EOF);
			//Finalizo o buffer de IO
			return;
        }
        else {
            //Se nao e a ultima linha, trato da forma usual com fgets
			fgets (vec_caracIn, MAX_IN + 1, file_ptr_in);
        }
		//O laco a seguir e o responsavel em gravar o arquivo de saida
		//em linhas que nao a ultima
		for (j = 0; j < MAX_IN; j++) {
			if (vec_caracIn[j] == '\n')
				break;
			fprintf (file_ptr_out ,"%X", vec_caracIn[j]);
		}
		if (count_line != lines_qnt - 1)
			fprintf (file_ptr_out, "\n");
	}

}

void func_decode () {
	
	int lines_qnt = 0, value_int, i;
	char arr_aux[2], aux_char;
	char * ptr_error;
	
	//Capturo a quantidade de linhas no arquivo
	fscanf (file_ptr_in, "%d", &lines_qnt);
	fgetc (file_ptr_in);
	fprintf (file_ptr_out, "%d\n", lines_qnt);
	
	//Para decodificar, capturo dois caracteres por vez, obtendo um valor
	//em hex. Com este valor obtido, converto para int utilizando o algoritmo
	//semelhante ao usado no calculo manual, obtendo o equivalente decimal ASCII
	//do caractere. Ao final, apenas imprimo no arquivo de saida.
	
	for (i = 1; i <= lines_qnt; i++) {
		do {
			int j;
			//Laco para capturar os dois caracteres hex.
			for (j = 0; j <= 1; j++) {
				arr_aux[j] = fgetc (file_ptr_in);
				if (arr_aux[j] == '\n')
					break;
			}
			if (arr_aux[0] == '\n')
				break;
			if (feof (file_ptr_in) != 0)
				return;
			value_int = func_hextodec (arr_aux);
			fprintf (file_ptr_out, "%c", value_int);	
		}while (aux_char != EOF);
		if (i < lines_qnt)
			fprintf (file_ptr_out, "\n");
	}
}


//A funcao abaixo realiza a conversao de um valor em Hex para Dec
int func_hextodec (char arr_hex[]) {
	int count_sig, dec_conv = 0, count_arr;
	for (count_sig = 1, count_arr = 0; count_sig >= 0; count_sig--, count_arr++) {
		//Como a base hex tem 16 caracteres diferentes, valeu mais a pena converte-los
		//atraves de condicionais simples
		if (arr_hex[count_arr] == 'A')
			dec_conv = dec_conv + (10 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == 'B')
			dec_conv = dec_conv + (11 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == 'C')
			dec_conv = dec_conv + (12 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == 'D')
			dec_conv = dec_conv + (13 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == 'E')
			dec_conv = dec_conv + (14 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == 'F')
			dec_conv = dec_conv + (15 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '0')
			dec_conv = dec_conv + (0 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '1')
			dec_conv = dec_conv + (1 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '2')
			dec_conv = dec_conv + (2 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '3')
			dec_conv = dec_conv + (3 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '4')
			dec_conv = dec_conv + (4 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '5')
			dec_conv = dec_conv + (5 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '6')
			dec_conv = dec_conv + (6 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '7')
			dec_conv = dec_conv + (7 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '8')
			dec_conv = dec_conv + (8 * chck_hex_condition(16, count_sig));
		if (arr_hex[count_arr] == '9')
			dec_conv = dec_conv + (9 * chck_hex_condition(16, count_sig));
	}
	//Retorna o valor do hex ja na base dec.
	return dec_conv;
}

//Esta funcao simplifica a potencia. Poderia ter usado a pow(), porem
//pertence a biblioteca math.h e foge das exigencias do projeto.
int chck_hex_condition (int base, int exp) {
	int val = base, i;
	if (exp == 0)
		return 1;
	if (exp = 1)
		return 16;
}
		
		
		
		
		