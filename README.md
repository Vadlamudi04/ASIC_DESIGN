# ASIC_DESIGN
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

