#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char nome[40];
    char endereco[40];
    char telefone_residesial[12];
    char telefone_celular[12];
    char data_nascimento[10];
} Contato;

Contato lista_contato[1000];
int contador = 0;

int get_size(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

void carregar()
{
    FILE * arquivo = fopen("ListaDeContatos.txt","r");
        if(get_size("ListaDeContatos.txt") == 0)
        {
            // printf("O arquivo esta vazio.\n");
            return;
        }
        else
        {   
    
            // printf("O arquivo nao esta vazio.\n");6

            char linha[500];
            fgets(linha,500,arquivo);
            // printf("Linha %s",linha);
            contador = atoi(linha);
            //lista_contato[contador];
            // lista_contato = malloc(sizeof(Contato)*contador);
            // printf(" Cont: %d\n",contador);



            char delim[] = ";";
            
            int pos = 0;
            int cont = 1;
            while (fscanf(arquivo,"%s",linha) != EOF)
            {
                // fgets(linha,500,arquivo);
                // printf("Contador: %s\n",linha);
                char *ptr = strtok(linha, delim);
                while(ptr != NULL)
                {

                    if(cont == 1){
                        strcpy(lista_contato[pos].nome,ptr);
                        cont++;

                    } else if(cont == 2){
                        strcpy(lista_contato[pos].endereco,ptr);
                        cont++;
                    } else if(cont == 3){
                        strcpy(lista_contato[pos].telefone_residesial,ptr);
                        cont++;
                    } else if(cont == 4){
                        strcpy(lista_contato[pos].telefone_celular,ptr);
                        cont++;
                    } else if(cont == 5){
                        strcpy(lista_contato[pos].data_nascimento,ptr);    
                    }
                    
                    // printf("'%s'\n", ptr);
                    ptr = strtok(NULL, delim);         
                    
                }
                cont = 1;

                // printf("Olha: %s\n",lista_contato[pos].nome);
                // printf("Olha: %s\n",lista_contato[pos].endereco);
                // printf("Olha: %s\n",lista_contato[pos].telefone_residesial);
                // printf("Olha: %s\n",lista_contato[pos].telefone_celular);
                // printf("Olha: %s\n",lista_contato[pos].data_nascimento);
        
                pos++;

            }
        }


    fclose(arquivo);

}

void listar()
{
    carregar();
    for (int i = 0; i < contador; i++)
    {
        printf("Contato %d ", i + 1);
        printf("%s",lista_contato[i].nome);
        printf("; %s",lista_contato[i].endereco);
        printf("; %s",lista_contato[i].telefone_residesial);
        printf("; %s",lista_contato[i].telefone_celular);
        printf("; %s;\n",lista_contato[i].data_nascimento);
    }
    printf("\n");

}


void escrever(){

    // lista_contato = realloc(lista_contato,sizeof(Contato)*(contador+2));
    FILE * arquivo = fopen("ListaDeContatos.txt","w");
    //escrever contador
    fprintf(arquivo,"%d\n",contador);
    for(int i = 0; i < contador;i++) {
        fprintf(arquivo,"%s",lista_contato[i].nome);
        fprintf(arquivo,";%s",lista_contato[i].endereco);
        fprintf(arquivo,";%s",lista_contato[i].telefone_residesial);
        fprintf(arquivo,";%s",lista_contato[i].telefone_celular);
        fprintf(arquivo,";%s;\n",lista_contato[i].data_nascimento);
    }
    // carregar();
    //escrever resto
    fclose(arquivo);
}


void adicionar()
{   
    carregar();
    Contato contato;
    char lixo;
    // char resposta;
    FILE *arquivo = fopen("./ListaDeContatos.txt","a");
    printf("Digite o nome do contato:\n");
    scanf("%s",contato.nome);
    //fprintf(arquivo,"%s;",contato.nome);
    printf("Digite o endereco do contato:\n");
    scanf("%s",contato.endereco);
    //fprintf(arquivo,"%s;",contato.endereco);
    scanf("%c",&lixo);
    printf("O contato possui telefone residencial S/N:\n");
    char resposta1;
    scanf("%c",&resposta1);
    // printf("%c",resposta1);
    if(resposta1 == 'S' || resposta1 == 's'){
        printf("Digite o telefone residencial do contato:\n");   
        scanf("%s",contato.telefone_residesial);
        // fprintf(arquivo,"%s;",contato.telefone_residesial); 
    } else {
       strcpy(contato.telefone_residesial,"---");
    }
    scanf("%c",&lixo);
    printf("O contato possui telefone celular S/N:\n");
    char resposta2;
    scanf("%c",&resposta2);
    if(resposta2 == 'S' || resposta2 == 's'){
        printf("Digite o telefone celular do contato:\n"); 
        scanf("%s",contato.telefone_celular);
        // fprintf(arquivo,"%s;",contato.telefone_celular);  
    } else {
        strcpy(contato.telefone_celular,"---");
    }
    printf("Digite a data de nascimento do contato:\n");
    scanf("%s",contato.data_nascimento);
    // fprintf(arquivo,"%s;",contato.data_nascimento);
    lista_contato[contador] = contato;
   
    // fprintf(arquivo,"\n");
    printf("Contato Adcionado\n");
    contador++;
    escrever();
    fclose(arquivo);
    
}

void remover()
{   
    carregar();
    char nome[30];
    printf("Digite o nome do contato para ser removido:");
    scanf("%s",nome);
    int pos = 0;
    Contato c[contador];     

    for (int i = 0; i < contador; i++)
    {
        if(!strcmp(nome,lista_contato[i].nome)==0){
            c[pos++] = lista_contato[i];
        }
    }

    for (int i = 0; i < contador-1; i++)
    {
        lista_contato[i] = c[i];
    }
    contador--;
   
    
    
           
  escrever();
}

void pesquisarNome()
{
    carregar();
    char nome[30];
    printf("Digite o nome do contato para ser pequisado:");
    scanf("%s",nome);
    for (int i = 0; i < contador; i++)
    {
        if(strcmp(nome,lista_contato[i].nome)==0){
            printf("%s",lista_contato[i].nome);
            printf("; %s",lista_contato[i].endereco);
            printf("; %s",lista_contato[i].telefone_residesial);
            printf("; %s",lista_contato[i].telefone_celular);
            printf("; %s;\nzn",lista_contato[i].data_nascimento);
        }
    }
    

}

void alterarContato()
{
    carregar();
    char nome[30];
    printf("Digite o nome do contato para ser alterado:");
    scanf("%s",nome); 

    Contato tmp;
    char lixo;   

    printf("Digite o novo nome do contato:\n");
    scanf("%s",tmp.nome);
    printf("Digite o novo endereco do contato:\n");
    scanf("%s",tmp.endereco);
    scanf("%c",&lixo);
    printf("O contato possui telefone residencial S/N:\n");
    char resposta1;
    scanf("%c",&resposta1);
    if(resposta1 == 'S' || resposta1 == 's'){
        printf("Digite o novo telefone residencial do contato:\n");   
        scanf("%s",tmp.telefone_residesial);
    } else {
       strcpy(tmp.telefone_residesial,"---");
    }
    scanf("%c",&lixo);
    printf("O contato possui telefone celular S/N:\n");
    char resposta2;
    scanf("%c",&resposta2);
    if(resposta2 == 'S' || resposta2 == 's'){
        printf("Digite o novo telefone celular do contato:\n"); 
        scanf("%s",tmp.telefone_celular);
    } else {
        strcpy(tmp.telefone_celular,"---");
    }
    printf("Digite a nova data de nascimento do contato:\n");
    scanf("%s",tmp.data_nascimento);

    for (int i = 0; i < contador; i++)
    {
        if(strcmp(nome,lista_contato[i].nome)==0){
            lista_contato[i] = tmp;
        }
    }

    escrever();
}

void menu() 
{
    printf("\t1. Adicionar\n"); 
    printf("\t2. Remover\n");
    printf("\t3. Pesquisar pelo nome\n"); // srcsrc conpara duas string ai se for iqual escreve o resto da string maior
    printf("\t4. Alterar\n");
    printf("\t5. Listar\n");
    printf("\t6. Sair\n");
}
int main()
{
    while(1){
        menu();
        int resposta;
        scanf("%d",&resposta);
        if(resposta == 1){
            adicionar();
        }
        else if(resposta == 2){
            remover();
        }
        else if(resposta == 3){
            pesquisarNome();
        }
        else if(resposta == 4){
            alterarContato();
        }
        else if(resposta == 5){
            listar();
        }
        else if(resposta == 6){
          return 0;
        }
    }
}