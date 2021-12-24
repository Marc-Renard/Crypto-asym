#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    uint8_t len = 20;
    uint8_t tab[len];
    for (int i = 0; i < len; i++)
    {
        tab[i] = 0;
    }
    
    I2OSP((uint64_t) 0xabccdef, len, tab );
    printf("[");
    int i = 0;
    while(tab[i] == 0){
        i++;
    }
    for(int j = i; j < (len - 1)  ; j++){
        fprintf(stdout, "0x%x ,", tab[j]);
    }
    fprintf(stdout, "0x%x]\n", tab[len-1]);

    uint64_t n = OS2IP(tab, len);
    fprintf(stdout, "Retour en int :\n0x%lx\n",n);

    return 0;
}