#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int READ = 0;
  int WRITE= 1;
  int childToPar[2];
  int parToChild[2];
  pipe(childToPar);
  pipe(parToChild);
  int f = fork();

  if (f == 0){ //child
    close(childToPar[READ]);
    close(parToChild[WRITE]);
    int s[1];
    read(parToChild[READ],s,sizeof(s));
    printf("[child]  Doing quick maths on: %d\n", s[0]);
    s[0] = s[0] + s[0] - 1;
    write(childToPar[WRITE], s, sizeof(s));
  } else { //parent
    close(parToChild[READ]);
    close(childToPar[WRITE]);
    int n[1];
    n[0] = 2;
    printf("[parent] Sending:  %d\n", n[0]);
    write(parToChild[WRITE], n, sizeof(n));
    int s[1];
    read(childToPar[READ],s,sizeof(s));
    printf("[parent] Recieved: %d\n", s[0]);
  }
}
