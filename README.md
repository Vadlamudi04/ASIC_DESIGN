# ASIC_DESIGN

## Lab Session 1

### Objective:
We need to compile and verify a basic C code of sum to numbers from 1 to n using GCC and by using RISC-V GNU compiler toolchain on Ubuntu, then compare the outputs.

### Tools required:
- GCC (GNU Compiler Collection)
- RISC-V GNU Compiler

### Procedure:

### Task1: Compile and verify using GCC Compiler:
1. **Code to create a texteditor**
   ```
   leafpad 1tonsum.c
   ```
    
2. **Code Snippet for finding sum of first n numbers:**

    ```c
    #include <stdio.h>
    int main() {
        int i=0;int sum=0;int n=8;
        for(int i=1;i<=n;i+=1){
          sum+=i;
        }
        printf("The sum of numbers from 1 to %d is %d\n",n,sum);
        return 0;
    }
    ```
3. **Command for compiling the above code in terminal using GCC compiler:**
   ```
   gcc 1tonsum.c
   ```
4. **Command for getting output:**
   ```c
   ./a.out
   ```
5. **Output:**
   ```c
   The sum of numbers from 1 to 8 is 36
   ```


### Task2: Compile and verify using RISC-V GNU Compiler and optimize the compilation using O1 and Ofast:

#### Using O1 optimization:

1. **Command for compiling the code using  RISC-V GCC compiler using O1 optimization:**
   ```c
   riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o 1tonsum.o 1tonsum.c
   ```
   **Result:** This creates an object file "1tonsum.o"
   
2. **Command for getting the assembly language code:**
   ```c
   riscv64-unknown-elf-objdump -d 1tonsum.o | less
   ```
   **Result:**  As soon as you enter the above command, a huge list of opcode is shown in the terminal.
   But we are interested in main section of the program so type : /main 
3. **Obseravtion:**
   
   There are x lines of opcode in the main section.

#### Using Ofast optimization:

1. **Command for compiling the code using  RISC-V GCC compiler using -O1 optimization:**
   ```c
   riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o 1tonsum.o 1tonsum.c
   ```
   **Result:** This creates an object file "1tonsum.o"
   
2. **Command for getting the assembly language code:**
   ```c
   riscv64-unknown-elf-objdump -d 1tonsum.o | less
   ```
   **Result:**  As soon as you enter the above command, a huge list of opcode is shown in the terminal.
   But we are interested in main section of the program so type : /main 
3. **Obseravtion:**
   
   There are x lines of opcode in the main section.
   
### Results:

1. There are x lines of opcode in the main section for O1.
2. There are x lines of opcode in the main section for Ofast.
3. There are x lines of opcode in the main section for O2.
4. There are x lines of opcode in the main section for O3.

**Hence The compilation in the Ox procedure is optimised**


### Resources:
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [RISC-V GNU Compiler Toolchain Documentation](https://riscv.org/software-tools/risc-v-gnu-compiler-toolchain/)

---
## Lab Session 2

### Objective:

1. **To compile the Object dump file and verify the output with the GCC output from Lab Session 1.**
2. **To debug the main section of the previous program and observe register values after each step of compilation.**

### Tools required:

- GCC (GNU Compiler Collection)
- RISC-V GNU Compiler Toolchain
- Spike RISC-V Simulator

### Procedure:

