#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void) {
  char const *server_path = "/tmp/unix_server_listener"

  int listener = socket(PF_UNIX, SOCK_STREAM, 0);

  unlink(server_path);
  int err = bind(listener, address);

  err = listen(listener, 2048);

  set listener close-on-fork

  int pid = fork();
  if (pid > 0) {
    // in child

    int client = socket(PF_UNIX, SOCK_STREAM, 0);

    int err = connect(client, address);

    exit(0);
  }

  if (pid == -1) {
    // err
    exit(1)
  }

  int connection = accept(listener);

  wait for readability

  attempt read

  return 0;
}
