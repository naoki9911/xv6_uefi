#include <stdio.h>
#include "font_bin.h"

int print_font(int index);

int main(void){
  print_font(0);
}

int print_font(int index){
  int bin;
  for(int i=0;i<30;i++){
    printf("\n");
    for(int j=14;j>-1;j--){
      bin = (font_bin[index][i])&(1 << j);
      if(bin == (1 << j)){
        printf("■");
      } else {
        printf("□");
      }
    }
  }
  printf("\n");
}

