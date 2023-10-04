# Sound-based-smart-switch
## Table of Contents
[Day 0]()
- Application Overview
- Flowchart
- Blockdiagram
- C code
- Assembly code
  - Unique instructions in assembly code

## Day 0 

Compile the c program using RISCV-V GNU Toolchain and dump the assembly code into obj_dump.txt using the below commands.  

```
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o clap_switch.o clap_switch.c
riscv64-unknown-elf-objdump -d clap_switch.o|less > obj_dump.txt
```
The written obj_dump file can be seen [here](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/blob/main/obj_dump.txt).  

**Note** 
In the above c program, digital read and digital write functions are commented to show how the inputs and outputs are given. For now, we need only the logic which controls the clap_switch.

