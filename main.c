#include <stdio.h>
#include <stdlib.h>
 
unsigned char *readBMP(char *filename, int *size) {
    int width, height;
    unsigned char *data;
    unsigned char info[54];
 
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
        return 0;
 
    fread(info, sizeof(unsigned char), 54, file); // leia o cabeçalho de 54 bytes
 
   // extrai a altura e a largura da imagem do cabeçalho
    width = *(int *) &info[18];
    height = *(int *) &info[22];
 
    *size = 3 * width * height;
    data = (unsigned char *) malloc(*size * sizeof(unsigned char)); // alocar 3 bytes por pixel
    fread(data, sizeof(unsigned char), (size_t) *size, file); // leia o resto dos dados de uma vez
    int i;
    for ( i = 0; i < *size; i += 3) {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }
 
    fclose(file);
    return data;
}
 
int main() {
    int size = 0;
    char filename[] = "teste.bmp";
    unsigned char *data = readBMP(filename, &size);
    int i;
    for ( i = 0; i < size; i++) {
        printf("%d. %d\n", i + 1, (int) data[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
 
    free(data);
    return 0;
}