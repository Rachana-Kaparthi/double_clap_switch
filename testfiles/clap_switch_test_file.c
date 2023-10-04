#include <stdio.h>
#include <time.h>

#define DIFF_MAX 500000

int firstClap = 0;
int secondClap = 0;
int offClap1 = 0;
clock_t firstClaptime;
clock_t secondClaptime;
clock_t offClap1time;

void read(int sensor_input);
int delay(int number_of_milli_seconds);

int main()
{
    int i = 0;
    int j = 0;
    int si = 0;
    while (j < 100)
    {
        if(i == 10) si = 1;
        read(si);
        if(i == 10) { si = 0; i = 0;}
        i++;
        j++;
    }

    return (0);
}

void read(int sensor_input)
{   
    printf("sensorinput value = %d\n", sensor_input);
    // sensor_input = digital_read(0);
    //int sensor_input = 1;
    int output;
    if (sensor_input == 1)
    {
        printf("first_clap_value %d second_clap_value %d\n", firstClap, secondClap);
        if (firstClap == 0)
        {
            firstClap = 1;
            firstClaptime = clock();
            printf("Setting first clap value to 1\n");
        }
        else if (firstClap == 1 && secondClap == 0)
        {
            if (clock() - firstClaptime < DIFF_MAX)
            {
                printf("Switching on the bulb by setting second clap value to 1\n");
                secondClap = 1;
                output = 1;
                // digitalWrite(2, output);
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
                printf("Setting first off clap value to 1\n");
            }
            else if (offClap1 == 1)
            {
                if (clock() - offClap1time < DIFF_MAX)
                {
                    firstClap = 0;
                    secondClap = 0;
                    output = 0; // digitalwrite(2,output);
                    printf("Switching off the bulb by setting first and second clap values to 0\n");
                }
                offClap1 = 0;
            }
        }
        delay(200);
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
