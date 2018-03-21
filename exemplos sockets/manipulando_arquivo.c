#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define MINHAPORTA 20000    /* Porta que os usuarios irão se conectar*/
#define BACKLOG 10     /* Quantas conexões pendentes serão indexadas */




int main()
{
    int Meusocket,client,slen;
    struct sockaddr_in local;
    struct sockaddr_in remoto;
    int len = sizeof(remoto);
    int tamanho;
    char buffer[4096];
    char bytes,bf[1]; // char tem 8 bits ou sejá um byte

    FILE *origem ,*destino;

    origem = fopen("/home/jpsamarino/Dropbox/REDES/1.pdf", "rb");
            if((fseek(origem, 0, SEEK_END))<0){printf("Arquivo não localizado");}
            int len2 =  ftell(origem);
            printf("Tamanho do arquivo: %d\n", len2);

    rewind (origem);//retorno o cursor para o inicio do arquivo

    destino = fopen( "/home/jpsamarino/Dropbox/REDES/2.pdf", "wb" );



    bytes = fread( bf, sizeof( char ), 1, origem );
    tamanho = 1;
    while( !feof( origem ) )
    {
        fwrite( bf, sizeof( char ), bytes, destino );
        bytes = fread( bf, sizeof( char ), 1, origem );
        tamanho++;
    }
    printf("qt de bytes realmente transferidos: %d\n",tamanho);

    fclose(origem);
    fclose(destino);







    if ((Meusocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    printf("servidor criado com sucesso");


    local.sin_family = AF_INET;
    local.sin_port = htons(MINHAPORTA);
    local.sin_addr.s_addr = INADDR_ANY; /* coloca IP automaticamente */
    //bzero(&(meu_endereco.sin_zero), 8); // diferent       /* Zera o resto da estrutura */
    memset(local.sin_zero,0x0,8);

    if (bind(Meusocket, (struct sockaddr *)&local, sizeof(local))== -1) //função associa porta da maquina a seu socket
    {
        perror("bind");
        exit(1);
    }

    if (listen(Meusocket, 1) < 0) //seta o numero maximo de concçoes
    {
        perror("listen");
        exit(1);
    }




    if ((client = accept(Meusocket, (struct sockaddr *)&remoto,&len)) < 0) // para o processo até alguem se conectar
    {
        perror("accept");

    }


    strcpy(buffer,"bem vindo\n\0");
    if(send(client,buffer,strlen(buffer),0))
    {
        printf("aguardando resposta do cliente\n");
        while(1)
        {
            memset(buffer,0x0,4096);

            if(slen=recv(client,buffer,4096,0)>0)// para o processo até receber a resposta
            {
                buffer[strlen(buffer)-1]='\0';

                printf("msg recebida %s\n",buffer);
                close(client);
                break;
            }
        }
    }

    close(Meusocket);
    return 0;
}


