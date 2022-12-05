#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
struct data
{
	int ano,mes,dia;
};
struct usuario
{
	char nome[40],emails[3][40],telefone[3][15],profissao[40],cpf[15],nro[15],cep[15];
	data nascimento;
};

struct livro
{
    char titulo[40], genero[40], autor[3][40],isbn[13],num_pagina[5]; 
};


struct emprestimo
{
	char chave_emprestimos[3][40],valormulta[4];
	data devolucao;
};



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
	
	struct emprestimo emprestimotemp;
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
			printf("Digite a Data de entrada no formato dd/mm/aaaa sem as barras:\n");
			gets(dataretirada);
			strcpy(chave_emprestimos[0],cpf);
			strcpy(chave_emprestimos[1],isbn);
			strcpy(chave_emprestimos[2],dataretirada);
				
			aut = buscar_emprestimo(Emprestimos,*qtdCadastroEmprestimos,*chave_emprestimos);
			
			if (aut == -1)
			{
				for(i=0;i<3;i++)
				{
					strcpy(emprestimotemp.chave_emprestimos[i],chave_emprestimos[i]);
				}
				
				
				fflush(stdin);
				printf("Digite o dia da data de devolução: \n");
				scanf("%d",&emprestimotemp.devolucao.dia);
				fflush(stdin);
				printf("Digite o mês da data de devolução: \n");
				scanf("%d",&emprestimotemp.devolucao.mes);
				fflush(stdin);
				printf("Digite o ano da data de devolução: \n");
				scanf("%d",&emprestimotemp.devolucao.ano);
				fflush(stdin);
				printf("Digite o valor de multa por atraso :\n");
				gets(emprestimotemp.valormulta);
				Emprestimos[*qtdCadastroEmprestimos] = emprestimotemp;
				(*qtdCadastroEmprestimos)++;
				Emprestimos = (emprestimo*) realloc (Emprestimos,*qtdCadastroEmprestimos * 136);
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
	int i,achou,op;
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
		printf("Empréstimo : \n");
		printf("CPF :\n");
		puts(Emprestimos[achou].chave_emprestimos[0]);
		printf("ISBN :\n");
		puts(Emprestimos[achou].chave_emprestimos[1]);
		printf("Data de retirada :\n");
		puts(Emprestimos[achou].chave_emprestimos[2]);
		printf("Data de devolução :\n");
		printf("%d/%d/%d",Emprestimos[achou].devolucao.dia,Emprestimos[achou].devolucao.mes,Emprestimos[achou].devolucao.ano);
		printf("Valor de multa por atraso :\n");
		puts(Emprestimos[achou].valormulta);
		printf("Confirma ?\n1.Sim\n2.Não\n");
		scanf("%d",&op);
		if (op == 1)
		{
			for(i=achou;i<*pos;i++)
			{
				Emprestimos[i] = Emprestimos[i+1];
			}
			(*pos)--;
			Emprestimos = (emprestimo*) realloc (Emprestimos,*pos * 136);
		
			printf("Empréstimo excluido com sucesso !\n");
		}
		else
			printf("Operação cancelada!\n");
		
		
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
					fflush(stdin);
					printf("Digite o dia da data de devolução: \n");
					scanf("%d",&Emprestimos[achou].devolucao.dia);
					fflush(stdin);
					printf("Digite o mês da data de devolução: \n");
					scanf("%d",&Emprestimos[achou].devolucao.mes);
					fflush(stdin);
					printf("Digite o ano da data de devolução: \n");
					scanf("%d",&Emprestimos[achou].devolucao.ano);
					fflush(stdin);
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
			printf("%d/%d/%d\n",Emprestimos[i].devolucao.dia,Emprestimos[i].devolucao.mes,Emprestimos[i].devolucao.ano);
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
		printf("listando empréstimo\n");
		printf("CPF :\n");
		puts(Emprestimos[achou].chave_emprestimos[0]);
		printf("ISBN :\n");
		puts(Emprestimos[achou].chave_emprestimos[1]);
		printf("Data de retirada :\n");
		puts(Emprestimos[achou].chave_emprestimos[2]);
		printf("Data de devolução :\n");
		printf("%d/%d/%d\n",Emprestimos[achou].devolucao.dia,Emprestimos[achou].devolucao.mes,Emprestimos[achou].devolucao.ano);
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
	int aut,i=0,op;
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
		printf("Digite o email :");
		gets(user.emails[i]);
		i++;
		fflush(stdin);
		do
		{
			if(i!=3)
			{
				printf("\nAdicionar mais um ?\n1.Sim\n2.Não\n");
				scanf("%d",&op);
				fflush(stdin);
				if(op == 1)
				{
					printf("Digite o email :");
					gets(user.emails[i]);
					i++;
				}
			}
		}while(i != 3 && op != 2);
		
		fflush(stdin);
		i=0;
		printf("Digite o Telefone :");
		gets(user.telefone[i]);
		i++;
		fflush(stdin);
		do
		{
			
			if(i!=3)
			{
				printf("\nAdicionar mais um ?\n1.Sim\n2.Não\n");
				scanf("%d",&op);
				fflush(stdin);
				if(op == 1)
				{
					printf("Digite o Telefone :");
					gets(user.telefone[i]);
					i++;
				}
			}
		}while(i != 3 && op != 2);
		
		fflush(stdin);
		printf("Digite o dia da data de nascimento: \n");
		scanf("%d",&user.nascimento.dia);
		fflush(stdin);
		printf("Digite o mês da data de nascimento: \n");
		scanf("%d",&user.nascimento.mes);
		fflush(stdin);
		printf("Digite o ano da data de nascimento: \n");
		scanf("%d",&user.nascimento.ano);
		fflush(stdin);
		printf("Digite a profissão :");
		gets(user.profissao);
	
		fflush(stdin);
	
		Usuarios[*qtdCadastro] = user;
		(*qtdCadastro)++;
		Usuarios = (usuario*) realloc (Usuarios,*qtdCadastro * 302);
		printf("\nUsuário cadastrado com sucesso !\n\n");
	}
	else
		printf("Usuário já está cadastrado !\n\n");
	
	system("pause");
}
void listarT_usuario(usuario *Usuarios,int pos)
{
	system("cls");
	
	int i=0,j=0,len;
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
			len = sizeof(Usuarios[i].emails)/sizeof(Usuarios[i].emails[0]);
			for(j=0;j<len;j++)
			{
				puts(Usuarios[i].emails[j]);
			}
			printf("\n");
			printf("Telefone(s) :\n");
			len = sizeof(Usuarios[i].telefone)/sizeof(Usuarios[i].telefone[0]);
			for(j=0;j<len;j++)
			{
				puts(Usuarios[i].telefone[j]);
			}
			printf("\n");
			printf("Data de nascimento :\n");
			printf("%d/%d/%d",Usuarios[i].nascimento.dia,Usuarios[i].nascimento.mes,Usuarios[i].nascimento.ano);
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
	int i,comparacao,len,j;
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
			len = sizeof(Usuarios[i].emails)/sizeof(Usuarios[i].emails[0]);
			for(j=0;j<len;j++)
			{
				puts(Usuarios[i].emails[j]);
			}
			printf("\n");
			printf("Telefone(s) :\n");
			len = sizeof(Usuarios[i].telefone)/sizeof(Usuarios[i].telefone[0]);
			for(j=0;j<len;j++)
			{
				puts(Usuarios[i].telefone[j]);
			}
			printf("\n");
			printf("Data de nascimento :\n");
			printf("%d/%d/%d",Usuarios[i].nascimento.dia,Usuarios[i].nascimento.mes,Usuarios[i].nascimento.ano);
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
	int i,comparacao,j,len,op,achou;
	char cpf[30];
	system("cls");
	printf("Digite o CPF do usuário :\n");
	fflush(stdin);
	gets(cpf);
	
	achou = buscar(Usuarios,*pos,cpf);
	if(achou != -1)
	{
		printf("Usuário \n");
		printf("Nome :\n");
		puts(Usuarios[achou].nome);
		printf("\n");
		printf("CPF :\n");
		puts(Usuarios[achou].cpf);
		printf("\n");
		printf("Número :\n");
		puts(Usuarios[achou].nro);
		printf("\n");
		printf("CEP :\n");
		puts(Usuarios[achou].cep);
		printf("\n");
		printf("Email(s) :\n");
		len = sizeof(Usuarios[achou].emails)/sizeof(Usuarios[achou].emails[0]);
		for(j=0;j<len;j++)
		{
			puts(Usuarios[achou].emails[achou]);
		}
		printf("\n");
		printf("Telefone(s) :\n");
		len = sizeof(Usuarios[achou].telefone)/sizeof(Usuarios[achou].telefone[0]);
		for(j=0;j<len;j++)
		{
			puts(Usuarios[achou].telefone[achou]);
		}
		printf("\n");
		printf("Data de nascimento :\n");
		printf("%d/%d/%d",Usuarios[achou].nascimento.dia,Usuarios[achou].nascimento.mes,Usuarios[achou].nascimento.ano);
		printf("\n");
		printf("Profissão :\n");
		puts(Usuarios[achou].profissao);
		printf("\n");
		printf("\n");
		printf("Confirma ?\n1.Sim\n2.Não\n");
		scanf("%d",&op);
		if (op == 1)
		{
			for(i=achou;i<*pos;i++)
			{
				Usuarios[achou] = Usuarios[achou+1];
			}
			(*pos)--;
			Usuarios = (usuario*) realloc (Usuarios,*pos * 302);
	
			printf("Usuário excluido com sucesso !\n");
			system("pause");
			return 1;
		}
		else
		{
			printf("Operação cancelada!\n");
			system("pause");
			return -1;
		}
			
	}
	return -1;	
}
void alterar_usuario(usuario *Vetor,int pos)
{
	char cpf[15],cpfNovo[15];
	int posicao,op,i=0,aut;
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
					gets(cpfNovo);
					aut = buscar(Vetor,pos,cpfNovo);
					if(aut != -1)
					{
						printf("CPF já cadastrado !");
					}
					else
						{
							strcpy(Vetor[posicao].cpf,cpfNovo);
							printf("Dado alterado com sucesso !\n\n");
						}
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
					gets(Vetor[posicao].emails[i]);
					i++;
					fflush(stdin);
					do
					{
						if(i!=3)
						{
							printf("\nAdicionar mais um ?\n1.Sim\n2.Não\n");
							scanf("%d",&op);
							fflush(stdin);
							if(op == 1)
							{
								printf("Digite o email :");
								gets(Vetor[posicao].emails[i]);
								i++;
							}
						}
					}while(i != 3 && op != 2);
					printf("Dado alterado com sucesso\n\n");
					system("pause");
					break;
				case 6:
					printf("\n\nDigite o novo dado :\n\n");
					gets(Vetor[posicao].telefone[i]);
					i++;
					fflush(stdin);
					do
					{
						
						if(i!=3)
						{
							printf("\nAdicionar mais um ?\n1.Sim\n2.Não\n");
							scanf("%d",&op);
							fflush(stdin);
							if(op == 1)
							{
								printf("Digite o Telefone :");
								gets(Vetor[posicao].telefone[i]);
								i++;
							}
						}
					}while(i != 3 && op != 2);
					printf("Dado alterado com sucesso\n\n");
					system("pause");
					break;
				case 7:
					fflush(stdin);
					printf("Digite o dia da data de nascimento: \n");
					scanf("%d",&Vetor[posicao].nascimento.dia);
					fflush(stdin);
					printf("Digite o mês da data de nascimento: \n");
					scanf("%d",&Vetor[posicao].nascimento.mes);
					fflush(stdin);
					printf("Digite o ano da data de nascimento: \n");
					scanf("%d",&Vetor[posicao].nascimento.ano);
					fflush(stdin);
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
  int aut,i,op;
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
	printf("Digite o autor :");
	gets(book.autor[i]);
	i++;
	fflush(stdin);
	do
		{
			if(i!=3)
			{
				printf("\nAdicionar mais um ?\n1.Sim\n2.Não\n");
				scanf("%d",&op);
				fflush(stdin);
				if (op == 1)
				{
					printf("Digite o autor :");
					gets(book.autor[i]);
					i++;
				}
			}
		}while(i != 3 && op != 2);
	
	fflush(stdin);
	printf("Digite o número de páginas: ");
	gets(book.num_pagina);
	
	fflush(stdin);
	
	livros[*qtdCadastro] = book;
	(*qtdCadastro)++;
	livros = (livro*) realloc (livros,*qtdCadastro * 218);
  }
  else
  	printf("Livro já está cadastrado !\n\n");
  system("pause");
 }
void listarT_livro(livro *livros, int pos)
{
    system("cls");
    int i=0,len,j;
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
            len = sizeof(livros[i].autor)/sizeof(livros[i].autor[0]);
			for(j=0;j<len;j++)
			{
				puts(livros[i].autor[j]);
			}
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
int listarE_livros(livro *livros, int pos)
{
    int i, comparacao,len,j;
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
            len = sizeof(livros[i].autor)/sizeof(livros[i].autor[0]);
			for(j=0;j<len;j++)
			{
				puts(livros[i].autor[j]);
			}
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
	int i,comparacao,j,achou,len,op;
	char isbn[13];
	system("cls");
	printf("Digite o ISBN do usuário :\n");
	fflush(stdin);
	gets(isbn);
	
	achou = buscar_livro(livros,*pos,isbn);
	
	if(achou != -1)
	{
     	printf("Listando livro \n");
        printf("Título :\n");
        puts(livros[achou].titulo);
        printf("\n");
        printf("ISBN :\n");
        puts(livros[achou].isbn);
        printf("\n");
        printf("Gênero :\n");
        puts(livros[achou].genero);
        printf("\n");
        printf("Autor :\n");
        len = sizeof(livros[achou].autor)/sizeof(livros[achou].autor[0]);
		for(j=0;j<len;j++)
		{
			puts(livros[achou].autor[j]);
		}
        printf("\n");
        printf("Número de páginas :\n");
        puts(livros[achou].num_pagina);
        printf("Confirma ?\n1.Sim\n2.Não\n");
		scanf("%d",&op);
		if (op == 1)
		{
			for(i=achou;i<*pos;i++)
			{
				livros[achou] = livros[achou+1];
			}
			(*pos)--;
			livros = (livro*) realloc (livros,*pos * 218);
			printf("Livro excluido com sucesso !\n");
		}
		else
			printf("Operação cancelada!\n");
    }
	else
	{
		printf("Livro não localizado!\n");
		return -1;
	}
	system("pause");

}
void alterar_livro(livro *Vetor, int pos)
{
    char isbn[13],isbnNovo[13];
    int posicao, op,i=0,aut;
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
     		        gets(isbnNovo);
     		        aut = buscar_livro(Vetor,pos,isbnNovo);
     		        if (aut != -1)
     		        {
     		        	printf("ISBN já cadastrado!\n");
					}
					else
						{
							strcpy(Vetor[posicao].isbn,isbnNovo);
							printf("Dado alterado com sucesso !\n\n");
						}
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
     		        printf("\n\n Digite o novo dado :\n\n");
     		        gets(Vetor[posicao].autor[i]);
					i++;
					fflush(stdin);
					do
						{
							if(i!=3)
							{
								printf("\nAdicionar mais um ?\n1.Sim\n2.Não\n");
								scanf("%d",&op);
								fflush(stdin);
								if (op == 1)
								{
									printf("Digite o autor :");
									gets(Vetor[posicao].autor[i]);
									i++;
								}
							}
						}while(i != 3 && op != 2);
     		        printf("Dado alterado com sucesso !\n\n");
     		        system("pause");
     		        break;
     		    case 5:
     		        printf("\n\n Digite o novo dado :\n\n");
     		        gets(Vetor[posicao].num_pagina);
     		        printf("Dado alterado com sucesso !\n\n");
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
void relatorio_a(usuario *Usuarios,int pos)
{
	int i,j,len,dataresult,idadeX;
	
	printf("Digite a idade:\n");
	scanf("%d",&idadeX);
	
	FILE *RelatorioA;
	RelatorioA = fopen("RelatorioA.txt","w+");
	if (RelatorioA == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	
	for(i=0;i<pos;i++)
	{
		dataresult = 2022 - Usuarios[i].nascimento.ano;
		if (dataresult > idadeX)
		{
			fprintf(RelatorioA,"Listando usuário \n");
			fprintf(RelatorioA,"Nome :\n");
			fputs(Usuarios[i].nome,RelatorioA);
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"CPF :\n");
			fputs(Usuarios[i].cpf,RelatorioA);
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"Número :\n");
			fputs(Usuarios[i].nro,RelatorioA);
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"CEP :\n");
			fputs(Usuarios[i].cep,RelatorioA);
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"Email(s) :\n");
			len = sizeof(Usuarios[i].emails)/sizeof(Usuarios[i].emails[0]);
			for(j=0;j<len;j++)
			{
				fputs(Usuarios[i].emails[j],RelatorioA);
			}
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"Telefone(s) :\n");
			len = sizeof(Usuarios[i].telefone)/sizeof(Usuarios[i].telefone[0]);
			for(j=0;j<len;j++)
			{
				fputs(Usuarios[i].telefone[j],RelatorioA);
			}
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"Data de nascimento :\n");
			fprintf(RelatorioA,"%d/%d/%d\n",Usuarios[i].nascimento.dia,Usuarios[i].nascimento.mes,Usuarios[i].nascimento.ano);
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"Profissão :\n");
			fputs(Usuarios[i].profissao,RelatorioA);
			fprintf(RelatorioA,"\n");
			fprintf(RelatorioA,"\n");
		}
	}
}
void relatorio_b()
{
}
void relatorio_c(emprestimo *Emprestimos,int pos)
{
	data dataX,dataY;
	int i;
	char dia[3],mes[3],ano[5];
	FILE *RelatorioC;
	RelatorioC = fopen("RelatorioC.txt","w+");
	if (RelatorioC == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	
	printf("Digite o dia da data X:\n");
	scanf("%d",&dataX.dia);
	fflush(stdin);
	printf("Digite o mes da data X:\n");
	scanf("%d",&dataX.mes);
	fflush(stdin);
	printf("Digite o ano da data X:\n");
	scanf("%d",&dataX.ano);
	fflush(stdin);
	
	printf("Digite o dia da data Y:\n");
	scanf("%d",&dataY.dia);
	fflush(stdin);
	printf("Digite o mes da data Y:\n");
	scanf("%d",&dataY.mes);
	fflush(stdin);
	printf("Digite o ano da data Y:\n");
	scanf("%d",&dataY.ano);
	fflush(stdin);
	for(i=0;i<pos;i++)
	{
		if(Emprestimos[i].devolucao.ano <= dataX.ano)
		{
			if(Emprestimos[i].devolucao.mes <= dataX.mes)
			{
				if(Emprestimos[i].devolucao.dia <= dataX.dia)
				{
					if(Emprestimos[i].devolucao.ano >= dataY.ano)
					{
						if(Emprestimos[i].devolucao.mes <= dataY.mes)
						{
							if(Emprestimos[i].devolucao.dia <= dataY.dia)
							{
								fputs("\nlistando empréstimo\n",RelatorioC);
								fprintf(RelatorioC,"CPF :\n");
								fputs(Emprestimos[i].chave_emprestimos[0],RelatorioC);
								fprintf(RelatorioC,"\nISBN :\n");
								fputs(Emprestimos[i].chave_emprestimos[1],RelatorioC);
								fprintf(RelatorioC,"\nData de retirada :\n");
								fputs(Emprestimos[i].chave_emprestimos[2],RelatorioC);
								fprintf(RelatorioC,"\nData de devolução :\n");
								fprintf(RelatorioC,"\n%d/%d/%d\n",Emprestimos[i].devolucao.dia,Emprestimos[i].devolucao.mes,Emprestimos[i].devolucao.ano);
								fputs(Emprestimos[i].valormulta,RelatorioC);
							}
						}
					}	
				}
			}
		}
	}
	

	fclose(RelatorioC);
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
void submenu_usuarios(int *pos,usuario *usuarios)
{
	system("cls");
	int op,flag,i;
	printf("---------Submenu Usuários---------");
	printf("\n1. Listar todos\n");
	printf("2. Listar especifico\n");
	printf("3. Incluir usuário\n");
	printf("4. Alterar usuario\n");
	printf("5. Excluir\n");
	printf("-----------------------------------\n\n");
	fflush(stdin);
	scanf("%d",&op);
	fflush(stdin);
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
	//Salvando arquivo
	// Depois de executar alguma função que possivelmente pode modificar o banco de dados de usuários,faz a inserção no arquivo
	FILE *arqUsuarios;
	
	arqUsuarios = fopen("usuarios.dat","wb"); //Abre no modo write pos como o vetor já carrega os dados anteriores,podemos excluir e realocalos tranquilamente.
	
	if (arqUsuarios == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	
	for (i=0; i<*pos; i++) {
	if (fwrite( &usuarios[i],sizeof(struct usuario), 1, arqUsuarios) != 1) //Salva 1 a 1 no arquivo.
		puts("Erro na escrita.");
	}
	rewind(arqUsuarios);
	fclose(arqUsuarios);
}

void submenu_livros(int *pos, livro *livros)
{
    system("cls");
    int op, flag,i;
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
 	//Salvando arquivo
	// Depois de executar alguma função que possivelmente pode modificar o banco de dados de livros,faz a inserção no arquivo
	FILE *arqLivros;
	arqLivros = fopen("livros.dat","wb"); //Abre no modo write pos como o vetor já carrega os dados anteriores,podemos excluir e realocalos tranquilamente.
	
	if (arqLivros == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	
	for (i=0; i<*pos; i++) {
	if (fwrite( &livros[i],sizeof(struct livro), 1, arqLivros) != 1) //Salva 1 a 1 no arquivo.
		puts("Erro na escrita.");
	}
	rewind(arqLivros);
	fclose(arqLivros);
}
void submenu_emprestimos(int *posLivros,int *posUsers,int *posEmprestimos,usuario *usuarios,livro *livros,emprestimo *emprestimos)
{
	system("cls");
	int op,flag,i;
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
	//Salvando arquivo
	// Depois de executar alguma função que possivelmente pode modificar o banco de dados de emprestimos,faz a inserção no arquivo
	FILE *arqEmprestimos;
	
	
	arqEmprestimos = fopen("emprestimos.dat","wb"); //Abre no modo write pos como o vetor já carrega os dados anteriores,podemos excluir e realocalos tranquilamente.
	
	if (arqEmprestimos == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	
	for (i=0; i<*posEmprestimos; i++) {
	if (fwrite( &emprestimos[i],sizeof(struct emprestimo), 1, arqEmprestimos) != 1) //Salva 1 a 1 no arquivo.
		puts("Erro na escrita.");
	}
	rewind(arqEmprestimos);
	fclose(arqEmprestimos);
}

void submenu_relatorios(emprestimo *Emprestimos,int *posUsers,usuario *Usuarios)
{
	system("cls");
	int op,flag;
	printf("---------Submenu Emprestimos---------");
	printf("\n1. Relatório A\n");
	printf("2. Relatório B\n");
	printf("3. Relatório C\n");
	printf("-----------------------------------\n\n");
	
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			relatorio_a(Usuarios,*posUsers);
			break;
		case 2:
			//Não fizemos :(
		case 3:
			relatorio_c(Emprestimos,*posUsers);
			break;
		default:break;
	}

}

int main()
{
	int op,i=0,n=0,endpoint=0,
	comeco,fim;
	int posLivro = 0,posUsers = 0,posEmprestimos = 0;
	setlocale(LC_ALL,"Portuguese");
	
	
	//---------------------------------------USUARIOS----------------------------------------------------//
	FILE *arqUsuarios; //Quando iniciar o programa,Carrega o vetor do arquivo binário para dentro do código na vetor global usuarios[]
	
	arqUsuarios = fopen("usuarios.dat","rb");
		
	if (arqUsuarios == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	//Verifica a quantida de cadastros
	
	fseek(arqUsuarios, 0L, SEEK_END);
	fim = ftell(arqUsuarios);
	rewind(arqUsuarios);
	
	posUsers = fim/302;
	
	//Aloca espaço para o vetor
	
	usuario *usuarios;
	usuarios = (usuario*) malloc (posUsers * 302);
	

	for(i=0;i<posUsers;i++)
	{
		if (fread(&usuarios[i],sizeof(struct usuario), 1, arqUsuarios) != 1) 
		{
			puts("Erro na escrita."); //Verifica se a leitura foi válida
		}
	}
	fclose(arqUsuarios);
	//---------------------------------------LIVROS----------------------------------------------------//
	FILE *arqLivros; //Quando iniciar o programa,Carrega o vetor do arquivo binário para dentro do código na vetor global livros[]
	
	arqLivros = fopen("livros.dat","rb");
		
	if (arqLivros == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	//Verifica a quantida de cadastros
	
	fseek(arqLivros, 0L, SEEK_END);
	fim = ftell(arqLivros);
	rewind(arqLivros);
	
	posLivro = fim/218;
	
	//Aloca espaço para o vetor
	
	livro *livros;
	livros = (livro*) malloc (posLivro * 218);
	

	for(i=0;i<posLivro;i++)
	{
		if (fread(&livros[i],sizeof(struct livro), 1, arqLivros) != 1) 
		{
			puts("Erro na escrita."); //Verifica se a leitura foi válida
		}
	}
	fclose(arqLivros);
	
	
	
	//---------------------------------------EMPRESTIMOS----------------------------------------------//
	FILE *arqEmprestimos; //Quando iniciar o programa,Carrega o vetor do arquivo binário para dentro do código na vetor global emprestimos[]
	
	arqEmprestimos = fopen("emprestimos.dat","rb");
		
	if (arqEmprestimos == NULL)
	{
		printf("Não foi possivel abrir o arquivo!");
		exit(0); //Se o arquivo for nulo por algum motivo, para o programa
	}
	//Verifica a quantida de cadastros
	
	fseek(arqEmprestimos, 0L, SEEK_END);
	fim = ftell(arqEmprestimos);
	rewind(arqEmprestimos);
	
	posEmprestimos = fim/136;
	
	//Aloca espaço para o vetor
	
	emprestimo *emprestimos;
	emprestimos = (emprestimo*) malloc (posEmprestimos * 136);
	

	for(i=0;i<posEmprestimos;i++)
	{
		if (fread(&emprestimos[i],sizeof(struct emprestimo), 1, arqEmprestimos) != 1) 
		{
			puts("Erro na escrita."); //Verifica se a leitura foi válida
		}
	}
	fclose(arqEmprestimos);
	do
	{
		op = menu();
		switch(op)
		{
			case 1:
				submenu_usuarios(&posUsers,usuarios);
				break;
			case 2:
				submenu_livros(&posLivro,livros);
				break;
			case 3:
				submenu_emprestimos(&posLivro,&posUsers,&posEmprestimos,usuarios,livros,emprestimos);
				break;
			case 4:
				submenu_relatorios(emprestimos,&posUsers,usuarios);
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


