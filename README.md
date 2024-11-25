# ASIC_DESIGN

<details>
<summary><strong>Pre Midterm</strong></summary>


<details>
<summary><strong>Lab Session 1</strong></summary>

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
   ```
   ./a.out
   ```
5. **Output:**
   ```
   Sum to numbers from 1 to 100 is 5050
   ```

   ![PHOTO-2024-08-07-16-04-09](https://github.com/user-attachments/assets/015736d9-882d-441b-b2b1-8a47916fd7e7)


### Task2: Compile and verify using RISC-V GNU Compiler and optimize the compilation using O1,Ofast,O2 and O3:

#### Using O1 optimization:

1. **Command for compiling the code using  RISC-V GCC compiler using O1 optimization:**
   ```c
   riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o 1tonsum.o 1tonsum.c
   ```
   **Result:** This creates an object file "1tonsum.o"
   
   ![2](https://github.com/user-attachments/assets/49269d01-46a2-45b1-8d36-12da7b295106)


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

**Hence Compilation using O1 optimization takes the most number of instructions(most time).**


### Resources:
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [RISC-V GNU Compiler Toolchain Documentation](https://riscv.org/software-tools/risc-v-gnu-compiler-toolchain/)
  
</details>
   
<details>
<summary><strong>Lab Session 2</strong></summary>
   
### Objective:

1. To compile the Object dump file and verify the output with the GCC output from Lab Session 1.
2. To debug the main section of the previous program and observe register values after each step of compilation.

### Tools required:

- GCC (GNU Compiler Collection)
- RISC-V GNU Compiler Toolchain
- Spike RISC-V Simulator

### Procedure:

<strong>Objective 1:</strong>

   1. **Use the below command for compiling 1tonsum.c using RISCV Compiler.**
   
   ```c
   riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o 1tonsum.o 1tonsum.c
   ```
   2. **After compiling our program with the RISC-V compiler, we need to run it to obtain the output, similar to how we use ./a.out with the GCC compiler. To achieve this, use 
   the Spike Simulator and enter the following command:**
   
   ```
   spike pk 1tonsum.o
   ```

   ![PHOTO-2024-08-07-19-20-10](https://github.com/user-attachments/assets/77847277-bdd6-44db-9add-70082692af55)


   **Observation:**
   
   We can see that output is same using the gcc and the riscv compiler.

<strong>Objective 2 (debuging the assembly code):</strong>


1. **Use the following code to open debuging mode:**
   ```
   spike -d pk 1tonsum.o
   ```
   
   ![PHOTO-2024-08-07-19-36-07](https://github.com/user-attachments/assets/f251a5c9-5dfe-484c-b059-bb07adeb22c2)

   After this we will be entering debuging mode.Now we will let the Spike debugger's program counter run until it reaches the 100b0 instruction which is the starting of main function by typing the below code.
   
   ![5](https://github.com/user-attachments/assets/78398fde-df3c-47f9-b480-670a4eb3e707)
   
3. **Use the following code to move pc to main function location:**
      ```
      until pc 0 100b0
      ```
   Since a2 is the register present at the location of 100b0 we will be checking the a2 register before and after execution of instruction.Inorder to move on to the next instruction press ```Enter```.
   
4. **Execute the following command in order to check the contents of registor 'a2':**

   ```
   reg 0 a2
   ```
   
   ![PHOTO-2024-08-07-19-37-40](https://github.com/user-attachments/assets/bae0a282-e88f-4aa9-8d3c-cbfb6ba3cd30)
   
   **Observation:**

   The lui a2, 0x1 instruction updates the a2 register's value from ```0x0000000000000000``` to ```0x0000000000001000```. This indicates that the lui instruction performs basic addition to the upper 20 bits of the register with the specified value (in this case, 0x1), while the lower 12 bits remain unchanged.

   Next, we will debug the next instruction addi sp, sp, -16, which reduces the stack pointer (sp) by 16. To do this run all the instructions till 100b8.
   
   ![5](https://github.com/user-attachments/assets/78398fde-df3c-47f9-b480-670a4eb3e707)
   
1. **Use the following code to move pc to location 100b8:**
   ```
   until pc 0 100b8
   ```
2. **Execute the following command in order to check the contents of 'sp':**

   ```
   reg 0 sp
   ```
   To check what "addi" instruction does we will be checking the value of sp before and after execution of instruction.Inorder to move on to the next instruction press ```Enter```.

   ![PHOTO-2024-08-07-19-38-59](https://github.com/user-attachments/assets/e4407027-a6a9-47fc-8599-b53f06f0babb)
   
   **Observation:**

   The addi sp,sp,-16 instruction updates the sp register's value from ```0x0000003ffffffb50``` to ```0x0000003ffffffb40```.Which makes it evident that the addition of (-16) took place and the value 10 ( 16 in decimal base and 10 in hexadecimal base ) has been deducted.

### References:

   - [Spike RISC-V Simulator Documentation](https://github.com/riscv-software-src/riscv-isa-sim)
      
</details>

<details>
<summary><strong>Lab Session 3</strong></summary>

### Objective:

1. To identify various RISC-V instruction types (R, I, S, B, U, J).
2. To determine the exact 32-bit instruction code for specific RISC-V instructions.

### Procedure:
- The RISC-V architecture uses several instruction formats to handle various operations. The six primary formats are R-Type, I-Type, S-Type, B-Type, U-Type, and J-Type, each designed for specific tasks such as arithmetic, logic operations, handling immediate values, branching, memory access, and jumps.
  
- Instruction formats for various RISC-V instruction types.

![r](https://github.com/user-attachments/assets/714d5206-0dc4-47fd-8c62-cf65fcec60a6)

- Base instruction set table for predefined values

![g](https://github.com/user-attachments/assets/55b8f0ef-0468-47ee-b882-c7ffde7c56c9)



<u>R-type</u>
---
   - In RISC-V, the R-Type instruction format is used for arithmetic, logical, and other operations that involve only registers. These instructions typically operate on two source registers and store the result in a destination register.
   - Structure of R-Type Instructions:
        - An R-Type instruction is 32 bits long and consists of the following fields:
           - ```funct7 (7 bits)```: Specifies the operation variant, often used to differentiate between similar operations (e.g., ADD vs. SUB).
           - ```rs2 (5 bits)```: The second source register.
           - ```rs1 (5 bits)```: The first source register.
           - ```funct3 (3 bits)```: Specifies the operation type (e.g., ADD, AND, OR).
           - ```rd (5 bits)```: The destination register where the result is stored.
           - ```opcode (7 bits)```: Identifies the general type of instruction (e.g., 0110011 for R-Type operations).

<u>I-type</u>
---
   - In RISC-V, the I-Type instruction format is used for operations that involve an immediate value (a constant encoded directly in the instruction) along with one or two registers. These instructions are typically used for arithmetic operations with an immediate, memory access (load), and certain control flow operations.
   - Structure of I-Type Instructions:
      - An I-Type instruction is 32 bits long and consists of the following fields:
         - ```imm[11:0] (12 bits)```: The immediate value, often sign-extended to 32 bits when used.
         - ```rs1 (5 bits)```: The source register that provides an operand.
         - ```funct3 (3 bits)```: Specifies the operation type (e.g., ADDI, SLTI, LW).
         - ```rd (5 bits)```: The destination register where the result is stored.
         - ```opcode (7 bits)```: Identifies the general type of instruction (e.g., 0010011 for arithmetic operations with an immediate).

<u>S-type</u>
---
   - In RISC-V, the S-Type instruction format is used for store operations, where data from a register is stored into memory. These instructions typically calculate the memory address using a base register and an immediate value, then store the data at that address.
   - Structure of S-Type Instructions:
      - An S-Type instruction is 32 bits long and consists of the following fields:
         - ```imm[11:5] (7 bits```: The upper 7 bits of the immediate value.
         - ```rs2 (5 bits)```: The source register containing the data to be stored.
         - ```rs1 (5 bits)```: The base register that provides the base address for the memory operation.
         - ```funct3 (3 bits)```: Specifies the operation type (e.g., SW for storing a word, SH for storing a halfword).
         - ```imm[4:0] (5 bits)```: The lower 5 bits of the immediate value.
         - ```opcode (7 bits)```: Identifies the general type of instruction (e.g., 0100011 for store operations).

<u>B-type</u>
---
   - In RISC-V, the B-Type instruction format is used for conditional branch operations. These instructions compare two registers and, based on the result, may branch to a different instruction address calculated using an immediate value.
   - Structure of B-Type Instructions:
      - A B-Type instruction is 32 bits long and consists of the following fields:
         - ```imm[12] (1 bit)```: The most significant bit of the immediate value.
         - ```imm[10:5] (6 bits)```: The next 6 bits of the immediate value.
         - ```rs2 (5 bits)```: The second source register for the comparison.
         - ```rs1 (5 bits)```: The first source register for the comparison.
         - ```funct3 (3 bits)```: Specifies the comparison operation type (e.g., BEQ for branch if equal, BNE for branch if not equal).
         - ```imm[4:1] (4 bits)```: The next 4 bits of the immediate value.
         - ```imm[11] (1 bit)```: The 11th bit of the immediate value.
         - ```opcode (7 bits)```: Identifies the general type of instruction (e.g., 1100011 for branch operations).

<u>U-type</u>
---
   - In RISC-V, the U-Type instruction format is used for operations that involve loading a large immediate value into a register. These instructions are typically used for creating 32-bit constants or setting the upper 20 bits of a register.
   - Structure of U-Type Instructions:
      - A U-Type instruction is 32 bits long and consists of the following fields:
         - ```imm[31:12] (20 bits)```: The immediate value, representing the upper 20 bits of the target value.
         - ```rd (5 bits)```: The destination register where the result is stored.
         - ```opcode (7 bits)```: Identifies the general type of instruction (e.g., 0110111 for LUI or 0010111 for AUIPC).

<u>J-type</u>
---
   - In RISC-V, the J-Type instruction format is used for jump operations, specifically for the JAL (Jump and Link) instruction. This instruction sets the program counter (PC) to a target address calculated using an immediate value, and it also stores the return address in a register.
   - Structure of J-Type Instructions:
      - A J-Type instruction is 32 bits long and consists of the following fields:
         - ```imm[20] (1 bit)```: The most significant bit of the immediate value.
         - ```imm[10:1] (10 bits)```: The next 10 bits of the immediate value.
         - ```imm[11] (1 bit)```: The 11th bit of the immediate value.
         - ```imm[19:12] (8 bits)```: The next 8 bits of the immediate value.
         - ```rd (5 bits)```: The destination register where the return address is stored.
         - ```opcode (7 bits)```: Identifies the general type of instruction (e.g., 1101111 for the JAL instruction).



<u>Identifying various RISC-V instruction type (R, I, S, B, U, J) and exact 32-bit instruction code in the instruction type format for below RISC-V instructions:</u>
---
   ```
    ADD r1, r2, r3
    SUB r3, r1, r2
    AND r2, r1, r3
    OR r8, r2, r5
    XOR r8, r1, r4
    SLT r10, r2, r4
    ADDI r12, r3, 5
    SW r3, r1, 4
    SRL r16, r11, r2
    BNE r0, r1, 20
    BEQ r0, r0, 15
    LW r13, r11, 2
    SLL r15, r11, r2
   ```
   - ```ADD r1, r2, r3```
      - Opcode for ADD = 0110011
      - rd = r1 = 00001
      - rs1 = r2 = 00010
      - rs2 = r3 = 00011
      - func3 = 000
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00011_00010_000_00001_0110011
      - **Hexadecimal representation:** 0x003100B3
      
        
   - ```SUB r3, r1, r2```
      - Opcode for SUB = 0110011
      - rd = r3 = 00011
      - rs1 = r1 = 00001
      - rs2 = r2 = 00010
      - func3 = 000
      - func7 = 0100000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0100000_00010_00001_000_00011_0110011
      - **Hexadecimal representation:** 0x402081B3
        
   - ```AND r2, r1, r3```
      - Opcode for AND = 0110011
      - rd = r2 = 00010
      - rs1 = r1 = 00001
      - rs2 = r3 = 00011
      - func3 = 111
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00011_00001_111_00010_0110011
      - **Hexadecimal representation:** 0x0030F133
        
   - ```OR r8, r2, r5```
      - Opcode for OR = 0110011
      - rd = r8 = 01000
      - rs1 = r2 = 00010
      - rs2 = r5 = 00101
      - func3 = 110
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00101_00010_110_01000_0110011
      - **Hexadecimal representation:** 0x00516433    
     
   - ```XOR r8, r1, r4```
      - Opcode for XOR = 0110011
      - rd = r8 = 01000
      - rs1 = r1 = 00001
      - rs2 = r4 = 00100
      - func3 = 100
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00100_00001_100_01000_0110011
      - **Hexadecimal representation:** 0x0040C433
 
   - ```SLT r10, r2, r4```
      - Opcode for SLT = 0110011
      - rd = r10 = 01010
      - rs1 = r2 = 00010
      - rs2 = r4 = 00100
      - func3 = 010
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00100_00010_010_01010_0110011
      - **Hexadecimal representation:** 0x00412533
 
   - ```ADDI r12, r3, 5```
      - Opcode for ADDI = 0010011
      - rd = r12 = 01100
      - rs1 = r3 = 00011
      - imm = 000000000101
      - func3 = 000
      - **Instruction Type:** I Type
      - **32-bit Instruction:** 000000000101_00011_000_01100_0010011
      - **Hexadecimal representation:** 0x00518613
      
   - ```SW r3, r1, 4```
      - Opcode for SW = 0100011
      - rs1 = r3 = 00011
      - rs2 = r1 = 00001
      - imm = 0000000 00100
      - func3 = 010
      - **Instruction Type:** S Type
      - **32-bit Instruction:** 0000000_00001_00011_010_00100_0100011
      - **Hexadecimal representation:** 0x0011A223

   - ```SRL r16, r11, r2```
      - Opcode for SRL = 0110011
      - rd = r16 = 10000
      - rs1 = r11 = 01011
      - rs2 = r2 = 00010
      - func3 = 101
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00010_01011_101_10000_0110011
      - **Hexadecimal representation:** 0x0025D833

   - ```BNE r0, r1, 20```
      - Opcode for BNE = 1100011
      - rs1 = r0 = 00000
      - rs2 = r1 = 00001
      - Imm[12:1] = 20 = 0 0 000001 0100
      - func3 = 001
      - **Instruction Type:** B Type
      - **32-bit Instruction:** 0_000001_00001_00000_001_0100_0_1100011
      - **Hexadecimal representation:** 0x02101463
        
   - ```BEQ r0, r0, 15```
      - Opcode for BEQ = 1100011
      - rs1 = r0 = 00000
      - rs2 = r0 = 00000
      - Imm[12:1] = 15 = 0 0 000000 1111
      - func3 = 000
      - **Instruction Type:** B Type
      - **32-bit Instruction:** 0_000000_00000_00000_000_1111_0_1100011
      - **Hexadecimal representation:** 0x00000F63
   
   - ```LW r13, r11, 2```
      - Opcode for LW = 0000011
      - rd = r13 = 01101
      - rs1 = r11 = 01011
      - imm = 000000000010
      - func3 = 010
      - **Instruction Type:** I Type
      - **32-bit Instruction:** 000000000010_01011_010_01101_0000011
      - **Hexadecimal representation:** 0x0025A683
              
   - ```SLL r15, r11, r2```
      - Opcode for SLL = 0110011
      - rd = r15 = 01111
      - rs1 = r11 = 01011
      - rs2 = r2 = 00010
      - func3 = 001
      - func7 = 0000000
      - **Instruction Type:** R Type
      - **32-bit Instruction:** 0000000_00010_01011_001_01111_0110011
      - **Hexadecimal representation:** 0x002597B3
        
### Summary table 

# Instruction Summary Table

This table provides a summary of RISC-V instructions, including their types, 32-bit patterns, and hexadecimal representations.


| Instruction          | Instruction Type | 32-bit Pattern                | Hexadecimal Pattern |
|----------------------|------------------|-------------------------------|---------------------|
| `ADD r1, r2, r3`     | R Type           | 0000000_00011_00010_000_00001_0110011 | 0x003100B3          |
| `SUB r3, r1, r2`     | R Type           | 0100000_00010_00001_000_00011_0110011 | 0x402081B3          |
| `AND r2, r1, r3`     | R Type           | 0000000_00011_00001_111_00010_0110011 | 0x0030F133          |
| `OR r8, r2, r5`      | R Type           | 0000000_00101_00010_110_01000_0110011 | 0x00516433          |
| `XOR r8, r1, r4`     | R Type           | 0000000_00100_00001_100_01000_0110011 | 0x0040C433          |
| `SLT r10, r2, r4`    | R Type           | 0000000_00100_00010_010_01010_0110011 | 0x00412533          |
| `ADDI r12, r3, 5`    | I Type           | 000000000101_00011_000_01100_0010011 | 0x00518613          |
| `SW r3, r1, 4`       | S Type           | 0000000_00001_00011_010_00100_0100011 | 0x0011A223          |
| `SRL r16, r11, r2`   | R Type           | 0000000_00010_01011_101_10000_0110011 | 0x0025D833          |
| `BNE r0, r1, 20`     | B Type           | 0_000001_00001_00000_001_0100_0_1100011 | 0x02101463          |
| `BEQ r0, r0, 15`     | B Type           | 0_000000_00000_00000_000_1111_0_1100011 | 0x00000F63          |
| `LW r13, r11, 2`     | I Type           | 000000000010_01011_010_01101_0000011 | 0x0025A683          |
| `SLL r15, r11, r2`   | R Type           | 0000000_00010_01011_001_01111_0110011 | 0x002597B3          |



### References:

   - [RISC-V Instruction Set Manual](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)


</details>

<details>
<summary><strong>Lab Session 4</strong></summary>

### Objective:

- Functional simulation Experiment

### Standard RISC-V ISA and Hardcoded ISA based on the provided Verilog code:

- In Verilog code, each instruction type has a different opcode, and instructions have distinct func3 and func7 values compared to original riscv values. The func7 value distinguishes immediate operations from other arithmetic functions; if not used for this purpose, func7 is set to b'0 in the verilog code.
  
- In the below table Hardcoded 32bit pattern is formed by using the op codes, func3 and  func7 values from the verilog code.

| S.No | Instruction        | Hardcoded 32bit pattern        | Hardcoded hexadecimal pattern | 32bit pattern                       | Hexadecimal pattern |
|------|--------------------|--------------------------------|--------------------------------|-------------------------------------|---------------------|
| 1    | ADD r1, r2, r3      | 0000001_00011_00010_000_00001_0000000 | 0x02310080                     | 0000000_00011_00010_000_00001_0110011 | 0x003100B3          |
| 2    | SUB r3, r1, r2      | 0000001_00010_00001_001_00011_0000000 | 0x02209180                     | 0100000_00010_00001_000_00011_0110011 | 0x402081B3          |
| 3    | AND r2, r1, r3      | 0000001_00011_00001_010_00010_0000000 | 0x0230A100                     | 0000000_00011_00001_111_00010_0110011 | 0x0030F133          |
| 4    | OR r8, r2, r5       | 0000001_00101_00010_011_01000_0000000 | 0x02513400                     | 0000000_00101_00010_110_01000_0110011 | 0x00516433          |
| 5    | XOR r8, r1, r4      | 0000001_00100_00001_100_01000_0000000 | 0x0240C400                     | 0000000_00100_00001_100_01000_0110011 | 0x0040C433          |
| 6    | SLT r10, r2, r4     | 0000001_00100_00010_101_01010_0000000 | 0x02415500                     | 0000000_00100_00010_010_01010_0110011 | 0x00412533          |
| 7    | ADDI r12, r3, 5     | 000000000101_00011_000_01100_0000000 | 0x00518600                     | 000000000101_00011_000_01100_0010011 | 0x00518613          |
| 8    | SW r3, r1, 4        | 0000000_00001_00011_001_00100_0000001 | 0X00119201                    | 0000000_00001_00011_010_00100_0100011 | 0x0011A223          |
| 9    | LW r13, r11, 2      | 000000000010_01011_000_01101_0000001 | 0x0258681                      | 000000000010_01011_010_01101_0000011 | 0x0025A683          |
| 10   | BEQ r0, r0, 15      | 0_000000_01111_00000_000_0000_0_0000010 | 0X00f00002                     | 0_000000_00000_00000_000_1111_0_1100011 | 0x00000F63          |
| 11   | SRL r16, r11, r2    | 0000000_00010_01011_001_10000_0000011 | 0x00259803                     | 0000000_00010_01011_101_10000_0110011 | 0x0025D833          |


 ### Output Waveforms for the instructions provided in the verilog code:
 
   ![im1](https://github.com/user-attachments/assets/f3910b2e-82af-45e8-a51e-f3894066cf42)

      
   |S. no.| Operation          | Standard RISCV ISA | Hardcoded ISA |
   |-----|--------------------|---------------------|---------------|
   |1.| ADD R6, R1, R2     | 0x00110333        | 0x02208300  |
   |2.| SUB R7, R1, R2     | 0x402083b3        | 0x02209380  |
   |3.| AND R8, R1, R3     | 0x0030f433        | 0x0230a400  |
   |4.| OR R9, R2, R5      | 0x005164b3        | 0x02513480  |
   |5.| XOR R10, R1, R4    | 0x0040c533        | 0x0240c500  |
   |6.| SLT R11, R2, R4     | 0x0045a0b3        | 0x02415580  |
   |7.| ADDI R12, R4, 5    | 0x004120b3        | 0x00520600  |
   |8.| SW R3, R1, 2       | 0x0030a123        | 0x00209181  |
   |9.| LW R13, R1, 2      | 0x0020a683        | 0x00208681  |
   |10.| BEQ R0, R0, 15   | 0x00000f63    | 0x00f00002   |
   |11.| ADD R14, R2, R2    | 0x00210733         | 0x00210700  |


   The following are the waveforms of each instruction by using the test bench code

   ```1.  ADD r6, r1, r2 ```
   
   ![PHOTO-2024-08-11-17-05-01](https://github.com/user-attachments/assets/d4736e6e-97f3-4fd1-868a-fcce723cbe70)


   ```2. SUB r7, r1, r2 ```

   ![PHOTO-2024-08-11-17-09-45](https://github.com/user-attachments/assets/d9dcbc88-1e4b-4962-838c-779cb422bda9)



   ```3.  AND r8, r1, r3 ```

   ![PHOTO-2024-08-11-17-10-31](https://github.com/user-attachments/assets/dbf8bdc2-07a2-49c5-a895-35bfee470d3b)


   ```4. OR r9, r2, r5 ```

   ![PHOTO-2024-08-11-17-11-33](https://github.com/user-attachments/assets/96629d0f-1020-490e-b2ee-3a0f339402d6)


   ```5. XOR r10, r1, r4 ```

   ![PHOTO-2024-08-11-17-12-30](https://github.com/user-attachments/assets/0b066277-4778-45ef-9748-cc17ea992fca)


   ```6. SLT r11, r2, r4 ```

   ![PHOTO-2024-08-11-17-13-11](https://github.com/user-attachments/assets/5e15331c-5ea9-41ec-ae8a-e91b8f700f1d)


   ```7. ADDI r12, r4, 5 ```

   ![PHOTO-2024-08-11-17-13-53](https://github.com/user-attachments/assets/5dbe3daa-c3c9-433f-8fb9-df1b0ea6f8dd)


   ```8. SW r3, r1, 2 ```

   ![PHOTO-2024-08-11-17-14-26](https://github.com/user-attachments/assets/fda3ea2e-7499-4a9c-8806-9b3096add011)


   ```9. LW r0, r0, 15 ```

   ![PHOTO-2024-08-11-17-14-58](https://github.com/user-attachments/assets/0033d654-56bf-4e7a-8c3b-73d0e06611f0)


   ```10. BEQ r0, r0, 15 ```

   ![PHOTO-2024-08-11-17-15-42](https://github.com/user-attachments/assets/0ac584e5-5031-42a9-a9bd-16870c7b01bf)


   ```11. ADD r14, r2, r2```
   
   ![im12](https://github.com/user-attachments/assets/139b89a2-fabe-4f8f-8125-11c5ed7bf6cb)


   The final output plot is :

   ![PHOTO-2024-08-11-17-18-55](https://github.com/user-attachments/assets/044915f8-6d13-44a9-89d7-dd1176c49adf)

   ### References:

   - [RISC-V Instruction Set Manual](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)

</details>

<details>
<summary><strong>Lab Session 5</strong></summary>

   ### Objective:
   - To verify that the output of the below code is same for both riscv-gcc and gcc compiler.

   ### Procedure: 

   - The code below is a C program that manages a stock portfolio, allowing users to add stocks, view the portfolio, and calculate its total value.

      ```c
            #include <stdio.h>
            #include <stdlib.h>
            #include <string.h>
            
            #define MAX_STOCKS 100
            #define MAX_NAME_LENGTH 50
            
            typedef struct {
                char symbol[MAX_NAME_LENGTH];
                double price;
                int quantity;
            } Stock;
            
            void add_stock(Stock portfolio[], int *num_stocks);
            void view_portfolio(Stock portfolio[], int num_stocks);
            void calculate_portfolio_value(Stock portfolio[], int num_stocks);
            
            int main() {
                Stock portfolio[MAX_STOCKS];
                int num_stocks = 0;
                int choice;
            
                while (1) {
                    printf("\nStock Portfolio Manager\n");
                    printf("------------------------\n");
                    printf("1. Add Stock\n");
                    printf("2. View Portfolio\n");
                    printf("3. Calculate Portfolio Value\n");
                    printf("4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
            
                    switch (choice) {
                        case 1:
                            add_stock(portfolio, &num_stocks);
                            break;
                        case 2:
                            view_portfolio(portfolio, num_stocks);
                            break;
                        case 3:
                            calculate_portfolio_value(portfolio, num_stocks);
                            break;
                        case 4:
                            printf("Exiting...\n");
                            return 0;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
            
                return 0;
            }
            
            void add_stock(Stock portfolio[], int *num_stocks) {
                if (*num_stocks >= MAX_STOCKS) {
                    printf("Portfolio is full. Cannot add more stocks.\n");
                    return;
                }
            
                printf("Enter stock symbol: ");
                scanf("%s", portfolio[*num_stocks].symbol);
                printf("Enter stock price: ");
                scanf("%lf", &portfolio[*num_stocks].price);
                printf("Enter stock quantity: ");
                scanf("%d", &portfolio[*num_stocks].quantity);
            
                (*num_stocks)++;
                printf("Stock added successfully.\n");
            }
            
            void view_portfolio(Stock portfolio[], int num_stocks) {
                if (num_stocks == 0) {
                    printf("Portfolio is empty.\n");
                    return;
                }
            
                printf("\nYour Portfolio:\n");
                printf("Symbol\tPrice\tQuantity\n");
                printf("-----------------------------\n");
            
                for (int i = 0; i < num_stocks; i++) {
                    printf("%s\t%.2f\t%d\n", portfolio[i].symbol, portfolio[i].price, portfolio[i].quantity);
                }
            }
            
            void calculate_portfolio_value(Stock portfolio[], int num_stocks) {
                if (num_stocks == 0) {
                    printf("Portfolio is empty.\n");
                    return;
                }
            
                double total_value = 0.0;
                for (int i = 0; i < num_stocks; i++) {
                    total_value += portfolio[i].price * portfolio[i].quantity;
                }
            
                printf("Total portfolio value: $%.2f\n", total_value);
            }
      ```

   - Commands to get output using GCC compiler

     ```c
     1.  gcc stock.c
      ```
     
     ```c
     2.   ./a.out
     ```
     
   - The below photo shows the output obtained by running the above C code using a standard GCC compiler.

      ![im2](https://github.com/user-attachments/assets/1f2a036e-042f-4c48-9aaa-dc095936b6a1)

   
   - Commands to get output using RISC-V GCC compiler
     
     ```c
     1.   riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o stock.o stock.c
     ```

     ```c
     2.  spike pk stock.o
     ```
   
   - The below photo shows the output obtained by running the above C code using a RISC-V GCC compiler.

      ![im3](https://github.com/user-attachments/assets/ff08e7d6-e3e0-4d2a-a03a-937b92216feb)


     ### Conclusion:

     - If we look at the above images we can see that output is same using the gcc and the riscv compiler.

</details>

<details>
<summary><strong>Lab Session 6</strong></summary>
<details>
<summary><strong>Day3</strong></summary>

## Digital Logic Design and TL-Verilog with Makerchip:

### Logic Gates: 
Logic Gates are the core components of digital circuits, performing essential logical operations on binary input signals. These gates are fundamental to the design of complex systems like processors, memory units, and controllers. Logic gates operate on binary signals, where "0" and "1" correspond to low and high voltage levels in a digital circuit. The gates take one or more input signals and produce an output signal based on specific logical functions.

Here are some common types of logic gates:
![d3_1](https://github.com/user-attachments/assets/e21f4645-26e8-445e-a32b-74f7f82ec93a)


### Multiplexer Using Ternary Operator: 

**2:1 Multiplexer:** The following Verilog code uses a ternary operator to implement a 2:1 multiplexer. The output f follows x1 when s is high (1) and x0 when s is low (0).
```
assign f = s ? x1 : x0;
```
This code translates into hardware that selects between x1 and x0 based on the value of s.

![d3_2](https://github.com/user-attachments/assets/b30c0560-d92d-4b9e-a64a-c1f636649b41)


**4:1 Multiplexer:**  A higher-bit multiplexer can be realized using nested ternary operators, as shown in the Verilog code below:
```
assign f = sel[0] ? a : (sel[1] ? b : (sel[2] ? c : d));
```
This code effectively creates a priority-encoded series of 2:1 multiplexers. Here, the sel vector is one-hot, meaning only one bit is high at any time, which directs the selection among inputs a, b, c, and d.

![d3_3](https://github.com/user-attachments/assets/3766ff9e-0f6f-4ed9-9053-1eea448b86dc)


### Transaction Level (TL) - Verilog: 

TL-Verilog is a modern extension of traditional Verilog, introduced by Redwood EDA, to simplify hardware modeling and design. It enhances the design process by providing a more abstract and efficient syntax while remaining compatible with standard Verilog. TL-Verilog supports transaction-level modeling, making it easier to manage complex microarchitectures. In this approach, a transaction moves through the architecture, interacting with components like pipelines, arbiters, and queues. TL-Verilog is particularly effective in reducing bugs and streamlining design with tools like Makerchip.

### Makerchip IDE: 

Makerchip IDE is a powerful tool for digital design, offering an integrated environment for coding, simulating, and testing HDL designs. Supporting languages like TL-Verilog, SystemVerilog, Verilog, and VHDL, Makerchip provides a visual platform to construct and simulate digital systems in real-time. Its user-friendly interface and extensive capabilities make it ideal for both beginners and experienced designers. With Makerchip, you can prototype, debug, and refine your digital designs efficiently, ensuring that your circuits function as intended before moving to hardware implementation.


### Basic Combinational Circuits in Makerchip:
---

#### 1. Inverter
Code is given below
```tl-verilog
$out = ! $in;
```
The generated block diagram and waveforms are as shown

![d3_4](https://github.com/user-attachments/assets/b649f4a3-c337-42fa-8be4-7f28a622468d)


#### 2. Arithmetic Operation on Vectors
Code is given below
```tl-verilog
$out[4:0] = $in1[3:0] + $in2[3:0];
```
The generated block diagram and waveforms are as shown

![d3_5](https://github.com/user-attachments/assets/b2b0c9d2-9ab7-4e41-99b6-4d6e5ed939e5)


#### 3. 2-Input And Gate
Code is given below
```tl-verilog
$out = $in1 && $in2;
```
The generated block diagram and waveforms are as shown

![d3_6](https://github.com/user-attachments/assets/c2848d8a-dff3-4603-a71e-d84fc2be26df)

#### 3. 2-Input OR Gate
Code is given below
```tl-verilog
$out = $in1 || $in2;
```
The generated block diagram and waveforms are as shown

![d3_7](https://github.com/user-attachments/assets/f91e714b-3ad9-4359-a0ec-132910cdbfc6)

#### 4. 2-Input XOR Gate
Code is given below
```tl-verilog
$out = $in1 ^ $in2;
```
The generated block diagram and waveforms are as shown

![d3_8](https://github.com/user-attachments/assets/9be94c4b-9c6a-4a7c-b37a-1fa762332f75)

#### 6. 2:1 MUX
Code is given below
```tl-verilog
$out[11:0] = $sel ? $in1[11:0] : $in0[11:0];
```
The generated block diagram and waveforms are as shown

![d3_9](https://github.com/user-attachments/assets/967d46ff-25ac-43ef-97ac-8096d597695a)

#### 7. Combinational Calculator Implementation in TL-Verilog

**Calculator Overview:**
In this section, we demonstrate a basic combinational calculator implemented using TL-Verilog on the Makerchip platform. The calculator does four fundamental arithmetic operations: addition, subtraction, multiplication, and division.

```tl-verilog
$val1[31:0] = $rand1[3:0];
$val2[31:0] = $rand2[3:0];

$sum[31:0]  = $val1[31:0] + $val2[31:0];
$diff[31:0] = $val1[31:0] - $val2[31:0];
$prod[31:0] = $val1[31:0] * $val2[31:0];
$quot[31:0] = $val1[31:0] / $val2[31:0];

$out[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
             ($sel[1:0] == 2'b01) ? $diff[31:0]:
             ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                    $quot[31:0];
```
**Description:** 

In this code snippet, two random 4-bit values, `$rand1[3:0]` and `$rand2[3:0]`, are assigned to the 32-bit variables `$val1[31:0]` and `$val2[31:0]`, respectively. The calculator then performs four arithmetic operations on these values:

The result of one of these operations is selected by a multiplexer (MUX), controlled by the selection bits `$sel[1:0]`. The MUX determines which operation's output is assigned to `$out[31:0]`.

The generated block diagram and waveforms are as shown


![d3_10](https://github.com/user-attachments/assets/a6578318-0ba3-4807-9689-15cebb601037)


### Sequential Circuits in Makerchip:
---

A sequential circuit is a digital circuit that uses memory components to retain data, allowing it to generate outputs based on both current inputs and the circuit's previous state. Unlike combinational circuits, which depend only on present inputs, sequential circuits use feedback loops and storage elements like flip-flops or registers to track their internal state. This internal state, along with current inputs, influences the circuit's behavior, enabling tasks that require input history, such as counting, data storage, or event sequencing.


#### 1. Fibbonacci Series:

Code is given below:

```tl-verilog

$num[31:0] = $reset ? 1 : (>>1$num + >>2$num);

```
The generated block diagram and waveforms are shown below:

<img width="323" alt="d3_10" src="https://github.com/user-attachments/assets/fe64a7b9-e04a-4b35-a710-489245398cc2">

<img width="1440" alt="Screenshot 2024-08-19 at 10 55 46 PM" src="https://github.com/user-attachments/assets/70f3befc-7fff-48fc-8458-a5cc00aefe46">


#### 2. Counter Series:

Code is given below:

```tl-verilog

$cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);

```
The generated block diagram and waveforms are shown below:

![d3_11](https://github.com/user-attachments/assets/86e41f88-23a0-41a9-beda-88066ce08588)

<img width="1439" alt="Screenshot 2024-08-19 at 10 57 11 PM" src="https://github.com/user-attachments/assets/0da1f14c-f56c-458a-ad53-044222bfe0bf">

#### 3.Sequential Calculator:

- Similar to previous combinational calculator but mimics real scenario in which the result of the previous operation is considered as one of the input for the next operation. Upon reset the result becomes zero.

Code is given below:
```tl-verilog

   $val1[31:0] = >>2$out;
   $val2[31:0] = $rand2[3:0];

   $sum[31:0]  = $val1[31:0] + $val2[31:0];
   $diff[31:0] = $val1[31:0] - $val2[31:0];
   $prod[31:0] = $val1[31:0] * $val2[31:0];
   $quot[31:0] = $val1[31:0] / $val2[31:0];

   $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                ($sel[1:0] == 2'b01) ? $diff[31:0]:
                ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                       $quot[31:0];
   
   $out[31:0] = $reset ? 32'h0 : $nxt;

```
The generated block diagram and waveforms are as shown:

![d3_14](https://github.com/user-attachments/assets/16422daa-a746-49b0-aee5-dd83259cb1c0)

![d3_13](https://github.com/user-attachments/assets/80e3e1fb-fd32-4e14-b228-000960b783b8)

### Pipelined Logic:
---

In Transaction-Level Verilog (TL-Verilog), pipelined logic is efficiently expressed using pipeline constructs that represent data flow across design stages, each corresponding to a clock cycle. This approach simplifies the modeling of sequential logic by automatically handling state propagation and enabling clear, concise descriptions of complex, multi-stage operations, improving both design clarity and maintainability.

#### 1. Recereating the design:

<img width="727" alt="Screenshot 2024-08-19 at 11 04 18 PM" src="https://github.com/user-attachments/assets/ffb5924f-b071-4e01-aaf6-d8ce569499ef">

Code is given below:
```tl-verilog
|pipe
  @1
    $err1 = $bad_input || $illegal_op;
  @3
    $err2 = $over_flow || $err1;
  @6
    $err3 = $div_by_zero || $err2;
```
The generated block diagram and waveforms are as shown:

<img width="1440" alt="Screenshot 2024-08-19 at 11 08 42 PM" src="https://github.com/user-attachments/assets/9835e32b-a376-4364-b3c9-d31fad051557">

So you can observe that the given design of pipeline and the recreated design are same.

#### 2. Pipelined Calculator:

- Similar to previous Sequential Calculator but with a pipelined design and using ```$valid``` inorder to clear alternate values.

Code is given below:
```tl-verilog
   |cal
      @1
         $reset = *reset;
         $clk_kar = *clk;

         $valid[31:0] = $reset ? 0 : (>>1$valid + 1);
         $valid_or_reset = $reset | ~$valid;
         
         $val1[31:0] = >>2$out;
         $val2[31:0] = $rand2[3:0];

         $sum[31:0]  = $val1[31:0] + $val2[31:0];
         $diff[31:0] = $val1[31:0] - $val2[31:0];
         $prod[31:0] = $val1[31:0] * $val2[31:0];
         $quot[31:0] = $val1[31:0] / $val2[31:0];
         
      @2
         $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                      ($sel[1:0] == 2'b01) ? $diff[31:0]:
                      ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                             $quot[31:0];
        
         
         $out[31:0] = $valid_or_reset ? 32'h0 : $nxt;
         
   
```
The generated block diagram and waveforms are as shown:

<img width="399" alt="Screenshot 2024-08-19 at 11 12 36 PM" src="https://github.com/user-attachments/assets/00fac17d-6f81-47e1-97a3-946ffaac0ce8">

<img width="1440" alt="Screenshot 2024-08-20 at 8 17 46 PM" src="https://github.com/user-attachments/assets/a793a04d-553a-4646-a02d-9349776cfdee">

#### 3. Cycle Calculator with validity:

- we add ```$valid_or_reset = $valid | $reset;``` as a when condition for calculation instead of zeroing ```$out```.

Code is given below:

```tl-verilog

   $reset = *reset;
   $clk_kar = *clk;
   
   |cal
      @1
         $reset = *reset;
         $clk_kar = *clk;
         
         $cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);
         $valid = $cnt;
         $valid_or_reset = ($reset | $valid);
         
      
      ?$valid
         @1
            $val1[31:0] = >>2$out;
            $val2[31:0] = $rand2[3:0];
            
            $sum[31:0]  = $val1[31:0] + $val2[31:0];
            $diff[31:0] = $val1[31:0] - $val2[31:0];
            $prod[31:0] = $val1[31:0] * $val2[31:0];
            $quot[31:0] = $val1[31:0] / $val2[31:0];
            
         @2
            $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                         ($sel[1:0] == 2'b01) ? $diff[31:0]:
                         ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                                $quot[31:0];
            
            $out[31:0] = $valid_or_reset ? 32'h0 : $nxt;
            
            
            
            
            
```

The generated block diagram and waveforms are as shown:

<img width="1439" alt="Screenshot 2024-08-20 at 8 11 41 PM" src="https://github.com/user-attachments/assets/673d049c-2bc6-41b1-aa17-f90b50a02737">



### References:
- [MYTH Workshop 2 TLV](https://drive.google.com/file/d/1ZcjLzg-53It4CO3jDLofiUPZJ485JZ_g/view)
- [GitHub](https://github.com/stevehoover/RISC-V_MYTH_Workshop?tab=readme-ov-file)

</details>

<details>
<summary><strong>Day4</strong></summary>

## Basic RISC-V CPU Micro-architecture

- This section will cover the implementation of a simple 3-stage RISC-V Core / CPU.
- The 3-stages broadly are: Fetch, Decode and Execute.
- The figure shown below is the basic block diagram of the CPU core:

<img width="536" alt="Screenshot 2024-08-21 at 2 29 38 AM" src="https://github.com/user-attachments/assets/34e0b4d5-31ab-4164-b572-6271da8ee3d0">

- **Implementation plan:**

<img width="644" alt="Screenshot 2024-08-21 at 2 30 44 AM" src="https://github.com/user-attachments/assets/6fbfd24b-e30c-488c-b25a-a3839d2b169e">

  
### 1. Program Counter

Program Counter, also called as Instruction Pointer is a block which contains the address of the next instruction to be executed. The program counter is supposed to increase its value by 4 to fetch the next instruction from the memory.In case a reset is triggered the program counter will be re initialised to zero for the next instruction and then it continues.


The following diagram explains the working of the program counter

<img width="626" alt="Screenshot 2024-08-21 at 2 35 15 AM" src="https://github.com/user-attachments/assets/e2453cd8-497e-41bf-ba5c-072eac517218">


The following is the code for the working of the program counter

```tl-verilog
$pc[31:0] = >>1$reset ? 0 : ( >>1$pc + 31'h4 );
```
We get the following output after executing the code:-

<img width="1439" alt="Screenshot 2024-08-21 at 3 31 32 AM" src="https://github.com/user-attachments/assets/d6a8b46e-2ccd-4098-8331-c25b0fcb30d3">


### 2. Adding the instruction memory

<img width="613" alt="Screenshot 2024-08-21 at 2 37 29 AM" src="https://github.com/user-attachments/assets/0352140c-a4e9-4e80-a391-7d7388b96abc">

- PC output is feed to the instruction memory, which in turn gives out the instruction to be executed.
- The program counter is incremented by 4, every valid iteration.
- The output of the program counter is used for fetching an instruction from the instruction memory.
- The instruction memory gives out a 32-bit instruction depending upon the input address.
- During Fetch Stage, processor fetches the instruction from the IM pointed by address given by PC.

<img width="250" alt="Screenshot 2024-08-21 at 2 38 00 AM" src="https://github.com/user-attachments/assets/4c29565a-993a-4bc8-9dad-ca400c096dff">

The following is the code for the instruction memory

```tl-verilog
$imem_rd_en = >>1$reset ? 0 : 1;
$imem_rd_addr[31:0] = $pc[M4_IMEM_INDEX_CNT+1:2];
$instr[31:0] = $imem_rd_data[31:0];
```

We get the following output after executing the code:-

<img width="1440" alt="Screenshot 2024-08-21 at 3 30 11 AM" src="https://github.com/user-attachments/assets/2d7ec324-740f-4130-ad61-e5e59e2f4669">


### 3. Decoding the instruction

<img width="639" alt="Screenshot 2024-08-21 at 2 40 54 AM" src="https://github.com/user-attachments/assets/2bc79bfe-2774-4b34-9463-ee401dfb5e51">

- The 32-bit fetched instruction has to be decoded first to determine the operation to be performed and the source / destination address.
- There are 6 types of Instructions namely,
   - R-type - Register
   - I-type - Immediate
   - S-type - Store
   - B-type - Branch (Conditional Jump)
   - U-type - Upper Immediate
   - J-type - Jump (Unconditional Jump)
- Instruction Format includes Opcode, immediate value, source address, destination address.
- During Decode Stage, processor decodes the instruction based on instruction format and type of instruction.
- Generally, RISC-V ISA provides 32 Register each of width = XLEN (for example, XLEN = 32 for RV32).
- Here, the register file used allows 2 - reads and 1 - write simultaneously.

<img width="672" alt="Screenshot 2024-08-21 at 2 42 01 AM" src="https://github.com/user-attachments/assets/16a7daf5-c03d-4b1d-8fd9-13fd76239b9e">

We have decoded the above instructions on the basis of all the 6 types of RISC V instruction set. The code for decoding is as follows:-

```tl-verilog
$is_i_instr = $instr[6:2] ==? 5'b0000x ||
              $instr[6:2] ==? 5'b001x0 ||
              $instr[6:2] ==? 5'b11001;
$is_r_instr = $instr[6:2] ==? 5'b01011 ||
              $instr[6:2] ==? 5'b011x0 ||
              $instr[6:2] ==? 5'b10100;
$is_s_instr = $instr[6:2] ==? 5'b0100x;
$is_b_instr = $instr[6:2] ==? 5'b11000;
$is_j_instr = $instr[6:2] ==? 5'b11011;
$is_u_instr = $instr[6:2] ==? 5'b0x101;
```

We get the following output after executing the code:-

<img width="1440" alt="Screenshot 2024-08-21 at 3 29 08 AM" src="https://github.com/user-attachments/assets/57fc8b2e-7d20-414e-bd32-f05d135fccbd">


### 3a. Immediate Decode Logic

a.<img width="661" alt="Screenshot 2024-08-21 at 2 43 15 AM" src="https://github.com/user-attachments/assets/832acd74-85d0-45f8-b7d4-93bba21faba7">

b.<img width="606" alt="Screenshot 2024-08-21 at 2 43 29 AM" src="https://github.com/user-attachments/assets/53e45a9e-c913-477f-8fcc-83a24e01e7ba">

The above instruction sets have an immediate field. In order to decode this field we use the following code:-

```tl-verilog
$imm[31:0] = $is_i_instr ? {{21{$instr[31]}}, $instr[30:20]} :
             $is_s_instr ? {{21{$instr[31]}}, $instr[30:25], $instr[11:7]} :
             $is_b_instr ? {{20{$instr[31]}}, $instr[7], $instr[30:25], $instr[11:8], 1'b0} :
             $is_u_instr ? {$instr[31:12], 12'b0} :
             $is_j_instr ? {{12{$instr[31]}}, $instr[19:12], $instr[20], $instr[30:21], 1'b0} : 32'b0;
```


<img width="1440" alt="Screenshot 2024-08-21 at 3 27 30 AM" src="https://github.com/user-attachments/assets/86a37f9f-5c69-40b8-8d2a-3c6515fcad1e">


### 3b. Decode logic for other fields like rs1,rs2,func3,func7

Apart from the immediate we have other fields which also need to be decoded. The code for the same is as follows:-

```tl-verilog
         $rs2_valid = $is_r_instr || $is_s_instr || $is_b_instr;
         ?$rs2_valid
            $rs2[4:0] = $instr[24:20];
            
         $rs1_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         ?$rs1_valid
            $rs1[4:0] = $instr[19:15];
         
         $funct3_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         ?$funct3_valid
            $funct3[2:0] = $instr[14:12];
            
         $funct7_valid = $is_r_instr ;
         ?$funct7_valid
            $funct7[6:0] = $instr[31:25];
            
         $rd_valid = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
         ?$rd_valid
            $rd[4:0] = $instr[11:7];

         $opcode[6:0] = $instr[6:0];
```

At any given time, only one instruction is decoded, which could belong to any of the six instruction types. Therefore, it's essential to validate the instruction to ensure it fits into its specific category, preventing conflicts between different instruction types.

<img width="1440" alt="Screenshot 2024-08-21 at 3 25 15 AM" src="https://github.com/user-attachments/assets/971198b3-aa24-400e-92dc-fa9f60c7fbf2">


### 3c. Decoding Individual Instructions

<img width="451" alt="Screenshot 2024-08-21 at 2 48 25 AM" src="https://github.com/user-attachments/assets/64ec1d71-d805-4f2d-bb6c-75f7e945d262">

In order to decode the above circled individual instructions use the following code

```tl-verilog
$dec_bits [10:0] = {$funct7[5], $funct3, $opcode};
$is_beq = $dec_bits ==? 11'bx_000_1100011;
$is_bne = $dec_bits ==? 11'bx_001_1100011;
$is_blt = $dec_bits ==? 11'bx_100_1100011;
$is_bge = $dec_bits ==? 11'bx_101_1100011;
$is_bltu = $dec_bits ==? 11'bx_110_1100011;
$is_bgeu = $dec_bits ==? 11'bx_111_1100011;
$is_addi = $dec_bits ==? 11'bx_000_0010011;
$is_add = $dec_bits ==? 11'b0_000_0110011;
```

We also need to update the program counter to account for branch instructions.

```tl-verilog
$pc[31:0] = >>1$reset ? 32'b0 :
            >>1$taken_branch ? >>1$br_target_pc :
            >>1$pc + 32'd4;
```


The output for the above code is as follows:-

<img width="1430" alt="Screenshot 2024-08-21 at 3 23 45 AM" src="https://github.com/user-attachments/assets/3a2784fd-bc31-4f2d-939d-8c58345008a6">


### 4. Register File Read and Enable

<img width="604" alt="Screenshot 2024-08-21 at 2 50 51 AM" src="https://github.com/user-attachments/assets/6f36089a-3922-4385-b561-1fbbc7eaaec3">

Here, instructions are read from the instruction memory and stored in registers. We have two register slots that read the instructions, and these stored instructions are then sent to the ALU for processing.

The code is as follows:-

```tl-verilog

$rf_rd_en1 = $rs1_valid;
$rf_rd_en2 = $rs2_valid;
$rf_rd_index1[4:0] = $rs1;
$rf_rd_index2[4:0] = $rs2;
$src1_value[31:0] = $rf_rd_data1;
$src2_value[31:0] = $rf_rd_data2;
```

The output for the code is as follows:-

<img width="1440" alt="Screenshot 2024-08-21 at 3 18 40 AM" src="https://github.com/user-attachments/assets/1c7e86ee-ac9d-4fb3-936b-5e07c931ac97">

### 5. Arithmetic and Logic Unit

<img width="603" alt="Screenshot 2024-08-21 at 2 51 56 AM" src="https://github.com/user-attachments/assets/dbec9e58-e4e5-4edf-ad27-a5052bb105f7">

Used to perform arithmetic operations on the values stored in the registers. The code for the same is as follows:-

```tl-verilog

$result[31:0] = $is_addi ? $src1_value + $imm :
                $is_add ? $src1_value + $src2_value :
                32'bx ;

```

In this section, we have implemented the code to account for ```addi``` and ```add``` operations.

<img width="1440" alt="Screenshot 2024-08-21 at 11 53 07 AM" src="https://github.com/user-attachments/assets/c0604b13-3f92-4747-92d7-4a2d41f249bf">

### 6. Register File Write

<img width="621" alt="Screenshot 2024-08-21 at 2 53 26 AM" src="https://github.com/user-attachments/assets/32a6160e-9c83-40a2-b015-69faf34d18be">


After the ALU performs operations on the values stored in the registers, we may need to write these values back into the registers. For this, we use the register file write. We must also ensure that no values are written to the destination register if it is x0, as it is always meant to remain 0. The code is as follows:

```tl-verilog
$rf_wr_en = $rd_valid && $rd != 5'b0;
$rf_wr_index[4:0] = $rd;
$rf_wr_data[31:0] = $result;
```
The output for the code is as follows:-

<img width="1440" alt="Screenshot 2024-08-21 at 3 11 56 AM" src="https://github.com/user-attachments/assets/849779bd-493b-40ec-8ce2-8265ab0be8ac">


### 7. Branch instructions

<img width="559" alt="Screenshot 2024-08-21 at 2 55 26 AM" src="https://github.com/user-attachments/assets/f65a4952-c6fb-4ea9-9f53-d6bdccb26215">

Based on the control input we may need to jump to some different address after a particular instruction based on some condition generated during run-time. This is when we use the branch instructions. The code is as follows:-

```bash

$taken_branch = $is_beq ? ($src1_value == $src2_value):
                $is_bne ? ($src1_value != $src2_value):
                $is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])):
                $is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])):
                $is_bltu ? ($src1_value < $src2_value):
                $is_bgeu ? ($src1_value >= $src2_value):1'b0;

$br_target_pc[31:0] = $pc +$imm;

```
The output is as follows:-

<img width="1440" alt="Screenshot 2024-08-21 at 3 07 58 AM" src="https://github.com/user-attachments/assets/45a95893-9f3e-41c4-a6db-96fe23b16615">




### Testbench
In order to check whether the code written is correct or not we verify it using the testbench for the 1st five cycles

```bash
*passed = |cpu/xreg[14]>>5$value == (1+2+3+4+5+6+7+8+9+10) ;
```
Upon checking the log file we get the following result

<img width="629" alt="Screenshot 2024-08-21 at 3 02 56 AM" src="https://github.com/user-attachments/assets/6a07e437-53bd-4f21-a7cd-b33d4f34fada">

### Observations:

**CLK:**

<img width="1440" alt="Screenshot 2024-08-21 at 1 31 18 PM" src="https://github.com/user-attachments/assets/6d0f6c9c-385c-4633-a043-4ead6817ab39">

**Reset:**

<img width="1440" alt="Screenshot 2024-08-21 at 1 32 01 PM" src="https://github.com/user-attachments/assets/61eed547-e223-41af-8c61-8eb90c9039d4">

**Waveforms showing output's gradual addition from 1 to 10 ;that is from 0(h00) to 55(h37):**

<img width="843" alt="Screenshot 2024-08-21 at 11 58 58 PM" src="https://github.com/user-attachments/assets/adfdbe8e-e782-48cc-8a8c-8c69cf1c307a">


</details>
<details>
<summary><strong>Day5</strong></summary>

## Pipelining the CPU:

Now pipelining of the CPU core is done below, which allows easy retiming and reduces functional bug to a great extent . For pipelining we simply need to add @1, @2 and so on. In TL verilog, another advantage is defining of pipeline in systematic order is not necessary. Pipelining introduces hazards, notably the "branch instruction hazard," or "branch penalty." This occurs because branch instructions determine execution sequence changes, creating uncertainties. Hazards include:

1. **Structural Hazards:** Resource conflicts like shared execution units, causing pipeline stalls until resolved.
   
2. **Data Hazards:** Dependencies on previous instruction results, risking incorrect outcomes if data isn't ready.

3. **Control Hazards (Branch Hazards):** Uncertainty over branch outcomes delays confirmation until execution, potentially leading to incorrect instruction fetches and performance penalties due to pipeline flushing.

### Valid signal for Pipelined Logic:

The TL-Verilog code to introduce valid signal for pipelined logic is given below :
```
$start = >>1$reset && !$reset;
$valid = $reset ? 1'b0 : ($start || >>3$valid);
$valid_or_reset = $valid || $reset;
$rs1_or_funct3_valid    = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
$rs2_valid              = $is_r_instr || $is_s_instr || $is_b_instr;
$rd_valid               = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
$funct7_valid           = $is_r_instr;
         
```

### Handling Data Hazards in Register File with Bypassing:

```
$src1_value[31:0] = $rs1_bypass ? >>1$result[31:0] : $rf_rd_data1[31:0];
$src2_value[31:0] = $rs2_bypass ? >>1$result[31:0] : $rf_rd_data2[31:0];
```

### Correcting branch target path:

```
   //Current instruction is valid if one of the previous 2 instructions were not (taken_branch or load or jump)
   $valid = ~(>>1$valid_taken_br || >>2$valid_taken_br || >>1$is_load || >>2$is_load || >>2$jump_valid 	|| >>1$jump_valid);
         
   //Current instruction is valid & is a taken branch
   $valid_taken_br = $valid && $taken_br;
         
   //Current instruction is valid & is a load
   $valid_load = $valid && $is_load;
         
   //Current instruction is valid & is jump
   $jump_valid = $valid && $is_jump;
   $jal_valid  = $valid && $is_jal;
   $jalr_valid = $valid && $is_jalr;
    
    *passed = |cpu/xreg[14]>>5$value == (1+2+3+4+5+6+7+8+9+10);

```
### Final 5 Stage Pipelined Logic:

```
\m4_TLV_version 1d: tl-x.org
\SV
   // Template code can be found in: https://github.com/stevehoover/RISC-V_MYTH_Workshop
   
   m4_include_lib(['https://raw.githubusercontent.com/BalaDhinesh/RISC-V_MYTH_Workshop/master/tlv_lib/risc-v_shell_lib.tlv'])

\SV
   m4_makerchip_module   // (Expanded in Nav-TLV pane.)
\TLV

   // /====================\
   // | Sum 0 to 10 Program |
   // \====================/
   //
   // Add 0,1,2,3,...,10 (in that order).
   //
   // Regs:
   //  r10 (a0): In: 0, Out: final sum
   //  r12 (a2): 10
   //  r13 (a3): 1..10
   //  r14 (a4): Sum
   // 
   // External to function:
   m4_asm(ADD, r10, r0, r0)             // Initialize r10 (a0) to 0.
   // Function:
   m4_asm(ADD, r14, r10, r0)            // Initialize sum register a4 with 0x0
   m4_asm(ADDI, r12, r10, 1011)         // Store count of 10 in register a2.
   m4_asm(ADD, r13, r10, r0)            // Initialize intermediate sum register a3 with 0
   // Loop:
   m4_asm(ADD, r14, r13, r14)           // Incremental addition
   m4_asm(ADDI, r13, r13, 1)            // Increment intermediate register by 1
   m4_asm(BLT, r13, r12, 1111111111000) // If a3 is less than a2, branch to label named <loop>
   m4_asm(ADD, r10, r14, r0)            // Store final result to register a0 so that it can be read by main program
   m4_asm(SW, r0, r10, 10000)           // Store r10 result in dmem
   m4_asm(LW, r17, r0, 10000)           // Load contents of dmem to r17
   m4_asm(JAL, r7, 00000000000000000000) // Done. Jump to itself (infinite loop). (Up to 20-bit signed immediate plus implicit 0 bit (unlike JALR) provides byte address; last immediate bit should also be 0)
   m4_define_hier(['M4_IMEM'], M4_NUM_INSTRS)

   |cpu
      @0
         $reset = *reset;
         $clk_kar = *clk;
         
         //PC fetch - branch, jumps and loads introduce 2 cycle bubbles in this pipeline
         $pc[31:0] = >>1$reset ? '0 : (>>3$valid_taken_br ? >>3$br_tgt_pc :
                                       >>3$valid_load     ? >>3$inc_pc[31:0] :
                                       >>3$jal_valid      ? >>3$br_tgt_pc :
                                       >>3$jalr_valid     ? >>3$jalr_tgt_pc :
                                                     (>>1$inc_pc[31:0]));
         // Access instruction memory using PC
         $imem_rd_en = ~ $reset;
         $imem_rd_addr[31:0] = $pc[M4_IMEM_INDEX_CNT+1:2];
         
         
      @1
         //Getting instruction from IMem
         $instr[31:0] = $imem_rd_data[31:0];
         
         //Increment PC
         $inc_pc[31:0] = $pc[31:0] + 32'h4;
         
         //Decoding I,R,S,U,B,J type of instructions based on opcode [6:0]
         //Only [6:2] is used here because this implementation is for RV64I which does not use [1:0]
         $is_i_instr = $instr[6:2] ==? 5'b0000x ||
                       $instr[6:2] ==? 5'b001x0 ||
                       $instr[6:2] == 5'b11001;
         
         $is_r_instr = $instr[6:2] == 5'b01011 ||
                       $instr[6:2] ==? 5'b011x0 ||
                       $instr[6:2] == 5'b10100;
         
         $is_s_instr = $instr[6:2] ==? 5'b0100x;
         
         $is_u_instr = $instr[6:2] ==? 5'b0x101;
         
         $is_b_instr = $instr[6:2] == 5'b11000;
         
         $is_j_instr = $instr[6:2] == 5'b11011;
         
         //Immediate value decode
         $imm[31:0] = $is_i_instr ? { {21{$instr[31]}} , $instr[30:20]} :
                      $is_s_instr ? { {21{$instr[31]}} , $instr[30:25] , $instr[11:8] , $instr[7]} :
                      $is_b_instr ? { {20{$instr[31]}} , $instr[7] , $instr[30:25] , $instr[11:8] , 1'b0} :
                      $is_u_instr ? { $instr[31] , $instr[30:12] , { 12{1'b0}} } :
                      $is_j_instr ? { {12{$instr[31]}} , $instr[19:12] , $instr[20] , $instr[30:21] , 1'b0} :
                      >>1$imm[31:0];
         
         //Generate valid signals for each instruction fields
         $rs1_or_funct3_valid    = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         $rs2_valid              = $is_r_instr || $is_s_instr || $is_b_instr;
         $rd_valid               = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
         $funct7_valid           = $is_r_instr;
         
         //Decode other fields of instruction - source and destination registers, funct, opcode
         ?$rs1_or_funct3_valid
            $rs1[4:0]    = $instr[19:15];
            $funct3[2:0] = $instr[14:12];
         
         ?$rs2_valid
            $rs2[4:0]    = $instr[24:20];
         
         ?$rd_valid
            $rd[4:0]     = $instr[11:7];
         
         ?$funct7_valid
            $funct7[6:0] = $instr[31:25];
         
         $opcode[6:0] = $instr[6:0];
         
         //Decode instruction in subset of base instruction set based on RISC-V 32I
         $dec_bits[10:0] = {$funct7[5],$funct3,$opcode};
         
         //Branch instructions
         $is_beq   = $dec_bits ==? 11'bx_000_1100011;
         $is_bne   = $dec_bits ==? 11'bx_001_1100011;
         $is_blt   = $dec_bits ==? 11'bx_100_1100011;
         $is_bge   = $dec_bits ==? 11'bx_101_1100011;
         $is_bltu  = $dec_bits ==? 11'bx_110_1100011;
         $is_bgeu  = $dec_bits ==? 11'bx_111_1100011;
         
         //Jump instructions
         $is_auipc = $dec_bits ==? 11'bx_xxx_0010111;
         $is_jal   = $dec_bits ==? 11'bx_xxx_1101111;
         $is_jalr  = $dec_bits ==? 11'bx_000_1100111;
         
         //Arithmetic instructions
         $is_addi  = $dec_bits ==? 11'bx_000_0010011;
         $is_add   = $dec_bits ==? 11'b0_000_0110011;
         $is_lui   = $dec_bits ==? 11'bx_xxx_0110111;
         $is_slti  = $dec_bits ==? 11'bx_010_0010011;
         $is_sltiu = $dec_bits ==? 11'bx_011_0010011;
         $is_xori  = $dec_bits ==? 11'bx_100_0010011;
         $is_ori   = $dec_bits ==? 11'bx_110_0010011;
         $is_andi  = $dec_bits ==? 11'bx_111_0010011;
         $is_slli  = $dec_bits ==? 11'b0_001_0010011;
         $is_srli  = $dec_bits ==? 11'b0_101_0010011;
         $is_srai  = $dec_bits ==? 11'b1_101_0010011;
         $is_sub   = $dec_bits ==? 11'b1_000_0110011;
         $is_sll   = $dec_bits ==? 11'b0_001_0110011;
         $is_slt   = $dec_bits ==? 11'b0_010_0110011;
         $is_sltu  = $dec_bits ==? 11'b0_011_0110011;
         $is_xor   = $dec_bits ==? 11'b0_100_0110011;
         $is_srl   = $dec_bits ==? 11'b0_101_0110011;
         $is_sra   = $dec_bits ==? 11'b1_101_0110011;
         $is_or    = $dec_bits ==? 11'b0_110_0110011;
         $is_and   = $dec_bits ==? 11'b0_111_0110011;
         
         //Store instructions
         $is_sb    = $dec_bits ==? 11'bx_000_0100011;
         $is_sh    = $dec_bits ==? 11'bx_001_0100011;
         $is_sw    = $dec_bits ==? 11'bx_010_0100011;
         
         //Load instructions - support only 4 byte load
         $is_load  = $dec_bits ==? 11'bx_xxx_0000011;
         
         $is_jump = $is_jal || $is_jalr;
         
      @2
         //Get Source register values from reg file
         $rf_rd_en1 = $rs1_or_funct3_valid;
         $rf_rd_en2 = $rs2_valid;
         
         $rf_rd_index1[4:0] = $rs1[4:0];
         $rf_rd_index2[4:0] = $rs2[4:0];
         
         //Register file bypass logic - data forwarding from ALU to resolve RAW dependence
         $src1_value[31:0] = $rs1_bypass ? >>1$result[31:0] : $rf_rd_data1[31:0];
         $src2_value[31:0] = $rs2_bypass ? >>1$result[31:0] : $rf_rd_data2[31:0];
         
         //Branch target PC computation for branches and JAL
         $br_tgt_pc[31:0] = $imm[31:0] + $pc[31:0];
         
         $rs1_bypass = >>1$rf_wr_en && (>>1$rd == $rs1);
         $rs2_bypass = >>1$rf_wr_en && (>>1$rd == $rs2);
         
      @3
         //ALU implementation
         $result[31:0] = $is_addi  ? $src1_value +  $imm :
                         $is_add   ? $src1_value +  $src2_value :
                         $is_andi  ? $src1_value &  $imm :
                         $is_ori   ? $src1_value |  $imm :
                         $is_xori  ? $src1_value ^  $imm :
                         $is_slli  ? $src1_value << $imm[5:0]:
                         $is_srli  ? $src1_value >> $imm[5:0]:
                         $is_and   ? $src1_value &  $src2_value:
                         $is_or    ? $src1_value |  $src2_value:
                         $is_xor   ? $src1_value ^  $src2_value:
                         $is_sub   ? $src1_value -  $src2_value:
                         $is_sll   ? $src1_value << $src2_value:
                         $is_srl   ? $src1_value >> $src2_value:
                         $is_sltu  ? $sltu_rslt[31:0]:
                         $is_sltiu ? $sltiu_rslt[31:0]:
                         $is_lui   ? {$imm[31:12], 12'b0}:
                         $is_auipc ? $pc + $imm:
                         $is_jal   ? $pc + 4:
                         $is_jalr  ? $pc + 4:
                         $is_srai  ? ({ {32{$src1_value[31]}} , $src1_value} >> $imm[4:0]) :
                         $is_slt   ? (($src1_value[31] == $src2_value[31]) ? $sltu_rslt : {31'b0, $src1_value[31]}):
                         $is_slti  ? (($src1_value[31] == $imm[31]) ? $sltiu_rslt : {31'b0, $src1_value[31]}) :
                         $is_sra   ? ({ {32{$src1_value[31]}}, $src1_value} >> $src2_value[4:0]) :
                         $is_load  ? $src1_value +  $imm :
                         $is_s_instr ? $src1_value + $imm :
                                    32'bx;
         
         $sltu_rslt[31:0]  = $src1_value <  $src2_value;
         $sltiu_rslt[31:0] = $src1_value <  $imm;
         
         //Jump instruction target PC computation
         $jalr_tgt_pc[31:0] = $imm[31:0] + $src1_value[31:0]; 
         
         //Branch equations
         $taken_br = $is_beq ? ($src1_value == $src2_value) :
                     $is_bne ? ($src1_value != $src2_value) :
                     $is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bltu ? ($src1_value < $src2_value) :
                     $is_bgeu ? ($src1_value >= $src2_value) :
                     1'b0;
         
         $valid = ~(>>1$valid_taken_br || >>2$valid_taken_br || >>1$is_load || >>2$is_load || >>2$jump_valid || >>1$jump_valid);
         
         //Current instruction is valid & is a taken branch
         $valid_taken_br = $valid && $taken_br;
         
         //Current instruction is valid & is a load
         $valid_load = $valid && $is_load;
         
         //Current instruction is valid & is jump
         $jump_valid = $valid && $is_jump;
         $jal_valid  = $valid && $is_jal;
         $jalr_valid = $valid && $is_jalr;
         
         //Destination register update - ALU result or load result depending on instruction
         $rf_wr_en = (($rd != '0) && $rd_valid && $valid) || >>2$valid_load;
         $rf_wr_index[4:0] = $valid ? $rd[4:0] : >>2$rd[4:0];
         $rf_wr_data[31:0] = $valid ? $result[31:0] : >>2$ld_data[31:0];
         
      @4
         //Data memory access for load, store
         $dmem_addr[3:0]     =  $result[5:2];
         $dmem_wr_en         =  $valid && $is_s_instr;
         $dmem_wr_data[31:0] =  $src2_value[31:0];
         $dmem_rd_en         =  $valid_load;
         
         //Write back data read from load instruction to register
         $ld_data[31:0]      =  $dmem_rd_data[31:0];
         
      
   *passed = |cpu/xreg[14]>>10$value == (1+2+3+4+5+6+7+8+9+10);
   //Run for 80 cycles without any checks
   *passed = *cyc_cnt > 80;
   *failed = 1'b0;
   
   // Macro instantiations for:
   //  o instruction memory
   //  o register file
   //  o data memory
   //  o CPU visualization
   |cpu
      m4+imem(@1)    // Args: (read stage)
      m4+rf(@2, @3)  // Args: (read stage, write stage) - if equal, no register bypass is required
      m4+dmem(@4)    // Args: (read/write stage)
   
   m4+cpu_viz(@4)    // For visualisation, argument should be at least equal to the last stage of CPU logic
                       // @4 would work for all labs
\SV
   endmodule
```

**Block diagram:**

<img width="556" alt="Screenshot 2024-08-22 at 12 14 00 AM" src="https://github.com/user-attachments/assets/b53d0cf0-016b-4c30-89b1-c586208863c3">

### Waveforms:

**CLK:**

<img width="678" alt="Screenshot 2024-08-21 at 11 51 47 PM" src="https://github.com/user-attachments/assets/62515060-da2a-4e99-a9c4-8036a8a29977">

**Reset:**

<img width="682" alt="Screenshot 2024-08-21 at 11 54 30 PM" src="https://github.com/user-attachments/assets/b60aa531-eb67-4906-bf2d-c24a3aa796e9">

**Gradual increment of output from 0(h00) to 55(h37):**

<img width="843" alt="Screenshot 2024-08-21 at 11 58 58 PM" src="https://github.com/user-attachments/assets/adfdbe8e-e782-48cc-8a8c-8c69cf1c307a">

**VIZ table:**

You can see that the value of reg 10 and reg 14 will reach to 55 after 64 cycles.

<img width="843" alt="Screenshot 2024-08-22 at 12 15 25 AM" src="https://github.com/user-attachments/assets/55cf2ca7-ff9b-41f9-9d57-e9386cf117e0">

**Simulation status:**

<img width="547" alt="Screenshot 2024-08-22 at 12 18 38 AM" src="https://github.com/user-attachments/assets/7ba653b5-744c-4151-8f0c-9fa751949f8b">




</details>
</details>

<details>
<summary><strong>Lab Session 7:</strong> Comparision of GTK wave output and Makerchip output</summary>

## Comparision of RISC-V Pre-Synthesis Simulation outputs using Iverilog GTKwave and Makerchip

The RISC-V processor was designed using TL-Verilog in the Makerchip IDE. To implement it on an FPGA, it needs to be converted to Verilog, which was done using the Sandpiper-SaaS compiler. Pre-synthesis simulations were then performed using the GTKWave simulator.

**Step-by-Step process of simulation:**

1. Run these set of commands to set up a development environment for working with simulation and synthesis tools, for tasks involving Verilog and RISC-V.

``` bash
$ sudo apt install make python python3 python3-pip git iverilog gtkwave

$ cd ~

$ sudo apt-get install python3-venv

$ python3 -m venv .venv

$ source ~/.venv/bin/activate

$ pip3 install pyyaml click sandpiper-saas
```

![image](https://github.com/user-attachments/assets/a22edab5-6c59-4e98-bac6-bb59c89a5234)


2. In order to install the Required Packages run these set of commands in virtual environment:
   
```bash
$ sudo apt install make python python3 python3-pip git iverilog gtkwave docker.io

$ sudo chmod 666 /var/run/docker.sock

$ cd ~

$ pip3 install pyyaml click sandpiper-saas

```
![image](https://github.com/user-attachments/assets/c2851530-1ddb-494e-8dda-accb4d7d0df7)


3. Now we can clone the following repository in home directory and make a ```pre_synth_sim``` directory which will contain output:

```bash
$ cd ~

$ git clone https://github.com/manili/VSDBabySoC.git

$ cd /home/vsduser/VSDBabySoC

$ make pre_synth_sim

```

![image](https://github.com/user-attachments/assets/36e4b6d9-fdad-43cb-a7c0-696abeeecad7)



4. Replace the ```rvmyth.tlv``` file in the VSDBabySoC/src/module folder with our RISC-V design from makerchip ```.tlv``` file which we want to convert into verilog and also change the testbench according to our makerchip code.

5. Inorder to get verilog code of our TLV code ie, to translate .tlv definition of RISC-V into .v definition use the following code.

```bash
$ sandpiper-saas -i ./src/module/rvmyth.tlv -o rvmyth.v --bestsv --noline -p verilog --outdir ./src/module/
```
![image](https://github.com/user-attachments/assets/abfa2d5b-9db8-4ddb-954c-6e248e450576)

6. Now to compile and simulate RISC-V design run the following code.
   
```bash
$ iverilog -o output/pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module
```

6. The result of the simulation (i.e. pre_synth_sim.vcd) will be stored in the output/pre_synth_sim directory.
```bash
$ cd output

$ ./pre_synth_sim.out
```
![image](https://github.com/user-attachments/assets/929c392e-aa09-4420-ac4f-6a3c2b04ba8a)


 7. To open the .vcd simulation file through GTKWave simulation tool
    
```bash
$ gtkwave pre_synth_sim.vcd
```

**Pre-synthesis Simulation results:**
Signals to plot are the following:
- clk_kar: This is the clock input to the RISC-V core. 
- reset: This is the input reset signal to the RISC-V core. 
- OUT[9:0]: This is the 10-bit output [9:0] OUT port of the RISC-V core. This port comes from the RISC-V register #14, originally.

**GTKWave Simulation waveforms:**

- clk_kar plot:
  
  ![image](https://github.com/user-attachments/assets/e9de0614-6697-444e-b026-6b9319ca76b2)
  
- reset plot:
  
  ![image](https://github.com/user-attachments/assets/6bf81794-13c7-439a-9c8b-2a8f380c2338)

  
- OUT[9:0] plot:

   ![image](https://github.com/user-attachments/assets/6ebd9c96-ce55-4b1e-a9f6-8566bb11b8ed)



**Makerchip IDE simulation results for comparison**

- clk_kar plot:
  
  <img width="1215" alt="Screenshot 2024-08-26 at 3 28 39 AM" src="https://github.com/user-attachments/assets/382dca2e-c408-4311-a6db-4ec9ed9781ce">

- reset plot:
  
  <img width="1227" alt="Screenshot 2024-08-26 at 3 28 01 AM" src="https://github.com/user-attachments/assets/60f4b3c2-8dcd-4b86-9295-c662b97cd198">

- OUT[9:0] plot:

   <img width="1100" alt="Screenshot 2024-08-26 at 3 31 43 AM" src="https://github.com/user-attachments/assets/c45eabdf-e38d-4ec8-9544-07139ced0b71">


## References:

*  https://forgefunder.com/~kunal/riscv_workshop.vdi
*  https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Options.html
*  https://github.com/vinayrayapati/rv32i
*  [https://github.com/stevehoover](https://github.com/stevehoover/RISC-V_MYTH_Workshop)
*  https://makerchip.com/sandbox
*  https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Options.html
  

   
</details>

<details>
<summary><strong>Lab Session 8:</strong>RISC-V Pre synthesis Analog simulation using IVerilog and GTKWave</summary>

## Analyzing RISC-V Pre-Synthesis Analog Simulation outputs using Iverilog GTKwave.

### TASK 1 : TOOLS INSTALLATION:

- Commands to install Yosys in UBUNTU :

``` bash
$ git clone https://github.com/YosysHQ/yosys.git

$ cd yosys

$ sudo apt install make (If make is not installed) 

$ sudo apt-get install build-essential clang bison flex \
        libreadline-dev gawk tcl-dev libffi-dev git \
        graphviz xdot pkg-config python3 libboost-system-dev \
        libboost-python-dev libboost-filesystem-dev zlib1g-dev

$ make config-gcc

$ make 

$ sudo make install
```

- To verify the installation of yosys, type yosys in terminal window :

![PHOTO-2024-09-02-23-29-23](https://github.com/user-attachments/assets/a369f8ec-ef54-4672-87b6-5f5c7844d267)


- Commands to install Iverilog in UBUNTU :

```bash
$ sudo apt-get install iverilog
```
- To verify the installation of iverilog in the system, check the below screenshot:

![PHOTO-2024-09-02-23-29-24](https://github.com/user-attachments/assets/949088e7-a0b3-4506-8b14-b430d7112eda)


- Commands to install GTKWave in UBUNTU(Linux) :

```bash
$ sudo apt update

$ sudo apt install gtkwave
```

- To verify the installation of gtkwave in the system,  check the below screenshot :

![PHOTO-2024-09-02-23-29-24 2](https://github.com/user-attachments/assets/f1089349-eb8e-436c-b93c-822c1aa3a1b7)


- Commands to install OpenSTA in UBUNTU :

```
$ git clone https://github.com/The-OpenROAD-Project/OpenSTA.git

$ cd OpenSTA

$ mkdir build

$ cd build

$ cmake ..

$ make

$ sudo make install
```


### TASK 2 : BabySoC Simulation  

The VSDBabySoC is a compact and efficient RISC-V-based System on Chip (SoC). Its primary purpose is to integrate and test three open-source IP cores simultaneously while calibrating its analog components. The VSDBabySoC features:

   - RVMYTH Microprocessor: A RISC-V microprocessor core that forms the central processing unit of the SoC.
   - 8x-PLL (Phase-Locked Loop): Generates a stable clock signal, crucial for synchronizing operations across the SoC.
   - 10-bit DAC (Digital-to-Analog Converter): Facilitates communication with other analog devices, enabling interaction with the analog world.
     
These components make VSDBabySoC a versatile and valuable tool for testing and calibration purposes.


___Phase-Locked-Loop (PLL)___

A Phase-Locked Loop (PLL) is an electronic circuit designed to synchronize the phase and frequency of its output signal with that of a reference signal. It usually comprises three key components:

- Phase Detector: Measures the phase difference between the reference and output signals, producing an error signal that reflects this discrepancy.

- Loop Filter: Smooths the error signal to minimize noise and enhance stability.

- Voltage-Controlled Oscillator (VCO): Modifies its output frequency in response to the filtered error signal, aiming to reduce the phase difference.

PLLs are commonly used in applications such as clock generation, frequency synthesis, and data recovery in communication systems.

___Digital-to-Analog Converter (DAC)___

A Digital-to-Analog Converter (DAC) is an electronic device that transforms digital signals (usually in binary form) into analog signals, such as voltage or current.

This conversion is essential for systems where digital data must be understood by analog devices or for creating outputs that humans can perceive, such as in audio and video equipment.

DACs are widely used in applications like audio playback, video display, and signal processing.


- Commands to run the `rvmyth.v` file
```
$ cd BabySoC_Simulation
```
```
$ iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
```

```
$ ./pre_synth_sim.out
```
```
$ gtkwave pre_synth_sim.vcd
```

### Task3 : Generating the output waveforms

The output waveforms are given below:

**1. clk and reset signals**

   ![PHOTO-2024-09-02-23-29-25](https://github.com/user-attachments/assets/30757617-19e4-4777-a1a2-1ca9db2b09e0)
   
   ![PHOTO-2024-09-02-23-29-25 2](https://github.com/user-attachments/assets/c91354b6-7094-4dc0-bd47-c4d1426e326d)

------

**2. PLL clock input and output signals**

   ![PHOTO-2024-09-02-23-29-26](https://github.com/user-attachments/assets/65c24233-a609-4fec-aa81-202a68445831)
   
   ![PHOTO-2024-09-02-23-45-20 2](https://github.com/user-attachments/assets/74081cfd-3ffe-47e5-a76a-9c9952e97179)


-----

**3. DAC output signal**

   ![PHOTO-2024-09-02-23-45-20](https://github.com/user-attachments/assets/34c53730-8a3d-4181-a88e-806661eaa693)


----


### References:

*  https://forgefunder.com/~kunal/riscv_workshop.vdi
*  https://github.com/vinayrayapati/rv32i
*  [https://github.com/stevehoover](https://github.com/stevehoover/RISC-V_MYTH_Workshop)
*  https://github.com/manili/VSDBabySoC.git

</details>


</details>



<details>
<summary><strong>Post Midterm</strong></summary>





<details>
<summary><strong>Lab Session 9:</strong> RTL Design using Verilog with Sky130 Technology</summary>


<details>
<summary><strong>Day 1:</strong>Introduction to Verilog RTL design and Synthesis.</summary>

## Introduction to iverilog

In digital circuit design, **Register-Transfer Level (RTL)** is an abstraction used to model synchronous digital circuits by describing the flow of data between hardware registers and the logic operations applied to these signals. This RTL abstraction is expressed using **HDL (Hardware Description Language)** to create high-level models, which are later transformed into lower-level representations and, ultimately, the physical hardware design.

**Simulator**: A tool used to verify the circuit design. In this workshop, we use the **Icarus Verilog (iverilog)** tool. Simulation involves creating models that mimic the behavior of the target device (simulation models) and using test models to validate the device (test benches). RTL design is typically composed of one or more Verilog files that specify the design’s functionality and requirements.

**Test Bench**: A setup that delivers stimulus (test vectors) to the design, verifying its behavior and ensuring it meets the required specifications.

### HOW SIMULATOR WORKS 
**Simulator** looks for changes on input signals and based on that output is evaluated if there is an input change, the output is evaluated; else the simulator will never evaluate the output.

![Screenshot from 2024-10-21 10-51-23](https://github.com/user-attachments/assets/8612b99d-cf8d-4e88-b1bc-89d8a0bb9bbc)


**Design** may have 1 or more primary inputs and primary outputs but **testbench** doesn't have it.

### SIMULATION FLOW

![Screenshot from 2024-10-21 10-59-06](https://github.com/user-attachments/assets/1862f4ea-b19a-4fce-9c8d-de6a2db43151)


## Introduction to LABS

### ENVIRONMENT SETUP

Set up the tool flow using the below commands:

```
mkdir VLSI

cd VLSI

git clone https://github.com/kunalg123/vsdflow.git

git clone https://github.com/kunalg123/sky130RTLDesignAndSynthesisWorkshop.git

cd sky130RTLDesignAndSynthesisWorkshop
```

![1](https://github.com/user-attachments/assets/886caef5-7f49-4ad1-a284-c46527dfab5d)

The **sky130RTLDesignAndSynthesisWorkshop** directory includes **My_Lib**, which holds all the required library files. The **lib** folder contains standard cell libraries for synthesis, while the **verilog_model** folder has the Verilog models for all the standard cells in the library. The **verilog_files** folder has all the lab session experiments, including both the Verilog code and testbench files.

![2](https://github.com/user-attachments/assets/a2aab1e9-a1d4-49f0-818d-7abd441c77f9)

## Labs using iverilog & gtkwave

### Simulation using iverilog simulator - 2:1 multiplexer rtl design

#### VERILOG FILE OF A SIMPLE 2:1 MUX

To compile the verilog and testbench file use the following commands which will generate an executable file and will dump the waveform to view it using the gtkwave

```
iverilog good_mux.v tb_good_mux.v

./a.out

gtkwave tb_good_mux.vcd
```

We can view the waveform of a simple 2:1 mux which selects the input based on the select line

![3](https://github.com/user-attachments/assets/a705b2dc-0cc5-478d-91cd-88f2c6f8c9d1)

![4](https://github.com/user-attachments/assets/2a3c1804-2649-44ed-b3dd-d2de421b194c)

![5](https://github.com/user-attachments/assets/af35f382-169a-4708-9361-96e45510197b)

#### Access Module Files
To view the contents of the **good_mux** file run the following command
```
 vim tb_good_mux.v -o good_mux.v 
```
![6](https://github.com/user-attachments/assets/95f2de3c-bc61-4608-adff-b236a92be5cb)

Design file and Testbench File

![7](https://github.com/user-attachments/assets/f7426364-9615-4332-9158-a48b67ae34cb)

![8](https://github.com/user-attachments/assets/ae047667-26ab-46c0-bfd2-4c12f3de54f2)

## Introduction to Yosys & Logic Synthesis

**Synthesizer** is a tool for converting the **RTL** to Netlist and here we are using the **Yosys** Synthesizer.

### Yosys SETUP

![Screenshot from 2024-10-21 11-10-21](https://github.com/user-attachments/assets/537bebbf-c706-46f3-84f2-f3d05a36656f)


### Verifying the Synthesis

![Screenshot from 2024-10-21 11-10-50](https://github.com/user-attachments/assets/a267721b-7a56-4396-ae22-671c7b0b62f3)

**Note**:- The set of Primary inputs / primary outputs will remain the same between the RTL design and Synthesis so we can use the same testbench.

## Logic Synthesis

RTL Design - behavioral representation in HDL form for the required specification.

 **Synthesis** - RTL to Gate level translation.
 The design is converted int gates and connections are made. This given outas a file called **netlist**.

**Liberty (.lib)** is a collection of logical modules, including basic logic gates like AND, OR, and NOT, with different variants such as 2-input, 3-input, and 4-input gates, as well as slow, medium, and fast versions. Fast cells are used for high-performance needs, while slower cells help address hold time issues. Using faster cells can increase area and power consumption and may cause hold time violations. On the other hand, overusing slower cells can degrade performance. Optimal cell selection during synthesis is based on constraints that balance area, power, and timing requirements.

![Screenshot from 2024-10-21 11-11-26](https://github.com/user-attachments/assets/0581e61c-704b-429f-bb03-2f115343d18c)

### Faster cells and Slower Cells

Cell delay in a digital logic circuit is influenced by the circuit's load, which is represented by capacitance. Faster charging or discharging of the capacitance results in a lower cell delay.

To speed up the charging/discharging process, wider transistors are used as they can provide more current, reducing cell delay. However, wider transistors also increase power consumption and area. On the other hand, narrower transistors reduce area and power consumption but lead to higher cell delay. Therefore, designing a circuit with low cell delay involves a trade-off between area and power.

![Screenshot from 2024-10-21 11-13-28](https://github.com/user-attachments/assets/b910f788-d5e3-4951-aaca-00eafaf3f7fe)

## Yosys flow

**1.**  start yosys.
          
```
yosys
```
![9](https://github.com/user-attachments/assets/08151e5a-7e5d-46c7-9442-fc3ce2488271)


**2.** load the sky130 standard library.
```
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
![10](https://github.com/user-attachments/assets/50fdfc82-4575-41a9-97b2-83cca515a035)


**3.** Read the design files
```
read_verilog good_mux.v
```
![11](https://github.com/user-attachments/assets/17565cfa-f144-49e2-aa9d-4a1904806202)


**4.** Synthesize the top level module
```
synth -top good_mux
```
![12](https://github.com/user-attachments/assets/6acc9e63-ad37-41ba-9e99-433a3b62d047)

        
**5.** Map to the standard library
```
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
![13](https://github.com/user-attachments/assets/b15da1a9-5d50-4ba3-97b8-c09841b69491)


**6.** Two view the result as a graphich use the show command.
```
show
```
![14](https://github.com/user-attachments/assets/ea7c1286-32cd-490f-9a3f-920f2957aaaf)

**7.** To write the result netlist to a file use the write_veriog command. This will output the netlist to a file in the current directory.
```
write_verilog -noattr good_mux_netlist.v
```
![15](https://github.com/user-attachments/assets/8bef8914-a156-4f91-bb35-afe25e7806ae)

</details>









<details>  
<summary><strong>Day 2:</strong>Timing libs, hierarchical vs flat synthesis and efficient flop coding styles.</summary>

## Introduction to timing labs

Run the following commands to view the contents inside the .lib file:

```
cd ASIC/sky130RTLDesignAndSynthesisWorkshop/lib/

vim sky130_fd_sc_hd__tt_025C_1v80.lib

```
![20](https://github.com/user-attachments/assets/b0b8f7e7-d713-4bee-9f9f-a076089a61db)

![21](https://github.com/user-attachments/assets/c28eee18-7a6a-442e-ac90-271ff76c94e2)


##  Cell library
 A standard cell library is a collection of characterized logic gates that can be used to implement digital circuits. The Liberty (.lib) files contain PVT parameters (Process, Voltage, Temperature) that can significantly impact circuit performance. Variations in manufacturing, changes in voltage, and fluctuations in temperature all play a role in affecting how the circuit functions.

![Screenshot from 2024-10-21 12-18-00](https://github.com/user-attachments/assets/e084adcb-14b2-4f9c-95e7-3a6c8a7ab6d8)

We can also find various flavours of AND gate

![22](https://github.com/user-attachments/assets/1c5784b6-d129-4b74-97cd-30a70c84b9fb)
![23](https://github.com/user-attachments/assets/619718fb-8e3b-4aeb-af6b-47d00f6f0f40)
![24](https://github.com/user-attachments/assets/1d6bc766-a9aa-47b4-9ce6-d2c201e5ce80)

We can observe that:
* and2_0 -- takes the least area, more delay and low power.
* and2_1 -- takes more area, less delay and high power.
* and2_2 -- takes the largest area, larger delay and highest power.

## Hierarchial synthesis vs Flat synthesis 

Hierarchical synthesis involves breaking down a complex design into various sub-modules, each of which is synthesized separately to produce gate-level netlists before being integrated. This approach enhances organization, allows for module reuse, and enables incremental design changes without impacting the entire system. In contrast, flat synthesis treats the entire design as a single unit during the synthesis process, resulting in a single netlist regardless of any hierarchical relationships. While flat synthesis can optimize certain designs, it becomes difficult to maintain, analyze, and modify the design due to its absence of structural modularity.

### Hierarchial synthesis  

Consider the verilog file ```multiple_modules.v``` which is given in the verilog_files directory
```
module sub_module2 (input a, input b, output y);
    assign y = a | b;
endmodule

module sub_module1 (input a, input b, output y);
    assign y = a&b;
endmodule


module multiple_modules (input a, input b, input c , output y);
    wire net1;
    sub_module1 u1(.a(a),.b(b),.y(net1));  //net1 = a&b
    sub_module2 u2(.a(net1),.b(c),.y(y));  //y = net1|c ,ie y = a&b + c;
endmodule
```
To perform hierarchical synthesis on the ```multiple_modules.v ``` file use the following commands:
```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog multiple_modules.v

synth -top multiple_modules

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show multiple_modules

write_verilog -noattr multiple_modules_hier.v

!vim multiple_modules_hier.v

```
When you do synth -top 'topmodulename' in yosys, it does an hierarchical synthesis. ie the different hierarchies between modules are preserved.

![25](https://github.com/user-attachments/assets/10c32b12-608c-4aa2-b3a4-0a4c91df3f7c)

**Staistics of Multiple Modules**

![26](https://github.com/user-attachments/assets/213f69a0-42c5-4806-bcb8-9ea0ef476e31)

**Realization of the Logic**

![27](https://github.com/user-attachments/assets/1977d040-8838-4377-a659-f75f12cc8a9e)


**Map to the standard library**

![28](https://github.com/user-attachments/assets/517adf42-36ce-41d2-bc7c-ced00cf540c5)


**Netlist file**

![29](https://github.com/user-attachments/assets/afb77c7e-1275-4bdb-bcc2-7a8aa1f3acf6)



#### Flat synthesis  
Merges all hierarchical modules in the design into a single module to create a flat netlist. To perform flat synthesis on the ```multiple_modules.v``` file type the following commands:
```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog multiple_modules.v

synth -top multiple_modules

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

flatten

show

write_verilog -noattr multiple_modules_flat.v

!vim multiple_modules_flat.v
```
![210](https://github.com/user-attachments/assets/42b2b8cc-8616-41fc-b79d-9674d6182b61)

**Realization of the Logic**

![211](https://github.com/user-attachments/assets/a609c2b8-4cdc-4ebc-a0ba-a780aa658123)

 
**Netlist file**

![212](https://github.com/user-attachments/assets/678bf842-c912-4818-8b94-8de47f26fae6)


### Sub Module Level Synthesis
This method is preferred when multiple instances of same module are used. The synthesis is carried out once and is replicate multiple times, and the multiple instances of the same module are stitched together in the top module. This method is helpful when making use of divide and conquer algorithm


 ```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog multiple_modules.v

synth -top sub_module1

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show
```

![213](https://github.com/user-attachments/assets/0a46f5fe-d9f0-4bef-a7d0-72f5192a9739)

**Realization of the Logic**

![214](https://github.com/user-attachments/assets/929837ca-475b-4fb3-be35-1a406aa5700e)


## Flop coding styles and optimization

Flip-Flops are an essential part of sequential logic in a circuit and here we explore the design and synthesis of various types of flip-flops. To prevent glitches in digital circuits, we use flip-flops to store intermediate values. This ensures that combinational circuit inputs remain stable until the clock edge, avoiding glitches and maintaining correct operation:

### Asynchronous Reset/set:

**Verilog Code for Asynchronous Reset:**

```
module dff_asyncres ( input clk ,  input async_reset , input d , output reg q );
always @ (posedge clk , posedge async_reset)
begin
	if(async_reset)
		q <= 1'b0;
	else	
		q <= d;
end
endmodule
```
**Verilog Code Asynchronous Set:**

```
module dff_async_set ( input clk ,  input async_set , input d , output reg q );
always @ (posedge clk , posedge async_set)
begin
	if(async_set)
		q <= 1'b1;
	else	
		q <= d;
end
endmodule
```

In this design, the `always` block is triggered by changes in the clock or the reset signal. The circuit is sensitive to the positive edge of the clock. When the reset/set signal goes low or high, the signal on the `q` line changes accordingly. Therefore, the behavior associated with the reset/set occurs immediately and does not wait for the positive edge of the clock.

### Synchronous Reset:

```
module dff_syncres ( input clk , input async_reset , input sync_reset , input d , output reg q );
always @ (posedge clk )
begin
	if (sync_reset)
		q <= 1'b0;
	else	
		q <= d;
end
endmodule
```

#### FLIP FLOP SIMULATION

```
iverilog dff_asyncres.v tb_dff_asyncres.v 

ls

./a.out

gtkwave tb_dff_asyncres.vcd
```

![215](https://github.com/user-attachments/assets/36a5bc0c-1680-4ddf-ab4f-9f5bd95a8ab6)

**GTK WAVE OF ASYNCHRONOUS RESET**

![216](https://github.com/user-attachments/assets/334cf593-e309-4d9b-b327-d5718cd02ee7)

**GTK WAVE OF ASYNCHRONOUS SET**

![217](https://github.com/user-attachments/assets/be12e8a3-a0fe-497d-92ae-9ee085ba3433)

**GTK WAVE OF SYNCHRONOUS RESET**

![218](https://github.com/user-attachments/assets/747dbaf4-61a0-4b9c-95bc-5cd1fbb61500)

#### FLIP FLOP SYNTHESIS

```

yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_asyncres.v

synth -top dff_asyncres

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show 
```
**Statistics of D FLipflop with Asynchronous Reset**

![219](https://github.com/user-attachments/assets/d1eb363e-908a-4f66-9adc-76ccc0d30f76)

![220](https://github.com/user-attachments/assets/7fdc1826-fd15-46c4-a7c2-8648275d7144)


**Realization of Logic**

![221](https://github.com/user-attachments/assets/eec91e5d-9634-4f87-8111-5e878760ecf4)



**Note:**  We wrote a flop with active high reset but the flop is having acting low reset so the tool inserted the inverter so (!(!(reset))) is just reset so at the end we got a flop with active high reset

**Statistics of D FLipflop with Asynchronous set**\
Follow the same steps as given above just the file name changes to dff_async_set.v

![222](https://github.com/user-attachments/assets/4e40503f-28f9-4c14-ab11-08a2de0946f1)

![223](https://github.com/user-attachments/assets/d4910286-fb0e-4e89-991b-d96d0e8b8653)

**Realization of Logic**

![224](https://github.com/user-attachments/assets/90253526-d4c0-472d-a5af-fd6c52c258dc)

**Note:**  We wrote a flop with active high set but the flop is having acting low set so the tool inserted the inverter so (!(!(set))) is just set so at the end we got a flop with active high set

**Statistics of D FLipflop with Synchronous Reset**

![225](https://github.com/user-attachments/assets/2359180b-0025-4e05-88fb-a62283acf525)

![226](https://github.com/user-attachments/assets/b1719320-bc77-4798-964f-3250cabe02c9)


**Realization of Logic**

![227](https://github.com/user-attachments/assets/b4a086a2-e521-437c-a8df-867890ba7ee7)



## Optimizations

### Example 1: mult_2.v 

**verilog code**

```
module mul2 (input [2:0] a, output [3:0] y);
assign y = a * 2;
endmodule
```

**truth table**

![Screenshot from 2024-10-21 15-35-31](https://github.com/user-attachments/assets/b53852d4-4db4-417e-8532-8f5e453fc84a)

We can see the multiplication of a number by 2 doesnt really need any extra hardware we just need to append the LSB's with zeroes and the remaining bits are the input bits of same, It can be realised by grouding the LSB's and wiring the input properly to the output.

Run the below code to view the netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog mult_2.v

synth -top mul2

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show 

write_verilog -noattr mult_2_net.v

!vim mult_2_net.v
```
**Statestics**

![228](https://github.com/user-attachments/assets/3f367c55-e759-4b11-8650-2a8b346811f8)


**Realization of Logic**

![229](https://github.com/user-attachments/assets/3092e0ce-3b9d-4085-bb8b-c07267f7492f)

**Netlist**

![230](https://github.com/user-attachments/assets/26ea571c-6b14-4dd7-8fff-e612712f93e8)


### Example 2: mult_8.v

**verilog code**

```
module mult8 (input [2:0] a , output [5:0] y);
	assign y = a * 9;
endmodule
```

**logic behaviour**

![Screenshot from 2024-10-21 15-43-38](https://github.com/user-attachments/assets/a66a1c34-977d-446c-a462-fae3073a1425)


In this design the 3-bit input number "a" is multiplied by 9 i.e (a9) which can be re-written as (a8) + a . The term (a8) is nothing but a left shifting the number a by three bits. Consider that a = a2 a1 a0. (a8) results in a2 a1 a0 0 0 0. (a9)=(a8)+a = a2 a1 a0 a2 a1 a0 = aa(in 6 bit format). Hence in this case no hardware realization is required. The synthesized netlist of this design is shown below:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog mult_8.v

synth -top mult8

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr mult_8_net.v

```

**Statestics**

![231](https://github.com/user-attachments/assets/04a1c856-0b9b-497f-94f2-7384a0a77071)


**Realization of Logic**

![232](https://github.com/user-attachments/assets/d520d717-8f5f-49c4-8788-d5a0a92e0781)


**Netlist**
 
![233](https://github.com/user-attachments/assets/a11b3e1b-df78-4dde-87bd-c4a1104741f0)



</details>

<details>
<summary><strong>Day 3:</strong>Introduction to Combinational and sequential optimizations.</summary>

##  Introduction to Combinational Logic Optimization and sequential Optimization
There are two types of optimisations: Combinational and Sequential optimisations. These optimisations are done inorder to achieve designs that are efficient in terms of area, power, and performance.

**Combinational Optimization**

The techiniques used are:

- Constant Propagation (Direct Optimisation)
- Boolean Logic Optimisation (using K-Map or Quine McCluskey method)

**Constant Propagation:**

Consider the below circuit:

![image](https://github.com/user-attachments/assets/24fcec7b-7b46-4d73-b93d-a257883ef6e5)

The top circuit uses 6 transistors (3 NMOS and 3 PMOS), while the bottom circuit uses 2 transistors (1 NMOS and 1 PMOS) when input A is set to zero, turning the logic into an inverter.

**Boolean Logic Optimisation:**

Consider the below verilog code:

```assign y = a?(b?c:(c?a:0)):(!c)```

The ternary operator (?:) will make the circuit behave like a mux upon synthesis as shown below. 

![Screenshot from 2024-10-21 16-15-29](https://github.com/user-attachments/assets/77afa517-d6e6-498e-be71-f5dac5c0d777)


The circuit can be optimised as follows:

![Screenshot from 2024-10-21 16-15-54](https://github.com/user-attachments/assets/e5cfb3b9-1e20-4a13-ad2e-3a4774e03632)


**Example 1:**

Verilog code:

```
module opt_check (input a , input b , output y);
	assign y = a?b:0;
endmodule
```

The above code infers a multiplexer and since one of the inputs of the multiplexer is always connected to the ground it will infer an AND gate on optimisation.

Run the following commands for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog opt_check.v

synth -top opt_check

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr opt_check_net.v

!vim opt_ckeck_net.v
```

![image](https://github.com/user-attachments/assets/c0b9561e-d5f6-4e60-a037-7388cec4a000)

![31](https://github.com/user-attachments/assets/c925acbe-5385-4c4f-a3b9-aa69c00d3f58)


**Example 2:**

Verilog code:

```
module opt_check2 (input a , input b , output y);
	assign y = a?1:b;
endmodule
```

Since one of the inputs of the multiplexer is always connected to the logic 1 it will infer an OR gate on optimisation.The OR gate will be NAND implementation since NOR gate has stacked pmos while NAND implementation has stacked nmos.

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog opt_check2.v

synth -top opt_check2

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr opt_check2_net.v

!vim opt_ckeck2_net.v
```

![image](https://github.com/user-attachments/assets/4aa3a255-c909-4786-bf65-760b816ffaaf)

![32](https://github.com/user-attachments/assets/08fe3c54-faf2-4093-ba77-83bc2971c509)


**Example 3:**

Verilog code:

```
module opt_check3 (input a , input b, input c , output y);
	assign y = a?(c?b:0):0;
endmodule
```

On optimisation the above design becomes a 3 input AND gate.

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog opt_check3.v

synth -top opt_check3

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr opt_check3_net.v

!vim opt_ckeck3_net.v
```

![image](https://github.com/user-attachments/assets/38a83f8b-73a8-4d44-b36d-84a716742514)

![33](https://github.com/user-attachments/assets/9764687e-9c97-46a6-bdc9-78e93d9bac15)

**Example 4:**

Verilog code:

```
module opt_check4 (input a , input b, input c , output y);
	assign y = a?(c?b:0):0;
endmodule
```

On optimisation the above design becomes a 2 input XNOR gate.

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog opt_check4.v

synth -top opt_check4

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr opt_check4_net.v

!vim opt_ckeck4_net.v
```
![image](https://github.com/user-attachments/assets/199b9558-76e1-4022-8d0c-cc46542da246)

![34](https://github.com/user-attachments/assets/a9c21325-aba8-4e4c-89d6-680b7b38bcfc)

**Example 5:**

Verilog code:

```
module sub_module1(input a , input b , output y);
 assign y = a & b;
endmodule

module sub_module2(input a , input b , output y);
 assign y = a^b;
endmodule

module multiple_module_opt(input a , input b , input c , input d , output y);
wire n1,n2,n3;

sub_module1 U1 (.a(a) , .b(1'b1) , .y(n1));
sub_module2 U2 (.a(n1), .b(1'b0) , .y(n2));
sub_module2 U3 (.a(b), .b(d) , .y(n3));

assign y = c | (b & n1); 

endmodule
```

On optimisation the above design becomes a AND OR gate

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog multiple_module_opt.v

synth -top multiple_module_opt

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

flatten

show

write_verilog -noattr multiple_module_opt_net.v

!vim multiple_module_opt_net.v
```

![Screenshot from 2024-10-21 17-32-18](https://github.com/user-attachments/assets/e2e1a6b2-4097-41d2-96e1-aaee5cfdd777)

![35](https://github.com/user-attachments/assets/05b7a73b-546a-4fff-b1d9-052d4328a81d)



**Example 6:**

Verilog code:

```
module sub_module(input a , input b , output y);
	assign y = a & b;
endmodule

module multiple_module_opt2(input a , input b , input c , input d , output y);
		wire n1,n2,n3;
	sub_module U1 (.a(a) , .b(1'b0) , .y(n1));
	sub_module U2 (.a(b), .b(c) , .y(n2));
	sub_module U3 (.a(n2), .b(d) , .y(n3));
	sub_module U4 (.a(n3), .b(n1) , .y(y));
endmodule
```

On optimisation the above design becomes Y=0 

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog multiple_module_opt2.v

synth -top multiple_module_opt2

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

flatten

show

write_verilog -noattr multiple_module_opt2_net.v

!vim multiple_module_opt_net2.v
```

![Screenshot from 2024-10-21 17-37-12](https://github.com/user-attachments/assets/8789b961-44eb-4451-97d3-aaac5ac73fec)



![36](https://github.com/user-attachments/assets/0416007d-9701-426c-b020-ca7144719062)


**Sequential Logic Optimizations**

**Example 1:**

Verilog code:

```
module dff_const1(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b0;
	else
		q <= 1'b1;
end
endmodule
```

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_const1.v

synth -top dff_const1

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr dff_const1_net.v

!vim dff_const1_net.v
```


![image](https://github.com/user-attachments/assets/080978a6-12a9-443c-8d25-e923d6560b9b)

![Screenshot from 2024-10-21 17-50-00](https://github.com/user-attachments/assets/42f1d861-1789-40b5-9ad3-9bfab4d82e59)


GTKWave Output:

```
iverilog dff_const1.v tb_dff_const1.v

./a.out

gtkwave tb_dff_const1.vcd

```
![Screenshot from 2024-10-21 17-54-37](https://github.com/user-attachments/assets/5d69a914-4870-47de-8522-1da1d3780cde)


**Example 2:**

Verilog code:

```
module dff_const2(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b1;
	else
		q <= 1'b1;
end
endmodule
```

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_const2.v

synth -top dff_const2

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr dff_const2_net.v

!vim dff_const2_net.v
```

![Screenshot from 2024-10-21 17-59-25](https://github.com/user-attachments/assets/27170a05-b904-4ab9-97ed-ae0303f50993)

![Screenshot from 2024-10-21 17-57-07](https://github.com/user-attachments/assets/437dc4e6-5ed5-4aa7-8cd9-716219293ae0)


GTKWave Output:

```
iverilog dff_const2.v tb_dff_const2.v

./a.out

gtkwave tb_dff_const2.vcd
```

![image](https://github.com/user-attachments/assets/c9147236-4f3a-4d12-b8fe-c506749b3890)

**Example 3:**

Verilog code:

```
module dff_const3(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b0;
	end
	else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_const3.v

synth -top dff_const3

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr dff_const3_net.v
```


![Screenshot from 2024-10-21 18-02-12](https://github.com/user-attachments/assets/1d405b4d-c7eb-4fb6-9bd2-88b6bdda4d3c)

![Screenshot from 2024-10-21 18-02-49](https://github.com/user-attachments/assets/5d0dbaa6-03d6-4650-9488-5ad58ddf6aaa)


GTKWave Output:

```
iverilog dff_const3.v tb_dff_const3.v

./a.out

gtkwave tb_dff_const3.vcd
```

![image](https://github.com/user-attachments/assets/a6718736-a93a-4f3e-90f5-f3f85f22292c)


**Example 4:**

Verilog code:

```
module dff_const4(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b1;
	end
else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_const4.v

synth -top dff_const4

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr dff_const4_net.v
```
![image](https://github.com/user-attachments/assets/a10095c1-63f2-4343-9304-413d0f941465)

![Screenshot from 2024-10-21 18-03-58](https://github.com/user-attachments/assets/0af3ff11-2c59-49ff-b9dd-49707a344c78)

 
GTKWave Output:

```
iverilog dff_const4.v tb_dff_const4.v

./a.out

gtkwave tb_dff_const4.vcd
```

![image](https://github.com/user-attachments/assets/790a1467-b14b-484d-8f1b-7212d66b051d)


**Example 5:**

Verilog code:

```
module dff_const5(input clk, input reset, output reg q);
reg q1;
always @(posedge clk, posedge reset)
	begin
		if(reset)
		begin
			q <= 1'b0;
			q1 <= 1'b0;
		end
	else
		begin
			q1 <= 1'b1;
			q <= q1;
		end
	end
endmodule
```

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_const5.v

synth -top dff_const5

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr dff_const5_net.v
```

![image](https://github.com/user-attachments/assets/42cac623-761a-4a4d-9678-7ce0960b0377)

![Screenshot from 2024-10-21 18-04-56](https://github.com/user-attachments/assets/1e6b6509-ede0-43e2-b877-7ab4f5047733)


GTKWave Output:

```
iverilog dff_const5.v tb_dff_const5.v

./a.out

gtkwave tb_dff_const5.vcd
```
![Screenshot from 2024-10-21 18-20-22](https://github.com/user-attachments/assets/917d71a5-b1bc-440d-82a3-b339a4da755c)



**Sequential Logic Optimizations for unused outputs**

**Example 1:**

Verilog code:

```
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = count[0];
always @(posedge clk ,posedge reset)
begin
	if(reset)
		count <= 3'b000;
	else
		count <= count + 1;
end
endmodule
```

Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog counter_opt.v

synth -top counter_opt

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr counter_opt_net.v
```

![image](https://github.com/user-attachments/assets/b08e9a6a-0947-4a36-9c34-1e722a09303e)

![Screenshot from 2024-10-21 18-05-56](https://github.com/user-attachments/assets/d1fd37cc-af90-4aa7-9af2-20618f664a21)


GTKWave Output:

```
iverilog counter_opt.v tb_counter_opt.v

./a.out

gtkwave tb_counter_opt.vcd
```

![image](https://github.com/user-attachments/assets/359ffb99-5980-459b-87d4-d153fa5f8da7)

Modified counter logic:

Verilog code:

```
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = {count[2:0]==3'b100};
always @(posedge clk ,posedge reset)
begin
if(reset)
	count <= 3'b000;
else
	count <= count + 1;
end
endmodule
```
Run the below code for netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog counter_opt.v

synth -top counter_opt

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr counter_opt_net.v

```
![image](https://github.com/user-attachments/assets/6b0daf62-32e0-486e-adfd-71fd8c8edac6)

![Screenshot from 2024-10-21 18-07-39](https://github.com/user-attachments/assets/758cc273-b58d-4286-a891-bf9f6756c58e)


GTKWave Output:

```
iverilog counter_opt.v tb_counter_opt.v

./a.out

gtkwave tb_counter_opt.vcd
```

![Screenshot from 2024-10-21 18-10-22](https://github.com/user-attachments/assets/ae5620f9-2bbb-4a74-bddb-1da1d42d427c)




</details>

<details>
<summary><strong>Day 4:</strong> GLS, blocking vs non-blocking and Synthesis-Simulation mismatch.</summary>

## Introduction to GLS and Synthesis-Simulation mismatch

Gate Level Simulation (GLS) is an important step in verifying digital circuits. It simulates the synthesized netlist, a lower-level representation of the design, using a testbench to check its logical accuracy and timing behavior. By comparing the simulation outputs with expected results, GLS ensures the synthesis process hasn't introduced any errors and that the design meets performance requirements.

Sensitivity lists are key for ensuring correct circuit behavior. An incomplete sensitivity list can result in unintended latches. Blocking and non-blocking assignments in `always` blocks behave differently, and improper use of blocking assignments can inadvertently create latches, leading to mismatches between synthesis and simulation. To prevent this, it's crucial to carefully review the circuit behavior and ensure the sensitivity list and assignments match the intended functionality.

![image](https://github.com/user-attachments/assets/fa59f230-4a0d-4c8e-9353-a01a9209a6d6)

**Example 1:**

Verilog code:

```
module ternary_operator_mux (input i0 , input i1 , input sel , output y);
assign y = sel?i1:i0;
endmodule
```

Simulation:

```
iverilog ternary_operator_mux.v tb_ternary_operator_mux.v

./a.out

gtkwave tb_ternary_operator_mux.vcd

```
![Screenshot from 2024-10-21 18-36-23](https://github.com/user-attachments/assets/0ba94bba-929e-40e3-a154-b33d79442f71)

Netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog ternary_operator_mux.v

synth -top ternary_operator_mux

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr ternary_operator_mux_net.v

```

![41](https://github.com/user-attachments/assets/413106d7-cffe-4db2-b0d5-03ae64f57749)

![42](https://github.com/user-attachments/assets/5d163f42-940a-40fe-a47f-071e14874175)

![43](https://github.com/user-attachments/assets/4e7c3528-38f2-4ad3-b97c-b6626b0076d9)


GLS:

```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v ternary_operator_mux_net.v tb_ternary_operator_mux.v

./a.out

gtkwave tb_ternary_operator_mux.vcd
```
![Screenshot from 2024-10-21 18-49-19](https://github.com/user-attachments/assets/e1592d89-2be4-4fd7-abdb-7acc50cbad31)


In this case there is no mismatch between the waveforms before and after synthesis

**Example 2:**

Verilog code:

```
module bad_mux (input i0 , input i1 , input sel , output reg y);
always @ (sel)
begin
	if(sel)
		y <= i1;
	else 
		y <= i0;
end
endmodule
```

Simulation:

```
iverilog bad_mux.v tb_bad_mux.v

./a.out

gtkwave tb_bad_mux.vcd
```

![Screenshot from 2024-10-21 18-51-31](https://github.com/user-attachments/assets/16e226d4-fb0c-468d-b8b6-1321afba599f)


Netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog bad_mux.v

synth -top bad_mux

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr bad_mux_net.v

```
![45](https://github.com/user-attachments/assets/11a81ae7-3362-4027-a698-6bc47a7c02bf)

![46](https://github.com/user-attachments/assets/dc8bacae-8c9b-43ef-8733-f998ceed06a4)

![47](https://github.com/user-attachments/assets/969d2bca-1c7d-4838-a20b-c36027faa24b)



GLS:

```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v bad_mux_net.v tb_bad_mux.v

./a.out

gtkwave tb_bad_mux.vcd
```
![48](https://github.com/user-attachments/assets/5a0ecd6f-caad-4dd1-8bfa-1ee5240d475a)


In this case there is a synthesis and simulation mismatch. While performing synthesis yosys has corrected the sensitivity list error.

**Labs on Synthesis-Simulation mismatch for blocking statements**

Verilog code:

```
module blocking_caveat (input a , input b , input  c, output reg d); 
reg x;
always @ (*)
begin
d = x & c;
x = a | b;
end
endmodule
```

Simulation:

```
iverilog blocking_caveat.v tb_blocking_caveat.v

./a.out

gtkwave tb_blocking_caveat.vcd
```
![51](https://github.com/user-attachments/assets/9f17e206-a0c9-47f5-9059-54837fe033e9)


Netlist:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog blocking_caveat.v

synth -top blocking_caveat

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show

write_verilog -noattr blocking_caveat_net.v
```
![52](https://github.com/user-attachments/assets/79448677-f0be-4e4d-b356-e19ea2dffcef)

![53](https://github.com/user-attachments/assets/4f3afeac-e175-4cd3-9634-d2013712693f)

![55](https://github.com/user-attachments/assets/ceab2f4b-72e7-4709-8827-f6c0bef97fc0)


GLS:

```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v blocking_caveat_net.v tb_blocking_caveat.v

./a.out

gtkwave tb_blocking_caveat.vcd
```
![56](https://github.com/user-attachments/assets/23fa7386-f479-4dc1-bc1c-f2385923eea6)


In this case there is a synthesis and simulation mismatch. While performing synthesis yosys has corrected the latch error.

</details>
</details>

<details>
<summary><strong>Lab Session 10</strong> Synthesize RISC-V and compare output with functional simulations</summary>
	
## Synthesizing RISC-V and comparing output with functional (RTL) simulation.


### Steps 

Copy the ```src``` folder from your ```BabySoC``` folder to your ```sky130RTLDesignAndSynthesisWorkshop``` folder in your ```VLSI``` folder from previous lab.

Now go the following Directory: 

```
cd /home/karthikeya/VLSI/sky130RTLDesignAndSynthesisWorkshop/src/module
```

### Synthesis: 

```
yosys       

read_liberty -lib /home/karthikeya/VLSI/sky130RTLDesignAndSynthesisWorkshop/lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog clk_gate.v

read_verilog rvmyth.v

synth -top rvmyth

abc -liberty /home/karthikeya/VLSI/sky130RTLDesignAndSynthesisWorkshop/lib/sky130_fd_sc_hd__tt_025C_1v80.lib

write_verilog -noattr rvmyth_net.v

!gvim rvmyth_net.v

exit
```

![3](https://github.com/user-attachments/assets/5c547ed5-1f14-476c-9bce-b225154366a5)

![4](https://github.com/user-attachments/assets/00f86b76-1b8c-4390-8772-d29075df22d3)

![5](https://github.com/user-attachments/assets/9672c299-f4f4-4f49-bb28-f6d942a41052)



Now to observe the output waveform of synthesised RISC-V
```
iverilog ../../my_lib/verilog_model/primitives.v ../../my_lib/verilog_model/sky130_fd_sc_hd.v rvmyth.v testbench.v vsdbabysoc.v avsddac.v avsdpll.v clk_gate.v

./a.out

gtkwave dump.vcd
```

<img width="1004" alt="Screenshot 2024-10-24 at 3 10 44 AM" src="https://github.com/user-attachments/assets/f5f17cae-aaa4-47a5-9fe8-7e6ee77e7a08">


![7](https://github.com/user-attachments/assets/ce4aa0e4-9542-46f8-a088-ab1f427e88b1)

### Realization: 

![PHOTO-2024-10-24-01-55-37](https://github.com/user-attachments/assets/f400bd2e-0285-4dcf-991a-46662df07a2b)

![PHOTO-2024-10-24-01-56-14](https://github.com/user-attachments/assets/9cb37544-d272-42b8-9006-3f3e86f2fc13)

![PHOTO-2024-10-24-02-46-15](https://github.com/user-attachments/assets/2319d29c-ec92-4d2b-8c91-677e2ced564f)



## RTL Simulations

 ### Command Steps :
 ```
cd BabySoC

iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/

./pre_synth_sim.out

gtkwave pre_synth_sim.vcd

```

![1](https://github.com/user-attachments/assets/8996b6f2-64cb-45b2-a534-d85e285d70b2)

![2](https://github.com/user-attachments/assets/6219ef9f-c391-4220-854c-403c88202790)

 
</details>



<details>
<summary><strong>Lab Session 11:</strong>Post Synthesis Static Timing Analysis using OpenSTA.</summary>
	
### Static Timing Analysis (STA)
Static Timing Analysis (STA) is a technique used to verify the timing performance of digital circuits without requiring dynamic simulation. It checks if a circuit meets timing constraints by analyzing the paths data takes from inputs to outputs, considering delays through gates and interconnects. STA identifies setup and hold time violations, ensuring data stability around clock edges. It also incorporates clock properties, including frequency, skew, and jitter, and assumes worst-case delay conditions to guarantee performance under varying conditions. Tools like Synopsys PrimeTime and Cadence Tempus automate this process, identifying timing issues early for reliable circuit operation at target speeds.

STA is essential in digital design for several reasons. It ensures data signals propagate within set time limits for valid outputs and identifies violations, ensuring flip-flops and sequential elements function reliably. STA aids performance optimization by highlighting critical paths that restrict the maximum operating frequency and allows for early detection of timing issues, minimizing costly redesigns. It also supports balancing performance with power efficiency by analyzing the power impact of clock frequency changes. Automated STA tools efficiently handle complex designs, incorporating variations in manufacturing, temperature, and voltage to ensure consistent performance.

### Reg-to-Reg Path
A reg-to-reg path connects two sequential elements, such as flip-flops, within a digital circuit. It’s a key focus in STA, verifying data flow between registers through combinational logic. Reg-to-reg paths help ensure correct data transfer and synchronization, particularly in pipelined or sequential designs. STA checks for setup and hold time compliance, ensuring data stability at the registers. Timing analysis considers delays through the connecting combinational logic, with critical reg-to-reg paths impacting the circuit's maximum frequency. For registers in different clock domains, STA accounts for additional considerations like metastability and synchronization.

### Clk-to-Reg Path
A clk-to-reg path connects a clock signal to a register, enabling proper register operation in response to clock edges. This path represents the delay for the clock signal to reach the register from its source, accounting for delays through buffers or routing. During setup analysis, it helps define when data must arrive at the register in relation to the clock edge. Clock delay affects the timing of data capture, and both setup and hold timing are analyzed, particularly when dealing with clock jitter or variations. Special considerations apply when registers belong to different clock domains, ensuring reliable synchronization.

### STA for synthesized Risc-V core using time period of 10.65 ns.
To verify that our synthesized RISC-V Core module meets its timing constraints, we will generate setup and hold timing reports. These reports will confirm that data signals propagate correctly throughout the core. Run the following commands:
```
set PERIOD 10.65

set_units -time ns

create_clock [get_pins {pll/CLK}] -name clk -period $PERIOD
set_clock_uncertainty -setup  [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_transition [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_uncertainty -hold [expr $PERIOD * 0.08] [get_clocks clk]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_CP]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_VCO]
set_input_transition [expr $PERIOD * 0.08] [get_ports REF]
set_input_transition [expr $PERIOD * 0.08] [get_ports VCO_IN]
set_input_transition [expr $PERIOD * 0.08] [get_ports VREFH]
```

Now, run the below commands:
```
cd VSDBabySoc/src

sta

read_liberty -min ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_liberty -min ./lib/avsdpll.lib

read_liberty -min ./lib/avsddac.lib

read_liberty -max ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_liberty -max ./lib/avsdpll.lib

read_liberty -max ./lib/avsddac.lib

read_verilog ../output/synth/vsdbabysoc.synth.v

link_design vsdbabysoc

read_sdc ./sdc/vsdbabysoc_synthesis.sdc

report_checks -path_delay min_max -format full_clock_expanded -digits 4
```

![image](https://github.com/user-attachments/assets/ba17e067-d19c-40ee-9c1f-40c6d3b909a7)

Setup Time:

![l2](https://github.com/user-attachments/assets/cb9ca529-063a-4e94-aa0b-6170afa51bc5)


Hold Time:

![l1](https://github.com/user-attachments/assets/5d2d5ea0-470a-4b7f-bc99-79c7d7cb9ca7)


</details>




<details>
<summary><strong>Lab Session 12:</strong>Post Synthesis Static Timing Analysis comparison for various sky libraries.</summary>

## STA comparison for various sky libraries

Store all the sky `lib` files in a folder named `timing_libs`. Now, go to `VSDBabySoC/src` and create a tickle file `sta_across_pvt.tcl` . The below block is the content of the tickle file:

```
set list_of_lib_files(1) "sky130_fd_sc_hd__ff_100C_1v65.lib"
set list_of_lib_files(2) "sky130_fd_sc_hd__ff_100C_1v95.lib"
set list_of_lib_files(3) "sky130_fd_sc_hd__ff_n40C_1v56.lib"
set list_of_lib_files(4) "sky130_fd_sc_hd__ff_n40C_1v65.lib"
set list_of_lib_files(5) "sky130_fd_sc_hd__ff_n40C_1v76.lib"
set list_of_lib_files(6) "sky130_fd_sc_hd__ff_n40C_1v95.lib"
set list_of_lib_files(7) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part1"
set list_of_lib_files(8) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part2"
set list_of_lib_files(9) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part3"
set list_of_lib_files(10) "sky130_fd_sc_hd__ss_100C_1v40.lib"
set list_of_lib_files(11) "sky130_fd_sc_hd__ss_100C_1v60.lib"
set list_of_lib_files(12) "sky130_fd_sc_hd__ss_n40C_1v28.lib"
set list_of_lib_files(13) "sky130_fd_sc_hd__ss_n40C_1v35.lib"
set list_of_lib_files(14) "sky130_fd_sc_hd__ss_n40C_1v40.lib"
set list_of_lib_files(15) "sky130_fd_sc_hd__ss_n40C_1v44.lib"
set list_of_lib_files(16) "sky130_fd_sc_hd__ss_n40C_1v60.lib"
set list_of_lib_files(17) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part1"
set list_of_lib_files(18) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part2"
set list_of_lib_files(19) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part3"
set list_of_lib_files(20) "sky130_fd_sc_hd__ss_n40C_1v76.lib"
set list_of_lib_files(21) "sky130_fd_sc_hd__tt_025C_1v80.lib"
set list_of_lib_files(22) "sky130_fd_sc_hd__tt_100C_1v80.lib"

for {set i 1} {$i <= [array size list_of_lib_files]} {incr i} {
read_liberty ./timing_libs/$list_of_lib_files($i)
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
check_setup -verbose
report_checks -path_delay min_max -fields {nets cap slew input_pins fanout} -digits {4} > ./sta_output/min_max_$list_of_lib_files($i).txt

}

```

![Screenshot from 2024-10-31 11-18-14](https://github.com/user-attachments/assets/050dc5f8-e7f7-486e-8d74-84d10fa1ad1c)

constraints file:

![Screenshot from 2024-10-31 11-28-12](https://github.com/user-attachments/assets/6e71de93-75f5-415d-af83-41fe91d04b37)


Now, run the following commands:

```
cd VSDBabySoC/src

sta

source sta_across_pvt.tcl
```

![Screenshot from 2024-10-31 11-21-20](https://github.com/user-attachments/assets/2a8e5d8e-b29f-4edb-850a-035ab4ea04f3)

table:

![Screenshot from 2024-10-31 12-24-26](https://github.com/user-attachments/assets/23f73fe3-9847-4a96-8b3a-d863e528c3fc)


Graphs:

**Worst Setup Slack:**

![Screenshot from 2024-11-02 11-18-26](https://github.com/user-attachments/assets/974952c0-8ba2-492e-b020-70139ea6f99c)


**Worst Hold Slack:**

![Screenshot from 2024-11-02 11-18-42](https://github.com/user-attachments/assets/18a62966-a8f0-479e-a166-e3a49e3cbc4f)


<details>
<summary><strong>Timing Reports:</strong></summary>
	
**sky130_fd_sc_hd__ff_100C_1v65.lib:**

![Screenshot from 2024-11-03 11-17-56](https://github.com/user-attachments/assets/0d42ab97-93f4-44c2-9cfb-6445d645db6e)

![Screenshot from 2024-11-03 11-17-39](https://github.com/user-attachments/assets/438d468c-91f9-4a64-b77a-2e4b8ae4fc8a)

**sky130_fd_sc_hd__ff_100C_1v95.lib:**

![Screenshot from 2024-11-03 11-18-20](https://github.com/user-attachments/assets/2eddb20e-e57d-46a7-b969-d1031b258502)

![Screenshot from 2024-11-03 11-18-15](https://github.com/user-attachments/assets/ea4167fe-3f35-44d2-be0d-d1787d579343)


**sky130_fd_sc_hd__ff_n40C_1v56.lib:**

![Screenshot from 2024-11-03 11-20-18](https://github.com/user-attachments/assets/b1b8ad30-792e-4585-ab69-88c97739bd5b)

![Screenshot from 2024-11-03 11-19-23](https://github.com/user-attachments/assets/d818abd1-02fe-4b4e-99e9-e694a2ef0cdb)

**sky130_fd_sc_hd__ff_n40C_1v65.lib:**

![Screenshot from 2024-11-03 11-20-37](https://github.com/user-attachments/assets/650adad4-5a42-4a0e-b109-c6208ac8820f)

![Screenshot from 2024-11-03 11-20-31](https://github.com/user-attachments/assets/7f76f46d-9a30-4951-93b5-d94ff8bad71f)

**sky130_fd_sc_hd__ff_n40C_1v76.lib:**

![Screenshot from 2024-11-03 11-20-52](https://github.com/user-attachments/assets/f2defda9-8859-4ef5-a87c-f6a270aed521)

![Screenshot from 2024-11-03 11-20-47](https://github.com/user-attachments/assets/ea3e0625-051e-42dd-b6e4-3debf3f3b7e8)

**sky130_fd_sc_hd__ff_n40C_1v95.lib:**

![Screenshot from 2024-11-03 11-21-07](https://github.com/user-attachments/assets/8dfea3de-38bb-413a-b73a-9ed18b8fde59)

![Screenshot from 2024-11-03 11-21-02](https://github.com/user-attachments/assets/981b75e7-13d3-40eb-8c6a-49319f6c223e)

**sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part1:**

![Screenshot from 2024-11-03 11-21-21](https://github.com/user-attachments/assets/e36ed78c-4f72-46e0-b04d-65e1d77d29d6)

![Screenshot from 2024-11-03 11-21-16](https://github.com/user-attachments/assets/2674e91f-c17f-4743-9270-a4fc88a63cbd)

**sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part2:**

![Screenshot from 2024-11-03 11-22-46](https://github.com/user-attachments/assets/de015b6a-db52-4268-a80e-71f03675cfe1)

![Screenshot from 2024-11-03 11-22-41](https://github.com/user-attachments/assets/bdd94725-a92c-4edd-8eab-9bdb8c3b184d)


**sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part3:**

![Screenshot from 2024-11-03 11-23-02](https://github.com/user-attachments/assets/dfd43174-1870-4aef-8d3a-81e15e8a3dfd)

![Screenshot from 2024-11-03 11-22-57](https://github.com/user-attachments/assets/4181e19d-81b6-4547-851a-7ac6376aaf45)


**sky130_fd_sc_hd__ss_100C_1v40.lib:**

![Screenshot from 2024-11-03 11-23-18](https://github.com/user-attachments/assets/bbbb34f5-46b5-4684-bc7a-fe67c436af6e)

![Screenshot from 2024-11-03 11-23-12](https://github.com/user-attachments/assets/33b9c806-ba9b-455a-acc2-040260f76995)

**sky130_fd_sc_hd__ss_100C_1v60.lib:**

![Screenshot from 2024-11-03 11-23-30](https://github.com/user-attachments/assets/cc2ddb82-f824-47cf-bb09-eafedd8f747e)

![Screenshot from 2024-11-03 11-23-26](https://github.com/user-attachments/assets/5b812d42-0ea1-452f-a406-a558274d4203)

**sky130_fd_sc_hd__ss_n40C_1v28.lib:**

![Screenshot from 2024-11-03 11-23-52](https://github.com/user-attachments/assets/31e7dc07-dff9-44dd-95ab-a65358700919)

![Screenshot from 2024-11-03 11-23-40](https://github.com/user-attachments/assets/00ad4368-89df-4b14-b410-1766ebf501fd)

**sky130_fd_sc_hd__ss_n40C_1v35.lib:**

![Screenshot from 2024-11-03 11-24-40](https://github.com/user-attachments/assets/e12c7eaa-2dcf-4366-acad-f9a17a5a866f)

![Screenshot from 2024-11-03 11-24-16](https://github.com/user-attachments/assets/5e7300ba-dd36-4805-abd9-96b5aba7aa72)

**sky130_fd_sc_hd__ss_n40C_1v40.lib:**

![Screenshot from 2024-11-03 11-25-21](https://github.com/user-attachments/assets/1d30d7a9-35b2-49a2-b85b-c2bfb415c766)

![Screenshot from 2024-11-03 11-24-55](https://github.com/user-attachments/assets/5e442603-e15d-4a51-92e0-54ddfa7f21c0)

**sky130_fd_sc_hd__ss_n40C_1v44.lib:**

![Screenshot from 2024-11-03 11-28-24](https://github.com/user-attachments/assets/bb22a65d-45bf-4363-a43d-944ddb46817a)

![Screenshot from 2024-11-03 11-28-15](https://github.com/user-attachments/assets/1272bd5d-69b2-4df6-b23b-0cd3f87127df)

**sky130_fd_sc_hd__ss_n40C_1v60.lib:**

![Screenshot from 2024-11-03 11-28-46](https://github.com/user-attachments/assets/fb5a7e32-2618-4a40-9f73-d60124a89ed0)

![Screenshot from 2024-11-03 11-28-36](https://github.com/user-attachments/assets/549b5eae-30e9-40f2-b035-6dc49138d631)

**sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part1:**

![Screenshot from 2024-11-03 11-29-23](https://github.com/user-attachments/assets/9bb8f620-31ce-46aa-aa38-c6b9bcf9e072)

![Screenshot from 2024-11-03 11-29-10](https://github.com/user-attachments/assets/1d149c79-57fe-4040-a417-cb11e65f36c9)


**sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part2:**

![Screenshot from 2024-11-03 11-29-57](https://github.com/user-attachments/assets/d23970d6-065a-4397-9434-150449d4cace)

![Screenshot from 2024-11-03 11-29-44](https://github.com/user-attachments/assets/e2675ca4-c894-4f4b-8d61-5bc5a696bdfb)

**sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part3:**

![Screenshot from 2024-11-03 11-30-19](https://github.com/user-attachments/assets/181879a1-38a8-4dc8-9da7-67be19a3224e)

![Screenshot from 2024-11-03 11-30-11](https://github.com/user-attachments/assets/6f7ae392-f51f-448d-8ab7-b156aaeaebdb)

**sky130_fd_sc_hd__ss_n40C_1v76.lib:**

![Screenshot from 2024-11-03 11-30-46](https://github.com/user-attachments/assets/31db73bf-0b8f-41be-b3e3-b6831264edce)

![Screenshot from 2024-11-03 11-30-31](https://github.com/user-attachments/assets/1b5a927a-ac6b-4b51-9560-25f2dbd4355f)

**sky130_fd_sc_hd__tt_025C_1v80.lib:**
![Screenshot from 2024-11-03 11-31-21](https://github.com/user-attachments/assets/37ecc157-00f7-41a4-865b-28a1a31cf19a)

![Screenshot from 2024-11-03 11-30-59](https://github.com/user-attachments/assets/b523e0b7-b17e-4b5c-b9a3-7a6e4f92f167)

**sky130_fd_sc_hd__tt_100C_1v80.lib:**

![Screenshot from 2024-11-03 11-35-48](https://github.com/user-attachments/assets/543fd4cb-a883-4934-9891-833055650399)

![Screenshot from 2024-11-03 11-35-42](https://github.com/user-attachments/assets/3e9fbbdf-beca-4f18-80ae-e1bbebadf6bb)


</details>

</details>


<details>
<summary><strong>Lab Session 13</strong>  Advanced Physical Design using OpenLane using Sky130</summary>

<details>
<summary><strong>Day-1:</strong>  Inception of open-source EDA, OpenLane and Sky130 PDK</summary>

## Inception of open-source EDA, OpenLane and Sky130 PDK

**QFN-48 Package**: The QFN-48 is a compact leadless package with 48 connection pads around its perimeter, providing excellent thermal and electrical performance, ideal for high-density applications.

![Screenshot from 2024-11-11 14-32-57](https://github.com/user-attachments/assets/3f1237c7-c6a6-453f-9655-636f8778eb9c)

**Chip**: An integrated circuit (IC) on a silicon substrate with various functional blocks like memory, processors, and I/O, designed for specific electronics applications.

![Screenshot from 2024-11-11 14-33-11](https://github.com/user-attachments/assets/32a46c31-bde4-46b7-807a-5f09e7a42a82)

**Pads**: Small metallic contact points on a chip or package, used to connect internal circuitry with external connections, enabling signal transfer.

**Core**: The main processing unit of a chip, containing functional logic optimized for power and performance.

**Die**: The section of a silicon wafer containing an individual IC before packaging, hosting all the active circuitry of the chip.

![Screenshot from 2024-11-11 14-33-23](https://github.com/user-attachments/assets/ff797bc6-ea8e-4bd9-be22-e3cf8ce4df95)

**IPs (Intellectual Properties)**: Pre-designed functional modules, such as USB controllers or memory interfaces, licensed for reuse in various designs to save development time and costs.

![Screenshot from 2024-11-11 14-33-32](https://github.com/user-attachments/assets/4e0b10e5-eea2-4b68-a42c-3db071423e38)

---

### Software to Hardware Execution Flow

When running an application on hardware, it first enters the system software layer, which translates it to binary form. Key components here include the Operating System (OS), Compiler, and Assembler.

1. **OS**: Breaks down application functions written in high-level languages (e.g., C, Java) and passes them to a compiler.
2. **Compiler**: Translates functions into hardware-specific low-level instructions.
3. **Assembler**: Converts these instructions into binary code, which the hardware can execute.

![Screenshot from 2024-11-11 14-33-50](https://github.com/user-attachments/assets/0f07a5f9-9ce0-457e-a7af-1caffa64f809)

For instance, take a stopwatch app running on a RISC-V core. The OS generates a function in C, which is sent to the compiler. The compiler produces RISC-V-specific instructions adapted to the architecture. These instructions are then processed by the assembler, converting them to binary code. This binary code is then integrated into the chip layout, allowing the hardware to execute the intended functionality.

![Screenshot from 2024-11-11 14-34-04](https://github.com/user-attachments/assets/1d9b1e0e-1170-4709-98b9-3f2f71f28098)

For the above stopwatch the below figure shows the input and output of the compiler and assembler.

![Screenshot from 2024-11-11 14-34-16](https://github.com/user-attachments/assets/205f26fb-62b5-40d4-8bf2-ef96fc9ff711)

The compiler produces instructions specific to the architecture, and the assembler converts these into corresponding binary patterns. To execute them on hardware, an RTL (written in a Hardware Description Language) interprets and implements the instructions. This RTL design is then synthesized into a netlist, represented by interconnected logic gates. Finally, the netlist undergoes physical design implementation, preparing it for chip fabrication.

![Screenshot from 2024-11-11 14-34-28](https://github.com/user-attachments/assets/f4df4c33-62e9-4a78-9f14-98282aa9c2a2)

---

### Components of ASIC Design

- **RTL IPs**: Verified circuit blocks (adders, flip-flops) in HDL, used to accelerate complex designs.
- **EDA Tools**: Automates ASIC tasks like synthesis, optimization, and timing analysis, ensuring performance meets requirements.
- **PDK Data**: Semiconductor foundry files defining the manufacturing process, ensuring ASIC designs are fabrication-ready.

![Screenshot from 2024-11-11 14-34-40](https://github.com/user-attachments/assets/610fc21f-8262-4d4b-b868-01a9d84b40ca)

---

### Simplified RTL to GDSII Flow

![Screenshot from 2024-11-11 14-34-49](https://github.com/user-attachments/assets/9d8d2664-476d-4cd6-b5b3-7e0aed241a2f)

1. **RTL Design**: Describes circuit function using HDLs like Verilog or VHDL.
2. **RTL Synthesis**: Converts RTL to a gate-level netlist with optimized cells.
3. **Floor and Power Planning**: Lays out major components, power grid, and I/O.
4. **Placement**: Allocates cells to minimize wirelength and signal delay.
5. **Clock Tree Synthesis (CTS)**: Distributes clock signals uniformly to reduce skew.
6. **Routing**: Connects components while meeting design rules.
7. **Sign-off**: Final verification, confirming design readiness for fabrication.
8. **GDSII Generation**: Creates the layout for chip production.

---

### OpenLane ASIC Flow Overview

![Screenshot from 2024-11-11 14-34-58](https://github.com/user-attachments/assets/414fbce3-7665-4375-9123-42a11f41ccec)

1. **RTL Synthesis and Technology Mapping**: Uses Yosys and ABC.
2. **Static Timing Analysis**: Uses OpenSTA.
3. **Floor Planning**: Utilizes init_fp, ioPlacer, pdn, tapcell.
4. **Placement**: Managed by RePLace, Resizer, OpenPhySyn, and OpenDP.
5. **Clock Tree Synthesis**: Uses TritonCTS.
6. **Fill Insertion**: Uses OpenDP.
7. **Routing**: Uses FastRoute/CU-GR (global) and TritonRoute/DR-CU (detailed).
8. **SPEF Extraction**: OpenRCX for parasitic data.
9. **GDSII Output**: Uses Magic and KLayout.
10. **Design Rule Checks**: Magic and KLayout.
11. **Layout vs. Schematic Check**: Uses Netgen.
12. **Antenna Checks**: Handled by Magic.

---

### OpenLane Directory Structure

```plaintext
├── OpenLane            # Tool directory
│   ├── designs         # Holds all designs
│   │   └── picorv32a   # Example design
├── pdks                # PDK-related files
│   ├── skywater-pdk    # Skywater 130nm PDKs
│   ├── open-pdks       # Scripts for open-source tool compatibility
│   ├── sky130A         # Open-source compatible PDK variant
│   │   ├── libs.ref    # Node-specific files (e.g., timing, tech LEF)
│   │   ├── libs.tech   # Tool-specific files (e.g., for KLayout)
```

### Running Synthesis in OpenLane

1. **Navigate and start OpenLane**:
   ```bash
   cd Desktop/work/tools/openlane_working_dir/openlane
   docker
   ./flow.tcl -interactive
   package require openlane 0.9
   prep -design picorv32a
   run_synthesis
   ```

   ![1](https://github.com/user-attachments/assets/79bf5c08-c476-4a13-aafa-fbe3660bab49)


3. **View the Netlist**:
   ```bash
   cd designs/picorv32a/runs/11-11_16-15/results/synthesis/
   gedit picorv32a.synthesis.v
   ```

   ![2](https://github.com/user-attachments/assets/a1181bfc-46e3-47c1-b840-b33829a2bb60)

   ![3](https://github.com/user-attachments/assets/e33278e6-b30b-4a4e-b81d-d5fa7c23eea0)

5. **Yosys Report**:
   ```bash
   cd ../..
   cd reports/synthesis
   gedit 1-yosys_4.stat.rpt
   ```

   ![5](https://github.com/user-attachments/assets/5a482c16-ee27-4e18-8335-5cb1a5ce84e7)


   ![4](https://github.com/user-attachments/assets/ce9c6b15-4c39-468c-a518-a3f2a06bf129)


  

**Report:**

```
28. Printing statistics.

=== picorv32a ===

   Number of wires:              14596
   Number of wire bits:          14978
   Number of public wires:        1565
   Number of public wire bits:    1947
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:              14876
     sky130_fd_sc_hd__a2111o_2       1
     sky130_fd_sc_hd__a211o_2       35
     sky130_fd_sc_hd__a211oi_2      60
     sky130_fd_sc_hd__a21bo_2      149
     sky130_fd_sc_hd__a21boi_2       8
     sky130_fd_sc_hd__a21o_2        57
     sky130_fd_sc_hd__a21oi_2      244
     sky130_fd_sc_hd__a221o_2       86
     sky130_fd_sc_hd__a22o_2      1013
     sky130_fd_sc_hd__a2bb2o_2    1748
     sky130_fd_sc_hd__a2bb2oi_2     81
     sky130_fd_sc_hd__a311o_2        2
     sky130_fd_sc_hd__a31o_2        49
     sky130_fd_sc_hd__a31oi_2        7
     sky130_fd_sc_hd__a32o_2        46
     sky130_fd_sc_hd__a41o_2         1
     sky130_fd_sc_hd__and2_2       157
     sky130_fd_sc_hd__and3_2        58
     sky130_fd_sc_hd__and4_2       345
     sky130_fd_sc_hd__and4b_2        1
     sky130_fd_sc_hd__buf_1       1656
     sky130_fd_sc_hd__buf_2          8
     sky130_fd_sc_hd__conb_1        42
     sky130_fd_sc_hd__dfxtp_2     1613
     sky130_fd_sc_hd__inv_2       1615
     sky130_fd_sc_hd__mux2_1      1224
     sky130_fd_sc_hd__mux2_2         2
     sky130_fd_sc_hd__mux4_1       221
     sky130_fd_sc_hd__nand2_2       78
     sky130_fd_sc_hd__nor2_2       524
     sky130_fd_sc_hd__nor2b_2        1
     sky130_fd_sc_hd__nor3_2        42
     sky130_fd_sc_hd__nor4_2         1
     sky130_fd_sc_hd__o2111a_2       2
     sky130_fd_sc_hd__o211a_2       69
     sky130_fd_sc_hd__o211ai_2       6
     sky130_fd_sc_hd__o21a_2        54
     sky130_fd_sc_hd__o21ai_2      141
     sky130_fd_sc_hd__o21ba_2      209
     sky130_fd_sc_hd__o21bai_2       1
     sky130_fd_sc_hd__o221a_2      204
     sky130_fd_sc_hd__o221ai_2       7
     sky130_fd_sc_hd__o22a_2      1312
     sky130_fd_sc_hd__o22ai_2       59
     sky130_fd_sc_hd__o2bb2a_2     119
     sky130_fd_sc_hd__o2bb2ai_2     92
     sky130_fd_sc_hd__o311a_2        8
     sky130_fd_sc_hd__o31a_2        19
     sky130_fd_sc_hd__o31ai_2        1
     sky130_fd_sc_hd__o32a_2       109
     sky130_fd_sc_hd__o41a_2         2
     sky130_fd_sc_hd__or2_2       1088
     sky130_fd_sc_hd__or2b_2        25
     sky130_fd_sc_hd__or3_2         68
     sky130_fd_sc_hd__or3b_2         5
     sky130_fd_sc_hd__or4_2         93
     sky130_fd_sc_hd__or4b_2         6
     sky130_fd_sc_hd__or4bb_2        2

   Chip area for module '\picorv32a': 147712.918400

```

**Report Summary**:

```
Flop ratio = Number of D Flip flops = 1613  = 0.1084
             ______________________   _____
             Total Number of cells    14876
```

- **Wire Count**: 14,596
- **Cell Count**: 14,876, including specific cells like `sky130_fd_sc_hd__a2111o_2`, `sky130_fd_sc_hd__and2_2`.
- **D Flip-flops**: 1,613 with a flop ratio of 0.1084

</details>

<details>
<summary><strong>Day-2:</strong>  Good floorplan vs bad floorplan and introduction to library cells </summary>

## Good floorplan vs bad floorplan and introduction to library cells 
 
### **Utilization Factor and Aspect Ratio**
In IC floor planning, the utilization factor and aspect ratio are key parameters. The utilization factor is defined as the area occupied by the netlist divided by the total core area. Although a utilization factor of 1 (100%) is ideal, practical designs aim for a factor of 0.5 to 0.6 to provide room for buffer zones, routing channels, and adjustments. The aspect ratio, calculated as height divided by width, determines the shape of the chip. An aspect ratio of 1 indicates a square, while other values create a rectangular layout, with the specific ratio chosen based on functional, packaging, and manufacturing requirements.

```
Utilization Factor =  Area occupied by netlist
                     __________________________
                         Total area of core
                         

Aspect Ratio =  Height
               ________
                Width
```

### **Pre-placed Cells**
Pre-placed cells are key functional blocks—like memory, custom processors, and analog circuits—that are placed manually in fixed positions. These blocks are crucial for performance and are kept fixed during placement and routing to maintain functionality and layout integrity.

### **Decoupling Capacitors**
Decoupling capacitors stabilize power supply voltages near logic circuits during transient events. Acting as local energy reserves, they reduce voltage fluctuations, crosstalk, and EMI, ensuring reliable power delivery to sensitive circuits.

### **Power Planning**
Effective power planning involves creating a power and ground mesh to evenly distribute VDD and VSS across the chip. This arrangement stabilizes power delivery, reduces voltage drops, and enhances efficiency. Multiple power and ground points further support power needs and reduce the risks of instability.

### **Pin Placement**
Strategic pin placement, or I/O planning, is essential for functionality and reliability. Proper pin assignments minimize signal degradation, manage heat dissipation, and support thermal stability. Placing power and ground pins strategically enhances both signal strength and manufacturability.

### **Floorplanning with OpenLANE**
To initiate floorplanning in OpenLANE, execute these commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
```

![6](https://github.com/user-attachments/assets/45b7ab86-7a1a-409b-8512-1faca81e8f3b)

![7](https://github.com/user-attachments/assets/0337802f-8d1d-4f40-923e-ec21cd5dcf91)

Then, in a new terminal, access the floorplan file as follows:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/11-11_16-28/results/floorplan
gedit picorv32a.floorplan.def
```
![8](https://github.com/user-attachments/assets/4e392782-99bb-4dfb-8126-09e68f33bf2f)

According to the floorplan definitions:

- 1000 Unit Distance = 1 Micron
- Die width in unit distance = 660685−0 = 660685  
- Die height in unit distance = 671405−0 = 671405  
- Width in microns = 660685 / 1000 = 660.685 Microns  
- Height in microns = 671405 / 1000 = 671.405 Microns  
- Die area in microns² = 660.685 × 671.405 = 443587.212425 Microns²  

To view the floorplan in Magic:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/11-11_16-28/results/floorplan/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.floorplan.def &
```
![9](https://github.com/user-attachments/assets/d9840e47-8674-4907-aaee-626c976c2180)


### **Decap and Tap Cells**

Decap cells and tap cells are placed to manage power delivery and maintain electrical connectivity across the chip.

![91](https://github.com/user-attachments/assets/7f8e09de-ac57-4f8e-83bd-1d2b556f0737)


### **Unplaced Standard Cells at Origin**

![92](https://github.com/user-attachments/assets/7e09a833-01b6-4e21-bf17-849ed2fc1b94)

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
run_placement
```

![93](https://github.com/user-attachments/assets/70f206ca-ebc8-432f-8176-5a27fa4e3799)

View the placement in Magic with:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/11-11_16-56/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &
```

![94](https://github.com/user-attachments/assets/ea69e54b-2497-4ecc-952e-195cc10be485)

![95](https://github.com/user-attachments/assets/7d8fc7fd-385f-4289-af88-7456b2e51b30)

### **Cell Design and Characterization Flow**
The library provides essential cell information, including various sizes, functionalities, and threshold voltages. A typical design flow includes:

- Inputs: Process Design Kits (PDKs) for DRC & LVS, SPICE models, and library/user-defined specs.
- Steps: Circuit design, layout design (using techniques like Euler’s path and stick diagrams), parasitic extraction, and characterization (timing, noise, power).
- Outputs: CDL, LEF, GDSII, extracted SPICE netlist (.cir), and timing/noise/power .lib files.

### **Standard Cell Characterization Flow**
Standard cell characterization includes:

1. Reading models and tech files
2. Loading the extracted SPICE netlist
3. Recognizing cell behavior
4. Reading subcircuits
5. Applying power sources
6. Stimulating characterization setup
7. Setting output capacitance loads
8. Running simulation commands

These steps are processed by the GUNA software to produce timing, noise, and power models.

### **Timing Parameters**

| Timing Definition     | Value       |
|-----------------------|-------------|
| slew_low_rise_thr     | 20%         |
| slew_high_rise_thr    | 80%         |
| slew_low_fall_thr     | 20%         |
| slew_high_fall_thr    | 80%         |
| in_rise_thr           | 50%         |
| in_fall_thr           | 50%         |
| out_rise_thr          | 50%         |
| out_fall_thr          | 50%         |

**Propagation Delay**: Time for an input change to reach 50% of its final value and affect the output similarly.

```
rise delay =  time(out_fall_thr) - time(in_rise_thr)
```

**Transition Time**: Time taken for signal transitions between 10% to 90% or 20% to 80% of signal levels.

```
Fall transition time: time(slew_high_fall_thr) - time(slew_low_fall_thr)
Rise transition time: time(slew_high_rise_thr) - time(slew_low_rise_thr)
```

</details>

<details>
<summary><strong>Day-3:</strong> Design library cell using Magic Layout and ngspice characterization </summary>

## CMOS Inverter NGSPICE Simulations

#### SPICE Deck for a CMOS Inverter Simulation

1. **Netlist Creation**: Define a netlist for the CMOS inverter circuit, labeling nodes clearly (e.g., `input`, `output`, `ground`, and `supply`) for easier identification during SPICE simulation.

2. **Device Sizing**: Define the Width-to-Length (W/L) ratios for the PMOS and NMOS transistors. Typically, the PMOS width is 2x to 3x the NMOS width for balanced drive strength.

3. **Voltage Levels**: Set gate and supply voltages in multiples of the transistor length.

4. **Node Naming**: Assign names (e.g., `VDD`, `GND`, `IN`, `OUT`) to nodes around each component in the SPICE netlist for easier reference.

   <img width="953" alt="Screenshot 2024-11-12 at 11 23 10 PM" src="https://github.com/user-attachments/assets/cbd5664c-8342-4f0c-9cc9-1320c3d1ca68">


5. **Simulation Commands**: For transient analysis, use:
   ``` 
   source [filename].cir 
   run 
   setplot 
   dc1 
   plot out vs in 
   ```

   <img width="938" alt="Screenshot 2024-11-12 at 11 23 32 PM" src="https://github.com/user-attachments/assets/4339530d-407c-4be8-a2de-ecdac84d3523">

#### Simulation and Analysis

- **Switching Threshold (Vm)**: Vm is the input voltage at which the inverter output switches between logic levels. For equal PMOS/NMOS sizes, Vm is around VDD/2. Adjusting PMOS or NMOS sizes shifts Vm higher or lower.

- **SPICE Command for Threshold Calculation**:
   ``` 
   Vin in 0 2.5 
   .op 
   .dc Vin 0 2.5 0.05 
   ```

    <img width="950" alt="Screenshot 2024-11-12 at 11 23 49 PM" src="https://github.com/user-attachments/assets/09eb989c-2a66-4225-b15a-2ded2d9299ee">


- **Transient Analysis for Propagation Delay**: SPICE command for pulse input:
   ``` 
   Vin in 0 0 pulse 0 2.5 0 10p 10p 1n 2n 
   .op 
   .tran 10p 4n 
   ```

    <img width="884" alt="Screenshot 2024-11-12 at 11 28 02 PM" src="https://github.com/user-attachments/assets/4f45f9d0-43ab-494e-8e18-c775f27509ae">

#### Cloning the Custom Inverter Layout

1. Clone the inverter:
   ``` 
   cd Desktop/work/tools/openlane_working_dir/openlane 
   git clone https://github.com/nickson-jose/vsdstdcelldesign 
   cd vsdstdcelldesign 
   cp /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech . 
   magic -T sky130A.tech sky130_inv.mag & 
   ```

   ![Screenshot from 2024-11-12 23-41-52](https://github.com/user-attachments/assets/7a9892ee-2b6f-4b28-98e1-b0f55c74fc26)

#### CMOS Fabrication Process (16 Masks)

1. **Substrate Preparation**: The process begins with silicon wafer preparation as the base for the circuit.

2. **N-Well Formation**: Phosphorus impurities are implanted or diffused to create N-well regions on the substrate.

3. **P-Well Formation**: P-well regions are formed similarly, using boron or other dopants through ion implantation or diffusion.

4. **Gate Oxide Deposition**: A thin layer of silicon dioxide is deposited to act as the gate insulator.

5. **Polysilicon Deposition**: A polysilicon layer is deposited on the gate oxide to form the gate electrode.

6. **Polysilicon Masking and Etching**: Areas where polysilicon should remain are defined with a photoresist mask, and unprotected sections are etched away.

7. **N-Well Masking and Implantation**: A mask preserves N-well regions while phosphorus or similar impurities are implanted in other areas.

8. **P-Well Masking and Implantation**: A mask protects P-well regions, allowing boron or equivalent dopants to be implanted elsewhere.

9. **Source/Drain Implantation**: Using masks, dopants (e.g., arsenic for NMOS, boron for PMOS) are implanted to form the source and drain regions.

10. **Gate Formation**: The gate electrode is defined by etching the polysilicon layer, guided by a mask.

11. **Source/Drain Masking and Etching**: Masks define the source and drain areas, followed by etching to clear the oxide from those regions.

12. **Contact/Via Formation**: Holes are etched through the oxide layer to expose areas like the source/drain or polysilicon gates for contacts.

13. **Metal Deposition**: A metal layer, usually aluminum or copper, is deposited to create electrical interconnections.

14. **Metal Masking and Etching**: Metal interconnect patterns are defined using a photoresist mask, with etching to remove unneeded metal.

15. **Passivation Layer Deposition**: A protective silicon dioxide or nitride layer is applied to shield metal interconnections.

16. **Final Testing and Packaging**: Rigorous testing ensures chip functionality, after which functional chips are separated, packaged, and prepared for deployment.

    <img width="773" alt="Screenshot 2024-11-12 at 11 46 46 PM" src="https://github.com/user-attachments/assets/1b5b48f3-ee2d-47a5-8ebd-41614f33b050">

#### Inverter Layout

![Screenshot from 2024-11-12 23-54-13](https://github.com/user-attachments/assets/2a56754f-c532-49fd-9b5b-fb856f12012a)

![Screenshot from 2024-11-12 23-54-26](https://github.com/user-attachments/assets/7674039b-6ed1-4ed1-9897-902f042e7096)

![Screenshot from 2024-11-12 23-54-39](https://github.com/user-attachments/assets/7d601e97-0fd2-458a-908f-90a123c57d53)

![Screenshot from 2024-11-12 23-55-26](https://github.com/user-attachments/assets/1445b939-6717-4fb0-8ff4-7a4edb397fbd)

![Screenshot from 2024-11-12 23-55-53](https://github.com/user-attachments/assets/da582617-e15b-47c5-b1f5-bd0777e9461e)

#### SPICE Extraction with Magic

Run commands in `tkcon` to extract and generate SPICE:
``` 
pwd 
extract all 
ext2spice cthresh 0 rthresh 0 
ext2spice 
```

![Screenshot from 2024-11-13 00-06-58](https://github.com/user-attachments/assets/da8b3fa8-5e39-480e-a472-58a994479b1a)

#### Modifying SPICE File for Transient Analysis

![Screenshot from 2024-11-13 00-07-35](https://github.com/user-attachments/assets/caa04964-e21d-49b0-9f7b-4c76b94fda3c)

![Screenshot from 2024-11-13 00-07-42](https://github.com/user-attachments/assets/0e09dbd7-2872-48c8-981a-b9ab25284ab6)

Edit `sky130_inv.spice`:
```
* SPICE3 file created from sky130_inv.ext - technology: sky130A

.option scale=0.01u
.include ./libs/pshort.lib
.include ./libs/nshort.lib

M1000 Y A VGND VGND nshort_model.0 w=35 l=23
+  ad=1.44n pd=0.152m as=1.37n ps=0.148m
M1001 Y A VPWR VPWR pshort_model.0 w=37 l=23
+  ad=1.44n pd=0.152m as=1.52n ps=0.156m

VDD VPWR 0 3.3V
VSS VGND 0 0V
Va A VGND PULSE(0V 3.3V 0 0.1ns 0.1ns 2ns 4ns)

.tran 1n 20n
.control
run
.endc
.end
```

To simulate:
``` 
ngspice sky130_inv.spice 
plot y vs time a 
```
![Screenshot from 2024-11-13 00-12-43](https://github.com/user-attachments/assets/86b19c94-3ce9-4e95-8aa3-6833c976202e)

![Screenshot from 2024-11-13 00-13-12](https://github.com/user-attachments/assets/defbf5aa-4975-4f56-bcf1-af4b032145fd)


#### Characterizing Slew Rate and Propagation Delay

Using transient response:
- **Rise Transition**: Time for output to rise from 20% to 80% of max value.
- **Fall Transition**: Time for output to fall from 80% to 20%.
- **Cell Rise/Fall Delay**: Difference in time for 50% output change compared to input transition.

Example calculations:
```
Rise Transition : 2.2424 - 2.1819 = 0.0605 = 60.6 ps
Fall Transition : 4.0955 - 4.05536 =  0.0419 ns = 41.9 ps
Rise Cell Delay =  2.20722 - 2.1501 = 0.05712 = 57.12 ps
Cell Fall Delay : 4.07807 - 4.05 =0.02 ns = 20 ps
```

#### Magic Tool DRC Rules Check

Set up and run:
``` 
cd 
wget http://opencircuitdesign.com/open_pdks/archive/drc_tests.tgz 
tar xfz drc_tests.tgz 
cd drc_tests 
gvim .magicrc 
magic -d XR & 
```

![Screenshot from 2024-11-13 00-18-20](https://github.com/user-attachments/assets/421d67f3-8c6e-46b8-9af5-df1339da4c91)

![Screenshot from 2024-11-13 00-21-58](https://github.com/user-attachments/assets/dc4f6182-faba-4842-a6cb-b1c8f35bb9ae)

Run DRC commands:
``` 
tech load sky130A.tech 
drc check 
drc why 
```

![Screenshot from 2024-11-13 00-33-24](https://github.com/user-attachments/assets/b99c626f-6e9f-4312-a934-31b964dc1a5c)

![Screenshot from 2024-11-13 00-35-16](https://github.com/user-attachments/assets/fe5c1e08-92e6-46b5-9791-34731fd28a46)

<img width="805" alt="Screenshot 2024-11-13 at 12 38 16 AM" src="https://github.com/user-attachments/assets/ddccab54-9579-42a6-80e2-a4b74dc21eea">

</details>

<details>
<summary><strong>Day-4:</strong> pre-layout timing analysis and importance of good clock tree </summary>

## pre-layout timing analysis and importance of good clock tree

Commands to extract `tracks.info` file:

```
cd Desktop/work/tools/openlane_working_dir/openlane/vsdstdcelldesign
cd ../../pdks/sky130A/libs.tech/openlane/sky130_fd_sc_hd/
less tracks.info
```

![Screenshot from 2024-11-13 02-35-59](https://github.com/user-attachments/assets/82177838-476c-4471-a17f-a665dcdba1b3)

Commands to set grid for tkcon window as tracks of locali layer use the following command

```
grid 0.46um 0.34um 0.23um 0.17um
```

![Screenshot from 2024-11-13 02-40-45](https://github.com/user-attachments/assets/5e6843f4-b3d1-413e-97d6-9665e544d4ea)


Now, save it by giving a custon mae

```
save sky130_karinv.mag
```
![Screenshot from 2024-11-13 02-43-18](https://github.com/user-attachments/assets/8621a99d-51fc-409e-acd6-4e62a53b6a1f)


Now, open it by using the following commands:

```
magic -T sky130A.tech sky130_karinv.mag &
```

![Screenshot from 2024-11-13 02-44-19](https://github.com/user-attachments/assets/d5e8ab1e-bbb7-4c0b-a52a-ae19ae96a1e1)



Now, type the following command in tkcon window:

```
lef write
```
![Screenshot from 2024-11-13 02-46-07](https://github.com/user-attachments/assets/7fefb973-a988-4dc3-a1ca-a70c8d878b2c)


Modify config.tcl:

```
# Design
set ::env(DESIGN_NAME) "picorv32a"

set ::env(VERILOG_FILES) "./designs/picorv32a/src/picorv32a.v"
set ::env(SDC_FILE) "./designs/picorv32a/src/picorv32a.sdc"

set ::env(CLOCK_PERIOD) "5.000"
set ::env(CLOCK_PORT) "clk"

set ::env(CLOCK_NET) $::env(CLOCK_PORT)

set ::env(LIB_SYNTH) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"
set ::env(LIB_FASTEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib"
set ::env(LIB_SLOWEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib"
set ::env(LIB_TYPICAL) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"

set ::env(EXTRA_LEFS) [glob $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/src/*.lef]

set filename $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/$::env(PDK)_$::env(STD_CELL_LIBRARY)_config.tcl
if { [file exists $filename] == 1 } {
  source $filename
}
```

Now, run openlane flow synthesis:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
run_synthesis
```

![Screenshot from 2024-11-13 14-27-23](https://github.com/user-attachments/assets/402eb305-8293-4338-a155-7c885827d838)

![Screenshot from 2024-11-13 14-30-18](https://github.com/user-attachments/assets/850bbff6-a9d2-455d-9a0c-8ccc18dd41a4)

![Screenshot from 2024-11-13 14-30-25](https://github.com/user-attachments/assets/88af10ad-cf03-4bf1-bd59-a35499618daf)

![Screenshot from 2024-11-13 14-30-29](https://github.com/user-attachments/assets/0c18335a-ea7b-4df5-be53-e5d7e9e2d96b)

**Delay Tables**

Delay plays a crucial role in cell timing, impacted by input transition and output load. Cells of the same type can have different delays depending on wire length due to resistance and capacitance variations. To manage this, "delay tables" are created, using 2D arrays with input slew and load capacitance for each buffer size as timing models. Algorithms compute buffer delays from these tables, interpolating where exact data isn’t available to estimate delays accurately, preserving signal integrity across varying load conditions.

![image](https://github.com/user-attachments/assets/095a59e1-158c-4870-88e3-b73cb3a3692c)

Fixing slack:

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a -tag 13-11_08-51 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
echo $::env(SYNTH_STRATEGY)
set ::env(SYNTH_STRATEGY) "DELAY 3"
echo $::env(SYNTH_BUFFERING
echo $::env(SYNTH_SIZING)
set ::env(SYNTH_SIZING) 1
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```

![Screenshot from 2024-11-13 14-38-01](https://github.com/user-attachments/assets/1eec47f5-27d0-4e46-8a18-01d0d51ecbb3)

![Screenshot from 2024-11-13 14-38-03](https://github.com/user-attachments/assets/beedf1e2-0762-466a-bd22-6aa1bedc3321)

![Screenshot from 2024-11-13 14-38-06](https://github.com/user-attachments/assets/7424c8c9-9877-47f5-b0da-b92ecc738855)

Now, run floorplan

```
run_floorplan
```

![Screenshot from 2024-11-13 14-38-58](https://github.com/user-attachments/assets/7ac7a413-fe91-460b-8534-af9f4e24fcc9)



Since we are facing unexpected un-explainable error while using run_floorplan command, we can instead use the following set of commands available based on information from `Desktop/work/tools/openlane_working_dir/openlane/scripts/tcl_commands/floorplan.tcl` and also based on Floorplan Commands section in `Desktop/work/tools/openlane_working_dir/openlane/docs/source/OpenLANE_commands.md`

```
init_floorplan
place_io
tap_decap_or
```

Now, do placement

```
run_placement
```

![Screenshot from 2024-11-13 14-39-27](https://github.com/user-attachments/assets/53ccc542-286a-43b7-9edf-3975b17facf8)

![Screenshot from 2024-11-13 14-40-26](https://github.com/user-attachments/assets/2d4f855a-2b01-40e4-ad3d-32bb74447023)


Now, open a new terminal and run the below commands to load placement def in magic

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_08-51/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &

```

Custom inverter inserted in placement def

![Screenshot from 2024-11-13 18-26-44](https://github.com/user-attachments/assets/ea1394be-06a7-4127-b365-e3b2104eee2e)

Now, select the cell and type `expand` in tkcon window to view internal layers of cells

![Screenshot from 2024-11-13 18-29-17](https://github.com/user-attachments/assets/f142cf04-95f6-4fe8-8441-f4a50f06de07)

**Timing analysis with ideal clocks using openSTA**

Pre-layout STA will include effects of clock buffers and net-delay due to RC parasitics (wire delay will be derived from PDK library wire model).

![image](https://github.com/user-attachments/assets/a74af227-70dd-4812-930d-b6e9e787a27f)

Since we are getting 0 wns after improved timing run, we will be doing the timing analysis on initial run of synthesis which has lots of violations and no parameters added to improve timing.

Commands to invoke the OpenLANE flow include new lef and perform synthesis:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9set
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
run_synthesis
```

Go, to `Desktop/work/tools/openlane_working_dir/openlane` and create a file `pre_sta.conf`. The contents of the file are:

```
set_cmd_units -time ns -capacitance pF -current mA -voltage V -resistance kOhm -distance um
read_liberty -max /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib
read_liberty -min /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib
read_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_08-51/results/synthesis/picorv32a.synthesis.v
link_design picorv32a
read_sdc /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/my_base.sdc
report_checks -path_delay min_max -fields {slew trans net cap input_pin}
report_tns
report_wns
```

Contents of `my_base.sdc`:

```
set ::env(CLOCK_PORT) clk
set ::env(CLOCK_PERIOD) 12.000
set ::env(SYNTH_DRIVING_CELL) sky130_fd_sc_hd__inv_8
set ::env(SYNTH_DRIVING_CELL_PIN) Y
set ::env(SYNTH_CAP_LOAD) 17.65
create_clock [get_ports $::env(CLOCK_PORT)]  -name $::env(CLOCK_PORT)  -period $::env(CLOCK_PERIOD)
set IO_PCT  0.2
set input_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
set output_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
puts "\[INFO\]: Setting output delay to: $output_delay_value"
puts "\[INFO\]: Setting input delay to: $input_delay_value"


set clk_indx [lsearch [all_inputs] [get_port $::env(CLOCK_PORT)]]
#set rst_indx [lsearch [all_inputs] [get_port resetn]]
set all_inputs_wo_clk [lreplace [all_inputs] $clk_indx $clk_indx]
#set all_inputs_wo_clk_rst [lreplace $all_inputs_wo_clk $rst_indx $rst_indx]
set all_inputs_wo_clk_rst $all_inputs_wo_clk


# correct resetn
set_input_delay $input_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] $all_inputs_wo_clk_rst
#set_input_delay 0.0 -clock [get_clocks $::env(CLOCK_PORT)] {resetn}
set_output_delay $output_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] [all_outputs]

# TODO set this as parameter
set_driving_cell -lib_cell $::env(SYNTH_DRIVING_CELL) -pin $::env(SYNTH_DRIVING_CELL_PIN) [all_inputs]
set cap_load [expr $::env(SYNTH_CAP_LOAD) / 1000.0]
puts "\[INFO\]: Setting load to: $cap_load"
set_load  $cap_load [all_outputs]
```

Commands to run STA:

```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```
![Screenshot from 2024-11-13 18-36-30](https://github.com/user-attachments/assets/f8c6ead2-098a-4922-bead-6c07a11ec03e)

![Screenshot from 2024-11-13 18-36-35](https://github.com/user-attachments/assets/5e5a72ee-60fd-4c71-afed-8abeec4d8f37)

We now try to optimise synthesis.

Go to new terminal and run the follwoing commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 13-11_08-51 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
set ::env(SYNTH_MAX_FANOUT) 4
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```

![Screenshot from 2024-11-13 18-38-35](https://github.com/user-attachments/assets/357af09d-5a63-4952-b4dd-ea02c970761e)

Commands to run STA:

```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```
![Screenshot from 2024-11-13 22-52-48](https://github.com/user-attachments/assets/3fa6dd43-ea1c-4578-8b1f-15741313173b)

![Screenshot from 2024-11-13 22-52-52](https://github.com/user-attachments/assets/b58d256e-fd53-4365-9ea8-811a196adbd4)

![Screenshot from 2024-11-13 22-52-57](https://github.com/user-attachments/assets/0599bfaa-fb55-4a51-beda-1c843c3a151a)


**Basic timing ECO**

NOR gate of drive strength 2 is driving 5 fanouts

![Uploading Screenshot 2024-11-14 at 1.28.09 AM.png…]()


Run the following commands to optimise timing:

```
report_net -connections _13111_
replace_cell _16171_ sky130_fd_sc_hd__nor3_2
report_checks -fields {net cap slew input_pins} -digits 4
```
<img width="1008" alt="Screenshot 2024-11-14 at 1 28 20 AM" src="https://github.com/user-attachments/assets/ebedc8d1-2c4d-4138-a31c-bb6b43edc491">


We can observe that the tns has reduced to -402.45 from -403.54 and wns has reduced to -5.44 from -5.59

**Clock tree synthesis TritonCTS and signal integrity**

Clock Tree Synthesis (CTS) techniques vary based on design needs:

- Balanced Tree CTS: Uses a balanced binary-like tree for equal path lengths, minimizing clock skew but with moderate power efficiency.
- H-tree CTS: Employs an "H"-shaped structure, good for large areas and power efficiency.

   ![image](https://github.com/user-attachments/assets/d1b13f19-a87f-41b6-8f29-a4e00a8e7216)

- Star CTS: Distributes the clock from a central point, minimizing skew but requiring more buffers near the source.
- Global-Local CTS: Combines star and tree topologies, with a global tree for clock domains and local trees within domains, balancing global and local timing.
- Mesh CTS: Uses a grid pattern ideal for structured designs, balancing simplicity and skew.
- Adaptive CTS: Dynamically adjusts based on timing and congestion, offering flexibility but with added complexity.

**Crosstalk**

Crosstalk is interference from overlapping electromagnetic fields between adjacent circuits, causing unwanted signals. In VLSI, it can lead to data corruption, timing issues, and higher power consumption. Mitigation strategies include optimized layout and routing, shielding, and clock gating to reduce dynamic power and minimize crosstalk effects.

![image](https://github.com/user-attachments/assets/21df4ac0-57aa-492e-adfa-7e04ce385680)

**Clock Net Shielding**

Clock net shielding prevents glitches by isolating the clock network, using shields connected to VDD or GND that don’t switch. It reduces interference by isolating clocks from other signals, often with dedicated routing layers and clock buffers. Additionally, clock domain isolation helps prevent cross-domain interference, avoiding metastability and maintaining synchronization.

![image](https://github.com/user-attachments/assets/bf85dd84-dc29-4962-877a-ce4f535bab2c)

Now to insert this updated netlist to PnR flow and we can use write_verilog and overwrite the synthesis netlist but before that we are going to make a copy of the old old netlist:

Run the following commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_08-51/results/synthesis/
ls
cp picorv32a.synthesis.v picorv32a.synthesis_old.v
ls
```

Commands to write verilog:

```
write_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_08-51/results/synthesis/picorv32a.synthesis.v
exit
```
Verified that the netlist is overwritten

![Screenshot from 2024-11-13 18-46-39](https://github.com/user-attachments/assets/6114fd42-47e6-4d90-9f10-ac0392e303b4)

Now, run the following commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 13-11_08-51 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_STRATEGY) "DELAY 3"
set ::env(SYNTH_SIZING) 1
run_synthesis
init_floorplan
place_io
tap_decap_or
run_placement
run_cts
```

![Screenshot from 2024-11-13 18-50-47](https://github.com/user-attachments/assets/3fbf78f4-9140-4fd1-a085-8b70a0bd55e5)

![Screenshot from 2024-11-13 18-51-32](https://github.com/user-attachments/assets/8629c0a7-5a50-43b5-815a-ef73bc43b40b)

![Screenshot from 2024-11-13 18-53-13](https://github.com/user-attachments/assets/bd5f9144-6886-45fa-b3e2-169e3972d893)

**Setup timing analysis using real clocks**

A real clock in timing analysis accounts for practical factors like clock skew and clock jitter. Clock skew is the difference in arrival times of the clock signal at different parts of the circuit due to physical delays, which affects setup and hold timing margins. Clock jitter is the variability in the clock period caused by power, temperature, and noise fluctuations, leading to uncertainty in clock edge timing. Both factors are crucial for accurate timing analysis, ensuring the design performs reliably in real-world conditions.

![image](https://github.com/user-attachments/assets/3526c927-e1a9-445a-9dae-22bc7e0446c7)

![image](https://github.com/user-attachments/assets/0c766405-5f9b-4700-a4cd-6fd19e9ea6cc)

Now, enter the following commands for Post-CTS OpenROAD timing analysis:

```
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/13-11_08-51/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/13-11_08-51results/cts/picorv32a.cts.def
write_db pico_cts.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_08-51/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit
```
<img width="1019" alt="Screenshot 2024-11-14 at 1 29 08 AM" src="https://github.com/user-attachments/assets/f09ec34a-7e7a-4467-bf06-fc880fdc7556">

<img width="1007" alt="Screenshot 2024-11-14 at 1 29 17 AM" src="https://github.com/user-attachments/assets/ac9e3380-1e82-4e53-9a32-cc1ed74e4243">

<img width="1006" alt="Screenshot 2024-11-14 at 1 29 33 AM" src="https://github.com/user-attachments/assets/ee06dcb4-380e-4c29-94e6-6d7e62b656a7">


Now, enter the following commands for exploring post-CTS OpenROAD timing analysis by removing 'sky130_fd_sc_hd__clkbuf_1' cell from clock buffer list variable 'CTS_CLK_BUFFER_LIST':

```
echo $::env(CTS_CLK_BUFFER_LIST)
set ::env(CTS_CLK_BUFFER_LIST) [lreplace $::env(CTS_CLK_BUFFER_LIST) 0 0]
echo $::env(CTS_CLK_BUFFER_LIST)
echo $::env(CURRENT_DEF)
set ::env(CURRENT_DEF) /openLANE_flow/designs/picorv32a/runs/13-11_08-51/results/placement/picorv32a.placement.def
run_cts
echo $::env(CTS_CLK_BUFFER_LIST)
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/13-11_08-51/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/13-11_08-51/results/cts/picorv32a.cts.def
write_db pico_cts1.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_08-51/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew transd net cap input_pins} -format full_clock_expanded -digits 4
report_clock_skew -hold
report_clock_skew -setup
exit
echo $::env(CTS_CLK_BUFFER_LIST)
set ::env(CTS_CLK_BUFFER_LIST) [linsert $::env(CTS_CLK_BUFFER_LIST) 0 sky130_fd_sc_hd__clkbuf_1]
echo $::env(CTS_CLK_BUFFER_LIST)
```

<img width="1006" alt="Screenshot 2024-11-14 at 1 29 45 AM" src="https://github.com/user-attachments/assets/09395e8f-3e6e-4f9c-87b4-4eaaf364fdac">


<img width="1001" alt="Screenshot 2024-11-14 at 1 29 53 AM" src="https://github.com/user-attachments/assets/c2cef32e-9b70-4340-843e-91f1e8b53c75">


<img width="1006" alt="Screenshot 2024-11-14 at 1 30 03 AM" src="https://github.com/user-attachments/assets/7b002f8d-34ac-4235-979c-a8575977653f">


</details>

<details>
<summary><strong>Day-5:</strong> Final steps for RTL2GDS using tritonRoute and openSTA </summary>

##  Final steps for RTL2GDS using tritonRoute and openSTA 

### 1. Perform generation of Power Distribution Network (PDN) and explore the PDN layout.

Commands to perform all necessary stages up until now
```

cd Desktop/work/tools/openlane_working_dir/openlane
docker

./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_STRATEGY) "DELAY 3"
set ::env(SYNTH_SIZING) 1
run_synthesis
init_floorplan
place_io
tap_decap_or
run_placement
run_cts
gen_pdn

```
Screenshots of power distribution network run

![Screenshot from 2024-11-14 00-02-24](https://github.com/user-attachments/assets/3d625e37-11e9-4584-bdfe-ef8cbc7f57f7)
![Screenshot from 2024-11-14 00-02-50](https://github.com/user-attachments/assets/36f07b0e-77e8-466a-b912-782d3d3c965f)
![Screenshot from 2024-11-14 00-02-53](https://github.com/user-attachments/assets/9d71f8e2-aaf1-41e3-ad84-5c7ba6009d45)
![Screenshot from 2024-11-14 00-03-02](https://github.com/user-attachments/assets/4226b564-44c6-47a1-b71e-ca6825614578)
![Screenshot from 2024-11-14 00-03-07](https://github.com/user-attachments/assets/5cf49287-29af-4aea-81bc-03c0b3bdd3e1)

<img width="993" alt="Screenshot 2024-11-14 at 1 14 54 AM" src="https://github.com/user-attachments/assets/9a2e38bd-9cae-47d2-9415-49884658d545">

<img width="1010" alt="Screenshot 2024-11-14 at 1 15 02 AM" src="https://github.com/user-attachments/assets/df16bfeb-33a4-488d-96b6-d9d9d33e9077">


## 2. Perfrom detailed routing using TritonRoute and explore the routed layout.
Command to perform routing
```
echo $::env(CURRENT_DEF)
echo $::env(ROUTING_STRATEGY)
run_routing
```
Screenshots of routing run

![Screenshot from 2024-11-14 00-25-50](https://github.com/user-attachments/assets/08b93b7f-bebe-482e-82ec-2cc0a751054b)
![Screenshot from 2024-11-14 00-29-26](https://github.com/user-attachments/assets/e0cdb4e7-b24c-43e2-b7b6-107c961b786b)
![Screenshot from 2024-11-14 00-34-39](https://github.com/user-attachments/assets/83684a88-d6be-471a-8b78-4a76bf2a2322)
![Screenshot from 2024-11-14 00-34-32](https://github.com/user-attachments/assets/57eabce7-2021-4977-8df9-2b2a5eeb7d9b)


<img width="1007" alt="Screenshot 2024-11-14 at 1 15 24 AM" src="https://github.com/user-attachments/assets/507ba59e-e8ce-4c0d-8d42-3f5d6b26c857">

<img width="623" alt="Screenshot 2024-11-14 at 1 18 40 AM" src="https://github.com/user-attachments/assets/975f23b9-3129-40d0-915d-2a12fde2df7d">

Screenshot of fast route guide present in openlane/designs/picorv32a/runs/13-11_18-24/tmp/routing directory

![Screenshot from 2024-11-14 01-10-16](https://github.com/user-attachments/assets/34cdaa8c-3c9b-40f4-a146-cd09a6d637f2)


## 3. Post-Route parasitic extraction using SPEF extractor.
Commands for SPEF extraction using external tool
```c

cd Desktop/work/tools/SPEF_EXTRACTOR

python3 main.py /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_18-24/tmp/merged.lef /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_18-24/results/routing/picorv32a.def
```

## 4. Post-Route OpenSTA timing analysis with the extracted parasitics of the route.
Commands to be run in OpenLANE flow to do OpenROAD timing analysis with integrated OpenSTA in OpenROAD
```
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/13-11_18-24/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/13-11_18-24/results/routing/picorv32a.def
write_db pico_route.db
read_db pico_route.db
read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_18-24/results/synthesis/picorv32a.synthesis_preroute.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
read_spef /openLANE_flow/designs/picorv32a/runs/13-11_18-24/results/routing/picorv32a.spef
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit

```
</details>
</details>

<details>
<summary><strong>Lab Session 14:</strong>OpenRoad Physical Design.</summary>

## Tool Installation

Installing and setting up ORFS:-

```

git clone --recursive https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts

cd OpenROAD-flow-scripts

sudo ./setup.sh

```

Build tool on local machine command:

```

./build_openroad.sh --local

```

To verify Installation:

```

source ./env.sh

yosys -help

openroad -help

cd flow

make

make gui_final

```


Automated RTL2GDS Flow for VSDBabySoC:

- Create a directory named `vsdbabysoc` inside `OpenROAD-flow-scripts/flow/designs/sky130hd`.  
- Copy the folders `gds`, `include`, `lef`, and `lib` from the `VSDBabySoC` folder on your system into this new directory.  

- Ensure the following files are present in each folder:  
  - **gds folder**: `avsddac.gds`, `avsdpll.gds`  
  - **include folder**: `sandpiper.vh`, `sandpiper_gen.vh`, `sp_default.vh`, `sp_verilog.vh`  
  - **lef folder**: `avsddac.lef`, `avsdpll.lef`  
  - **lib folder**: `avsddac.lib`, `avsdpll.lib`  

- Copy the constraints file `vsdbabysoc_synthesis.sdc` from the `VSDBabySoC` folder into the `vsdbabysoc` directory.  
- Copy the files `macro.cfg` and `pin_order.cfg` from the `VSDBabySoC` folder into the same directory.  


Now run the following commands in terminal:

```

cd OpenROAD-flow-scripts

source env.sh

cd flow

```

### Commands for synthesis:

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk synth
```


### Commands for floorplan:

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk floorplan
```



</details>

































