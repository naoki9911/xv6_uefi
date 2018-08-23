#include <stdio.h>
#define PIXEL_NUM 325
#define HORIZONTAL_MAX 489
#define VERTICAL_MAX 155
#define SIKII 0xFE
struct rgb {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
};
struct rgb bmp_bin[VERTICAL_MAX][HORIZONTAL_MAX];

struct font {
  unsigned short bin[30];
};
int convert(int index, struct font *font_data);
int print_font(struct font *font_data);
int print_code(unsigned int index, struct font *font_data);
int main(void){
  FILE *fp;
  
  fp = fopen("font.bmp","rb");
  if(fp == NULL){
    printf("Failed to Load font.bmp\n");
    return -1;
  }

  fseek(fp,54,SEEK_SET);
  for(int i=0;i<VERTICAL_MAX;i++){
    fread(bmp_bin[i],sizeof(struct rgb),HORIZONTAL_MAX,fp);
    fseek(fp,1,SEEK_CUR);
  }
  for(int j=139;j>0;j--){
    if((j < 140 && j > 109) || (j < 86 && j > 55 ) || (j < 34 && j > 3)){
      printf("\n");
      for(int i=2;i<483;i++){
        if(bmp_bin[j][i].blue > SIKII && bmp_bin[j][i].green > SIKII && bmp_bin[j][i].red > SIKII){
          printf("□");
        }else{
          printf("■");
        }
      }
      printf("Addr:%x ",j*HORIZONTAL_MAX*3);
      printf("index: %d",j);
    }
  }
  struct font test_font;
  convert(0,&test_font);
  print_font(&test_font);
  print_code(0,&test_font);
  return 0;
}


int convert(int index, struct font *font_data){
  if(index > 33 ){
    return -1;
  }
  int start_addr = index*15+2;
  for(int i=0;i<30;i++){
    font_data->bin[i] = 0;
    for(int j=start_addr;j<start_addr+15;j++){
      font_data->bin[i] = font_data->bin[i] << 1;
      if(bmp_bin[139-i][j].blue == 0xFF && bmp_bin[139-i][j].green == 0xFF && bmp_bin[139-i][j].red == 0xFF){
      }else{
        font_data->bin[i] = font_data->bin[i] + 1;
      }
    }
  }
}

int print_font(struct font *font_data){
  int bin;
  for(int i=0;i<30;i++){
    printf("\n");
    for(int j=14;j>0;j--){
      bin = (font_data->bin[i])&(1 << j);
      if(bin == (1 << j)){
        printf("■");
      } else {
        printf("□");
      }
    }
  }
}

int print_code(unsigned int index, struct font *font_data){
  printf("\nfont_data[%d] = { \n",index);
  for(int i=0;i<5;i++){
    printf("  0x%X, 0x%X, 0x%X, 0x%X, 0x%x,\n",font_data->bin[i*5],font_data->bin[i*5+1],font_data->bin[i*5+2],font_data->bin[i*5+3],font_data->bin[i*5+4]);
  }
  printf("  0x%X, 0x%X, 0x%X, 0x%X, 0x%X\n };\n",font_data->bin[25],font_data->bin[26],font_data->bin[27],font_data->bin[28],font_data->bin[29]);
}
