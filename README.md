# ASIC_DESIGN
<h2>Lab Session 1</h2>
<h3><u>Objective:</u></h3>
We need to compile and verify a basic C code of sum to numbers from 1 to n using GCC and by using RISC-V GNU compiler toolchain on Ubuntu, then compare the outputs.
<h3><u>Tools required:</u></h3>
<ul>
  <li>GCC(GNU Compiler Collection)</li>
  <li>RISC-V GNU Compiler</li>
</ul>
<h3>Procedure:</h3>
<h4>Compile and verify using GCC Compiler:</h4>
<ol>
  <li><b>Code Snippet:</b></li>
  
    #include <stdio.h>
    int main() {
        int i=0;int sum=0;int n=8;
        for(int i=1;i<=n;i+=1){
          sum+=i;
        }
        printf("The sum of numbers from 1 to %d is %d",n,sum);
        return 0;
    }
  
</ol>
<h4>Compile and verify using RISC-V GNU Compiler:</h4>
