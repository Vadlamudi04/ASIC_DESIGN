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

   - The code in the photo is a Random Number Guessing game where the computer generates a random number within a range, and the user attempts to guess it. The program gives feedback if the guess is too high or low and tracks the number of attempts needed to guess correctly.

      ![PHOTO-2024-08-13-14-37-07](https://github.com/user-attachments/assets/6cd8e9c9-2a3b-4880-8221-6d846f713d24)

   - The below photo shows the output obtained by running the above C code using a standard GCC compiler.

     ![l5-2](https://github.com/user-attachments/assets/43a6b274-2043-4638-851b-d3a702ef2a2e)

   
   - The below photo shows the output obtained by running the above C code using a RISC-V GCC compiler.

     ![l5-3](https://github.com/user-attachments/assets/2ed1805f-6f7d-4649-9941-8c92bc6d969c)

     ### Conclusion:

     - If we look at the above images we can see that output is same using the gcc and the riscv compiler.

</details>
