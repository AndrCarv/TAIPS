/*
Projecto: FAIP - AFP
Nome: Andre Carvalho
N.º 202200878
Nome: Jose da Silva
N.º 202200892

nota: verificar o editar em idS, historico
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

/*DEFINES*/
#define MAXPASSAGEIROS 4
#define MAXVOOS 100
#define FROTA 10
#define MAXCHAR 80
#define ULTVOO 3



/*Structs mudar para os seus modulos depois de testar tudo*/
typedef struct Passageiro{
    long nif;
    char nome [71];
}Passageiro;

enum Estado{
    Pronto,
    Autorizacao
};

enum Localidades{
    VilaReal,
    Tires,
    Portimao
};

typedef struct Voo{
    int nVoos; //contador para numero de voos
    enum Localidades origem;
    enum Localidades destino;
    char *ultimosVoos[ULTVOO];
}Voo;

typedef struct Aeronave{
    int id;
    int capacidade; //2, 3 ou 4
    int nPassageiros;
    enum Estado state;
    Passageiro passageiros[MAXPASSAGEIROS]; //struct de passageiros
    Voo voos;
}Aeronave;

typedef struct Frota{
    Aeronave * aeronaves;
    int nAeronave;
} Frota;

/*Sub Programas, transferir depois para os modulos*/

//Conjunto void pedir
void pedirInteiro(char frase[], int* num);
void pedirString(char frase[], char* str);
void pedirChar(char frase[], char* ch);
void pedirLong(char frase[], long* numer);
void pedirInteiroEstado(char frase[], enum Estado* num);
void pedirInteiroLocalidade(char frase[], enum Localidades* num);
//
int menu();//este fica na main
//
void mostrarDados(Frota frota, int i); //sub para mostrar os dados, ira ser usado na maiora das opcoes
void opcao1(Frota frota); //mostrar todas as aeronaves
void opcao2(Frota frota); //mostrar aeronave do estado pronto
void opcao3(Frota frota);//mostrar dados se estiver no estado Em Autorizacao
void opcao4(Frota frota);//mostrar dados num certo ID
//opcao 5
void opcao5(Frota* frota, Aeronave* novaAeronave); // inserir os dados do programa para a struc
void opcao5DadosAviao(Frota* frota, Aeronave* novaAeronave);//inserir os dados associado a aeronave
void opcao5DadosPassageiros(Frota* frota, Aeronave* novaAeronave);//inserir os dados associados aos passageiros
void opcao5DadosVoos(Frota* frota, Aeronave* novaAeronave);//inserir os dados associados aos voos
//
void opcao6(Frota* frota);//eliminar a aeronave
//opcao7
int menu1Opcao7(Frota* frota, int i);//Primeiro menu para a opcao editar, se estiver em Autorizacao
int menu2Opcao7(Frota* frota, int i);//Segundo menu para a opcao editar, se estiver em Pronto
void opcao7(Frota* frota);//Editar
void opcao7Autorizacao(Frota* frota, int i, int *op1);//editar se a aeronave estiver no estado Em Autorizacao
void opcao7Pronto(Frota* frota, int i, int *op2);//editar se a aeronave estiver no estado pronto
//
void opcao8(Frota* frota);//realizar o voo
void opcao9(Frota* frota);//reset do estado e clear dos passageiros
char opcao11(int *s); //opcao sair - opcoes vao para o modulo de metodos


int main (){
    setlocale(LC_ALL,"");
    int sair=1; // sair verificador para saber quando terminar o programa

    Frota frota;
    //alocar memória para guardar os aviões dentro da frota
    frota.aeronaves = malloc(sizeof(Aeronave) * FROTA); //criar e alocar a memoria do array


  if (frota.aeronaves == NULL) {
    // Trata o erro de alocação de memória
    return 1;
  } //testar para fazer o historico, apagar se nao for preciso
  frota.nAeronave = 0;
  for (int i = 0; i < frota.nAeronave; i++){
    for (int j = 0; j < ULTVOO; j++) {
        frota.aeronaves[i].voos.ultimosVoos[j] = malloc(sizeof(char) * MAXCHAR);
    }
  }

  while(sair != 0){
    int op=menu();
    switch (op){
      case 1:
        opcao1(frota);
        break;
      case 2:
        opcao2(frota);
        break;
      case 3:
        opcao3(frota);
        break;
        case 4:
        opcao4(frota);
        break;
      case 5:
        {
        Aeronave* novaAeronave = &frota.aeronaves[frota.nAeronave]; //apontador novaAeronave para &frota, usado para inserir novas
        //aeronaves em frota.aeronaves
        if (frota.nAeronave >= FROTA){
          printf("A frota esta cheia de momento, por favor escolher outra opcao ou eliminar um aviao\n");
          continue;
        }
        opcao5(&frota, novaAeronave);
        break;
        }
      case 6:
        opcao6(&frota);
        break;
      case 7:// editar dados
        opcao7(&frota);
        break;
      case 8: //realiza o voo
        opcao8(&frota);
        break;
      case 9: //reset para em Autorizacao
        opcao9(&frota);
        break;
      case 10:
        printf("Em Construcao\n");
        break;
      case 11:{
          char opS; /*variavel so vai ser utilizada para afectar o verificador de sair*/
          do{
            opS=opcao11(&sair);
          }while(opS != 's' && opS != 'S' && opS != 'n' && opS != 'N');
          }
        free(frota.aeronaves);// temporario, para ir contra um erro de comp
        break;
      default:
        printf("Inseriu uma opcao invalida\n");
        break;
      //ver como inserir os resultados no hitorico deume sempre erro
    }
  }
  return 0;
}

int menu(){//menu principal
    int op;
    //opçoes placeholder para saber o que preciso de fazer, depois mudar as opcoes e meter elas em comentario em comentario
      printf("\n");
      puts("1. Listar aeronaves e detalhes (por ordem descrescente de numero de voos");
      puts("2. Listar aeronaves no estado pronto e detalhes (total e por localizacao)");
      puts("3. Listar aeronaves a aguardar autorizacao e detalhes (total e por localizacao)");
      puts("4. Consultar aeronaves especifica mostrando respectivos detalhes (por id)");
      puts("5. Adicionar aeronave a frota (Indicando os respectivos detalhes)");
      puts("6. Eliminar aeronave da frota (apenas possivel se a lista de passageiros estiver vazia e se estiver no estado pronto");
      puts("7. Editar aeronave  (apenas sera possivel editar a capacidade da aeronave, respeitando os limites, \ne reiniciar o numero de voos efetuados. Caso a aeronave esteja a aguardar autorizacao, sera \napenas possivel editar/adicionar/remover os passageiros e editar o destino);");
      puts("8. Autorizar voo (por id da aeronave)");
      puts("9. Cancelar voo (por id da aeronave");
      puts("10. Gravar listagem das aeronaves para ficheiro texto (com todos os detalhes)");
      puts("11. Sair");
      printf("Insira a opcao que deseja: ");
      scanf("%d",&op);
      fflush(stdin);
      printf("\n");
      return op;
}

int menu1Opcao7(Frota* frota, int i){//se detectar a aeronave como "Em Autorizaçao", ira correr este menu
  int op1;
  printf("Editar a aeronave ID: %d em Autorizacao so pode alterar dados dos passageiros e editar o destino\n",frota->aeronaves[i].id);
  puts("1. Adicionar passageiros");//vai realizar o case para adicionar passageiros
  puts("2. Remover passageiros");//vai realizar o case para remover passageiros
  puts("3. Editar o destino");//vai realizar o case para editar o destino, tera de ser diferente que a origem
  puts("Insira a opcao que desejar");//
  scanf("%d", &op1);
  fflush(stdin);
  return op1;
}

int menu2Opcao7(Frota* frota, int i){//se detectar a aeronave como "Pronto", ira correr este menu
  int op2;
  printf("Editar a aeronave ID: %d em Autorizacao so pode alterar dados dos passageiros e editar o destino\n",frota->aeronaves[i].id);
  puts("1. Editar a capacidade da aeronave (2/3/4)");//vai realizar o case para modificar a capacidade da nave, entre 2 ou 4, para meter mais ou menos do que tem actualmente
  puts("2. Reiniciar os voos");//vai realizar o case para reniciar o numero de voos
  puts("Insira a opcao que desejar");
  scanf("%d", &op2);
  fflush(stdin);
  return op2;
}


void mostrarDados(Frota frota, int i){
  printf("**********************\n"); // separador para o dados das aeronaves n ficarem muito juntos
  printf("Aeronave ID: %d | Capacidade: %d/%d | Estado: ",frota.aeronaves[i].id, frota.aeronaves[i].nPassageiros, frota.aeronaves[i].capacidade);//mostrar os dados associados a aeronave
  switch (frota.aeronaves[i].state){//switch para mostrar se a aeronave se encontra em estado "Pronto" ou "Em Autorizaçao"
    case Pronto:
      printf("Pronto\n");
      break;
    case Autorizacao:
      printf("Em autorizacao\n");
      break;
    }
    puts("**Passageiros**");//ira mostrar os dados associados aos passageiros
    for (int j=0;j<frota.aeronaves[i].nPassageiros;j++){/* ira verificar a array dos passageiros que esta
      dentro da struc aronave que esta guardado na array frota o ciclo da array da frota
      sendo o i e o array dos passageiros sendo o j, assim na aeronave 1 ira verificar a array de
      passageiro J usando a capacidade como maximo*/
      printf("Nome: %s \nNIF: %ld \n", frota.aeronaves[i].passageiros[j].nome, frota.aeronaves[i].passageiros[j].nif);
    }
    //localidade - fazer em switch e nao if, para ser mais conciso e facil para o programa na altura
    //da execuçao, como nao tem muitas condiçoes
    printf("Origem - Destino\n");
    switch(frota.aeronaves[i].voos.origem){ // dois switches para mostrar os enums
      case VilaReal:
        printf("Vila Real");
        break;
      case Tires:
        printf("Tires");
        break;
      case Portimao:
        printf("Portimao");
        break;
    }
    printf(" - "); //output Origem: xxx - Destino: yyy "\n"
        switch(frota.aeronaves[i].voos.destino){
          case VilaReal:
            printf("Vila Real\n");
            break;
          case Tires:
            printf("Tires\n");
            break;
          case Portimao:
            printf("Portimao\n");
            break;
        }/*
        printf("**Historico**\n");
        for (int j = 0; j < ULTVOO; j++){
          printf("%s\n", frota.aeronaves[i].voos.ultimosVoos);
        }*/
        printf("Numero de voos: %d \n", frota.aeronaves[i].voos.nVoos); //mostrar o numero de voos
}

void opcao1(Frota frota){
  if (frota.nAeronave != 0){//if que ira verificar se existe aeronaves na frota(nAeronaves != 0)
  //for que ira correr todas as aeronaves existentes na altura e ira correr o subprg mostrarDados() para mostrar os dados todos da aeronave
    puts("**Dados da frota**");
    for (int i=0;i < frota.nAeronave;i++){
      mostrarDados(frota, i);
    }
  }else{
    puts("**Nao ha avioes**");
  }
}

void opcao2(Frota frota){
  if (frota.nAeronave != 0){//if que ira verificar se existe aeronaves na frota(nAeronaves != 0)
  //existe um ciclo para verificar nas aeronaves existentes se existe alguma com o estado em "Pronto" e ira mostrar no ecra sempre que a detectar
    puts("**Dados da frota**");
    for (int i = 0; i < frota.nAeronave; i++){
      if (frota.aeronaves[i].state == Pronto){
        mostrarDados(frota, i);
      }
    }
  }else{
    puts("**Nao ha avioes**");
  }
}

void opcao3(Frota frota){
  if (frota.nAeronave != 0){//if que ira verificar se existe aeronaves na frota(nAeronaves != 0)
    //ciclo para correr as aeronaves existentes autualmente, e mostrar no ecra se detetar alguma no estado "Em Autorizaçao"
    puts("**Dados da frota**");
    for (int i = 0; i < frota.nAeronave; i++){
      if (frota.aeronaves[i].state == Autorizacao)
      {
        mostrarDados(frota, i);
      }
    }
  }else{
    puts("**Nao ha avioes**");
  }
}

void opcao4(Frota frota){
  if (frota.nAeronave != 0){//verificar se existe aeronaves, se existir entra no if
    int id;
    int idVe = 0;
    pedirInteiro("Qual o ID da aeronave que quer verificar?", &id); //pedir e guardar um id que sera libertado apos este subprgr ter sido corrido
    for (int i = 0; i < frota.nAeronave; i++){ //um ciclo para correr as aeronaves ja existentes e um SE para verificar se existe esse ID temporario com os ID's 
    //guardados actualmente nas aeronaves, se for detectado, ira mostrar os dados e o verificador continuara como 0
      if (id == frota.aeronaves[i].id){
        mostrarDados(frota, i);
        idVe = 0;
        break;
      }else{//Senao nao ira mostrar nada e ira meter o verificador como 1
        idVe = 1;
      }
    }
    if (idVe == 1){//Se o verificador for 1 ira mostrar o printf a dizer que nao existe aeronaves com esse ID
      printf("Nao existe aeronave com esse ID\n");
    }
  }else{//Este Senao esta ligado ao Se a verificar se existia aeronaves, e ira dizer que nao existe aeronaves
  puts("**Nao ha avioes**");
  }
}

//subprogr relacionados a opcao 5
void opcao5(Frota* frota, Aeronave* novaAeronave){//opcao 5 principal, foi divido os dados que serao mostrados entre
//dados da aeronave, dados passageiro e dados voo
  opcao5DadosAviao(frota, novaAeronave);
  opcao5DadosPassageiros(frota, novaAeronave);
  opcao5DadosVoos(frota, novaAeronave);
}

void opcao5DadosAviao(Frota* frota, Aeronave* novaAeronave){//dados da aeronave
  int capacidade; // tem de ser 2 a 4
  //pensar em alterar o id para inserido pelo utilizador ou e automatico
  printf("A aeronave vai ser criada com o id %d \n", frota->nAeronave +1); // aeronave no espaço 0 com o id:1
  novaAeronave->id = frota->nAeronave+1; //placeholder por agora, vou trocar isto depois para sempre acrescentar o ID, mesmo depois de apgar a numeracao continua
  do{ //ciclo para perguntar a capacidade, so ira aceitar e terminar o ciclo se a capacidade for entre 2 e MAXPASSAGEIROS (4)
    pedirInteiro("Inserir a capacidade da aeronave (2/3/4)", &capacidade);
    if (capacidade >= 2 || capacidade <= MAXPASSAGEIROS){//validar a capacidade
      novaAeronave->capacidade = capacidade;
    }
  }while (novaAeronave->capacidade < 2 || novaAeronave->capacidade > MAXPASSAGEIROS); // ira repetir sempre que inserir valores diff a capacidade disponivel
  //placeholder
  novaAeronave->state = Autorizacao; // meter em Autorizaçao
  //lista de passageiros
  while(1){ //ciclo que ira pedir o numero de passageiros e so ira terminar o ciclo 
    printf("Insira o numero de passageiros\n");
    scanf("%d", &novaAeronave->nPassageiros);
    fflush(stdin);
    if (novaAeronave->nPassageiros > 0 && novaAeronave->nPassageiros <= capacidade){//SE o nPassageiros for entre 0 e a capacidade da aeronave inserida
      printf("Vai ser aceite %d passageiro, se quiser alterar o numero, por favor usar a opcao editar\n", novaAeronave->nPassageiros);
      break;
    }else{
      printf("O numero de passageiros tem de ser entre 1 e %d capacidade do aviao\n", novaAeronave->capacidade); //Senao mostra uma mensagem de erro a dizer para inserir os valores entre 1 e a capacidade
    }
  }
}

void opcao5DadosPassageiros(Frota* frota, Aeronave* novaAeronave){//dados de passageiros
  long nif; //nif que ira correr neste sub para depois se comparar aseguir
  puts("Dados do passageiro");
  for (int i = 0; i<novaAeronave->nPassageiros; i++){
    pedirLong("Inserir o NIF do passageiro, inserir so digitos: ", &nif);
    int nifExistente = 0; // var verificador NIF
    for (int j = 0; j < i; j++) {
      if (novaAeronave->passageiros[j].nif == nif) { // se detectar se o nif ja existe
      //muda o verificador para 1
        nifExistente = 1;
        break;
      }
    } // fim do for para verificar o NIF
    if (nifExistente == 1){
      puts("O NIF inserido ja existe por outro passageiro, neste voo");
      i--; // se detetar que o NIF ja existe volta um espaço no array para tras
    }else{
      novaAeronave->passageiros[i].nif = nif; // else se for diferente, ira gravar o nif na struc
      pedirString("Insira o nome do passageiro: ", novaAeronave->passageiros[i].nome);
    }
  } // fim do ciclo
}

void opcao5DadosVoos(Frota* frota, Aeronave* novaAeronave){//dados de voos
  //localidade atual e destino, tem de ser dif
  while(1){ //ciclo a terminar quando inserir (1/2/3)
  //Se para dar continue e pedir outra vez se inserir na origem e destino valores diferentes dos correctos
    pedirInteiroLocalidade("Insira a origem (0 - Vila Real. 1 - Tires . 2 - Portimao: ", &novaAeronave->voos.origem);
    if (novaAeronave->voos.origem < 0 || novaAeronave->voos.origem >2){
      puts("Origem Invalida");
      continue;
    }
    
    pedirInteiroLocalidade("Insira a destino (0 - Vila Real. 1 - Tires . 2 - Portimao: ", &novaAeronave->voos.destino);
    if (novaAeronave->voos.destino < 0 || novaAeronave->voos.destino > 2){
      puts("Destino Invalido");
      continue;
    }
    if (novaAeronave->voos.destino != novaAeronave->voos.origem){ //Se e senao para comparar de o destino != da origem
      break;
    }else{
      puts("A origem e o destino nao podem ser iguais");
    }
  } // Inserir como adicionar a origem e destino no array
/*
  for (int i = ULTVOO - 1; i > 0; i--){
    strcpy(novaAeronave->voos.ultimosVoos[0], novaAeronave->voos.ultimosVoos[i]);
  }

  // Switch case para guardar dentro do array historico a origem e o destino 
  switch(novaAeronave->voos.origem){
    case VilaReal:
      strcpy(novaAeronave->voos.ultimosVoos[0], "Vila Real");
      break;
    case Tires:
      strcpy(novaAeronave->voos.ultimosVoos[0], "Tires");
      break;
    case Portimao:
      strcpy(novaAeronave->voos.ultimosVoos[0], "Portimao");
      break;
  }
  strcat(novaAeronave->voos.ultimosVoos[0], " - ");
  switch(novaAeronave->voos.destino){
    case VilaReal:
      strcat(novaAeronave->voos.ultimosVoos[0], "Vila Real");
      break;
    case Tires:
      strcat(novaAeronave->voos.ultimosVoos[0], "Tires");
      break;
    case Portimao:
      strcat(novaAeronave->voos.ultimosVoos[0], "Portimao");
      break;
  }*/
  novaAeronave->voos.nVoos = 0;
  (frota->nAeronave)++; 
}

//
void opcao6(Frota* frota){
  if (frota->nAeronave != 0){//verificar se existe aeronaves, se existir entra no if
    int id, i;
    // Pedir o ID da aeronave a ser eliminada
    pedirInteiro("Qual o ID da aeronave que quer eliminar?", &id);
    // Procurar a aeronave com o ID fornecido
    for (i = 0; i < frota->nAeronave; i++){
      if (id == frota->aeronaves[i].id){
        // Verificar se a lista de passageiros está vazia e se o estado da aeronave é "Pronto"
        if (frota->aeronaves[i].nPassageiros == 0 && frota->aeronaves[i].state == Pronto){
          if ( frota->nAeronave == 1){ //Se houver so uma aeronave, ira entrar neste SE e ira mudar o valor de nAeronave de 1 para 0
            frota->nAeronave = 0;
          }else{//Senao
            // Decrementar o contador de aeronaves
            frota->nAeronave--;
          // Deslocar as aeronaves seguintes para trás
            for (int j = i; j < frota->nAeronave; j++){
              frota->aeronaves[j] = frota->aeronaves[j+1];
              frota->aeronaves[j].id--;
            }
          }
        }else{//Senao associao ao SE que faz a comparaçao do ID
          printf("Impossivel eliminar a Aeronave com o id %d, por favor verifique se ela esta em estado Pronto e a lista de passageiros esta vazia.\n", id);
        }
        break; // Sair do loop
      }
    }
  }else{//Senao associado ao primeiro SE que serve para verificar se existe aeronaves
    puts("**Nao ha avioes**\n");
  }
}

//subprogr relacionados a opcao 7
void opcao7(Frota* frota){
  if (frota->nAeronave != 0){//verificar se existe aeronaves, se existir entra no if
    int id;
      puts("**Editar ");
      puts("Se a aeronave estiver no estado em Autorizacao so podera alterar a capacidade e o numero de voos");
      puts("Se a aeronave estiver no estado Pronto, podera alterar os dados relacionados ao passageiros e o destino do voo");
      pedirInteiro("Qual o ID da aeronave que quer editar?", &id);
      for (int i = (id-1); i < frota->nAeronave; i++){ //idVer diz que quer-se alterar o dado do aviao
          //por exemplo, do id 2, como esta guardado no espaço do array em 01,
          //fazendo id-1, o for começa no espaço onde o id deve estar situado no
        if (id == frota->aeronaves[i].id && frota->aeronaves[i].state == Autorizacao){//SE utilizado para comparar se o ID que recebo
        //ja existe na frota e tambem se a aeronave com esse ID se encontra no estado "Em Autorizacao"
          while(1){ //este ciclo ira mostrar o menu associado as aeronaves em autorizacao
            int op1=menu1Opcao7(frota, i); //ira correr o subprg do menu1 da opcao 7 e ira returnar o valor, que sera guardado como int op1
            opcao7Autorizacao(frota, i, &op1);//vai usar a op1 neste subprg, tambem manda o i para dentro para poder usar o i para identificar a aeronave a editar
            break;
          }
        }else if (id == frota->aeronaves[i].id && frota->aeronaves[i].state == Pronto){//SE utilizado para comparar se o ID que recebo
        //ja existe na frota e tambem se a aeronave com esse ID se encontra no estado "Pronto"
          while(1){
            int op2=menu2Opcao7(frota, i);//ira correr o subprg do menu2 da opcao 7 e ira returnar o valor, que sera guardado como int op2
            opcao7Pronto(frota, i, &op2);//vai usar a op1 neste subprg, tambem manda o i para dentro para poder usar o i para identificar a aeronave a editar
            break;
          }
        }else if (frota->aeronaves[i].id != id){//esta a dar erro se meter algo que n seja o 1 mas faz os outros if a mesma
        //se nao for detetado o ID
        puts("Nao foi detectado nenhuma aeronave com esse ID ");
        }
    }
  }else{//Senao associado a verificaçao se existe aeronaves
    puts("Nao ha avioes");
  }
}

void opcao7Autorizacao(Frota* frota, int i, int *op1){//opcao realizada se for detectado aeronaves Em Autorizacao
  switch (*op1){
    case 1:
    {
      long nif;
      int novoPassageiros, novoLimite=0;
      if (frota->aeronaves[i].nPassageiros >= frota->aeronaves[i].capacidade){//Se nPassageiros for maior ou igual a capacidade
      //ira mostrar a mensagem e dará break desde switch 
        puts("A aeronave esta na capacidade maxima de passageiros");
        break;
      }
      while(1){ //se o prgr nao sair na comparaçao anterior ira inicializar este ciclo
      //neste ciclo será pedido ao utilizador quantos passageiros ele quer adicionar a uma aeronave ja existente
        printf("Capacidade atual da aeronave ID:%d %d/%d\n", frota->aeronaves[i].id,frota->aeronaves[i].nPassageiros,frota->aeronaves[i].capacidade);
        printf("Ao editar ira adicionar passageiros ao que a aeronave ja tem, quanto passageiros quer inserir?\n");
        scanf("%d", &novoPassageiros);
        fflush(stdin);
        if (novoPassageiros > 0 && novoPassageiros + frota->aeronaves[i].nPassageiros <= frota->aeronaves[i].capacidade){//este SE vai verificar se o novo valor de nPassageiros
        //se encontra entre 0 e capacidade, se sim ira mostrar a mensager a dizer quantos passageiros foram aceites e da o break para sair deste ciclo de repeticao e continuar
          printf("Apos editar sera aceite neste voo +%d passageiros\n", novoPassageiros);
          novoLimite = novoPassageiros + frota->aeronaves[i].nPassageiros;
          //novoLimite vai ser usado temporariamente para verificar que o numero adicionado sumado com o que ja existe nao passa da capacidade 
          break;
        }else{//Senao ira mostrar a mensagem que o numero de passageiros tem de ser entre 1 e a capacidade atual da aeronave
          printf("Erro a inserir o numero de passageiros\n");
        }
      }//ira pedir um nif como que sera guardado como long
      for (int j = 0; j < frota->aeronaves[i].nPassageiros; j++){
        for (int k = frota->aeronaves[i].nPassageiros; k < novoLimite; k++) {
          pedirLong("Inserir o NIF do passageiro, se inserir letras, serao removidas como nao sao aceites: ", &nif);
          int nifExistente = 0; //declarar um verificador para o nif
          for (int x = 0; x < frota->aeronaves[i].nPassageiros; x++){ //ciclo que ira correr as posicoes dos passageiros na aeronave[i]
            if (frota->aeronaves[i].passageiros->nif == nif){ //se detectar um nif igual ira entrar neste Se e mudar o valor do verificador para 1
            puts("O NIF inserido ja existe neste voo");
            break;
          } else {//Senao ira guardar o nif e o nome novo dentro do espaço k e aumentar o nPassageiro por um
            frota->aeronaves[i].passageiros[k].nif = nif;
            pedirString("Insira o nome do passageiro: ", frota->aeronaves[i].passageiros[k].nome);
            (frota->aeronaves[i].nPassageiros)++;
            break;
            }
          }
          //break;
        }
        break;
      }
      break;
    }
    case 2:{
      long nif1; //criar outro var nif, e pedir nif ao utilizador
      pedirLong("Inserir o NIF do passageiro, se inserir letras, serao removidas como nao sao aceites: ", &nif1);
      int indicePassageiro = -1;
      int nifExistente = 0;
      for (int j = 0; j < frota->aeronaves[i].nPassageiros; j++) {//ciclo for para verificar em nPassageiros se existe esse nif
      //se existir ira trocar o verificador para 1 e ira guardar o j para o indice de passageiro
        if (frota->aeronaves[i].passageiros[j].nif == nif1) {
          nifExistente = 1;
          indicePassageiro = j;
          break;
        }
      }
      // Se o NIF não existir, mostrar mensagem ao utilizador
      if (nifExistente == 0) {
        puts("O NIF inserido nao corresponde a nenhum passageiro neste voo");
      } else {
      // Caso contrário, eliminar o passageiro (move todos os passageiros seguintes uma posição para trás)
        for (int j = indicePassageiro; j < frota->aeronaves[i].nPassageiros - 1; j++) {
          frota->aeronaves[i].passageiros[j] = frota->aeronaves[i].passageiros[j + 1];
        }
        (frota->aeronaves[i].nPassageiros)--; // decrementar o número de passageiros
        break;
      }
      break;
    }
  case 3:
    while(1){//ciclo infinito que ira terminar so se for inserido um valor valido
      int temp; //var temporaria
      pedirInteiroLocalidade("Insira a destino (0 - Vila Real. 1 - Tires . 2 - Portimao: ", (enum Localidades*) &temp);//guardar o resultado da enum em temp
      if (temp < 0 || temp > 2){//Se for inserido um valor invalido, ira mostrar esta mensageme da continue
        puts("Destino Invalido");
        continue;
      }
      if (temp != (char) frota->aeronaves[i].voos.destino && (temp != (char) frota->aeronaves[i].voos.origem)){//este SE ira verificar se o temp com o novo enum e diferente que a origem e destino ja existente 
      //na base de dados, se sim ira meter o valor do temp como o novo destino, senao mostra a mensagem de erro
        frota->aeronaves[i].voos.destino = temp;
        break;
      }else{
        puts("A origem e o destino nao podem ser iguais");
      }
    }break; 
  default:
    puts("Opcao invalida");
    break;
  }
}
void opcao7Pronto(Frota* frota, int i, int *op2){ //opcao que sera realizado se a aeronave de um certo ID estiver no estado "Pronto"
  switch (*op2){
    case 1:{//case 1 com o objt de definiar uma nova capacidade para a aeronave
      while(1){
        int capacidade;
        pedirInteiro("Inserir nova capacidade", &capacidade);//pede a nova capacidade
        if (capacidade < 2 || capacidade > MAXPASSAGEIROS){//ira verificar se a capacidade esta fora dos limite, entre 2 e o MAXPASSAGERISO (4)
          puts("Inseriu um valor invalido para a capacidade, tem de ser entre 2 e 4");
          break;
        }
        printf("%d",frota->aeronaves[i].nPassageiros);
        if (capacidade != frota->aeronaves[i].capacidade && capacidade > frota->aeronaves[i].capacidade){//Se a nova capacidade for maior que a capacidade existente
        //ira transferir o valor da nova capacidade para aeronaves.capacidade -> apagar o !=
          frota->aeronaves[i].capacidade = capacidade;
          break;
        }else if (capacidade != frota->aeronaves[i].capacidade && capacidade < frota->aeronaves[i].capacidade){//Senao Se a nova capacidade for menor que a capacidade actual da
        //aeronave, a capacidade ira receber o valor da capacidade nova
          frota->aeronaves[i].capacidade = capacidade;
          break;
        }else{//Senao mostra esta mensagem de erro
          puts("A nova capacidade tem de ser diferente que a original");
          break;
        }
      }
      break;
    }
    case 2: //este case ira fazer um reset ao nVoos
      frota->aeronaves[i].voos.nVoos = 0;
      break;
    default:
      puts("Opcao invalida");
      break;
  }
}

//
void opcao8(Frota* frota){//estas opcao ira verificar se a opcao tem alguma aeronave, Se tiver ira pedir um id
//e com esse id ira verificar se existe alguma aeronave com esse ID na frota e se o estado esta em "Autorizacao" para iniciar o voo
  int id;
  if (frota->nAeronave != 0){
    pedirInteiro("Qual o ID da aeronave a realizar o voo?", &id);//pede o id como int
    for (int i = (id-1); i < frota->nAeronave; i++){//ciclo na frota para verificar se existe o id e esta no estado necessario para funcionar
      if (id == frota->aeronaves[i].id && frota->aeronaves[i].state == Autorizacao){
       // verificacao de numero de voos e origem - destino, se o numero estive entre 0 a 99 ira realizar o voo
       //vai passar o destino como a nova origem, acrescentar ao nVoos+1, mudar o estado para Pronto e ira limpar a lista de passageiros
        if (frota->aeronaves[i].voos.nVoos <=99 && frota->aeronaves[i].voos.origem != frota->aeronaves[i].voos.destino && frota->aeronaves[i].nPassageiros > 0){
          puts("Voo realizado, a aeronave agora tera como origem o destino do voo actual, para realizar outro voo por favor mudar o destino");
          frota->aeronaves[i].voos.origem = frota->aeronaves[i].voos.destino;//meter o destino como a nova origem
          frota->aeronaves[i].voos.nVoos++;//Adicionar +1 aos voos
          frota->aeronaves[i].state = Pronto;//Meter o estado em Pronto
          frota->aeronaves[i].nPassageiros = 0;//reset de nPassageiros
            for (int j=0; j < MAXPASSAGEIROS; j++){
                frota->aeronaves[i].passageiros[j].nif = 0;//zerar o nif
                strcpy(frota->aeronaves[i].passageiros[j].nome, "");//deixar a string em branco
            }
        break;
        }else if ((frota->aeronaves[i].voos.nVoos <=99 && frota->aeronaves[i].voos.origem == frota->aeronaves[i].voos.destino) || frota->aeronaves[i].nPassageiros <= 0){
          //Senao ira mostrar esta mensagem de erro
          puts("Erro a realizar o voo, verificar o destino e a lista de passageiros, voo so ira realizar se houver passageiros e o destino for diferente que a origem");
        }else if (frota->aeronaves[i].voos.nVoos == 100){
          //Se estiver com 100 voos ira mostrar uma mensagem de erro a dizer que a aeronvae ja chegou ao limite de voos
          puts("A aeronave ja realizou os 100 voos autorizados, terá de editar ou remover esta aeronave da frota");
        }
      }else{//Senao ligado ao SE de verif de ID, ira mostrar este erro se nao encontrar um ID ou se nao estiver em Autorizacao
        printf("ID invalido ou a aeronave nao se encontra em Autorizacao\n");
        break;
      }
    }
  }else{
    puts("**Nao ha avioes**");
  }
}

void opcao9(Frota* frota){//opcao para "cancelar o voo", dar reset a aeronave para poder realizar outro voo
  int id;
  if (frota->nAeronave != 0){
    pedirInteiro("Qual o ID da aeronave que quer dar reset ao estado?", &id);
    for (int i = (id-1); i < frota->nAeronave; i++){
      if (id == frota->aeronaves[i].id && frota->aeronaves[i].state == Pronto){//se no ciclo encontrar o ID e estiver no estado Pronto
        puts("Reset ao estado da aeronave, pode realizar o voo outra vez apos mudar o destino em editar");
        frota->aeronaves[i].state = Autorizacao;//troca o estado para autorizacao
        break;
      }else{
        puts("Erro a dar reset a aeronave, ou o ID nao existe ou a aeronave ja se encontra em Autorizacao");
      }
    }
  }else{
    puts("**Nao ha avioes**");
  }
}

char opcao11(int *s){
    char opSair;
    while (1){ //loop infinito ate inserir s/S ou n/N
    printf("Deseja sair [s/n]: ");
    scanf("%c",&opSair);
    fflush(stdin);
    printf("\n");
    if (opSair=='s'||opSair=='S'){
        *s=0;
        break;
    }else if (opSair=='n'||opSair=='N')
        break;
    else
        printf("Inseriu uma opcao errada\n");
    }
    return opSair;
}

void pedirLong(char mensagem[], long* valor){
  printf("%s", mensagem); //mostra a mensagem
  char input[10];
  fgets(input, 10, stdin); //guarda no input com ate tamanho 9 + \n
  char *p = strtok(input, "\n"); //strtok esta a ser usado para apontar e remover o ('\n') do final da string lida com a função fgets
  if (strlen(input) < 9 || (strspn(input, "0123456789") != strlen(input) && (input[strlen(input)-1] != '\n'))) { //strspn esta a verificar o que esta guardado em p e ver se sao digitos entre 0 a 9
    printf("Apenas sera aceite 9 digitos.\n");
    pedirLong(mensagem, valor);
    return;
  }
  *valor = strtol(p, NULL, 10); // biblioteca stdlib, converter de volta para long
  fflush(stdin);
}

void pedirInteiroEstado(char frase[], enum Estado* num){// criado para poder receber o
//pointeiro para a enum Estado
    puts(frase);
    int valor;
    //printf("%s", frase);
    scanf("%d", &valor);
    fflush(stdin);
    *num = (enum Estado)valor;
}

void pedirInteiroLocalidade(char frase[], enum Localidades* num){ // criado para poder receber o
//pointeiro para a enum Localidades
    puts(frase);
    int valor;
    //printf("%s", frase);
    scanf("%d", &valor);
    fflush(stdin);
    *num = (enum Localidades)valor;
}

void pedirInteiro(char frase[], int* num){
    puts(frase);
    //printf("%s", frase);
    scanf("%d", num);
    fflush(stdin);
}

//este tambem pertence ao string, para verificacao das letras
int veriString(char* str){
  for (int i = 0; i < (str[i] != '\0'); i++){
    if (!isalpha(str[i])){
      return 0;
    }
  }
  return 1;
}
void pedirString(char frase[], char* str){
  char input[MAXCHAR];
  int sair = 0;
  while (sair == 0){
    puts(frase); //frase da pergunta
    fgets(input, MAXCHAR, stdin); //fgets guarda o texto inserido no teclado e a tecla de enter (\n)
    for(int i = 0; input[i] != '\0'; i++){ //ciclo para remover o \n
      if(input[i] == '\n'){
        input[i] = '\0';
        break;
      }
    }
    if (veriString(input)){ //verificar se e so letras
      strcpy(str, input); //vai copiar a string ja verificada para o str
      sair = 1;
    }else{ //se invalido, ou se estiver algo que n seja letra ira fazer o else
      printf("Erro, foi digitado caracteres invalidos no espaço do nome\n");
    }
  }
}

void pedirChar(char frase[], char* ch){
    puts(frase);
    scanf("%c", ch);
    fflush(stdin);
}

