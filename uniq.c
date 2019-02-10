#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char prev[512];
char line[512];
char copyPrev[512];
char copyLine[512];

void toLower(char *str){
    while(*str != '\0'){
        if(*str >=65 && *str<=90){
            // It fails in the below assignment
            *str = *str + 32;
        }
        str++;
    }
}

void uniq(int fd, int flags[]){
  int i;
  int n;
  int c;

  int count;
  int countFlag;
  int dupli;
  int caseFlag;

  c = 0;
  count = 0;

  countFlag = flags[0];
  dupli = flags[1];
  caseFlag = flags[2];




  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      if(buf[i] != '\n'){
        line[c] = buf[i];
        c++;
      }
      else{
        if(caseFlag != 1){
          if (strcmp(prev, line) != 0 && prev[0] != '\0'){
            if (dupli == 1 && count > 1){
              if(countFlag == 1){
                printf(1, "%d %s\n", count, prev);
              }
              else {
                printf(1, "%s\n", prev);
              }
            }

            else if (dupli != 1){
              if(countFlag == 1){
                printf(1, "%d %s\n", count, prev);
              }
              else {
                printf(1, "%s\n", prev);
              }
            }
            count = 0;
          }
        }
        else{
          strcpy(copyLine,line);
          strcpy(copyPrev,prev);
          toLower(copyLine);
          toLower(copyPrev);

          if (strcmp(copyPrev, copyLine) != 0 && prev[0] != '\0'){
            if (dupli == 1 && count > 1){
              if(countFlag == 1){
                printf(1, "%d %s\n", count, prev);
              }
              else {
                printf(1, "%s\n", prev);
              }
            }

            else if (dupli != 1){
              if(countFlag == 1){
                printf(1, "%d %s\n", count, prev);
              }
              else {
                printf(1, "%s\n", prev);
              }
            }
            count = 0;
          }
        }

        count++;
        strcpy(prev, line);

        line[1] = '\0';
        c = 0;

      }
    }
  }


  if(caseFlag != 1){
    if (strcmp(prev, line) != 0 && prev[0] != '\0'){
      if (dupli == 1 && count > 1){
        if(countFlag == 1){
          printf(1, "%d %s\n", count, prev);
        }
        else {
          printf(1, "%s\n", prev);
        }
      }

      else if (dupli != 1){
        if(countFlag == 1){
          printf(1, "%d %s\n", count, prev);
        }
        else {
          printf(1, "%s\n", prev);
        }
      }
      count = 0;
    }
  }
  else{
    strcpy(copyLine,line);
    strcpy(copyPrev,prev);
    toLower(copyLine);
    toLower(copyPrev);

    if (strcmp(copyPrev, copyLine) != 0 && prev[0] != '\0'){
      if (dupli == 1 && count > 1){
        if(countFlag == 1){
          printf(1, "%d %s\n", count, prev);
        }
        else {
          printf(1, "%s\n", prev);
        }
      }

      else if (dupli != 1){
        if(countFlag == 1){
          printf(1, "%d %s\n", count, prev);
        }
        else {
          printf(1, "%s\n", prev);
        }
      }
      count = 0;
    }
  }

  if(n < 0){
    printf(1, "uniq: read error\n");
    exit();
  }
}

int main(int argc, char* argv[]){
  int fd;
  int i;

  int flags[] = {0,0,0}; //[countFlag, dupli, caseFlag]

  char counterFlag[] = "-c";
  char dupliFlag[] = "-d";
  char caseFlag[] = "-i";

  if (argc <= 1){
    uniq(0, flags);
    exit();
  }
  else if (argc >= 2){
    for(i = 1; i < argc; i++){
      if (strcmp(argv[i], counterFlag) == 0){
        flags[0] = 1;
      }
      else if (strcmp(argv[i], dupliFlag) == 0){
        flags[1] = 1;
      }
      else if (strcmp(argv[i], caseFlag) == 0){
        flags[2] = 1;
      }

      else if ((fd = open(argv[i], 0)) < 0){
        printf(1, "uniq: cannot open %s\n", argv[i]);
        exit();
      }

      if(i == (argc - 1)){
        uniq(fd, flags);
        close(fd);
      }
    }
  }

  exit();
}
