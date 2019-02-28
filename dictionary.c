#include <stdio.h>
#include <string.h>
#include <stdlib.h>



 int main(){
   char **dictionary;
   dictionary=(char**)malloc(sizeof(char *)*(370200));
   for(int x =0; x<370100; x++){
     dictionary[x]=(char *)malloc(30);
   }
  FILE *d = fopen("dictionary.txt", "r");
  if (d ==NULL){
    printf("Error Opening File.\n");
    return(-1);
}

int i=0;
while(!feof(d)){
	fscanf(d, "%s", dictionary[i]);
  i++;
}

char word[30]= "zuza";
for (int y=0; y<370099; y++){
  if (strcmp(word, dictionary[y])==0){
    printf("%s   %s\n", dictionary[y], word);
  }
}

free(dictionary);
  fclose(d);

  return (0);
}
