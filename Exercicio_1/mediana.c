#include <stdio.h>
#include <stdlib.h>
#include "mediana.h"

int calculo_mediana(int a, int b, int c){
    int nums[3] = {a, b, c};

  for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (nums[i] > nums[j]) {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
    
    return nums[1];
}

int main() {
    int entrada[3];
    int i = 0;
    
    while (1) {
        int num;
        scanf("%d", &num);
        
        if (num == 0 && i >= 2) {
            break;
        }
        
        entrada[i % 3] = num;
        if (i >= 2) {
            int mediana = calculo_mediana(entrada[0], entrada[1], entrada[2]);
            printf("%d\n", mediana);
        }
        
        i++;
    }
    
    return 0;

}