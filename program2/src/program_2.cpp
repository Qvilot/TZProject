#include "../include/program_2.h"

void handle_client(int client_socket)
{
    char buffer[1024];
    int recvlen;
    while (true)
    {
        recvlen = recv(client_socket, buffer, sizeof(buffer), 0);
        if (recvlen <= 0)
        {
            std::cerr << "Client disconnected or error: " << recvlen << std::endl;
            break;
        }
        buffer[recvlen] = '\0';
        std::string received_data(buffer);
        std::cout << "Received: " << received_data << std::endl;

        if (checkString(received_data))
        {
            std::cout << "Data: " << received_data << std::endl;
        }
        else
        {
            std::cout << "The message does not meet the condition" << std::endl;
        }
    }
    close(client_socket);
}

int main()
{
    int listenfd;
    struct sockaddr_in servaddr;

    int reuse = 1;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        perror("setsockopt");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, 10) == -1)
    {
        perror("listen");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);

    while (true)
    {
        int client_socket = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if (client_socket == -1)
        {
            perror("accept");
            continue;
        }
        std::thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }

    close(listenfd);
    return 0;
}
