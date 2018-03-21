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
    int Meusocket,slen;
    struct sockaddr_in remoto;
    int len = sizeof(remoto);
    char buffer[4096];

    if ((Meusocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    printf("Sou o cliente\n");


    remoto.sin_family = AF_INET;
    remoto.sin_port = htons(MINHAPORTA);
    remoto.sin_addr.s_addr = inet_addr("127.0.0.1"); /* coloca IP automaticamente */
    //bzero(&(meu_endereco.sin_zero), 8); // diferent       /* Zera o resto da estrutura */
    memset(remoto.sin_zero,0x0,8);



        if ((connect(Meusocket, (struct sockaddr *)&remoto,len)) < 0)//esta diferente
        {
            perror("connect");

        }


            while(1)
                {
                memset(buffer,0x0,4096);

               if(slen=recv(Meusocket,buffer,4096,0)>0){
                buffer[strlen(buffer)-1]='\0';

                printf("msg recebida: %s\n",buffer);

               }

               memset(buffer,0x0,4096);
               fgets(buffer,4096,stdin);
               send(Meusocket,buffer,strlen(buffer),0);

                break;
            }


        close(Meusocket);
        return 0;
    }

