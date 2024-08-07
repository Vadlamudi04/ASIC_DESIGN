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
        int i;int sum=0;int n=100;
        for(int i=1;i<=n;i++){
          sum+=i;
        }
        printf("Sum to numbers from 1 to %d is %d\n",n,sum);
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
   Sum to numbers from 1 to 100 is 5050
   ```

   ![PHOTO-2024-08-07-16-04-09](https://github.com/user-attachments/assets/015736d9-882d-441b-b2b1-8a47916fd7e7)


### Task2: Compile and verify using RISC-V GNU Compiler and optimize the compilation using O1 and Ofast:

#### Using O1 optimization:

1. **Command for compiling the code using  RISC-V GCC compiler using O1 optimization:**
   ```c
   riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o 1tonsum.o 1tonsum.c
   ```
   **Result:** This creates an object file "1tonsum.o"
   
   ![PHOTO-2024-08-07-16-04-09](https://github.com/user-attachments/assets/3b1bdf64-c5fb-46e7-aed3-27a6f184d8c9)

3. **Command for getting the assembly language code:**
   ```c
   riscv64-unknown-elf-objdump -d 1tonsum.o | less
   ```
   **Result:**  As soon as you enter the above command, a huge list of opcode is shown in the terminal.
   But we are interested in main section of the program so type : /main 
4. **Obseravtion:**
   
   ![3](https://github.com/user-attachments/assets/af0fd908-3d5d-4fd3-b7e1-d2dc56efc951)

   There are 15 lines of opcode in the main section.

#### Using Ofast optimization:

1. **Command for compiling the code using  RISC-V GCC compiler using -Ofast optimization:**
   ```c
   riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o 1tonsum.o 1tonsum.c
   ```
   **Result:** This creates an object file "1tonsum.o"
   
   ![4](https://github.com/user-attachments/assets/35cf5501-0d07-43af-a492-55ac1765d998)

3. **Command for getting the assembly language code:**
   ```c
   riscv64-unknown-elf-objdump -d 1tonsum.o | less
   ```
   **Result:**  As soon as you enter the above command, a huge list of opcode is shown in the terminal.
   But we are interested in main section of the program so type : /main 
4. **Obseravtion:**
   
   ![5](https://github.com/user-attachments/assets/2b63d5c8-4618-497e-a036-588297b97d47)

   There are 12 lines of opcode in the main section.
   
### Results:

   ![6](https://github.com/user-attachments/assets/6846d35c-1aee-4997-be56-750b753b8c9b)

1. There are 15 lines of opcode in the main section for O1.
2. There are 12 lines of opcode in the main section for Ofast.
3. There are 12 lines of opcode in the main section for O2.
4. There are 12 lines of opcode in the main section for O3.

**Hence The compilation in the O1 procedure is the one which takes most number of instructions.**


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

