#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#define LISTEN_PORT 2908
#define MAX_CONNECTION 30
#define BUF_SIZE 200

void *server_thread(void *param) {
    int clnt_sock = *(int *) param;
    char *buf = (char *) malloc(BUF_SIZE * sizeof(char));
    strcpy(buf, "hello");
    while (1) {
        write(clnt_sock, buf, strlen(buf)); // 写的时候时字符串后面的空字节也会被写出
        sleep(1);
    }
    close(clnt_sock);


    free(buf);
    return NULL;
}


int main() {

    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(LISTEN_PORT);
    bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(serv_sock, MAX_CONNECTION);

    while (1) {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
        pthread_t pid;
        pthread_create(&pid, NULL, server_thread, (void *) &clnt_sock);
    }
}

#pragma clang diagnostic pop