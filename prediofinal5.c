#include "stdio.h"
#include "time.h"
#include "funcoespredio5.c"
#define TOT 240
#define TOTESCOLHA 11
#define tempo /*125*/172800

void main()
{
    FILE* pfarquivo1;
    char cfarquivo1[]="//home//rafaeldenadary//codeblocks//projetopredio//arquivos//arquivo1.txt";
    char cfarquivo2[]="//home//rafaeldenadary//codeblocks//projetopredio//arquivos//arquivo2.txt";
    char cfarquivo3[]="//home//rafaeldenadary//codeblocks//projetopredio//arquivos//arquivo3.txt";
    char cfarquivo4[]="//home//rafaeldenadary//codeblocks//projetopredio//arquivos//arquivo4.txt";
    char cfcomissaotxt[]="//home//rafaeldenadary//codeblocks//projetopredio//arquivos//comissoes.txt";

    FILE* pfcadastro;
    FILE* pfcomissao;
    char cfcomissao[]="filecomissoes.txt";
    FILE* pfvendedores;
    char cfvendedores[]="filevendedores.txt";
    FILE* pfmnumdequartos;
    char cfmnumdequartos[]="filematriznumdequartos.txt";
    FILE* pfmvalorbaseap;
    char cfmvalorbaseap[]="filematrizvlabsoluto.txt";
    FILE* pfvagas;
    char cfvagas[]="filevagas.txt";
    FILE* pfindice;
    char cfindice[]="fileindice.txt";
    FILE* pfiletime;
    char cfiletime[]="filetime.txt";
    FILE* pfvcomissaoreservada;
    char cfvcomissaoreservada[]="filevcomissaoreservada.txt";
    char nomedovendedor[55],nomes2[4][55];

    dados vscadastro[TOT];
    float vcomissaoreservada[TOT],valorbasevaga=20000,mvalorbaseap[10][3],mvagas[4][10][10],vcomissao[4],mtabelavalores[TOT][3],valordavaga,valordoap;
    int structreduzida[6][TOT],vaux[TOT],vindices[TOT],mnumdequartos[4][10][6],vaga1,vaga2,nvagas,escolha=99,count1,i,j,k,x,y,usuario,soma,indice,nquartos,bloco,andar,coluna,descoufinanc;
    time_t testehora,testehora2,vhoras[TOT];
    double hora,minutos,segundos;

    //1 - Abrir fileindice - esse fica o programa inteiro aberto
    pfindice = fopen(cfindice,"r+b");
    if(pfindice == NULL)
    {printf("Erro, nao foi possivel abrir o arquivo fileindice.txt\n");}
	fread(vindices,sizeof(int),TOT,pfindice);

	for(i=0;i<TOT;i++)
	{vscadastro[i].svendaoureserva=vindices[i];}


	//2 - Abrir file vendedores - esse fica aberto o programa inteiro
	pfvendedores=fopen(cfvendedores,"rb");
	if(pfvendedores == NULL)
    {printf("Erro, nao foi possivel abrir o arquivo filevendedores.txt\n");}
    fread(nomes2,sizeof(char),220,pfvendedores);

    //3 - Abrir filematriznumdequartos - esse fecha agora e abre e fecha durante o programa
    pfmnumdequartos=fopen(cfmnumdequartos,"r+b");
    if(pfmnumdequartos == NULL)
    {printf("Erro, nao foi possivel abrir o arquivo filenumdequartos.txt\n");}
    rewind(pfmnumdequartos);
    fread(mnumdequartos,sizeof(int),TOT,pfmnumdequartos);
    fclose(pfmnumdequartos);

    //4 - Abrir filemvalorabsoluto(matriz com os valores dos aps - esse fecha agora e abre e fecha durante o programa
    pfmvalorbaseap=fopen(cfmvalorbaseap,"r+b");
    if(pfmvalorbaseap == NULL)
    {printf("Erro, nao foi possivel abrir o arquivo mvalorbaseap.txt\n");}
    fread(mvalorbaseap,sizeof(float),30,pfmvalorbaseap);
    fclose(pfmvalorbaseap);

    //5 - Abrir filevagas - esse fecha agora e abre e fecha durante o programa
    pfvagas=fopen(cfvagas,"r+b");
    if(pfvagas == NULL)
    {printf("Erro, nao foi possivel abrir o arquivo mvalorbaseap.txt\n");}
    fread(mvagas,sizeof(float),400,pfvagas);
    fclose(pfvagas);

    //6 - Abrir filetime - esse abre agora e abre so no final do programa
    pfiletime=fopen(cfiletime,"r+b");
    if(pfiletime == NULL)
    {printf("Erro, nao foi possivel abrir pfiletime\n");}
    fread(vhoras,sizeof(time_t),TOT,pfiletime);

    //7 - Abrir filevcomissaoreservada - esse abre agora e abre so no final do programa
    pfvcomissaoreservada=fopen(cfvcomissaoreservada,"r+b");
    if(pfvcomissaoreservada == NULL)
    {printf("Erro, nao foi possivel abrir pfvcomissaoreservada\n");}
    fread(vcomissaoreservada,sizeof(float),TOT,pfvcomissaoreservada);

    //INICIANDO O PROGRAMA
	printf("\nO programa trabalha com 4 vendedores\n Suas matriculas sao 1010, 1011, 1012 e 1013");
	printf("\nPara iniciar, digite uma das matriculas");
	printf("\nUsuario:\n");
    scanf("%d",&usuario);
    while(usuario!=1010 && usuario!=1011 && usuario!=1012 && usuario!=1013)
    {
        printf("\nUsuario inexistente\n\nUsuario: ");
        scanf("%d",&usuario);
    }
    usuario=usuario%10;
    for(i=0;i<55;i++)
    {nomedovendedor[i]=nomes2[usuario][i];}
    //i=0;
    printf("\nBem vindo %s\n",nomedovendedor);


    while(escolha)//Apresenta o menu e volta pra ele enquanto usuario nao digita 0.0 encerra o programa
    {
        count1=0;
        for(i=0;i<TOT;i++)
        {
            if(vindices[i]>10)
            {count1++;}
        }

        if(count1)//se count1 diferente de zero é pq tem aps reservados, tem que testar os tempos
        {
            //printf("\n\n numero de aps reservados = %d",count1);
            //printf("\nquem reservou\n");
            j=0;
            for(i=0;i<TOT;i++)
            {
                if(vindices[i]>10)
                {
                    //printf("%d\t",vindices[i]/10);
                    vaux[j]=i;
                    j++;
                }
            }

            for(i=0;i<count1;i++)//vou chamar a função testatempo count1 vezes
            {
                k=vaux[i];
                y=testatempo(vhoras[k]);
                //func testatempo devolve 1 se o tempo se esgotou e 0 se não
                printf("\nO ap %d estourou o tempo? %d",vindices[k]/10,y);
                if(y==1)
                {

                    //1. remarcar o ap com o n de quartos
                    soma=vindices[k];
                    decifrar(vindices[k]/10,&bloco,&andar,&coluna);
                    nquartos=descobrenumdequartos(coluna);
                    mnumdequartos[bloco-1][andar-1][coluna-1]=nquartos;
                    pfmnumdequartos=fopen(cfmnumdequartos,"r+b");
                    if(pfmnumdequartos == NULL)
                    {printf("Erro, nao foi possivel abrir o arquivo filevendedores.txt\n");}
                    rewind(pfmnumdequartos);
                    fwrite(mnumdequartos,sizeof(int),TOT,pfmnumdequartos);
                    fclose(pfmnumdequartos);
                    //2 remarcar as vagas
                    for(x=0;x<10;x++)
                    {
                        for(y=0;y<10;y++)
                        {
                            if(mvagas[bloco-1][x][y]==vindices[k]/10)
                            {
                                mvagas[bloco-1][x][y]=((bloco-1)*100)+((x)*10)+y+1;
                            }
                        }
                    }
                    pfvagas=fopen(cfvagas,"r+b");
                    if(pfvagas == NULL)
                    {printf("Erro, nao foi possivel abrir o arquivo mvalorbaseap.txt\n");}
                    rewind(pfvagas);
                    fwrite(mvagas,sizeof(float),400,pfvagas);
                    fclose(pfvagas);
                    //3.zerar vcadastro[k]
                    vscadastro[k].svendaoureserva=0;
                    vindices[k]=0;
                    vscadastro[k].shoradavenda=0;
                    vhoras[k]=0;
                    vcomissaoreservada[k]=0;
                    //avisar vendedor
                    printf("\nApartamento %d liberado",soma);
                    k++;
                }
                k++;
            }
        }

        menuinicial();
        scanf("%d",&escolha);
        while(escolha<0||escolha>TOTESCOLHA)
        {
            printf("\nopcao invalida, insira numero entre 0 e %d",TOTESCOLHA);
            scanf("%d",&escolha);
        }
        if(escolha==1)
        {
            count1=contasituacao(mnumdequartos,0,0);
            printf("\nTotal de apartamentos no condominio:\t\t\t%d",TOT);
            printf("\nTotal de apartamentos disponiveis no condominio:\t%d",TOT-count1);
            printf("\nDeseja gerar um arquivo .txt para impressao?");
            scanf("%d",&i);
            i=looppergunta(i,0);
            if(i==1)
            {
                pfarquivo1 = fopen(cfarquivo1,"w");
                if(pfarquivo1 == NULL)
                {printf("Erro, nao foi possivel abrir o arquivo Arquivo1.txt\n");}
                rewind(pfarquivo1);
                fprintf(pfarquivo1,"\nTotal de apartamentos no condominio:\t\t\t%d",TOT);
                fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no condominio:\t%d",TOT-count1);
                fclose(pfarquivo1);
                printf("\nO arquivo arquivo1.txt foi criado na pasta arquivos");
            }

        }
        if(escolha==2)
        {
            printf("\nTotal de apartamentos por bloco:\t\t%d",TOT/4);
            count1=contasituacao(mnumdequartos,0,1);
            printf("\nTotal de apartamentos disponiveis no bloco 1:\t%d\n",(TOT/4)-count1);
            exibe(mnumdequartos,0,1);

            count1=contasituacao(mnumdequartos,0,2);
            printf("\nTotal de apartamentos disponiveis no bloco 2:\t%d\n",(TOT/4)-count1);
            exibe(mnumdequartos,0,2);

            count1=contasituacao(mnumdequartos,0,3);
            printf("\nTotal de apartamentos disponiveis no bloco 3:\t%d\n",(TOT/4)-count1);
            exibe(mnumdequartos,0,3);

            count1=contasituacao(mnumdequartos,0,4);
            printf("\nTotal de apartamentos disponiveis no bloco 4:\t%d\n",(TOT/4)-count1);
            exibe(mnumdequartos,0,4);

            printf("\nDeseja gerar um arquivo .txt para impressao?(1-S/0-N)");
            scanf("%d",&i);
            i=looppergunta(i,0);
            if(i==1)
            {
                pfarquivo1 = fopen(cfarquivo2,"w");
                if(pfarquivo1 == NULL)
                {printf("Erro, nao foi possivel abrir o arquivo \n");}
                rewind(pfarquivo1);
            fprintf(pfarquivo1,"\nTotal de apartamentos por bloco:\t\t%d\n",TOT/4);
            count1=contasituacao(mnumdequartos,0,1);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no bloco 1:\t%d",(TOT/4)-count1);
            count1=contasituacao(mnumdequartos,0,2);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no bloco 2:\t%d",(TOT/4)-count1);
            count1=contasituacao(mnumdequartos,0,3);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no bloco 3:\t%d",(TOT/4)-count1);
            count1=contasituacao(mnumdequartos,0,4);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no bloco 4:\t%d\n",(TOT/4)-count1);

            //fwrite(mnumdequartos,sizeof(int),TOT,pfarquivo1);
            for(x=0;x<4;x++)
            {
                for(y=0;y<10;y++)
                {
                    for(k=0;k<6;k++)
                    {fprintf(pfarquivo1,"\t%d",mnumdequartos[x][y][k]);}
                    fprintf(pfarquivo1,"\n");
                }
                fprintf(pfarquivo1,"\n");
            }

            fclose(pfarquivo1);
            printf("\nO arquivo arquivo2.txt foi criado na pasta arquivos");
            }
        }

        if(escolha==3)
        {
            printf("\nTotal de apartamentos de 1 quarto:\t%d",TOT/3);
            printf("\nTotal de apartamentos de 2 quartos:\t%d",TOT/3);
            printf("\nTotal de apartamentos de 3 quartos:\t%d",TOT/3);
            count1=contasituacao (mnumdequartos,1,0);
            printf("\nTotal de apartamentos disponiveis no condominio de 1 quarto:\t%d",count1);
            count1=contasituacao (mnumdequartos,2,0);
            printf("\nTotal de apartamentos disponiveis no condominio de 2 quartos:\t%d",count1);
            count1=contasituacao (mnumdequartos,3,0);
            printf("\nTotal de apartamentos disponiveis no condominio de 3 quartos:\t%d",count1);
            printf("\ndigite o numero de quartos desejado ou 0 para continuar:\t");
            scanf("%d",&nquartos);
            while(nquartos<0||nquartos>3)
            {
                printf("\nopcao invalida, escolha um numero entre 1 e 3:\t");
                scanf("%d",&nquartos);
            }
                if(nquartos)
                {
                    printf("\ndigite o numero do bloco para filtrar por bloco, ou 0 para continuar:\t");
                    scanf("%d",&bloco);
                    while(bloco<0||bloco>4)
                    {
                        printf("\nopcao invalida, escolha um numero de 0 a 4\t");
                        scanf("%d",&bloco);
                    }
                }
                else
                {
                    bloco=0;
                }
            while(bloco)
            {
                count1=contasituacao(mnumdequartos,nquartos,bloco);
                printf("\nTotal de apartamentos de %d quarto(s) no bloco %d:\t%d",nquartos,bloco,count1);
                printf("\n");
                exibe(mnumdequartos,nquartos,bloco);
                printf("\ndigite o numero do bloco para filtrar por bloco, ou 0 para continuar:\t");
                scanf("%d",&bloco);
                while(bloco<0||bloco>4)
                {
                    printf("\nopcao invalida, escolha um numero de 0 a 4\t");
                    scanf("%d",&bloco);
                }
            }
            //////////////////////////////////////////////qqq
        printf("\nDeseja gerar um arquivo .txt para impressao?(1-S/0-N)");
        scanf("%d",&i);
        i=looppergunta(i,0);
        if(i==1)
        {
            pfarquivo1 = fopen(cfarquivo3,"w");
            if(pfarquivo1 == NULL)
            {printf("Erro, nao foi possivel abrir o arquivo \n");}
            rewind(pfarquivo1);
            fprintf(pfarquivo1,"\nTotal de apartamentos de 1 quarto:\t%d",TOT/3);
            fprintf(pfarquivo1,"\nTotal de apartamentos de 2 quartos:\t%d",TOT/3);
            fprintf(pfarquivo1,"\nTotal de apartamentos de 3 quartos:\t%d",TOT/3);
            count1=contasituacao (mnumdequartos,1,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no condominio de 1 quarto:\t%d",count1);
            count1=contasituacao (mnumdequartos,2,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no condominio de 2 quartos:\t%d",count1);
            count1=contasituacao (mnumdequartos,3,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis no condominio de 3 quartos:\t%d",count1);
            fclose(pfarquivo1);
            printf("\nO arquivo arquivo3.txt foi criado na pasta arquivos");

        }
        }

        if(escolha==4)
        {
            count1=contasituacao(mnumdequartos,0,0);
            printf("\nTotal de apartamentos disponiveis:\t%d",TOT-count1);
            count1=contasituacao(mnumdequartos,4,0);
            printf("\nTotal de apartamentos vendidos:\t\t%d",count1);
            count1=contasituacao(mnumdequartos,5,0);
            printf("\nTotal de apartamentos reservados:\t%d",count1);
            count1=contasituacao(mnumdequartos,6,0);
            printf("\nTotal de apartamentos da construtora:\t%d",count1);

        printf("\nDeseja gerar um arquivo .txt para impressao?(1-S/0-N)");
        scanf("%d",&i);
        i=looppergunta(i,0);
        if(i==1)
        {
            pfarquivo1 = fopen(cfarquivo4,"w");
            if(pfarquivo1 == NULL)
            {printf("Erro, nao foi possivel abrir o arquivo \n");}
            rewind(pfarquivo1);
            count1=contasituacao(mnumdequartos,0,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos disponiveis:\t%d",TOT-count1);
            count1=contasituacao(mnumdequartos,4,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos vendidos:\t\t%d",count1);
            count1=contasituacao(mnumdequartos,5,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos reservados:\t%d",count1);
            count1=contasituacao(mnumdequartos,6,0);
            fprintf(pfarquivo1,"\nTotal de apartamentos da construtora:\t%d",count1);
            fclose(pfarquivo1);
            printf("\nO arquivo arquivo4.txt foi criado na pasta arquivos");

        }
        }
        if(escolha==5)
        {
            for(i=0;i<TOT;i++)
            {
                if(vscadastro[i].svendaoureserva==0)
                {
                    break;
                }
            }
            indice=i;
            //printf("\nteste do indice a ser gravada a venda = %d",indice);
            printf("\ninsira o bloco:\t\t");
            scanf("%d",&vscadastro[indice].sbloco);
            vscadastro[indice].sbloco=looppergunta(vscadastro[indice].sbloco,4);
            printf("\ninsira o andar:\t\t");
            scanf("%d",&vscadastro[indice].sandar);
            vscadastro[indice].sandar=looppergunta(vscadastro[indice].sandar,10);
            printf("\ninsira a coluna:\t");
            scanf("%d",&vscadastro[indice].scoluna);
            vscadastro[indice].scoluna=looppergunta(vscadastro[indice].scoluna,6);
            vscadastro[indice].snquartos=descobrenumdequartos(vscadastro[indice].scoluna);

            somar(vscadastro[indice].sbloco,vscadastro[indice].sandar,vscadastro[indice].scoluna,&soma); //BAAC
            count1=teste(mnumdequartos,soma);
            if (count1==1)
            {count1=vender(mvalorbaseap,soma,&valordoap,&descoufinanc);}
            vscadastro[indice].svalordoap=valordoap;
            vscadastro[indice].sdescoufinanc=descoufinanc;

            if(count1==1)
            {
                //tem que perguntar se ele quer vaga:
                printf("\nO valor de cada vaga eh %.2f",valorbasevaga);
                printf("\nDeseja adquirir vaga(s)(1-S/0-N)?");
                scanf("%d",&count1);
                count1=looppergunta(count1,0);
                if (count1==1)
                {
                vscadastro[indice].svalordavaga=vendervaga(mvagas,soma,&nvagas,&vaga1,&vaga2);//valordavaga=valorfinal ja calculado o desconto. nvagas=num de vagas. vaga1=LLCC, vaga2=LLCC
                vscadastro[indice].snvagas=nvagas;
                vscadastro[indice].svaga1=vaga1;
                vscadastro[indice].svaga2=vaga2;
                }
                else
                {
                vscadastro[indice].svalordavaga=0;
                vscadastro[indice].snvagas=0;
                }

                printf("\nInsira o nome do Cliente:\n");
                scanf(" %[^\n]s%*c", vscadastro[indice].scnome);
                printf("\nTelefone:\t");
                scanf(" %[^\n]s%*c", vscadastro[indice].sctelefone);
                printf("\nCPF:\t\t");
                scanf(" %[^\n]s%*c", vscadastro[indice].sccpf);

                vscadastro[indice].svendaoureserva=4;
                cadastroclientestruct(vscadastro[indice],nomedovendedor);
                printf("\nConfirma venda do apartamento?");
                scanf("%d",&count1);
                count1=looppergunta(count1,0);
                if(count1==1)
                {
                    //1-marcar as vagas
                    pfvagas = fopen(cfvagas,"r+b");
                    if(pfvagas==NULL)
                    {printf("\nnao foi possivel abrir o arquivo filevagas.txt");}
                    rewind(pfvagas);
                    fwrite(mvagas,sizeof(float),400,pfvagas);
                    fclose(pfvagas);
                    //2-marcar na mnumdequartos que esse ap foi vendido
                    pfmnumdequartos = fopen(cfmnumdequartos,"r+b");
                    if(pfmnumdequartos==NULL)
                    {printf("\nnao foi possivel abrir o arquivo filematriznumdequartos.txt");}
                    mnumdequartos[vscadastro[indice].sbloco-1][vscadastro[indice].sandar-1][vscadastro[indice].scoluna-1]=4;
                    rewind(pfmnumdequartos);
                    fwrite(mnumdequartos,sizeof(int),240,pfmnumdequartos);
                    fclose(pfmnumdequartos);
                    //3-calcular comissao do vendedor
                    pfcomissao = fopen(cfcomissao,"r+b");
                    if (pfcomissao==NULL)
                    {printf("\nNao foi possivel abrir filecomissoes.txt");}
                    fread(vcomissao,sizeof(float),4,pfcomissao);
                    vcomissao[usuario]=vcomissao[usuario]+(vscadastro[indice].svalordoap+vscadastro[indice].svalordavaga)*0.004;
                    rewind(pfcomissao);
                    fwrite(vcomissao,sizeof(float),4,pfcomissao);
                    fclose(pfcomissao);
                    //4-marcar a hora da venda
                    time(&vscadastro[indice].shoradavenda);
                    //5 gravar num file externo
                    cadastroclientestructfile(vscadastro[indice],nomedovendedor,pfcadastro);
                    printf("Venda realizada com sucesso");
                }
                else
                {
                    vscadastro[indice].svendaoureserva=0;
                    printf("\nVenda nao realizada");
                }
        }
    }
        if(escolha==6)
        {
            for(i=0;i<TOT;i++)
            {
                if(vscadastro[i].svendaoureserva==0)
                {
                    break;
                }
            }
            indice=i;
            //printf("\nteste do indice. indice a ser gravada a reserva = %d",indice);
            printf("\ninsira o bloco:\t\t");
            scanf("%d",&vscadastro[indice].sbloco);
            vscadastro[indice].sbloco=looppergunta(vscadastro[indice].sbloco,4);
            printf("\ninsira o andar:\t\t");
            scanf("%d",&vscadastro[indice].sandar);
            vscadastro[indice].sandar=looppergunta(vscadastro[indice].sandar,10);
            printf("\ninsira a coluna:\t");
            scanf("%d",&vscadastro[indice].scoluna);
            vscadastro[indice].scoluna=looppergunta(vscadastro[indice].scoluna,6);
            vscadastro[indice].snquartos=descobrenumdequartos(vscadastro[indice].scoluna);

            somar(vscadastro[indice].sbloco,vscadastro[indice].sandar,vscadastro[indice].scoluna,&soma); //BAAC
            count1=teste(mnumdequartos,soma);
            if (count1==1)
            {count1=vender(mvalorbaseap,soma,&valordoap,&descoufinanc);}
            vscadastro[indice].svalordoap=valordoap;
            vscadastro[indice].sdescoufinanc=descoufinanc;

            if(count1==1)
            {
                //tem que perguntar se ele quer vaga:
                printf("\nO valor de cada vaga eh %.2f",valorbasevaga);
                printf("\nDeseja adquirir vaga(s)(1-S/0-N)?");
                scanf("%d",&count1);
                count1=looppergunta(count1,0);
                if (count1==1)
                {
                vscadastro[indice].svalordavaga=vendervaga(mvagas,soma,&nvagas,&vaga1,&vaga2);//valordavaga=valorfinal ja calculado o desconto. nvagas=num de vagas. vaga1=LLCC, vaga2=LLCC
                vscadastro[indice].snvagas=nvagas;
                vscadastro[indice].svaga1=vaga1;
                vscadastro[indice].svaga2=vaga2;
                }
                else
                {
                vscadastro[indice].svalordavaga=0;
                vscadastro[indice].snvagas=0;
                }

                printf("\nInsira o nome do Cliente:\n");
                scanf(" %[^\n]s%*c", vscadastro[indice].scnome);
                printf("\nTelefone:\t");
                scanf(" %[^\n]s%*c", vscadastro[indice].sctelefone);
                printf("\nCPF:\t\t");
                scanf(" %[^\n]s%*c", vscadastro[indice].sccpf);

                cadastroclientestruct(vscadastro[indice],nomedovendedor);
                printf("\nConfirma reserva do apartamento?");
                scanf("%d",&count1);
                count1=looppergunta(count1,0);
                if(count1==1)
                {
                    //1-marcar as vagas
                    pfvagas = fopen(cfvagas,"r+b");
                    if(pfvagas==NULL)
                    {printf("\nnao foi possivel abrir o arquivo filevagas.txt");}
                    rewind(pfvagas);
                    fwrite(mvagas,sizeof(float),400,pfvagas);
                    fclose(pfvagas);
                    //2-marcar na mnumdequartos que esse ap foi reservado
                    pfmnumdequartos = fopen(cfmnumdequartos,"r+b");
                    if(pfmnumdequartos==NULL)
                    {printf("\nnao foi possivel abrir o arquivo filematriznumdequartos.txt");}
                    mnumdequartos[vscadastro[indice].sbloco-1][vscadastro[indice].sandar-1][vscadastro[indice].scoluna-1]=5;
                    rewind(pfmnumdequartos);
                    fwrite(mnumdequartos,sizeof(int),240,pfmnumdequartos);
                    fclose(pfmnumdequartos);
                    //3-calcular comissao do vendedor - (deixo reservado)
                    pfcomissao = fopen(cfcomissao,"r+b");
                    //if (pfcomissao==NULL)
                    //{printf("\nNao foi possivel abrir filecomissoes.txt");}
                    //fread(vcomissao,sizeof(float),4,pfcomissao);
                    vcomissaoreservada[indice]=(vscadastro[indice].svalordoap+vscadastro[indice].svalordavaga)*0.004;
                    //rewind(pfcomissao);
                    //fwrite(vcomissao,sizeof(float),4,pfcomissao);
                    //fclose(pfcomissao);
                    //4-marcar a hora da venda
                    time(&testehora);
                    testehora=testehora+tempo;
                    vscadastro[indice].shoradavenda=testehora;
                    vhoras[indice]=testehora;
                    vscadastro[indice].shoradavenda=vscadastro[indice].shoradavenda+tempo;
                    //5-gravar dados do cliente num file
                    cadastroclientestructfile(vscadastro[indice],nomedovendedor,pfcadastro);
                    //6-gravar um BAACI
                    soma=soma*10;
                    soma=soma+5;
                    vscadastro[indice].svendaoureserva=soma;
                    vindices[indice]=soma;

                    printf("Reserva realizada com sucesso\nO cliente tem 48h para efetivar a compra");
                }
                else
                {
                    vscadastro[indice].svendaoureserva=0;
                    printf("\nReserva nao realizada");
                }
        }
    }
        if(escolha==7)
        {
            exibe2(mvalorbaseap);
        }
        if(escolha==8)
        {
        count1=0;
        for(i=0;i<TOT;i++)
        {
            if(vindices[i]>10)
            {count1++;}
        }
        if(count1)
        {
            k=1;
            time(&testehora);
            printf("\n\t|Ap\t|Tempo restante\t|\n");
            for(i=0;i<TOT;i++)
            {
                if(vindices[i]>10)
                {
                    //somar(vscadastro[i].sbloco,vscadastro[i].sandar,vscadastro[i].scoluna,&soma);
                    testehora2=difftime(vhoras[i],testehora);
                    convertehora(testehora2,&hora,&minutos,&segundos);
                    printf("%d\t| %d\t|  %2.0f:%2.0f:%2.0f\t|",k,vindices[i]/10,hora,minutos,segundos);
                    printf("\n");
                    //time(&testehora);
                    k++;
                }
            }
            printf("\nDeseja encerrar a venda de um desses apartamentos?(1-S/0-N)");
            scanf("%d",&count1);
            count1=looppergunta(count1,0);
            if(count1==1)
            {
                printf("\nEscolha o apartamento a ser vendido");
                scanf("%d",&k);
                //k=looppergunta(k,k-1);
                count1=0;
                for(i=0;i<TOT;i++)
                {

                    if(vindices[i]>10)
                    {
                        count1++;
                        if(count1==k)
                        {
                            break;
                        }
                    }
                }
                //somar(vscadastro[i].sbloco,vscadastro[i].sandar,vscadastro[i].scoluna,&soma);
                //printf("\nO apartemento a ser vendido eh o %d?",soma);
                //1-marcar na pnmumdequartos que ap foi vendido
                vindices[i]=vindices[i]/10;
                soma=vindices[i];
                decifrar(vindices[i],&bloco,&andar,&coluna);
                pfmnumdequartos=fopen(cfmnumdequartos,"r+b");
                mnumdequartos[bloco-1][andar-1][coluna-1]=4;
                if(pfmnumdequartos == NULL)
                {printf("Erro, nao foi possivel abrir o arquivo filenumdequartos.txt\n");}
                rewind(pfmnumdequartos);
                fwrite(mnumdequartos,sizeof(int),TOT,pfmnumdequartos);
                fclose(pfmnumdequartos);
                //2-zerar e marcar 4 na struct
                vscadastro[i].shoradavenda=0;
                vhoras[i]=0;
                vscadastro[i].svendaoureserva=4;
                vindices[i]=4;
                //3-pagar a comissao do vendedor
                pfcomissao = fopen(cfcomissao,"r+b");
                if (pfcomissao==NULL)
                {printf("\nNao foi possivel abrir filecomissoes.txt");}
                fread(vcomissao,sizeof(float),4,pfcomissao);
                vcomissao[usuario]=vcomissao[usuario]+vcomissaoreservada[i];
                rewind(pfcomissao);
                fwrite(vcomissao,sizeof(float),4,pfcomissao);
                fclose(pfcomissao);

                cadastroclientestructfile(vscadastro[i],nomedovendedor,pfcadastro);

                printf("\nA venda do apartamento %d foi consolidada",soma);

            }
        }
        else
        {
            printf("\nnao ha apartamentos reservados");
        }
        }
        if (escolha==9)
        {
            printf("\n---OPCOES---");
            printf("\n1 - exibir todas as vagas do condominio");
            printf("\n2 - filtrar vagas por bloco\n");
            scanf("%d",&count1);
            count1=looppergunta(count1,2);
            if(count1==1)
            {exibe4(mvagas,0);}
            else
            {
                printf("\ninsira o bloco a ser filtrado");
                scanf("%d",&count1);
                exibe4(mvagas,count1);
            }
        }
        if(escolha==10)
        {
            printf("\ninsira o bloco:\t\t");
            scanf("%d",&bloco);
            bloco=looppergunta(bloco,4);
            printf("\ninsira o andar:\t\t");
            scanf("%d",&andar);
            andar=looppergunta(andar,10);
            printf("\ninsira a coluna:\t");
            scanf("%d",&coluna);
            coluna=looppergunta(coluna,6);
            somar(bloco,andar,coluna,&soma);
            count1=teste(mnumdequartos,soma);
            if(count1==1)
            {
                mnumdequartos[bloco-1][andar-1][coluna-1]=6;
                pfmnumdequartos = fopen(cfmnumdequartos,"r+b");
                if(pfmnumdequartos==NULL)
                {
                    printf("\nnao foi possivel abrir o arquivo filematriznumdequartos.txt");
                }
                fwrite(mnumdequartos,sizeof(int),TOT,pfmnumdequartos);
                fclose(pfmnumdequartos);
                printf("\nApartamento reservado para a construtora");
            }
            else
            {
                printf("\nNao eh possivel reservar este apartamento");
            }
        }
        if(escolha==11)
        {
            pfcomissao = fopen(cfcomissao,"r+b");
            if (pfcomissao==NULL)
            {printf("\nNao foi possivel abrir filecomissoes.txt");}
            fread(vcomissao,sizeof(float),4,pfcomissao);
             fclose(pfcomissao);
            printf("\n");
            for(i=0;i<4;i++)
            {
                printf("%s\t%.2f",nomes2[i],vcomissao[i]);
                printf("\n");
            }
            printf("\nDeseja gerar um arquivo .txt para impressao?(1-s/0-n)");
            scanf("%d",&i);
            i=looppergunta(i,0);
            if(i==1)
            {
                pfarquivo1 = fopen(cfcomissaotxt,"w");
                if (pfarquivo1==NULL)
                {printf("\nNao foi possivel abrir filecomissoes.txt");}
                for(i=0;i<4;i++)
                {
                    fprintf(pfarquivo1,"%s\t%.2f",nomes2[i],vcomissao[i]);
                    fprintf(pfarquivo1,"\n");
                }
                fclose(pfarquivo1);
                printf("\nFoi criado o arquivo comissoes.txt na mesma pasta desse programa");

            }

        }


    }
    fclose(pfvendedores);
    for(i=0;i<TOT;i++)
	{vindices[i]=vscadastro[i].svendaoureserva;}
	rewind(pfindice);
	fwrite(vindices,sizeof(int),TOT,pfindice);
	fclose(pfindice);
	rewind(pfiletime);
	fwrite(vhoras,sizeof(time_t),TOT,pfiletime);
	fclose(pfiletime);
	rewind(pfvcomissaoreservada);
	fwrite(vcomissaoreservada,sizeof(float),TOT,pfvcomissaoreservada);
	fclose(pfvcomissaoreservada);
}

