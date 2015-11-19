#include "stdio.h"
#include "time.h"
#define TOT 240
#define TOTESCOLHA 11
#define TRUE 1
#define valor_vaga 20000

typedef struct
    {
    char scnome[TOT];
    char sctelefone[TOT];
    char sccpf[TOT];
    int sbloco,sandar,scoluna,snquartos,snvagas,sdescoufinanc,svendaoureserva,svaga1,svaga2;
    float svalordavaga,svalordoap;
    time_t shoradavenda;
    }dados;

void convertehora(time_t horaentrada,double* phoras,double* pminutos ,double* psegundos)
{
    //recebe a hora em segundos e devolve quebrado
    int aux;
    double horas,minutos,segundos;
    horas=horaentrada/3600;
    aux=horaentrada%3600;
    minutos=aux/60;
    segundos=aux%60;
    *phoras=horas;
    *pminutos=minutos;
    *psegundos=segundos;

}

void cadastroclientestruct(dados p,char vendedor[])
{
    char status1,status2,status3,status4;
    char status5[TOT],nomedovendedor[55];

    if(p.sdescoufinanc==1)
    {
        //descoufinanc =1 significa que venda foi a vista
        status1='x';
        status2=' ';
        status5[0]='d';
        status5[1]='e';
        status5[2]='s';
        status5[3]='c';
        status5[4]='o';
        status5[5]='n';
        status5[6]='t';
        status5[7]='o';
        status5[8]='\0';

    }
    else
    {
        status1=' ';
        status2='x';
        status5[0]='f';
        status5[1]='i';
        status5[2]='n';
        status5[3]='a';
        status5[4]='n';
        status5[5]='c';
        status5[6]='i';
        status5[7]='a';
        status5[8]='m';
        status5[9]='e';
        status5[10]='n';
        status5[11]='t';
        status5[12]='o';
        status5[13]='\0';
    }

    if(p.svendaoureserva==4)
    {
        //compraoureserva =4 significa que ap foi comprado
        status3='x';
        status4=' ';
    }
    else
    {
        //compraoureserva =5 significa que ap foi reservado
        status3=' ';
        status4='x';
    }

    printf("\n-------Cadastro do cliente-------\n");
    printf("\nNome:\t\t%s",p.scnome);
    printf("\nTelefone:\t%s",p.sctelefone);
    printf("\nCPF:\t\t%s",p.sccpf);
    printf("\nApartamento: Bloco: %d - Andar: %d - Coluna - %d - #quartos: %d",p.sbloco,p.sandar,p.scoluna,p.snquartos);
    printf("\n(%c)Comprado (%c)Reservado",status3,status4);
    printf("\n(%c)A vista (%c)Financiado",status1,status2);
    printf("\nValor do apartamento com %s:\t%.2f",status5,p.svalordoap);
    printf("\n#vagas: %d",p.snvagas);
    printf("\nValor da(s) vaga(s): %.2f",p.svalordavaga);
    printf("\nVendedor: %s",vendedor);
}
void cadastroclientestructfile(dados p,char vendedor[],FILE* pfcadastro)
{
    char status1,status2,status3,status4;
    char status5[TOT],nomedovendedor[55];
    char cfcadastro[]="//home//rafaeldenadary//codeblocks//projetopredio//arquivos//filecadastro.txt";

    if(p.sdescoufinanc==1)
    {
        //descoufinanc =1 significa que venda foi a vista
        status1='x';
        status2=' ';
        status5[0]='d';
        status5[1]='e';
        status5[2]='s';
        status5[3]='c';
        status5[4]='o';
        status5[5]='n';
        status5[6]='t';
        status5[7]='o';
        status5[8]='\0';

    }
    else
    {
        status1=' ';
        status2='x';
        status5[0]='f';
        status5[1]='i';
        status5[2]='n';
        status5[3]='a';
        status5[4]='n';
        status5[5]='c';
        status5[6]='i';
        status5[7]='a';
        status5[8]='m';
        status5[9]='e';
        status5[10]='n';
        status5[11]='t';
        status5[12]='o';
        status5[13]='\0';
    }

    if(p.svendaoureserva==4)
    {
        //compraoureserva =4 significa que ap foi comprado
        status3='x';
        status4=' ';
    }
    else
    {
        //compraoureserva =5 significa que ap foi reservado
        status3=' ';
        status4='x';
    }

    pfcadastro = fopen(cfcadastro,"a");
    if(pfcadastro == NULL)
    {printf("Erro, nao foi possivel abrir o arquivo fileindice.txt\n");}

    fprintf(pfcadastro,"\n-------Cadastro do cliente-------\n");
    fprintf(pfcadastro,"\nNome:\t%s",p.scnome);
    fprintf(pfcadastro,"\nTelefone:\t%s",p.sctelefone);
    fprintf(pfcadastro,"\nCPF:\t%s",p.sccpf);
    fprintf(pfcadastro,"\nApatamento: Bloco: %d - Andar: %d - Coluna - %d - #quartos: %d",p.sbloco,p.sandar,p.scoluna,p.snquartos);
    fprintf(pfcadastro,"\n(%c)Comprado (%c)Reservado",status3,status4);
    fprintf(pfcadastro,"\nValor do apartamento com %s:\t%.2f",status5,p.svalordoap);
    fprintf(pfcadastro,"\n(%c)A vista (%c)Financiado",status1,status2);
    fprintf(pfcadastro,"\n#vagas: %d",p.snvagas);
    fprintf(pfcadastro,"\nValor da(s) vaga(s): %.2f",p.svalordavaga);
    fprintf(pfcadastro,"\nVendedor: %s",vendedor);
    fclose(pfcadastro);
}
int looppergunta(int x,int y)
{

    if(y)
    {
    while(x<1||x>y)
    {
        printf("\nOpcao invalida, insira um numero entre 1 e %d",y);
        scanf("%d",&x);
    }
    }
    else
    while(x<0||x>1)
    {
        printf("\nOpcao invalida, insira 1 para sim e 0 para nao");
        scanf("%d",&x);
    }
    return x;
    //retorna 1 para sim e 0 para nao
}
int procurar(int oque,int aonde[TOT])
{
    //devolve o indice do que se procura dentro do vetor
    int i,x;
    for (i=0;i<TOT;i++)
    {
        if(oque==aonde[i])
        {
            x=i;
        }
    }
    return x;
}
void somar (int bloco, int andar, int coluna, int* psoma)
{
    int soma;
    bloco=bloco*1000;
    andar=andar*10;
    soma=bloco+andar+coluna;
    *psoma=soma;
}

void decifrar (int soma,int* pbloco, int* pandar, int* pcoluna)
{
    int bloco, andar, coluna,aux;
    coluna=soma%10;
    bloco=soma/1000;
    aux=soma/10;
    andar=aux%100;
    *pbloco=bloco;
    *pandar=andar;
    *pcoluna=coluna;
}
/////////////////
int descobrenumdequartos (int coluna)
{
    if(coluna>=3)
    {
        coluna=coluna-3;
    }
    coluna++;
    if(coluna>=4)
    {
        coluna=1;
    }
    return coluna;
}

void descobrirvagas(int vaga1, int vaga2,int* linha1,int* coluna1,int* linha2, int* coluna2)
{
    int cc1,cc2,ll1,ll2;
    //vaga1=LLCC
    cc1=vaga1%100;
    ll1=vaga1/100;
    cc2=vaga2%100;
    ll2=vaga2/100;
    *linha1=ll1;
    *linha2=ll2;
    *coluna1=cc1;
    *coluna2=cc2;
}

int testatempo(time_t horaentrada)
{
    time_t loopnow;
    int x=0;
    time(&loopnow);
    if(loopnow>=horaentrada)
    {
        x=1;
    }
    return x;
}
int testevaga(float matriz[][10][10],int b,int linha,int coluna)
{
    //retorna 1 para vaga disponivel ou 0 para vaga ocupada
    int x=1;

if(matriz[b-1][linha-1][coluna-1]>400)
    {
        printf("\nOpcao invalida, esta vaga ja foi ocupada");
        x=0;
    }
return x;
}

void exibe4 (float matriz[][10][10],int n)
{
    int i,l,c;
    int contbloco=1,contlinha=1;
    if(n)
    {
        printf("\n\t");
        for(c=1;c<=10;c++)
        {
            printf("\t %d",c);
        }
        printf("\n");
        for(l=0;l<10;l++)
        {
            printf("Linha %2.0d",contlinha);
            for(c=0;c<10;c++)
            {
                printf("\tG%4.0f",matriz[n-1][l][c]);
            }
            contlinha++;
            printf("\n");
        }
    }
    else
    {
        printf("\n\t");
        for(c=1;c<=10;c++)
        {
            printf("\t %d",c);
        }
        printf("\n");
        for(i=0;i<4;i++)
        {
            printf("\nBloco %2.0d\n",contbloco);
            for(l=0;l<10;l++)
            {
                printf("Linha %2.0d",contlinha);
                for(c=0;c<10;c++)
                {
                    printf("\tG%4.0f",matriz[i][l][c]);
                }
                contlinha++;
            printf("\n");
            }
        contbloco++;
        printf("\n");
        }
    }
}

void escolhervaga(float matriz[][10][10],int bloco,int*linha,int*coluna)
{
    int x,l,c;

    exibe4(matriz,bloco);
    printf("\nEscolha a vaga\n");
    printf("Linha:");
    scanf("%d",&l);
    l=looppergunta(l,10);
    printf("Coluna:");
    scanf("%d",&c);
    c=looppergunta(c,10);
    x=testevaga(matriz,bloco,l,c);
    //x=1, vaga liberada, x=0, vaga ocupada
    while(x==0)
    {
        exibe4(matriz,bloco);
        printf("\nEscolha a vaga\n");
        printf("Linha:");
        scanf("%d",&l);
        l=looppergunta(l,10);
        printf("Coluna:");
        scanf("%d",&c);
        c=looppergunta(c,10);
        x=testevaga(matriz,bloco,l,c);
    }
    *linha=l;
    *coluna=c;
}

int calculadesconto (float valorbruto, int multiplicador, int descoufinanc,float* pconfirma)
{
    //devolve 1 para cliente aceitou desconto ou 0 se cliente não aceitou
    //multiplicador=1 = 1 vaga/ multiplicador=2 = 2 vagas
    //ponteiro devolve valor calculado
    float resultfinal,desconto,limitador;
    char status5[TOT];
    int confirma;

    if(descoufinanc==1)
    {
        limitador=15;
        status5[0]='d';
        status5[1]='e';
        status5[2]='s';
        status5[3]='c';
        status5[4]='o';
        status5[5]='n';
        status5[6]='t';
        status5[7]='o';
        status5[8]='\0';
    }
    else
    {
        limitador=95;
        status5[0]='f';
        status5[1]='i';
        status5[2]='n';
        status5[3]='a';
        status5[4]='n';
        status5[5]='c';
        status5[6]='i';
        status5[7]='a';
        status5[8]='m';
        status5[9]='e';
        status5[10]='n';
        status5[11]='t';
        status5[12]='o';
        status5[13]='\0';
    }
    valorbruto=multiplicador*valorbruto;

    printf("\nDigite o valor do %s em %%:\t",status5);
    scanf("%f",&desconto);
        while(desconto<0||desconto>limitador)
        {
        printf("\nValor invalido. Valor maximo de %s eh %.2f %%",status5,limitador);
        scanf("%f",&desconto);
        }
    if(descoufinanc==1)
    {resultfinal=valorbruto-(desconto/100)*valorbruto;}
    else
    {resultfinal=valorbruto+(desconto/100)*valorbruto;}

    printf("\nO valor final com %.2f %% de %s ficou: %.2f\n",desconto,status5,resultfinal);
    printf("\nConfirma pagamento (1-S/0-N)?");

    scanf("%d",&confirma);
    confirma=looppergunta(confirma,0);
    if(confirma==0)
    {
        if(descoufinanc==1)
        {resultfinal=valorbruto;}
        if(descoufinanc==2)
        {resultfinal=1.95*valorbruto;}
    }
    *pconfirma=resultfinal;
    return confirma;

}
float terminavenda(float matriz[][10][10],int nvagas,int soma,int l,int c,int l2,int c2,int* pvaga1,int* pvaga2)
{
    int x,comprar,bloco,andar,coluna,vaga1,vaga2;
    float valorfinal,valordavaga=20000;
    decifrar(soma,&bloco,&andar,&coluna);
if(nvagas==1)
{
    //para clientes que so tem direito a 1 vaga
    //printf("\nValor da vaga: %.2f",valor_vaga);
    printf("\nDeseja pagamento a vista(1-s/0-n)?");
    scanf("%d",&comprar);
    comprar=looppergunta(comprar,0);
    if(comprar==1)
    {
        //cliente quer pagar a vista. calcular o desconto e perguntar se ele aceita
        //no final dessa rotina, valorfinal vai conter o valor final calculado
        x=calculadesconto(valordavaga,1,1,&valorfinal);
        if(x==1)
        {
            //cliente aceitou o desconto
            printf("\nVaga(s) adquirida(s) por = %.2f\n",valorfinal);
            matriz[bloco-1][l-1][c-1]=soma; //vaga ocupada
            vaga1=l*100+c;
            vaga2=0;
        }
        else
        {
            matriz[bloco-1][l-1][c-1]=soma; //vaga ocupada
            valorfinal=valordavaga;
            printf("\nVaga adquirida sem desconto\n");
            vaga1=l*100+c;
            vaga2=0;
        }
    }
    else
    {
        //cliente não quer comprar a vista
        matriz[bloco-1][l-1][c-1]=soma; //vaga ocupada
        valorfinal=valordavaga;
        printf("\nVaga adquirida sem desconto\n");
        vaga1=l*100+c;
        vaga2=0;
    }
}
else
{
    //nvagas = 2
    printf("\nDeseja pagamento a vista?(1-S/0-N)");
    scanf("%d",&comprar);
    comprar=looppergunta(comprar,0);
    if(comprar==1)
    {
        //cliente aceitou pagar as 2 vagas a vista
        comprar=calculadesconto(valordavaga,2,1,&valorfinal);
        if(comprar==1)
        {
            //cliente aceitou o desconto
            matriz[bloco-1][l-1][c-1]=soma; //vaga ocupada
            matriz[bloco-1][l2-1][c2-1]=soma; //vaga ocupada
            printf("\nVagas adquiridas\n");
            vaga1=l*100+c;
            vaga2=l2*100+c;
        }
        else
        {
            matriz[bloco-1][l-1][c-1]=soma; //vaga ocupada
            matriz[bloco-1][l2-1][c2-1]=soma; //vaga ocupada
            printf("\nVagas adquiridas sem desconto\n");
            vaga1=l*100+c;
            vaga2=l2*100+c;
        }
    }
    else
    {
        matriz[bloco-1][l-1][c-1]=soma; //vaga ocupada
        matriz[bloco-1][l2-1][c2-1]=soma; //vaga ocupada
        printf("\nVagas adquiridas sem desconto\n");
        vaga1=l*100+c;
        vaga2=l2*100+c;
        valorfinal=2*valordavaga;
    }
}
*pvaga1=vaga1;
*pvaga2=vaga2;
return valorfinal;
}

float vendervaga(float matriz[][10][10],int soma,int* pnvagas,int* pvaga1, int* pvaga2)
{
    int l,c,l2,c2,comprar,nvagas,bloco,andar,coluna,vaga1,vaga2;
    float valorfinal;
    decifrar(soma,&bloco,&andar,&coluna);
    coluna=descobrenumdequartos(coluna);

    if(coluna>2)
    {
        nvagas=2;
        escolhervaga(matriz,bloco,&l,&c);//essa função so marca onde será vendido
        printf("\nDeseja adquirir outra vaga?(1-s/0-n)");
        scanf("%d",&comprar);
        comprar=looppergunta(comprar,0);
        if(comprar==1)
        {
            escolhervaga(matriz,bloco,&l2,&c2);
            while(l2==l&&c2==c)
            {
                printf("\Essa vaga ja foi escolhida, escolha outra vaga");
                escolhervaga(matriz,bloco,&l2,&c2);
            }
        }
        else
        {
            nvagas=1;
            l2=c2=0;
        }
    }
    else
    {
        nvagas=1;
        escolhervaga(matriz,bloco,&l,&c);
        l2=c2=0;
    }
    valorfinal=terminavenda(matriz,nvagas,soma,l,c,l2,c2,&vaga1,&vaga2);
    *pnvagas=nvagas;
    *pvaga1=vaga1;
    *pvaga2=vaga2;
    return valorfinal;
}

int vender(float matriz[][3],int soma,float* pvalorvendaap,int* descoufinanc)
{
    //retorna 1 se cliente aceita o valor e 0 se nao
    int bloco,andar,coluna,status=0,escolha=99,confirma,vendido;
    float valor;

    vendido=1;
    decifrar(soma,&bloco,&andar,&coluna);
    coluna=descobrenumdequartos(coluna);
    printf("\nO valor do apartamento eh:\t%.2f",valor=matriz[andar-1][coluna-1]);
    //*pvalorabsoluto=valor;
    printf("\n----OPCOES----\n");
    printf("\n1 - Pagamento a vista");
    printf("\n2 - Pagamento financiado\n\n");
    scanf("%d",&escolha);
    escolha=looppergunta(escolha,2);
    if(escolha==1)
    {
    confirma=calculadesconto(valor,1,1,&valor);//valor=valorbaseap-desconto
    if(confirma==1)
    {
        printf("\nConfirmado");
        status=1;
        escolha=0;
    }
    else
    {
        printf("\nPagamento a vista cancelado");
        escolha=99;
        vendido=0;
    }

    }//financiamento;
    if(escolha==2)
    {
    confirma=calculadesconto(valor,1,2,&valor);//valor=valorbaseap+financ
    if(confirma==1)
    {
        printf("\nConfirmado");
        escolha=0;
        status=2;
    }
    else
    {
        printf("\nPagamento financiado cancelado");
        escolha=99;
        vendido=0;
    }
    }

    *descoufinanc=status;
    *pvalorvendaap=valor;
    return vendido;
}

int teste(int mnumdequartos[][10][6],int soma)
{
    //retorna 1 para ap disponivel ou 0 para ap ocupado
    int x=1,bloco,andar,coluna;
    decifrar(soma,&bloco,&andar,&coluna);
if(mnumdequartos[bloco-1][andar-1][coluna-1]==4)
    {
        printf("\nOpcao invalida, este apartamento ja foi vendido");
        x=0;
    }
    else
    {
        if(mnumdequartos[bloco-1][andar-1][coluna-1]==5)
        {
            printf("\nOpcao invalida, este apartamento ja foi reservado");
            x=0;
        }
        else
        {
            if(mnumdequartos[bloco-1][andar-1][coluna-1]==6)
            {
                printf("\nOpcao invalida, este apartamento eh de uso exclusivo da construtora");
                x=0;
            }
        }
    }
return x;
}

void exibe (int matriz[][10][6],int nquartos,int bloco)
{
    //nquartos=0, print full;
    int l,c,i,o,contandar=10,contbloco=1;
    if(bloco==0)
    {
        bloco=4;
        o=0;
    }
    else
    {
        o=bloco-1;
    }
  if(nquartos)
  {
    printf("Coluna\t");
    for(i=1;i<=6;i++)
    {printf("  %d ",i);}
    printf("\n\n\t+---+---+---+---+---+---+\n");

    for (i=o;i<bloco;i++)
     {
      for(l=9;l!=-1;l--)
      {
            printf("Andar%d\t",contandar);
            for(c=0;c<6;c++)
            {
                //rotina para nquartos!=0:
                if(matriz[i][l][c]!=nquartos)
                {
                    printf("|%c%c%c",'X','X','X');
                }
                else
                {
                printf("| %d ",matriz[i][l][c]);
                }
            }
            contandar--;
            printf("|\n\t+---+---+---+---+---+---+\n");
      }
      printf("\n");
    }
    printf("\n");
  }
  else
  {
    printf("Coluna\t");
    for(i=1;i<=6;i++)
    {printf("  %d ",i);}
    printf("\n\n\t+---+---+---+---+---+---+\n");

    for (i=o;i<bloco;i++)
    {
    for(l=9;l!=-1;l--)
    {
     printf("Andar%d\t",contandar);
        for(c=0;c<6;c++)
        {
            if(matriz[i][l][c]==4)
            {
                printf("|%c%c%c",'V','N','D');
            }
                else
                {
                if(matriz[i][l][c]==5)
                {
                    printf("|%c%c%c",'R','S','V');
                }
                    else
                    {
                    if(matriz[i][l][c]==6)
                    {
                        printf("|%c%c%c",'C','T','T');
                    }
                    else
                        {printf("| %d ",matriz[i][l][c]);}
                    }
                }
        }
        contandar--;
        printf("|\n\t+---+---+---+---+---+---+\n");
    }
    printf("\n");
    }

  }
}

void exibe2 (float matriz[][3])
{
    int l,c;

    for(l=0;l<10;l++)
    {
        for(c=0;c<3;c++)
        {
            printf("\t%.2f",matriz[l][c]);
        }
        printf("\n");
    }
}

int contasituacao (int matriz[][10][6],int n,int m)
{
int contazero=0,l,c,i,o;
if(n==0)
{
    if(m==0)
    {
        m=4;
        o=0;
    }
    else
    {
        o=m-1;
    }
    for(i=o;i<m;i++)
    {
    for(l=0;l<10;l++)
    {
        for(c=0;c<6;c++)
        {
            if(matriz[i][l][c]>3)
            {
                contazero++;
            }
        }
    }
    }
}
else
{
    if(m==0)
    {
        m=4;
        o=0;
    }
    else
    {
        o=m-1;
    }

    for(i=o;i<m;i++)
    {
    for(l=0;l<10;l++)
    {
    for(c=0;c<6;c++)
    {
        if(matriz[i][l][c]==n)
        {
            contazero++;
        }
    }
    }
    }
}
return contazero;
}

void menuinicial ()
{
    printf("\n\n------MENU INICIAL------");
    printf("\n1 - apartamentos por condominio");
    printf("\n2 - apartamentos por bloco");
    printf("\n3 - apartamentos por numero de quartos");
    printf("\n4 - Consulta por status (vendido, reservado, disponível, construtora) e/ou bloco");
    printf("\n5 - vender um apartamento");
    printf("\n6 - reservar um apartamento");
    printf("\n7 - exibir tabela de precos");
    printf("\n8 - consulta apartamentos reservados");
    printf("\n9 - consulta mapa de vagas");
    printf("\n10- reservar apartamentos para a construtora");
    printf("\n11- exibir tabela de comissoes");
    printf("\n\n");
}


