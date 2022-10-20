#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct usuario
{
	char nome[40],emails[3][40],telefone[3][15],profissao[40],datanasc[10],cpf[15],nro[15],cep[15];
	
}usuarios[20];

struct livro
{
    char titulo[40], genero[40], autor[40],isbn[13],num_pagina[5]; 
}livros[20];



int buscar(usuario *Usuarios,int pos,char *cpf)
{
	int i,result;
	for(i=0;i<pos;i++)
	{
		result = strcmp(Usuarios[i].cpf,cpf);
		if (result == 0)
			return i;
	}
	return -1;
}

void incluir_usuario(usuario *Usuarios,int *qtdCadastro)
{
	system("cls");
	char cpf[15];
	struct usuario user;
	int aut;
	fflush(stdin);
	printf("Digite o CPF :");
	gets(cpf);
	
	aut = buscar(Usuarios,*qtdCadastro,cpf);
	
	if(aut == -1)
	{
		strcpy(user.cpf,cpf);
		fflush(stdin);
		printf("Digite o Nome :");
		gets(user.nome);
		fflush(stdin);
		printf("Digite o Número :");
		gets(user.nro);
		fflush(stdin);
		printf("Digite o CEP :");
		gets(user.cep);
		fflush(stdin);
		printf("Digite o(s) email(s) :"); //Falta incluir repetição para colocar mais de 1 se quiser!!!
		gets(user.emails[0]);
		fflush(stdin);
		printf("Digite o(s) telefone(s) :");
		gets(user.telefone[0]);
		fflush(stdin);
		printf("Digite o data de nascimento dd/mm/aa :");
		gets(user.datanasc);
		fflush(stdin);
		printf("Digite a profissão :");
		gets(user.profissao);
	
		fflush(stdin);
	
		Usuarios[*qtdCadastro] = user;
		(*qtdCadastro)++;
		printf("\nUsuário cadastrado com sucesso !\n\n");
	}
	else
		printf("Usuário já está cadastrado !\n\n");
	
	system("pause");
	
}

void listarT_usuario(usuario *Usuarios,int pos)
{
	system("cls");
	
	int i=0;
	if (pos > 0)
	{
		for(i=0;i<pos;i++)
		{
			printf("Listando %dº usuário \n",i+1);
			printf("Nome :\n");
			puts(Usuarios[i].nome);
			printf("\n");
			printf("CPF :\n");
			puts(Usuarios[i].cpf);
			printf("\n");
			printf("Número :\n");
			puts(Usuarios[i].nro);
			printf("\n");
			printf("CEP :\n");
			puts(Usuarios[i].cep);
			printf("\n");
			printf("Email(s) :\n");
			puts(Usuarios[i].emails[0]);
			printf("\n");
			printf("Telefone(s) :\n");
			puts(Usuarios[i].telefone[0]);
			printf("\n");
			printf("Data de nascimento :\n");
			puts(Usuarios[i].datanasc);
			printf("\n");
			printf("Profissão :\n");
			puts(Usuarios[i].profissao);
			printf("\n");
			printf("\n");
		}
	system("pause");
	}
	else
	{
		printf("Sem cadastros disponiveis !");
		system("pause");
	}
	
}
int listarE_usuario(usuario *Usuarios,int pos)
{
	int i,comparacao;
	char cpf[30];
	system("cls");
	printf("Digite o CPF do usuário :\n");
	fflush(stdin);
	gets(cpf);
	
	for(i=0;i<pos;i++)
	{
		comparacao = strcmp(Usuarios[i].cpf,cpf);
		if(comparacao == 0)
		{
			system("cls");
			printf("Listando usuário \n");
			printf("Nome :\n");
			puts(Usuarios[i].nome);
			printf("\n");
			printf("CPF :\n");
			puts(Usuarios[i].cpf);
			printf("\n");
			printf("Número :\n");
			puts(Usuarios[i].nro);
			printf("\n");
			printf("CEP :\n");
			puts(Usuarios[i].cep);
			printf("\n");
			printf("Email(s) :\n");
			puts(Usuarios[i].emails[0]);
			printf("\n");
			printf("Telefone(s) :\n");
			puts(Usuarios[i].telefone[0]);
			printf("\n");
			printf("Data de nascimento :\n");
			puts(Usuarios[i].datanasc);
			printf("\n");
			printf("Profissão :\n");
			puts(Usuarios[i].profissao);
			printf("\n");
			return 1;	
		}
	}
	
	return -1;
}

int excluir_usuario(usuario *Usuarios,int *pos)
{
	int i,comparacao,j;
	char cpf[30];
	system("cls");
	printf("Digite o CPF do usuário :\n");
	fflush(stdin);
	gets(cpf);
	
	for(i=0;i<*pos;i++)
	{
		comparacao = strcmp(Usuarios[i].cpf,cpf);
		if(comparacao == 0)
		{
			for(j=0;j<*pos;j++)
			{
				Usuarios[j] = Usuarios[j+1];
			}
			(*pos)--;
			
			return 1;
		}
		
	}
	
}

void alterar_usuario(usuario *Vetor,int pos)
{
	char cpf[15];
	int posicao,op;
	system("cls");
	printf("Digite o cpf :\n");
	fflush(stdin);
	gets(cpf);
	
	posicao = buscar(Vetor,pos,cpf);
	
	if (posicao != -1)
	{
		do
		{
			printf("O que deseja alterar ?\n\n");
			printf("1. Cpf\n");
			printf("2. Nome\n");
			printf("3. Número\n");
			printf("4. Cep\n");
			printf("5. E-mail(s)\n");
			printf("6. telefone(s)\n");
			printf("7. Data de nascimento\n");
			printf("8. Profissão\n\n");
		
			scanf("%d",&op);
			fflush(stdin);
			system("cls");
			switch(op)
			{
				case 1:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].cpf); //Falta verificar se está cadastrado !!
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 2:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].nome);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 3:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].nro);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 4:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].cep);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 5:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].emails[0]);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 6:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].telefone[0]);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 7:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].datanasc);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				case 8:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].profissao);
					printf("Dado alterado com sucesso !\n\n");
					system("pause");
					break;
				default:
					printf("opção inválida !");
					system("pause");
			}
		}while(op>8 || op <=0);
	}
	else
	{
		printf("Usuário não cadastrado !\n\n");
		system("pause");
	}
}

int buscar_livro(livro *livros, int pos, char *isbn)
{
  int i, result;
  for(i=0; i,pos; i++)
  {
    result = strcmp(livros[i].isbn,isbn);
    if (result == 0)
      return i;
  }
  return -1;
}

void adicionar_livro(livro *livros, int *qtdCadastro)
{
  system("cls");
  char isbn[13];
  struct livro user;
  int aut;
  fflush(stdin);
  printf("DIgite o ISBN do livro: ");
  gets(isbn);

  aut = buscar_livro(livros, *qtdCadastro,isbn);
  

  fflush(stdin);
  printf("Digite o título do livro: ");
  gets(user.titulo);

  fflush(stdin);
  printf("Digite o gênero do livro: ");
  gets(user.genero);

  fflush(stdin);
  printf("Digite o autor do livro - Se for mais de um, coloque  / na frente: ");
  gets(user.autor);

  fflush(stdin);
  printf("Digite o número de páginas: ");
  gets(user.num_pagina);

  fflush(stdin);

  livros[*qtdCadastro] = user;
  (*qtdCadastro)++;
 }

int menu()
{
	system("cls");
	int op;
	printf("---------Menu Principal---------");
	printf("\n1. Submenu de Usuários\n");
	printf("2. Submenu de Livros\n");
	printf("3. Submenu de Empréstimos\n");
	printf("4. Submenu de Relatórios\n");
	printf("5. Sair\n");
	printf("--------------------------------\n\n");
	
	scanf("%d",&op);
	return op;
}
void submenu_usuarios(int *pos)
{
	system("cls");
	int op,flag;
	printf("---------Submenu Usuários---------");
	printf("\n1. Listar todos\n");
	printf("2. Listar especifico\n");
	printf("3. Incluir usuário\n");
	printf("4. Alterar usuario\n");
	printf("5. Excluir\n");
	printf("-----------------------------------\n\n");
	
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			listarT_usuario(usuarios,*pos);
			
			break;
		case 2:
			flag = listarE_usuario(usuarios,*pos);
			if (flag == -1)
				printf("Usuário não cadastrado!\n");
			system("pause");
			break;
		case 3:
			incluir_usuario(usuarios,pos);
			break;
		case 4:
			alterar_usuario(usuarios,*pos);
			break;
		case 5:
			excluir_usuario(usuarios,pos);
			break;
		default:
			printf("Opção inválida !\n");
			system("pause");
			break;
	}
}

int main()
{
	int op,pos=0;
	setlocale(LC_ALL,"Portuguese");
	
	do
	{
		op = menu();
		switch(op)
		{
			case 1:
				submenu_usuarios(&pos);
				break;
			case 2:
				//submenu_livros();
				break;
			case 3:
				//submenu_emprestimos();
				break;
			case 4:
				//submenu_relatorios();
				break;
			case 5:
				printf("\nSaindo...");
				break;
			default:
				printf("Opção inválida !\n");
				system("pause");
				break;
		}
	}while(op!=5);
	
}
