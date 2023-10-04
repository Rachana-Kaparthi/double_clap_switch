# Sound-based-smart-switch
## Table of Contents
[Introduction](#introduction)
- [Application Overview](#application-overview)
- [Flowchart](#flowchart)
- [C code](#c-code)
- [Assembly code conversion](#assembly-code-conversion)
  - [Unique instructions in assembly code](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/edit/main/README.md#unique-instructions-in-assembly-code)

## Introduction 
### Application Overview
  I am trying to build a smart switch on detection of two consecutive claps from the user. Initially we set the sensor threshold so that any sound heard above the threshold is detected as high by the sensor and the same is sent to the processor, processor waits for the seecond high signal to turn the switch on and if the switch is already on then the switch is set to low upon to two consecutive high sound levels. I have set the minimum time delay between 2 consecutive claps as 200 ms so that the processor is not detecting the same clap twice before the sound is elapsed and the maximum delay between the claps is set to 500 ms before any action is taking place. The output of the switch can be connected to any home appliance such as light, fan etc using relays or motors at the output.

### Flowchart of the code
![](![clap_switch](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/assets/140998470/f071487a-66b3-4e08-a2cd-db3a35716b89)  

### C code  
C code for the Clap switch is shown below:  
```
#include <stdio.h>
#include <time.h>

#define DIFF_MAX 500000

int firstClap = 0;
int secondClap = 0;
int offClap1 = 0;
clock_t firstClaptime;
clock_t secondClaptime;
clock_t offClap1time;

int delay(int number_of_milli_seconds)
{
    // Converting time into milli_seconds

    int clocks = 1000 * number_of_milli_seconds;

    // Storing start time

    clock_t start_time = clock();

    // looping till required time is not achieved

    while (clock() < start_time + clocks)
        ;
}

void read()
{
    // sensor_input = digital_read(0);
    int sensor_input = 1;
    int output;
    if (sensor_input == 1)
    {
        if (firstClap == 0)
        {
            firstClap = 1;
            firstClaptime = clock();
        }
        else if (firstClap == 1 && secondClap == 0)
        {
            if (clock() - firstClaptime < DIFF_MAX)
            {
                secondClap = 1;
                output = 1;
                // digitalWrite(3, output);
            }
            else
            {
                firstClap = 0;
            }
        }
        else if (firstClap == 1 && secondClap == 1)
        {
            if (offClap1 == 0)
            {
                offClap1 = 1;
                offClap1time = clock();
            }
            else if (offClap1 == 1)
            {
                if (clock() - offClap1time < DIFF_MAX)
                {
                    firstClap = 0;
                    secondClap = 0;
                    output = 0; // digitalwrite(3,output);
                }
                offClap1 = 0;
            }
        }
        delay(200); //// time to wait after a clap (prevents detecting lots of claps as 1 signal)
    }

    if (firstClap == 1 && secondClap == 0 && (clock() - firstClaptime > DIFF_MAX))
    {
        firstClap = 0;
    }
    if (offClap1 == 1 && (clock() - offClap1time > DIFF_MAX))
    {
        offClap1 = 0;
    }
}

int main()
{
    while (1)
    {
        read();
    }

    return (0);
}
```
C code can be compiled by running the below commands in terminal -  
```
gcc clap_switch.c
./a.out
```

Test file for the above C code can be seen [here](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/blob/main/testfiles/clap_switch_test_file.c).   
Below is the output seen upon execution of the test file using gcc compiler-  
![](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/blob/main/images/clap_switch_test_output.png)  


### Assembly code Conversion  

Compile the c program using RISCV-V GNU Toolchain and dump the assembly code into obj_dump.txt using the below commands.  

```
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o clap_switch.o clap_switch.c
riscv64-unknown-elf-objdump -d clap_switch.o|less > obj_dump.txt
```
The written obj_dump.txt file can be seen [here](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/blob/main/obj_dump.txt).  


**Note** 
In the above c program, digital read and digital write functions are commented to show how the inputs and outputs are given. For now, we need only the logic which controls the clap_switch.  

#### Unique instructions in assembly code  

To get the number of instructions, run the python script file instruction_counter.py.  

Suppose your assembly code contains instructions like addi, lw, sw, and so on. Running the instruction_counter.py on this dump_obj.txt would yield:  
![](https://github.com/Rachana-Kaparthi/Sound-based-smart-switch/blob/main/images/total_instructions_used.png)  


