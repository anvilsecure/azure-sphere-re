#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// Sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "applibs_versions.h"
#include <applibs/log.h>

#include "shell.h"

void error(const char *msg) {
    Log_Debug("Failed: %s - %s (%d)", msg, strerror(errno), errno);
    exit(-1);
}

int main()
{
    Log_Debug("Starting shell spawner.");

    // ignore children 
    signal(SIGCHLD, SIG_IGN);

    int server_fd;
    int reuse;
    struct sockaddr_in addr;

    // create the server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        error("socket");
    }
    // re-use the port
    reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0) {
        error("setsockopt - SO_REUSEADDR");
    }
    // bind to port 4444
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        error("bind");
    }
    // and listen for connections
    if (listen(server_fd, 5) != 0) {
        error("listen");
    }

    Log_Debug("Waiting for connections");

    while (1) {
        socklen_t addr_len = sizeof(addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);
        if (client_fd < 0) {
            error("accept");
        }
        Log_Debug("Accepted connection from: %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

        int pid = fork();
        if (pid == 0) {
            // child process
            // we don't need the server sock
            close(server_fd);

            // dup the client fd into stdin/out/err
            dup2(client_fd, 0);
            dup2(client_fd, 1);
            dup2(client_fd, 2);
            
            run_shell();
        } else if (pid > 0) {
            // we are the server, close the client's fds
            close(client_fd);
        } else {
            error("fork");
        }
    }

    return 0;
}