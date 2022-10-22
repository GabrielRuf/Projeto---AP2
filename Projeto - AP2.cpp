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
    char titulo[40], genero[40], autor[3][40],isbn[13],num_pagina[5]; 
}livros[20];


struct emprestimo
{
	char chave_emprestimos[3][40],datadevolucao[10],valormulta[4];
}emprestimos[20];


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

int buscar_emprestimo(emprestimo *Emprestimos,int pos,char *chave)
{
	int i,comparacao,comparacao2,comparacao3,j=0;
	
	
	for(i=0;i<pos;i++)
	{
			comparacao = strcmp(Emprestimos[i].chave_emprestimos[j],chave);
			if(comparacao == 0)
			{
				j++;
				comparacao2 = strcmp(Emprestimos[i].chave_emprestimos[j],chave+40);
				if(comparacao2 == 0)
				{
					j++;
					comparacao3 = strcmp(Emprestimos[i].chave_emprestimos[j],chave+80);
					if(comparacao3 == 0)
					{
						return i;
					}
					else
						j--;
						
				}
				else
					j--;
			}
	}
	return -1;
}

int buscar_livro(livro *livros, int pos, char *isbn)
{
  int i, result;
  for(i=0; i<pos; i++)
  {
    result = strcmp(livros[i].isbn,isbn);
    if (result == 0)
      return i;
  }
  return -1;
}
void incluir_emprestimo(emprestimo *Emprestimos,livro *livros,usuario *Usuarios,int *qtdCadastroLivros,int *qtdCadastroUsers,int *qtdCadastroEmprestimos)
{
	system("cls");
	char cpf[15],isbn[13],dataretirada[7],chave_emprestimos[3][40];
	
	struct emprestimo emprestimo;
	int aut,i;
	fflush(stdin);
	printf("Digite o CPF :");
	gets(cpf);
	
	aut = buscar(Usuarios,*qtdCadastroUsers,cpf);
	if(aut != -1)
	{
		fflush(stdin);
		printf("\nDigite o ISBN do livro :\n");
		gets(isbn);
		
		aut = buscar_livro(livros,*qtdCadastroLivros,isbn);
		if(aut != -1)
		{
			fflush(stdin);
			printf("Digite a Data de entrada no formato dd/mm/aaaa sem as barras :");
			gets(dataretirada);
			strcpy(chave_emprestimos[0],cpf);
			strcpy(chave_emprestimos[1],isbn);
			strcpy(chave_emprestimos[2],dataretirada);
				
			aut = buscar_emprestimo(Emprestimos,*qtdCadastroEmprestimos,*chave_emprestimos);
			
			if (aut == -1)
			{
				for(i=0;i<3;i++)
				{
					strcpy(emprestimo.chave_emprestimos[i],chave_emprestimos[i]);
				}
				
				
				fflush(stdin);
				printf("Digite a data de devolução :\n");
				gets(emprestimo.datadevolucao);
				fflush(stdin);
				printf("Digite o valor de multa por atraso :\n");
				gets(emprestimo.valormulta);
				Emprestimos[*qtdCadastroEmprestimos] = emprestimo;
				(*qtdCadastroEmprestimos)++;
					
				printf("\nEmpréstimo cadastrado com sucesso !\n\n");
			}
			else
				printf("Impossivel fazer esse impréstimo !\n");		
		}
		else
			printf("Livro não cadastrado !\n");
		
	}else
		printf("Usuário não cadastrado !\n");

	system("pause");	
}

void excluir_emprestimos(emprestimo *Emprestimos,int *pos)
{
	system("cls");
	int i,achou;
	char chavetemp[3][40];
	fflush(stdin);
	printf("Digite o CPF:\n");
	gets(chavetemp[0]);
	printf("Digite o ISBN:\n");
	gets(chavetemp[1]);
	printf("Digite a data de retirada:\n");
	gets(chavetemp[2]);
	
	achou = buscar_emprestimo(Emprestimos,*pos,*chavetemp);
	
	if(achou != -1)
	{
		for(i=0;i<*pos;i++)
			{
				Emprestimos[i] = Emprestimos[i+1];
			}
			(*pos)--;
		
		printf("Empréstimo excluido com sucesso !\n");
	}
	else
		printf("Empréstimo não localizado!\n");
	system("pause");
	
}

void alterar_emprestimos(emprestimo *Emprestimos,livro *livros,usuario *Usuarios,int qtdCadastroLivros,int qtdCadastroUsers,int qtdCadastroEmprestimos)
{
	system("cls");
	int i,achou,op,procurado;
	char chavetemp[3][40];
	fflush(stdin);
	printf("Digite o CPF:\n");
	gets(chavetemp[0]);
	printf("Digite o ISBN:\n");
	gets(chavetemp[1]);
	printf("Digite a data de retirada:\n");
	gets(chavetemp[2]);
	
	achou = buscar_emprestimo(Emprestimos,qtdCadastroEmprestimos,*chavetemp);
	
	if(achou != -1)
	{
		do
		{
		
			system("cls");
			printf("O que deseja alterar ?\n\n");
			printf("1. CPF\n");
			printf("2. ISBN\n");
			printf("3. Data de retirada\n");
			printf("4. Data de devolução\n");
			printf("5. Valor de multa por atraso\n\n");
			scanf("%d",&op);
			fflush(stdin);
			switch(op)
			{
				case 1:
					printf("Digite o CPF:\n");
					gets(chavetemp[0]);
					procurado = buscar_emprestimo(Emprestimos,qtdCadastroEmprestimos,*chavetemp);
					if(procurado != -1)
					{
						printf("Cadastro indisponível!\n");
					}
					else
					{
						procurado = buscar(Usuarios,qtdCadastroUsers,chavetemp[0]);
						if(procurado != -1)
						{
							strcpy(Emprestimos[achou].chave_emprestimos[0],chavetemp[0]);
							printf("Dado alterado !\n");
						}
						else
							printf("CPF não cadastrado!\n");
						
					}
					
					break;
				case 2:
					printf("Digite o ISBN:\n");
					gets(chavetemp[1]);
					procurado = buscar_emprestimo(Emprestimos,qtdCadastroEmprestimos,*chavetemp);
					if(procurado != -1)
					{
						printf("Cadastro indisponível!\n");
					}
					else
					{
						procurado = buscar_livro(livros,qtdCadastroLivros,chavetemp[1]);
						if(procurado != -1)
						{
							strcpy(Emprestimos[achou].chave_emprestimos[1],chavetemp[1]);
							printf("Dado alterado !\n");
						}
						else
							printf("ISBN não cadastrado!\n");
					}
					
					break;
				case 3:
					printf("Digite a data de retirada:\n");
					gets(chavetemp[2]);
					procurado = buscar_emprestimo(Emprestimos,qtdCadastroEmprestimos,*chavetemp);
					if(procurado != -1)
					{
						printf("Cadastro indisponível!\n");
					}
					else
					{
						strcpy(Emprestimos[achou].chave_emprestimos[2],chavetemp[2]);
						printf("Dado alterado !\n");
					}
					
					break;
				case 4:
					printf("Digite a data de devolução :\n");
					gets(Emprestimos[qtdCadastroEmprestimos].datadevolucao);
					printf("Dado alterado!\n");
					
					break;
				case 5:
					printf("Digite o valor de multa por atraso :\n");
					gets(Emprestimos[qtdCadastroEmprestimos].valormulta);
					printf("Dado alterado!\n");
					
					break;
				default : printf("Opção inválida!");
			}
		}while(op <= 0 || op >=6);
	}
	else
		printf("Empréstimo não localizado!\n");
	system("pause");
}



void listarT_emprestimos(emprestimo *Emprestimos,int pos)
{
	system("cls");
	int i;
	
	if (pos > 0)
	{
		for(i=0;i<pos;i++)
		{
			printf("Listando %dº empréstimo \n",i+1);
			printf("CPF :\n");
			puts(Emprestimos[i].chave_emprestimos[0]);
			printf("ISBN :\n");
			puts(Emprestimos[i].chave_emprestimos[1]);
			printf("Data de retirada :\n");
			puts(Emprestimos[i].chave_emprestimos[2]);
			printf("Data de devolução :\n");
			puts(Emprestimos[i].datadevolucao);
			printf("Valor de multa por atraso :\n");
			puts(Emprestimos[i].valormulta);
		}
		
	}
	else
		printf("Não existe empréstimo cadastrado!");
	system("pause");
	
}
int listarE_emprestimos(emprestimo *Emprestimos,int pos)
{
	system("cls");
	int i,achou;
	char chavetemp[3][40];
	fflush(stdin);
	printf("Digite o CPF:\n");
	gets(chavetemp[0]);
	printf("Digite o ISBN:\n");
	gets(chavetemp[1]);
	printf("Digite a data de retirada:\n");
	gets(chavetemp[2]);
	
	achou = buscar_emprestimo(Emprestimos,pos,*chavetemp);
	
	if(achou != -1)
	{
		system("cls");
		printf("listando empréstimo");
		printf("CPF :\n");
		puts(Emprestimos[achou].chave_emprestimos[0]);
		printf("ISBN :\n");
		puts(Emprestimos[achou].chave_emprestimos[1]);
		printf("Data de retirada :\n");
		puts(Emprestimos[achou].chave_emprestimos[2]);
		printf("Data de devolução :\n");
		puts(Emprestimos[achou].datadevolucao);
		printf("Valor de multa por atraso :\n");
		puts(Emprestimos[achou].valormulta);
		return 1;
	}
	return -1;
	system("cls");
	
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
		printf("Digite o(s) telefone(s) :"); //Falta incluir repetição para colocar mais de 1 se quiser!!!
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
	return -1;
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

void adicionar_livro(livro *livros, int *qtdCadastro)
{
  system("cls");
  char isbn[13];
  struct livro book;
  int aut;
  fflush(stdin);
  printf("DIgite o ISBN do livro: ");
  gets(isbn);

  aut = buscar_livro(livros, *qtdCadastro,isbn);
  
  if(aut == -1)
  {
	strcpy(book.isbn,isbn);
	fflush(stdin);
	printf("Digite o título do livro: ");
	gets(book.titulo);
	
	fflush(stdin);
	printf("Digite o gênero do livro: ");
	gets(book.genero);
	
	fflush(stdin);
	printf("Digite o autor do livro - Se for mais de um, coloque  / na frente: "); //Falta incluir repetição para colocar mais de 1 se quiser!!!
	gets(book.autor[0]);
	
	fflush(stdin);
	printf("Digite o número de páginas: ");
	gets(book.num_pagina);
	
	fflush(stdin);
	
	livros[*qtdCadastro] = book;
	(*qtdCadastro)++;
  }
  else
  	printf("Livro já está cadastrado !\n\n");
  system("pause");
 }

void listarT_livro(livro *livros, int pos)
{
    system("cls");
    int i=0;
    if (pos >0){
        for (i=0; i<pos; i++){
            printf("Listando %d° livro\n", i+1);
            printf("Título :\n");
            puts(livros[i].titulo);
            printf("\n");
            printf("ISBN :\n");
            puts(livros[i].isbn);
            printf("\n");
            printf("Gênero :\n");
            puts(livros[i].genero);
            printf("\n");
            printf("Autor :\n");
            puts(livros[i].autor[0]);
            printf("\n");
            printf("Número de páginas :\n");
            puts(livros[i].num_pagina);
        }
        system("pause");
    }
    else{
        printf("Sem cadastros disponiveis !");
        system("pause");
    }
}

int listarE_livros(livro *livros, int pos){
    int i, comparacao;
    char isbn[13];
    system("cls");
    printf("Digite o ISBN do livro: \n");
    fflush(stdin);
    gets(isbn);
    
    for (i=0;i<pos;i++){
        comparacao = strcmp(livros[i].isbn,isbn);
        if(comparacao == 0){
            system("cls");
            printf("Listando livro \n");
             printf("Título :\n");
            puts(livros[i].titulo);
            printf("\n");
            printf("ISBN :\n");
            puts(livros[i].isbn);
            printf("\n");
            printf("Gênero :\n");
            puts(livros[i].genero);
            printf("\n");
            printf("Autor :\n");
            puts(livros[i].autor[0]);
            printf("\n");
            printf("Número de páginas :\n");
            puts(livros[i].num_pagina);
            return 1;
        }
    }
    return -1;
}

int excluir_livro(livro *livros,int *pos)  
{
	int i,comparacao,j;
	char isbn[13];
	system("cls");
	printf("Digite o ISBN do usuário :\n");
	fflush(stdin);
	gets(isbn);
	
	for(i=0;i<*pos;i++)
	{
		comparacao = strcmp(livros[i].isbn,isbn);
		if(comparacao == 0)
		{
			for(j=0;j<*pos;j++)
			{
				livros[j] = livros[j+1];
			}
			(*pos)--;
			
			return 1;
		}
		
	}
	
}

void alterar_livro(livro *Vetor, int pos)
{
    char isbn[13];
    int posicao, op;
    system("cls");
    printf("Digite o ISBN :\n");
    fflush(stdin);
    gets(isbn);
    
    posicao = buscar_livro(Vetor,pos,isbn);
    
    if (posicao != -1){
        do
        {
            printf("O que deseja alterar ?\n\n");
            printf("1. ISBN\n");
			printf("2. Título\n");
			printf("3. Gênero\n");
			printf("4. Autor(s)\n");
     		printf("5. Número de páginas\n");
     		
     		scanf("%d", &op);
     		fflush(stdin);
     		system("cls");
     		switch(op)
     		{
     		    case 1:
     		        printf("\n\n Digite o novo dado :\n\n");
     		        gets(Vetor[posicao].isbn);
     		        printf("Dado alterado com sucesso !\n\n");
     		        system("pause");
     		        break;
     		    case 2:
     		        printf("\n\n Digite o novo dado :\n\n");
     		        gets(Vetor[posicao].titulo);
     		        printf("Dado alterado com sucesso !\n\n");
     		        system("pause");
     		        break;
     		    case 3:
     		        printf("\n\n Digite o novo dado :\n\n");
     		        gets(Vetor[posicao].genero);
     		        printf("Dado alterado com sucesso !\n\n");
     		        system("pause");
     		        break;
     		    case 4:
     		        printf("\n\n Digite o novo dado :\n\n");//Falta incluir repetição para colocar mais de 1 se quiser!!!
     		        gets(Vetor[posicao].autor[0]);
     		        printf("Dado alteradocom sucesso !\n\n");
     		        system("pause");
     		        break;
     		    case 5:
     		        printf("\n\n Digite o novo dado :\n\n");
     		        gets(Vetor[posicao].num_pagina);
     		        printf("Dado alteradocom sucesso !\n\n");
     		        system("pause");
     		        break;
     		    default:
     		        printf("opção inválida !");
     		        system("pause");
     		}
        } while (op>8 || op <=0);
    }
    else
    {
        printf("Livro não cadastrado !\n\n");
        system("pause");
    }
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

void submenu_livros(int *pos)
{
    system("cls");
    int op, flag;
    printf("---------Submenu Livros---------");
    printf("\n1. Listar todos\n");
 	printf("2. Listar especifico\n");
 	printf("3. Adicionar livro\n");
	printf("4. Alterar livro\n");
 	printf("5. Excluir\n");
 	printf("-----------------------------------\n\n");
 	
 	scanf("%d", &op);
 	switch(op)
 	{
 	    case 1:
 	        listarT_livro(livros, *pos);
 	        break;
 	    case 2:
 	        flag = listarE_livros(livros, *pos);
 	        if (flag == -1)
 	            printf("Livro não cadastrado!\n");
 	            system("pause");
 	            break;
 	    case 3:
 	        adicionar_livro(livros, pos);
 	        break;
 	    case 4:
 	        alterar_livro(livros, *pos);
 	        break;
 	    case 5:
 	        excluir_livro(livros, pos);
 	        break;
 	    default:
 	        printf("Opção inválida !\n");
 	        system("pause");
 	        break;
 	}
}
void submenu_emprestimos(int *posLivros,int *posUsers,int *posEmprestimos)
{
	system("cls");
	int op,flag;
	printf("---------Submenu Emprestimos---------");
	printf("\n1. Listar todos\n");
	printf("2. Listar especifico\n");
	printf("3. Incluir empréstimos\n");
	printf("4. Alterar empréstimos\n");
	printf("5. Excluir\n");
	printf("-----------------------------------\n\n");
	
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			listarT_emprestimos(emprestimos,*posEmprestimos);
			
			break;
		case 2:
			flag = listarE_emprestimos(emprestimos,*posEmprestimos);
			if (flag == -1)
				printf("Empréstimo não cadastrado!\n");
			system("pause");
			break;
		case 3:
			incluir_emprestimo(emprestimos,livros,usuarios,posLivros,posUsers,posEmprestimos);
			break;
		case 4:
			alterar_emprestimos(emprestimos,livros,usuarios,*posLivros,*posUsers,*posEmprestimos);
			break;
		case 5:
			excluir_emprestimos(emprestimos,posEmprestimos);
			break;
		default:
			printf("Opção inválida !\n");
			system("pause");
			break;
	}
}

int main()
{
	int op;
	int posLivro = 0,posUsers = 0,posEmprestimos = 0;
	setlocale(LC_ALL,"Portuguese");
	
	do
	{
		op = menu();
		switch(op)
		{
			case 1:
				submenu_usuarios(&posUsers);
				break;
			case 2:
				submenu_livros(&posLivro);
				break;
			case 3:
				submenu_emprestimos(&posLivro,&posUsers,&posEmprestimos);
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


