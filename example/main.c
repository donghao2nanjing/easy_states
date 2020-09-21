#include "stdio.h"
#include "../src/state.h"
#include "stdlib.h"

extern state ov1, ov2, ov3;
extern state uv1, uv2; 

int main(void){
    float t, y1, y2 ; 
    int count = 0 ; 
    char line[128] ;
    FILE * f = fopen("sinewave.txt", "r"); 

    if(f == NULL){
        printf("open file sinewave failed\n");
        return -1; 
    }else{
        // printf("open sinewave.txt OK\n");
    }    

    state_init();

    while(fgets(line, sizeof(line), f) != NULL ){
        count ++ ; 
        if(count == 500){
            set_state_masked(&uv2, 0); 
        }
        sscanf(line, "%f,%f,%f\n", &t, &y1, &y2);
        state_check_value(&ov1, y1);
        state_check_value(&ov2, y1);
        state_check_value(&ov3, y1);
        state_check_value(&uv1, y2);
        state_check_value(&uv2, y2);
        printf("%d,%d,%d,%d,%d\n", ov1.status.bits.valid, 
            ov2.status.bits.valid,
            ov3.status.bits.valid,
            uv1.status.bits.valid,
            uv2.status.bits.valid);
    }
    
    return 0 ; 
}