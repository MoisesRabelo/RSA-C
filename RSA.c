#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <math.h>

#define TAM 2000

//variáveis Globais
long int e[TAM],d[TAM],temp[TAM],m[TAM],en[TAM];
long int first,second; //os dois primos
long int totient,n;
long int i,j,flag;
char msg[TAM];

//funções Gráficas
void menu(int *opcao);
void menu_1();
void menu_2();
void continuar();
void sair();
void false_option();
void false_primo();

//funções Funcionais
void recebe_primo();
void encrypt();
void decrypt();
long int constructor_d(long int);
void constructor_e();
void create_temp();
int verifica_primo(long int);

//______________________________

void menu(int *opcao){
	system("cls");
	printf("       _______________________________________________________________________\n");
	printf("      |                                                                      |\n");       
	printf("      |      ___________________________________________________________     |\n");
	printf("      |     |                           RSA                             |    |\n");
	printf("      |     |___________________________________________________________|    |\n");
	printf("      |                                                                      |\n");
	printf("      |                    |----------->MENU<-----------|                    |\n");
	printf("      |                    |____________________________|                    |\n");
	printf("      |                    |                            |                    |\n");
	printf("      |                    |  1 - Codificar Mensagem    |                    |\n");
	printf("      |                    |  2 - Decodificar Mensagem  |                    |\n");
	printf("      |                    |  0 - Sair                  |                    |\n");              
	printf("      |                    |____________________________|                    |\n");
	printf("      |                                                                      |\n");
	printf("      |______________________________________________________________________|\n");              
	printf("                             INFORME A SUA OPÇÃO: ");
	scanf("%d",opcao);//recebe o numero para a opcao
}
void menu_1(){
	system("cls");
    printf("\n _____________________________________________________________________________");
    printf("\n|                          Codificação de Mensagem                            |");
    printf("\n|_____________________________________________________________________________|\n\n");
}
void menu_2(){
	system("cls");
	printf("\n _____________________________________________________________________________");
	printf("\n|                          Decodificação de Mensagem                          |");
	printf("\n|_____________________________________________________________________________|\n\n");
}
void continuar(){
	
	printf("\n|                   PRESSIONE QUALQUER TECLA PARA CONTINUAR                   |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
void sair(){
	printf("\n _____________________________________________________________________________");
	printf("\n|                     VOCE OPTOU POR FINALIZAR O PROGRAMA!                    |");
	printf("\n|                      PRESSIONE QUALQUER TECLA PARA SAIR                     |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
void false_option(){
	printf("\n _____________________________________________________________________________");
	printf("\n|                       OPÇÃO INVÁLIDA! TENTE NOVAMENTE                       |");
	printf("\n|                   PRESSIONE QUALQUER TECLA PARA CONTINUAR                   |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
void false_primo(){
	printf("\n _____________________________________________________________________________");
	printf("\n|                       PRIMO INVÁLIDO! TENTE NOVAMENTE                       |");
	printf("\n|                   PRESSIONE QUALQUER TECLA PARA CONTINUAR                   |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
void recebe_primo(){
	
	while(1)
	{
		printf("\nPrimeiro Número Primo:\n"); 
		scanf("%d",&first);	 
		flag = verifica_primo(first);
	 
		if(flag == 0)
		{ 
			false_primo();
			menu_1();
		}else break;
	}
	
 	
 	while(1)
	{
		printf("\nSegundo Número Primo\n"); 
		scanf("%d",&second);	 
		flag = verifica_primo(second);
	 
		if(flag == 0 || first == second)
		{ 
			false_primo();
			menu_1();
		}else break;
	}
	
}
int verifica_primo(long int pr){
	
	long int i;
	j = sqrt(pr);
 
	for (i = 2;  i<=j; i++) {
 		if(pr%i == 0) return 0; 
	} 
	return 1; 
}
void create_temp(){
	
	long int pt,k,length = strlen(msg);
	long int key = e[0];
	for(i = 0; i < length; i++)
	{
		pt = m[i];
		pt = pt-96;
		k = 1;
 
		for (j = 0; j < key; j++) 
		{ 
			k = k*pt;
 			k = k%n;
 		}
 		temp[i] = k;
	}
}
void encrypt() {
 
	long int pt,ct,k,length;
 	long int key = e[0];
 	
	length = strlen(msg);
	i = 0;
	
	while(i != length)
	{
		pt = m[i];
		pt = pt-96;
		k = 1;
 
		for (j = 0; j < key; j++) 
		{ 
			k = k*pt;
 			k = k%n;
 		}
 		temp[i] = k;
 		ct = temp[i] +96;
 		en[i] = ct;
 		i++;
 	}
	en[i] = -1;
 
 	printf("\nn: "); 
	printf("%ld",n);
 
 	printf("\ne and d:\n"); 
 	printf("\n%ld\t%ld",e[0],d[0]);
 
	printf("\nMensagem Encriptada:\n"); 
	for (i=0;en[i]!=-1;i++) printf("%c",en[i]); 
}
void decrypt() {

	long int k,pt,ct;
 	long int key = d[0];
	i = 0;
 	create_temp();
	while(en[i] != -1)
	{ 
		ct = temp[i];
		k = 1;
 
		for (j = 0; j < key; j++) {
			k = k*ct;
			k = k%n;
		} 
		pt = k+96;
 		m[i] = pt;
 		i++;
 	}
	m[i] = -1;
 
	printf("\nMensagem Descriptografada:\n");
 
 	for(i = 0; msg[i] != '\0'; i++) {
 		if(m[i] == 95) msg[i] = 32;
	}
 	
	for (i = 0; m[i] != -1; i++) printf("%c",m[i]); 
}
void constructor_e() {
 
	int k = 0;
 
	for (i = 2; i < totient; i++)
	{
		if(totient % i == 0) continue; //se totient for divisivel por i, pulamos para o prox laço
 
		flag = verifica_primo(i);
 
		if(flag == 1 && i != first && i != second)
		{
			e[k] = i;
 
			flag = constructor_d(e[k]);
 
			if(flag > 0) { 
				d[k] = flag;  //se os requisitos forem cumpridos, ele vira 
				k++;
			}
			if(k == (TAM-1)) break;
		}
	}
}
long int constructor_d(long int e) {
 
	long int k = 1;
 
	while(1)
	{
 		k = k + totient;
 		if(k%e == 0) return (k/e);
	}
 
}
int main(){
	
	int opcao;
	bool fim = true;
	opcao = 0;

	setlocale(LC_ALL, "Portuguese"); //Para aceitar acentuação
	
	while(fim)
	{
		menu(&opcao);
		
		if(opcao > 2) false_option();
		
		switch(opcao)
		{
			case 0: //Fechar software
				sair();
				fim = false;
				break;
				
			case 1: //criptografar mensgagem
				menu_1();
				recebe_primo();
			 
				printf("\nEscreva a mensagem: \n");
				fflush(stdin); //limpar buffer do teclado
				gets(msg);
			 
				for (i = 0; msg[i] != '\0'; i++) m[i] = msg[i];
			 
				n = first*second; //módulo da chave privada e pública
			 
				totient = (first-1)*(second-1); //função totient
			 
				constructor_e();
				encrypt();
				
				continuar();
				break;
			
			case 2: //descriptografar mensagem
				menu_2();
				
				printf("\nDigite n: \n");
				//fflush(stdin); //limpar buffer do teclado
				scanf("%d", &n);
				
				printf("\nChave Pública(e): \n");
				fflush(stdin); //limpar buffer do teclado
				scanf("%d", &e[0]);
				
				printf("\nChave Privada(d): \n");
				fflush(stdin); //limpar buffer do teclado
				scanf("%d", &d[0]);
				
				
				// Ler a mensagem
				
				printf("\nEscreva a mensagem: \n");
				fflush(stdin); //limpar buffer do teclado
				scanf("%ld", &en);
				
				//recebe_chave();
				decrypt();
				continuar();
				break;				
		}		
	}
	return 0;
}
