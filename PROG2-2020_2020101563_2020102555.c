/*
PROG II TRABALHO SARS-COV-2 ES Statistics
MATEUS TICIANELI SARTORIO  - 2020101563
THIAGO AYOLPHI LIUTH - 2020102555
NOVEMBRO/DEZEMBRO 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

//o tamanho se refere à quantidade total de linhas
#define tamanho 202362



//struct para datas
typedef struct
{
  int dia;
  int mes;
  int ano;
} Data;


//struct para valores int das comorbidades
typedef struct
{
  int Pulmao;
  int Cardio;
  int Renal;
  int Diabetes;
  int Tabagismo;
  int Obesidade;
} Tratados;

//struct principal
typedef struct
{
  Tratados Comorbidade;
  Data dataCadastro;
  int Cadastro;
  Data dataObito;
  int Obito;
  char Class[15];
  int Classificacao;
  char NomeMunicipio[30];
  int CodigoMunicipio;
  int IdadeNaDataNotificacao;
  char Pulmao[5];
  char Cardio[5];
  char Renal[5];
  char Diabetes[5];
  char Tabagismo[5];
  char Obesidade[5];
  char Internado[15];
  int FicouInternado;
} DadosDoArquivo;


//lista de strings para tratamento de dados dos municipios
char municipio0[30] = "AFONSO CLAUDIO";
char municipio1[30] = "AGUA DOCE DO NORTE";
char municipio2[30] = "AGUIA BRANCA";
char municipio3[30] = "ALEGRE";
char municipio4[30] = "ALFREDO CHAVES";
char municipio5[30] = "ALTO RIO NOVO";
char municipio6[30] = "ANCHIETA";
char municipio7[30] = "APIACA";
char municipio8[30] = "ARACRUZ";
char municipio9[30] = "ATILIO VIVACQUA";
char municipio10[30] = "BAIXO GUANDU";
char municipio11[30] = "BARRA DE SAO FRANCISCO";
char municipio12[30] = "BOA ESPERANCA";
char municipio13[30] = "BOM JESUS DO NORTE";
char municipio14[30] = "BREJETUBA";
char municipio15[30] = "CACHOEIRO DE ITAPEMIRIM";
char municipio16[30] = "CARIACICA";
char municipio17[30] = "CASTELO";
char municipio18[30] = "COLATINA";
char municipio19[30] = "CONCEICAO DA BARRA";
char municipio20[30] = "CONCEICAO DO CASTELO";
char municipio21[30] = "DIVINO DE SAO LOURENCO";
char municipio22[30] = "DOMINGOS MARTINS";
char municipio23[30] = "DORES DO RIO PRETO";
char municipio24[30] = "ECOPORANGA";
char municipio25[30] = "FUNDAO";
char municipio26[30] = "GOVERNADOR LINDENBERG";
char municipio27[30] = "GUACUI";
char municipio28[30] = "GUARAPARI";
char municipio29[30] = "IBATIBA";
char municipio30[30] = "IBIRACU";
char municipio31[30] = "IBITIRAMA";
char municipio32[30] = "ICONHA";
char municipio33[30] = "IRUPI";
char municipio34[30] = "ITAGUACU";
char municipio35[30] = "ITAPEMIRIM";
char municipio36[30] = "ITARANA";
char municipio37[30] = "IUNA";
char municipio38[30] = "JAGUARE";
char municipio39[30] = "JERONIMO MONTEIRO";
char municipio40[30] = "JOAO NEIVA";
char municipio41[30] = "LARANJA DA TERRA";
char municipio42[30] = "LINHARES";
char municipio43[30] = "MANTENOPOLIS";
char municipio44[30] = "MARATAIZES";
char municipio45[30] = "MARECHAL FLORIANO";
char municipio46[30] = "MARILANDIA";
char municipio47[30] = "MIMOSO DO SUL";
char municipio48[30] = "MONTANHA";
char municipio49[30] = "MUCURICI";
char municipio50[30] = "MUNIZ FREIRE";
char municipio51[30] = "MUQUI";
char municipio52[30] = "NOVA VENECIA";
char municipio53[30] = "PANCAS";
char municipio54[30] = "PEDRO CANARIO";
char municipio55[30] = "PINHEIROS";
char municipio56[30] = "PIUMA";
char municipio57[30] = "PONTO BELO";
char municipio58[30] = "PRESIDENTE KENNEDY";
char municipio59[30] = "RIO BANANAL";
char municipio60[30] = "RIO NOVO DO SUL";
char municipio61[30] = "SANTA LEOPOLDINA";
char municipio62[30] = "SANTA MARIA DE JETIBA";
char municipio63[30] = "SANTA TERESA";
char municipio64[30] = "SAO DOMINGOS DO NORTE";
char municipio65[30] = "SAO GABRIEL DA PALHA";
char municipio66[30] = "SAO JOSE DO CALCADO";
char municipio67[30] = "SAO MATEUS";
char municipio68[30] = "SAO ROQUE DO CANAA";
char municipio69[30] = "SERRA";
char municipio70[30] = "SOORETAMA";
char municipio71[30] = "VARGEM ALTA";
char municipio72[30] = "VENDA NOVA DO IMIGRANTE";
char municipio73[30] = "VIANA";
char municipio74[30] = "VILA PAVAO";
char municipio75[30] = "VILA VALERIO";
char municipio76[30] = "VILA VELHA";
char municipio77[30] = "VITORIA";

//string diretorio para impressão de saída
char diretorio[20];

// vetor que armazena todos os dados do arquivo de entrada
DadosDoArquivo dados[202362];


//funcões de saída
void ordemAlfabetica(int n);
int numeroDeCasos(Data d1, Data d2);
void cidadesTop(int n, Data d1, Data d2);
void porcentagensNosMunicipios(char municipio[30]);
void mediaDesvioPadrao(Data d1, Data d2);

//funções auxiliares
void trataDados();
int filtroDeData(Data data);
void retornaMunicipio(int codigo, char municipio[30]);
void corrigeMunicipio(char string[30]);
int codificaMunicipio(char Municipio[30]);


int main()
{
    //abrindo arquivo
    FILE *fp;
    fp = fopen("covid19ES.csv", "r");
    if(fp == NULL)
    {
      printf("Erro na abertura do arquivo\n");
      exit(1);
    }

    int i;

    // ignorando a primeira linha do csv
    fscanf(fp, "%*[^\n]%*c");

    //realiza a leitura percorrendo linha por linha
    for(i=0; i<tamanho; i++){
        // lendo as duas datas
        fscanf(fp, "%d-%d-%d,%d-%d-%d,", &dados[i].dataCadastro.ano, &dados[i].dataCadastro.mes, &dados[i].dataCadastro.dia, &dados[i].dataObito.ano, &dados[i].dataObito.mes, &dados[i].dataObito.dia);
        // lendo classificação
        fscanf(fp, "%[^,],", dados[i].Class);
        // lendo municipio
        fscanf(fp, "%[^,],", dados[i].NomeMunicipio);
        // ler idade, que está entre aspas duplas
        fscanf(fp, "%*c%d %*[^\"]%*c,", &dados[i].IdadeNaDataNotificacao);
        // lendo as comorbidades
        fscanf(fp, "%[^,],", dados[i].Pulmao);
        fscanf(fp, "%[^,],", dados[i].Cardio);
        fscanf(fp, "%[^,],", dados[i].Renal);
        fscanf(fp, "%[^,],", dados[i].Diabetes);
        fscanf(fp, "%[^,],", dados[i].Tabagismo);
        fscanf(fp, "%[^,],", dados[i].Obesidade);
        fscanf(fp, "%[^\n]%*c", dados[i].Internado);
    }

    //fechando arquivo
    fclose(fp);

    //trata comorbidades, classificação e ficou internado para valores inteiros
    trataDados(dados);

    //variáveis usadas para ler as entradas dos testes
    int item3_n, item5_n;
    Data item4_d1, item4_d2, item5_d1, item5_d2, item7_d1, item7_d2;
    char item_6_municipio[30];

    //lendo entrada dos testes
    scanf("./%[^\n]\n", diretorio);
    scanf("%d\n2020-%d-%d 2020-%d-%d\n%d 2020-%d-%d 2020-%d-%d\n%[^\n]%*c2020-%d-%d 2020-%d-%d", &item3_n, &item4_d1.mes, &item4_d1.dia, &item4_d2.mes, &item4_d2.dia,
    &item5_n, &item5_d1.mes, &item5_d1.dia, &item5_d2.mes, &item5_d2.dia, item_6_municipio, &item7_d1.mes, &item7_d1.dia, &item7_d2.mes, &item7_d2.dia);

    //criando o diretório definido no teste
    mkdir(diretorio, 0777);

    //chama as funções de saída
    ordemAlfabetica(item3_n);
    numeroDeCasos(item4_d1, item4_d2);
    cidadesTop(item5_n, item5_d1, item5_d2);
    porcentagensNosMunicipios(item_6_municipio);
    mediaDesvioPadrao(item7_d1, item7_d2);


    return 0;
}


//Função 3
void ordemAlfabetica(int n)
{
  //cria string que define diretório de saída (usa a string da entrada do teste concatenada com o nome esperado do arquivo de saída)
  char pasta[30];

  strcpy(pasta, diretorio);
  strcat(pasta, "item3.txt");

  //cria arquivo de saída
  FILE *f3;
  f3 = fopen(pasta, "w");
  char municipio[30];

  //declarando variáveis, sendo contmunicipio a contagem de casos confirmados em cada um
  int cont, k, contmunicipio[78] = {0};


    //esse loop percorre todas as linhas. Em cada uma percorre a lista de municipios e verifica se a classificação é 1. Nesse caso, aumenta o contador do municipio
    long int i;
    for(i = 0; i < tamanho; i++)
    {

           for(k=0; k<78; k++){
                if(dados[i].CodigoMunicipio == k && dados[i].Classificacao==1)
                  contmunicipio[k]++;


           }


    }


    //passa por cada municipio, já distribuidos em ordem alfabética, e verifica se o número de casos está acima do n pedido pelo teste
    for(k=0; k<78; k++){
        if(contmunicipio[k]>n){
            retornaMunicipio(k, municipio);
            fprintf(f3, "- %s: %d casos\n", municipio, contmunicipio[k]);
        }
    }


    return;
}


//função 4
int numeroDeCasos(Data d1, Data d2)
{
  //cria string que define diretório de saída
  char pasta[30];
  strcpy(pasta, diretorio);
  strcat(pasta, "item4.txt");

  FILE *f4;
  f4 = fopen(pasta, "w");

  //declarando variáveis
  int numCasos = 0;
  int Nd1, Nd2;
  long int i = 0;

  //transformando mes e dia para um valor único
  Nd1 = filtroDeData(d1);
  Nd2 = filtroDeData(d2);



  //esse for verifica se a data está dentro do intervalo desejado e se a classificação é 1. Caso atenda ambas as condições, aumenta o contador de casos
  for(i = 0; i < tamanho; i++)
  {

    if(dados[i].Cadastro >= Nd1 && dados[i].Cadastro <= Nd2)
    {
      if(dados[i].Classificacao==1)
      {
        numCasos++;
      }
    }
  }

  //imprimindo resultado no arquivo
  fprintf(f4, "- Total de pessoas: %d", numCasos);

  return numCasos;

}


//função 5
void cidadesTop(int n, Data d1, Data d2)
{
  //cria string que define diretório de saída
  char pasta[30];
  strcpy(pasta, diretorio);
  strcat(pasta, "item5.txt");

  FILE *f5;
  f5 = fopen(pasta, "w");

  //declarando variáveis
  int Nd1, Nd2, j, k, cont, troca;
  int valor, temp;
  char municipio[30];

  long int i;

  //transformando mês e dia para um valor inteiro
  Nd1 = filtroDeData(d1);
  Nd2 = filtroDeData(d2);

  //zerando posições do vetor
  int contmunicipio[78]={0};


  //conta quantidade de casos de cada município dentro de um intervalo de datas
  for(i = 0; i < tamanho; i++)
  {
    if(dados[i].Cadastro >= Nd1 && dados[i].Cadastro <= Nd2)
    {
      for(k=0; k<78; k++){
                if(dados[i].CodigoMunicipio == k && dados[i].Classificacao==1)
                contmunicipio[k]++;
           }

    }
  }

  int matriz[78][2];

  for(j = 0; j < 78; j++)
  {
    matriz[j][0] = j;
    matriz[j][1] = contmunicipio[j];
  }


  int menor, aux1, aux2;

  //utiliza bubble sort para ordenar os vetores em ordem decrescente
  for(j = 0; j < 77; j++)
  {
    menor = j;

    for(k = j + 1; k < 78; k++)
    {
      if(matriz[menor][1] > matriz[k][1])
        menor = k;

    }
    if(j != menor)
    {
      aux1 = matriz[j][1];
      aux2 = matriz[j][0];

      matriz[j][1] = matriz[menor][1];
      matriz[j][0] = matriz[menor][0];
      matriz[menor][1] = aux1;
      matriz[menor][0] = aux2;
    }
  }

  //imprime resultados em um arquivo
  for(i = 77; i >= 78 - n; i--)
  {
    retornaMunicipio(matriz[i][0], municipio);
    fprintf(f5, "- %s: %d casos\n", municipio, matriz[i][1]);
  }

  return;

}


//função 6
void porcentagensNosMunicipios(char municipio[30])
{
  //cria string que define diretório de saída
  char pasta[30];

  strcpy(pasta, diretorio);
  strcat(pasta, "item6.txt");

  FILE *f6;
  f6 = fopen(pasta, "w");

  //essa função assegura que todos os caracteres da string municipio são maiúsculas
  corrigeMunicipio(municipio);

  //declarando variáveis que serão utilizadas nas operações
  int codigo;
  long int i, confirmado = 0, confirmadoEInternado = 0, confirmadoEObito = 0, confirmadoEInternadoEObito = 0;
  float porcentConfirmadoEInternado, porcentObito, porcentInternadoEObito;

  //caso a entrada referente a municipio no teste seja TODAS a função percorrerá todas as linhas, somando os valores necessários às operações
  if(strcmp(municipio, "TODAS")==0){
    for(i=0; i<tamanho; i++){
      if(dados[i].Classificacao == 1)
        confirmado++;
      if(dados[i].Classificacao==1 && dados[i].FicouInternado==1)
        confirmadoEInternado++;
      if(dados[i].Classificacao==1 && dados[i].Obito!=0)
        confirmadoEObito++;
      if(dados[i].Classificacao==1 && dados[i].Obito!=0 && dados[i].FicouInternado==1)
        confirmadoEInternadoEObito++;
      }

  //caso a string referente a municipio seja de um em específico, além de percorrer as linhas ele verifica se a linha em questão se refere ao município alvo
  }else{
    //a função codigicaMunicipio atribui um valor int para cada município para ser utilizado nas operações
    codigo = codificaMunicipio(municipio);

    for(i=0; i<tamanho; i++){

      if(dados[i].CodigoMunicipio==codigo){

      if(dados[i].Classificacao == 1)
        confirmado++;
      if(dados[i].Classificacao==1 && dados[i].FicouInternado==1)
        confirmadoEInternado++;
      if(dados[i].Classificacao==1 && dados[i].Obito!=0)
        confirmadoEObito++;
      if(dados[i].Classificacao==1 && dados[i].Obito!=0 && dados[i].FicouInternado==1)
        confirmadoEInternadoEObito++;
      }

      }
  }

  //calcula os valores pedidos
  porcentConfirmadoEInternado = (confirmadoEInternado*100.0)/((float) confirmado );
  porcentObito=(confirmadoEObito*100.0)/((float)confirmado);
  porcentInternadoEObito=(confirmadoEInternadoEObito*100.0)/((float) confirmadoEObito);

  //imprime resultados no arquivo
  fprintf(f6, "- Resultados para %s:\n- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n- A %% de pessoas com Covid-19 que morreram: %.3f%%\n- A %% de pessoas que ficaram internadas e morreram: %.3f%%",
        municipio, porcentConfirmadoEInternado, porcentObito, porcentInternadoEObito);

  return;
}

//função 7
void mediaDesvioPadrao(Data d1, Data d2)
{
  //cria string que define diretório de saída
  char pasta[30];

  strcpy(pasta, diretorio);
  strcat(pasta, "item7.txt");

  FILE *f7;
  f7 = fopen(pasta, "w");

  //declarando variáveis
  int Nd1, Nd2;

  long int i = 0, k = 0,  semComorbidade =  0, totalMortes = 0, somaIdade = 0;

  double mediaIdade, desvioPadrao, variancia = 0, porcentSemComorbidade;

  int idade[tamanho + 1];

  //transforma mês e dia em um único valor int
  Nd1 = filtroDeData(d1);
  Nd2 = filtroDeData(d2);

  //calcula o total de mortes, o total de mortes sem comorbidade e a soma das idades
  for(i=0; i<tamanho; i++){
    if(dados[i].Cadastro >= Nd1 && dados[i].Cadastro <= Nd2 && dados[i].Obito != 0 && dados[i].Classificacao==1)
    {
      somaIdade += dados[i].IdadeNaDataNotificacao;
      idade[k] = dados[i].IdadeNaDataNotificacao;
      k++;

      totalMortes++;

      if(dados[i].Comorbidade.Pulmao==0 && dados[i].Comorbidade.Cardio==0 && dados[i].Comorbidade.Renal==0 && dados[i].Comorbidade.Diabetes==0 && dados[i].Comorbidade.Tabagismo==0 && dados[i].Comorbidade.Obesidade==0)
        semComorbidade++;
    }
  }

    mediaIdade = ( somaIdade ) / ( (float) totalMortes );

    //calcula a variância
    for(k = 0; k < totalMortes; k++)
    {
      variancia += pow((idade[k] - mediaIdade), 2);
    }

    //calcula o desvio padrão
    desvioPadrao = sqrt( ( (float) variancia ) / ( (float) (totalMortes - 1) ) );

    porcentSemComorbidade = (semComorbidade*100.0)/(float)totalMortes;


    fprintf(f7, "A media e desvio padrao da idade: %0.3f -- %0.3f\nA %% de pessoas que morreram sem comorbidade: %0.3f%%", mediaIdade, desvioPadrao, porcentSemComorbidade);

    return;

}



//todas as funções daqui para baixo são auxiliares


//transforma as datas de entrada em apenas um valor inteiro igual a 100*mês + dia
int filtroDeData(Data data)
{
  int ndia = 0;

  ndia = 100*data.mes + data.dia;

  return ndia;

}


/*
  recebe uma string com o nome do municipio e retorna um inteiro
  o primeiro municipio em ordem alfabetica retorna 0 e o ultimo retorna 77
*/
int codificaMunicipio(char Municipio[30])
{
  int codigo;

  if(strcmp(Municipio, municipio0) == 0)
    codigo = 0;
  else if(strcmp(Municipio, municipio1) == 0)
    codigo = 1;
  else if(strcmp(Municipio, municipio2) == 0)
    codigo = 2;
  else if(strcmp(Municipio, municipio3) == 0)
    codigo = 3;
  else if(strcmp(Municipio, municipio4) == 0)
    codigo = 4;
  else if(strcmp(Municipio, municipio5) == 0)
    codigo = 5;
  else if(strcmp(Municipio, municipio6) == 0)
    codigo = 6;
  else if(strcmp(Municipio, municipio7) == 0)
    codigo = 7;
  else if(strcmp(Municipio, municipio8) == 0)
    codigo = 8;
  else if(strcmp(Municipio, municipio9) == 0)
    codigo = 9;
  else if(strcmp(Municipio, municipio10) == 0)
    codigo = 10;
  else if(strcmp(Municipio, municipio11) == 0)
    codigo = 11;
  else if(strcmp(Municipio, municipio12) == 0)
    codigo = 12;
  else if(strcmp(Municipio, municipio13) == 0)
    codigo = 13;
  else if(strcmp(Municipio, municipio14) == 0)
    codigo = 14;
  else if(strcmp(Municipio, municipio15) == 0)
    codigo = 15;
  else if(strcmp(Municipio, municipio16) == 0)
    codigo = 16;
  else if(strcmp(Municipio, municipio17) == 0)
    codigo = 17;
  else if(strcmp(Municipio, municipio18) == 0)
    codigo = 18;
  else if(strcmp(Municipio, municipio19) == 0)
    codigo = 19;
  else if(strcmp(Municipio, municipio20) == 0)
    codigo = 20;
  else if(strcmp(Municipio, municipio21) == 0)
    codigo = 21;
  else if(strcmp(Municipio, municipio22) == 0)
    codigo = 22;
  else if(strcmp(Municipio, municipio23) == 0)
    codigo = 23;
  else if(strcmp(Municipio, municipio24) == 0)
    codigo = 24;
  else if(strcmp(Municipio, municipio25) == 0)
    codigo = 25;
  else if(strcmp(Municipio, municipio26) == 0)
    codigo = 26;
  else if(strcmp(Municipio, municipio27) == 0)
    codigo = 27;
  else if(strcmp(Municipio, municipio28) == 0)
    codigo = 28;
  else if(strcmp(Municipio, municipio29) == 0)
    codigo = 29;
  else if(strcmp(Municipio, municipio30) == 0)
    codigo = 30;
  else if(strcmp(Municipio, municipio31) == 0)
    codigo = 31;
  else if(strcmp(Municipio, municipio32) == 0)
    codigo = 32;
  else if(strcmp(Municipio, municipio33) == 0)
    codigo = 33;
  else if(strcmp(Municipio, municipio34) == 0)
    codigo = 34;
  else if(strcmp(Municipio, municipio35) == 0)
    codigo = 35;
  else if(strcmp(Municipio, municipio36) == 0)
    codigo = 36;
  else if(strcmp(Municipio, municipio37) == 0)
    codigo = 37;
  else if(strcmp(Municipio, municipio38) == 0)
    codigo = 38;
  else if(strcmp(Municipio, municipio39) == 0)
    codigo = 39;
  else if(strcmp(Municipio, municipio40) == 0)
    codigo = 40;
  else if(strcmp(Municipio, municipio41) == 0)
    codigo = 41;
  else if(strcmp(Municipio, municipio42) == 0)
    codigo = 42;
  else if(strcmp(Municipio, municipio43) == 0)
    codigo = 43;
  else if(strcmp(Municipio, municipio44) == 0)
    codigo = 44;
  else if(strcmp(Municipio, municipio45) == 0)
    codigo = 45;
  else if(strcmp(Municipio, municipio46) == 0)
    codigo = 46;
  else if(strcmp(Municipio, municipio47) == 0)
    codigo = 47;
  else if(strcmp(Municipio, municipio48) == 0)
    codigo = 48;
  else if(strcmp(Municipio, municipio49) == 0)
    codigo = 49;
  else if(strcmp(Municipio, municipio50) == 0)
    codigo = 50;
  else if(strcmp(Municipio, municipio51) == 0)
    codigo = 51;
  else if(strcmp(Municipio, municipio52) == 0)
    codigo = 52;
  else if(strcmp(Municipio, municipio53) == 0)
    codigo = 53;
  else if(strcmp(Municipio, municipio54) == 0)
    codigo = 54;
  else if(strcmp(Municipio, municipio55) == 0)
    codigo = 55;
  else if(strcmp(Municipio, municipio56) == 0)
    codigo = 56;
  else if(strcmp(Municipio, municipio57) == 0)
    codigo = 57;
  else if(strcmp(Municipio, municipio58) == 0)
    codigo = 58;
  else if(strcmp(Municipio, municipio59) == 0)
    codigo = 59;
  else if(strcmp(Municipio, municipio60) == 0)
    codigo = 60;
  else if(strcmp(Municipio, municipio61) == 0)
    codigo = 61;
  else if(strcmp(Municipio, municipio62) == 0)
    codigo = 62;
  else if(strcmp(Municipio, municipio63) == 0)
    codigo = 63;
  else if(strcmp(Municipio, municipio64) == 0)
    codigo = 64;
  else if(strcmp(Municipio, municipio65) == 0)
    codigo = 65;
  else if(strcmp(Municipio, municipio66) == 0)
    codigo = 66;
  else if(strcmp(Municipio, municipio67) == 0)
    codigo = 67;
  else if(strcmp(Municipio, municipio68) == 0)
    codigo = 68;
  else if(strcmp(Municipio, municipio69) == 0)
    codigo = 69;
  else if(strcmp(Municipio, municipio70) == 0)
    codigo = 70;
  else if(strcmp(Municipio, municipio71) == 0)
    codigo = 71;
  else if(strcmp(Municipio, municipio72) == 0)
    codigo = 72;
  else if(strcmp(Municipio, municipio73) == 0)
    codigo = 73;
  else if(strcmp(Municipio, municipio74) == 0)
    codigo = 74;
  else if(strcmp(Municipio, municipio75) == 0)
    codigo = 75;
  else if(strcmp(Municipio, municipio76) == 0)
    codigo = 76;
  else if(strcmp(Municipio, municipio77) == 0)
    codigo = 77;
  else
    printf("Parece que esta tendo algum erro na codificacao do municipio\n");

  return codigo;
}


/*transforma os dados lidos do arquivo covid19ES.csv e os transforma em numeros
  para as comorbidades, Sim retorna 1 e Não retorna 0
  caso o paciente foi diagnosticado com covid-19 sua classificacão recebe 1 e caso contrário recebe 0
  o municipio é codificado pela função anterior
  caso o paciente ficou internado sua variável FicouInternado recebe 1 e caso contrário recebe 0
*/
void trataDados()
{
  long int i;

  for(i=0; i<tamanho; i++){
    if(dados[i].Pulmao[0]=='S')
        dados[i].Comorbidade.Pulmao = 1;
    else
        dados[i].Comorbidade.Pulmao = 0;


    if(dados[i].Cardio[0]=='S')
        dados[i].Comorbidade.Cardio = 1;
    else
        dados[i].Comorbidade.Cardio = 0;

    if(dados[i].Renal[0]=='S')
        dados[i].Comorbidade.Renal = 1;
    else
        dados[i].Comorbidade.Renal = 0;

    if(dados[i].Diabetes[0]=='S')
        dados[i].Comorbidade.Diabetes = 1;
    else
        dados[i].Comorbidade.Diabetes = 0;

    if(dados[i].Tabagismo[0]=='S')
        dados[i].Comorbidade.Tabagismo = 1;
    else
        dados[i].Comorbidade.Tabagismo = 0;

    if(dados[i].Obesidade[0]=='S')
        dados[i].Comorbidade.Obesidade = 1;
    else
        dados[i].Comorbidade.Obesidade = 0;

    if(dados[i].Class[0]=='C')
        dados[i].Classificacao=1;
    else
        dados[i].Classificacao=0;

    if(dados[i].Internado[0]=='S')
        dados[i].FicouInternado=1;
    else
        dados[i].FicouInternado=0;

    dados[i].Cadastro = filtroDeData(dados[i].dataCadastro);
    dados[i].Obito = filtroDeData(dados[i].dataObito);
    dados[i].CodigoMunicipio = codificaMunicipio(dados[i].NomeMunicipio);
  }

}


//essa função recebe um inteiro que representa o código de um município e retorna uma string com o seu nome
void retornaMunicipio(int codigo, char municipio[30])
{
    switch(codigo)
    {
    case 0:
        strcpy(municipio, municipio0);
        break;

    case 1:
        strcpy(municipio, municipio1);
        break;

    case 2:
        strcpy(municipio, municipio2);
        break;

    case 3:
        strcpy(municipio, municipio3);
        break;

    case 4:
        strcpy(municipio, municipio4);
        break;

    case 5:
        strcpy(municipio, municipio5);
        break;

    case 6:
        strcpy(municipio, municipio6);
        break;

    case 7:
        strcpy(municipio, municipio7);
        break;

    case 8:
        strcpy(municipio, municipio8);
        break;

    case 9:
        strcpy(municipio, municipio9);
        break;

    case 10:
        strcpy(municipio, municipio10);
        break;

    case 11:
        strcpy(municipio, municipio11);
        break;

    case 12:
        strcpy(municipio, municipio12);
        break;

    case 13:
        strcpy(municipio, municipio13);
        break;

    case 14:
        strcpy(municipio, municipio14);
        break;

    case 15:
        strcpy(municipio, municipio15);
        break;

    case 16:
        strcpy(municipio, municipio16);
        break;

    case 17:
        strcpy(municipio, municipio17);
        break;

    case 18:
        strcpy(municipio, municipio18);
        break;

    case 19:
        strcpy(municipio, municipio19);
        break;

    case 20:
        strcpy(municipio, municipio20);
        break;

    case 21:
        strcpy(municipio, municipio21);
        break;

    case 22:
        strcpy(municipio, municipio22);
        break;

    case 23:
        strcpy(municipio, municipio23);
        break;

    case 24:
        strcpy(municipio, municipio24);
        break;

    case 25:
        strcpy(municipio, municipio25);
        break;

    case 26:
        strcpy(municipio, municipio26);
        break;

    case 27:
        strcpy(municipio, municipio27);
        break;

    case 28:
        strcpy(municipio, municipio28);
        break;

    case 29:
        strcpy(municipio, municipio29);
        break;

    case 30:
        strcpy(municipio, municipio30);
        break;

    case 31:
        strcpy(municipio, municipio31);
        break;

    case 32:
        strcpy(municipio, municipio32);
        break;

    case 33:
        strcpy(municipio, municipio33);
        break;

    case 34:
        strcpy(municipio, municipio34);
        break;

    case 35:
        strcpy(municipio, municipio35);
        break;

    case 36:
        strcpy(municipio, municipio36);
        break;

    case 37:
        strcpy(municipio, municipio37);
        break;

    case 38:
        strcpy(municipio, municipio38);
        break;

    case 39:
        strcpy(municipio, municipio39);
        break;

    case 40:
        strcpy(municipio, municipio40);
        break;

    case 41:
        strcpy(municipio, municipio41);
        break;

    case 42:
        strcpy(municipio, municipio42);
        break;

    case 43:
        strcpy(municipio, municipio43);
        break;

    case 44:
        strcpy(municipio, municipio44);
        break;

    case 45:
        strcpy(municipio, municipio45);
        break;

    case 46:
        strcpy(municipio, municipio46);
        break;

    case 47:
        strcpy(municipio, municipio47);
        break;

    case 48:
        strcpy(municipio, municipio48);
        break;

    case 49:
        strcpy(municipio, municipio49);
        break;

    case 50:
        strcpy(municipio, municipio50);
        break;

    case 51:
        strcpy(municipio, municipio51);
        break;

    case 52:
        strcpy(municipio, municipio52);
        break;

    case 53:
        strcpy(municipio, municipio53);
        break;

    case 54:
        strcpy(municipio, municipio54);
        break;

    case 55:
        strcpy(municipio, municipio55);
        break;

    case 56:
        strcpy(municipio, municipio56);
        break;

    case 57:
        strcpy(municipio, municipio57);
        break;

    case 58:
        strcpy(municipio, municipio58);
        break;

    case 59:
        strcpy(municipio, municipio59);
        break;

    case 60:
        strcpy(municipio, municipio60);
        break;

    case 61:
        strcpy(municipio, municipio61);
        break;

    case 62:
        strcpy(municipio, municipio62);
        break;

    case 63:
        strcpy(municipio, municipio63);
        break;

    case 64:
        strcpy(municipio, municipio64);
        break;

    case 65:
        strcpy(municipio, municipio65);
        break;

    case 66:
        strcpy(municipio, municipio66);
        break;

    case 67:
        strcpy(municipio, municipio67);
        break;

    case 68:
        strcpy(municipio, municipio68);
        break;

    case 69:
        strcpy(municipio, municipio69);
        break;

    case 70:
        strcpy(municipio, municipio70);
        break;

    case 71:
        strcpy(municipio, municipio71);
        break;

    case 72:
        strcpy(municipio, municipio72);
        break;

    case 73:
        strcpy(municipio, municipio73);
        break;

    case 74:
        strcpy(municipio, municipio74);
        break;

    case 75:
        strcpy(municipio, municipio75);
        break;

    case 76:
        strcpy(municipio, municipio76);
        break;

    case 77:
        strcpy(municipio, municipio77);
        break;

    default:
        break;
        printf("Esta dando erro ao imprimir municipio");
    }

}


//essa função recebe uma string com o nome de um município e transforma todas suas letras em letras maiúsculas
void corrigeMunicipio(char string[30])
{
  int i;

  for(i = 0; i < 30; i++)
  {
    if(string[i] >= 'a' && string[i] <= 'z')
    {
      string[i] -= 32;
    }
  }
}
