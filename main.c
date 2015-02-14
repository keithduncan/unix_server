#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

int main(void) {
  char *server_path = "/tmp/unix_server_listener";

  int listener = socket(PF_UNIX, SOCK_STREAM, 0);
  if (listener == -1) {
    fprintf(stderr, "server socket() %d\n", errno);
    exit(1);
  }

  unlink(server_path);

  struct sockaddr_un address = {
    .sun_family = AF_UNIX,
  };
  strcpy(address.sun_path, server_path);
  address.sun_len = SUN_LEN(&address);

  int err = bind(listener, (const struct sockaddr *)&address, address.sun_len);
  if (err != 0) {
    fprintf(stderr, "server bind() %d\n", errno);
    exit(1);
  }

  err = listen(listener, 2048);
  if (err != 0) {
    fprintf(stderr, "server listen() %d\n", errno);
    exit(1);
  }

  fprintf(stderr, "server listening\n");

  int pid = fork();
  if (pid > 0) {
    // in child

    int client = socket(PF_UNIX, SOCK_STREAM, 0);
    if (client == -1) {
      fprintf(stderr, "client socket() %d\n", errno);
      exit(1);
    }

    int err = connect(client, (const struct sockaddr *)&address, address.sun_len);
    if (err != 0) {
      fprintf(stderr, "client connect() %d\n", errno);
      exit(1);
    }

    fprintf(stderr, "client connected\n");

    exit(0);
  }

  if (pid == -1) {
    fprintf(stderr, "server fork() %d\n", errno);
    exit(1);
  }

  int connection = accept(listener, NULL, NULL);
  if (connection == -1) {
    fprintf(stderr, "server accept() %d\n", errno);
    exit(1);
  }

  while (1) {
    uint8_t buffer[8];
    int rd = read(connection, buffer, sizeof(buffer)/sizeof(*buffer));
    if (rd == -1) {
      fprintf(stderr, "server read() %d\n", errno);
      exit(1);
    }

    if (rd == 0) {
      fprintf(stderr, "server read eof\n");
      break;
    }
  }

  return 0;
}
