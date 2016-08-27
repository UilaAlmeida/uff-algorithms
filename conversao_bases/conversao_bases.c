#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//------------------------------ FUNCTIONS --------------------------------------

#define INVALIDO -1

char int_hexadecimal(int digito){
	switch(digito){
		case 10:
			return 'A';
		case 11:
			return 'B';
		case 12:
			return 'C';
		case 13:
			return 'D';
		case 14:
			return 'E';
		case 15:
			return 'F';
		default: 
			return INVALIDO + '0';
	}
}

int hexadecimal_int(char digito){
	switch(digito){
		case 'A':
			return 10;
		case 'B':
			return 11;
		case 'C':
			return 12;
		case 'D':
			return 13;
		case 'E':
			return 14;
		case 'F':
			return 15;
		default: 
			return INVALIDO;
	}
}

int char_int(char digito, int base_entrada){
	//printf("[DEBUG] Transformando em inteiro digito %c\n", digito);
	if(digito >= '0' && digito <= '9'){
		return atoi(&digito);
	}
	if((digito >= 'A' && digito <= 'F') && (base_entrada = 16)){
		return hexadecimal_int(digito);
	}
	return INVALIDO;
}

char int_char(int digito, int base_saida){
	//printf("[DEBUG] Transformando em char digito %d\n", digito);
	if(digito >= 0 && digito <= 9){
		return digito + '0';
	}
	if((digito >= 10 && digito <= 15) && (base_saida = 16)){
		return int_hexadecimal(digito);
	}
	return INVALIDO + '0';
}

int converte_base_x(char numero[], int numero_base_10, int base_saida){
	//printf("\n[DEBUG] Iniciando conversao do numero decimal %d para base %d\n", numero_base_10, base_saida);

	char resultado[1000];
	int quociente=0, resto=0, indice=0, i=0;

	while(numero_base_10 != 0){
		quociente = (numero_base_10 / base_saida);
		resto = (numero_base_10 % base_saida);
		//printf("[DEBUG] Quociente: %d dividido %d = %d | Resto: %d modulo %d = %d\n", numero_base_10, base_saida, quociente, numero_base_10, base_saida, resto);

		numero_base_10 = quociente;
		resultado[indice++] = int_char(resto, base_saida);
	}

	printf("Numero %s(%d) = ", numero, base_saida);
	for(i = indice-1; i >= 0; i--){
		printf("%c", resultado[i]);
	}
	printf("\n");

	return 1;
}

int converte_base_10(char numero[], int base_entrada, int base_saida){
	//printf("\n[DEBUG] Iniciando conversao do numero %s para base %d\n", numero, base_entrada);

	int i=0, posicao=0;
	int resultado=0;
	
	for (i = strlen(numero)-1; i >= 0; i--){
		char digito_char = numero[posicao++];
		int digito_int = char_int(digito_char, base_entrada);

		double termo = (pow(base_entrada, i) * digito_int);
		//printf("[DEBUG] Indice: %d - Digito: %d | Calculo: (%d ^ %d) * %d = %f \n", i, digito_int, base_entrada, i, digito_int, termo);
		resultado += termo;
	}

	//printf("[DEBUG] Resultado = %d\n", resultado);
	//printf("[DEBUG] Conversao finalizada\n");

	if(base_saida == 10){
		printf("Numero %s(%d) = %d\n", numero, base_saida, resultado);
	}
	return resultado;
}

int numero_valido(char numero[], int base_entrada){
	//printf("\n[DEBUG] Iniciando validacao do numero %s na base %d", numero, base_entrada);

	int i=0, valido=1;
	int quantidade_digitos = strlen(numero);
	for (i = 0; i < quantidade_digitos; i++){
		char digito_char = numero[i];
		int digito_int = char_int(digito_char, base_entrada);

		//printf("[DEBUG] Verificando validade do digito %d\n", digito_int);
		if(digito_int == INVALIDO || (digito_int < 0 || digito_int >= base_entrada)){
			valido = 0;
			//printf("[DEBUG] Digito %d invalido\n", digito_int);
		}
	}
	//printf("[DEBUG] Validacao finalizada\n");
	return valido;
}

void converte(char numero[], int base_entrada, int base_saida){
	int numero_base_10 = converte_base_10(numero, base_entrada, base_saida);
	if(base_saida != 10){
		converte_base_x(numero, numero_base_10, base_saida);
	}
}

//------------------------------ FUNCTIONS --------------------------------------

int main()
{
	char numero[1000];
	int base_entrada=0, base_saida=0;
	int resultado=0;

	printf("Digite um numero: ");
	scanf("%s", numero);
	printf("Digite a base de entrada: ");
	scanf("%d", &base_entrada);
	printf("Digite a base de saida: ");
	scanf("%d", &base_saida);

	printf("-----------------------------\n");

	if(numero_valido(numero, base_entrada)){
		converte(numero, base_entrada, base_saida);
	}else {
		printf("\nNumero %s na base %d invalido!\n", numero, base_entrada);
	}

	getchar();
	return 0;
}