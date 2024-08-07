# ASIC_DESIGN

## Lab Session 1

### Objective:
We need to compile and verify a basic C code of sum to numbers from 1 to n using GCC and by using RISC-V GNU compiler toolchain on Ubuntu, then compare the outputs.

### Tools required:
- GCC (GNU Compiler Collection)
- RISC-V GNU Compiler

### Procedure:

#### Compile and verify using GCC Compiler:
1. **Code Snippet for finding sum of first n numbers:**

    ```c
    #include <stdio.h>
    int main() {
        int i=0;int sum=0;int n=4;
        for(int i=1;i<=n;i+=1){
          sum+=i;
        }
        printf("The sum of numbers from 1 to %d is %d\n",n,sum);
        return 0;
    }
    ```
2. **Command for compiling the above code in terminal using GCC compiler:**
   ```
   gcc 1tonsum.c
   ```
3. **Command for getting output:**
   ```c
   ./a.out
   ```
4. **Output:**
   ```c
   The sum of numbers from 1 to 4 is 10
   ```

#### Compile and verify using RISC-V GNU Compiler:
1.**Command for compiling the code using  RISC-V GCC compiler:**
  ```c
  riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sumton.o sumton.c
  ```
2.**Command for getting the assembly language code:**
  ```c
  riscv64-unknown-elf-objdump -d sumton.o | less
  ```
3.**Output:**
