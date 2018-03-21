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

main()
{
    int Meusocket,client,slen;
    struct sockaddr_in local;
    struct sockaddr_in remoto;
    int len = sizeof(remoto);
    int tamanho;
    char buffer[4096];

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

    if (bind(Meusocket, (struct sockaddr *)&local, sizeof(local))== -1) //diferente
    {
        perror("bind");
        exit(1);
    }

    if (listen(Meusocket, 1) < 0)
    {
        perror("listen");
        exit(1);
    }




        if ((client = accept(Meusocket, (struct sockaddr *)&remoto,&len)) < 0)
        {
            perror("accept");

        }

        strcpy(buffer,"bem vindo\n\0");
        if(send(client,buffer,strlen(buffer),0))
        {
            printf("aguardando resposta do cliente\n");
            while(1){
                memset(buffer,0x0,4096);
               if(slen=recv(client,buffer,4096,0)>0){
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


