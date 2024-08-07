# ASIC_DESIGN

## Lab Session 1

### Objective:
We need to compile and verify a basic C code of sum to numbers from 1 to n using GCC and by using RISC-V GNU compiler toolchain on Ubuntu, then compare the outputs.

### Tools required:
- GCC (GNU Compiler Collection)
- RISC-V GNU Compiler

### Procedure:

#### Compile and verify using GCC Compiler:
1. **Code Snippet:**

    ```c
    #include <stdio.h>
    int main() {
        int i=0;int sum=0;int n=8;
        for(int i=1;i<=n;i+=1){
          sum+=i;
        }
        printf("The sum of numbers from 1 to %d is %d",n,sum);
        return 0;
    }
    ```

#### Compile and verify using RISC-V GNU Compiler:
