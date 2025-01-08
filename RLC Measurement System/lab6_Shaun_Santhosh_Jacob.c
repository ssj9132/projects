#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clock.h"
#include "uart0.h"
#include "tm4c123gh6pm.h"
#include <ctype.h>
#include "wait.h"

#define MAX_CHARS 80
#define MAX_FIELDS 5
bool success = false;

typedef struct _USER_DATA
{
    char buffer[MAX_CHARS+1];
    uint8_t fieldCount;
    uint8_t fieldPosition[MAX_FIELDS];
    char fieldType[MAX_FIELDS];
} USER_DATA;

#define MEAS_C (*((volatile uint32_t *)(0x42000000 +(0x400253FC-0x40000000)*32 + 3*4))) //PF3
#define LOWSIDE_R (*((volatile uint32_t *)(0x42000000 +(0x400063FC-0x40000000)*32 + 5*4))) //PC5
#define INTEGRATE (*((volatile uint32_t *)(0x42000000 +(0x400073FC-0x40000000)*32 + 6*4))) //PD6
#define MEAS_LR (*((volatile uint32_t *)(0x42000000 +(0x400073FC-0x40000000)*32 + 2*4))) //PD2
#define HIGHSIDE_R (*((volatile uint32_t *)(0x42000000 +(0x400073FC-0x40000000)*32 + 0*4))) //PD0
#define SWITCH_1  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 4*4)))//PF4
#define RED_LED      (*((volatile uint32_t *)(0x42000000 + (0x400043FC-0x40000000)*32 + 6*4)))  // PA6 controls red led bit 6
#define GREEN_LED    (*((volatile uint32_t *)(0x42000000 + (0x4000253FC-0x40000000)*32 + 3*4))) //PF3

#define MEAS_C_MASK 8
#define LOWSIDE_R_MASK  32
#define INTEGRATE_MASK  64
#define MEAS_LR_MASK  4
#define HIGHSIDE_R_MASK  1
#define SWITCH_1_MASK 16
#define RED_LED_MASK  64
#define GREEN_LED_MASK  8
#define COMP_MASK 128

uint32_t timerValue=0;


//-----------------------------------------------------------------------------
// Subroutines
//-----------------------------------------------------------------------------
void compISR()
{
    putsUart0("Triggerd");
    timerValue = TIMER1_TAV_R;
    GREEN_LED ^= 1;
    LOWSIDE_R = 1;
//    TIMER1_ICR_R = TIMER_ICR_TATOCINT;
    COMP_ACMIS_R = COMP_ACMIS_IN0;
    COMP_ACINTEN_R &= ~COMP_ACINTEN_IN0;
    success = true;

}

void inittimer()
{


    TIMER1_CTL_R &= ~TIMER_CTL_TAEN;                // Turn off timer before reconfiguring
    TIMER1_CFG_R = TIMER_CFG_32_BIT_TIMER;          // Configure as 32-bit timer (concatenated mode)
    TIMER1_TAMR_R = TIMER_TAMR_TAMR_1_SHOT | TIMER_TAMR_TACDIR; // Configure for one-shot mode, count up
    TIMER1_TAV_R = 0;                               // Set TAV to 0 for initial value
//    TIMER1_IMR_R = TIMER_IMR_TATOIM;                // Enable timeout interrupts in timer module
    TIMER1_CTL_R |= TIMER_CTL_TAEN;                 // Turn on timer
}



void initcomp()
{



        COMP_ACREFCTL_R |= COMP_ACREFCTL_EN;
        COMP_ACREFCTL_R &= ~COMP_ACREFCTL_RNG;
        COMP_ACREFCTL_R |= COMP_ACREFCTL_VREF_M;
        COMP_ACCTL0_R |= COMP_ACCTL0_CINV;
        COMP_ACCTL0_R |= COMP_ACCTL0_ISLVAL;
        COMP_ACCTL0_R |= COMP_ACCTL0_ASRCP_REF;
        waitMicrosecond(10);
        NVIC_EN0_R =1 << (INT_COMP0-16);
}
// Initialize Hardware
void initHw()
{
    // Initialize system clock to 40 MHz
    initSystemClockTo40Mhz();


       SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0 | SYSCTL_RCGCGPIO_R2 | SYSCTL_RCGCGPIO_R3| SYSCTL_RCGCGPIO_R5 ;
       SYSCTL_RCGCACMP_R |= SYSCTL_RCGCACMP_R0;
       SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;      // Enable clock to Timer 1
       _delay_cycles(3);
    //  LED and pushbutton pins
       GPIO_PORTF_DIR_R |= MEAS_C_MASK ;
       GPIO_PORTC_DIR_R |= LOWSIDE_R_MASK ;
       GPIO_PORTD_DIR_R |= INTEGRATE_MASK ;   // bits 1 and 3 are outputs, other pins are inputs
       GPIO_PORTD_DIR_R |= MEAS_LR_MASK;               // bit 4 is an input
       GPIO_PORTD_DIR_R |= HIGHSIDE_R_MASK ;
       GPIO_PORTA_DIR_R |= RED_LED_MASK ;
       GPIO_PORTF_DIR_R |= GREEN_LED_MASK ;
       GPIO_PORTC_DEN_R &= ~COMP_MASK;
       GPIO_PORTC_AFSEL_R |= COMP_MASK;
       GPIO_PORTC_AMSEL_R |= COMP_MASK;
       //Configures LED pins as outputs by setting corresponding bits in the DIR(direction) reg of each port


       GPIO_PORTF_DIR_R &= ~SWITCH_1_MASK; //pushbutton pins are sets as inputs by clearing correspd bits
       //setting a bit to 0 makes the pin an input and bit to 1 = output

       //enables dig functionality of leds and sw pins => den reg controls whether pins in that port are enabled
         GPIO_PORTF_DEN_R |= MEAS_C_MASK ;
         GPIO_PORTC_DEN_R |= LOWSIDE_R_MASK ;
         GPIO_PORTD_DEN_R |= INTEGRATE_MASK ;   // bits 1 and 3 are outputs, other pins are inputs
         GPIO_PORTD_DEN_R |= MEAS_LR_MASK;               // bit 4 is an input
         GPIO_PORTD_DEN_R |= HIGHSIDE_R_MASK ;
         GPIO_PORTA_DEN_R |= RED_LED_MASK ;
         GPIO_PORTF_DEN_R |= GREEN_LED_MASK ;
         GPIO_PORTF_DEN_R |= SWITCH_1_MASK;



                                                            // enable LEDs and pushbuttons // enable internal pull-up for push button
         GPIO_PORTF_PUR_R |= SWITCH_1_MASK;         //Pull down reg enabled for sw1




}

//-----------------------------------------------------------------------------
// UART Input Function
//-----------------------------------------------------------------------------
void getsUart0(USER_DATA *data)
{
    uint8_t count = 0;
    while (true)
    {
        char c = getcUart0();

        if ((c == 8 || c == 127) && count > 0)
        {
            count--;
        }
        else if (c == 13)
        {
            data->buffer[count] = '\0';
            return;
        }
        else if (c >= 32)
        {
                data->buffer[count] = c;
                count++;
                if (count == MAX_CHARS)
                {
                   data->buffer[count] = '\0';
                   return;
                }
        }


    }
}




void parseFields(USER_DATA *data)
{
    bool prevDelim = true;
    data->fieldCount = 0;
    uint8_t N = MAX_CHARS+1;
    uint8_t i;

    for(i = 0; i < N; i++)
    {
        char c = data->buffer[i];

        if(data->fieldCount >= MAX_FIELDS)
        {
            return;
        }

        if (prevDelim && isalpha(c))
        {
            data->fieldPosition[data->fieldCount] = i;
            data->fieldType[data->fieldCount] = 'a';
            data->fieldCount++;
            prevDelim = false;
        }

        else if(prevDelim && isdigit(c))
        {
            data->fieldPosition[data->fieldCount] = i;
            data->fieldType[data->fieldCount] = 'n';
            data->fieldCount++;
            prevDelim = false;
        }

        else if(c == ' ' || c==',')
        {
            data->buffer[i] = '\0';
            prevDelim = true;
        }
    }

}

char* getFieldString(USER_DATA* data, uint8_t fieldNumber)
{
    if(fieldNumber <= data->fieldCount)
    {
        return &data->buffer[data->fieldPosition[fieldNumber]];
    }
    else
    {
        return NULL;
    }
}

int32_t getFieldInteger(USER_DATA* data, uint8_t fieldNumber)
{
    if(fieldNumber < data->fieldCount || data -> fieldType[fieldNumber] == 'n')
    {
         return atoi(&data->buffer[data->fieldPosition[fieldNumber]]);
    }
    else
    {
        return 0;
    }
}


bool strCompare(const char str1[], const char str2[])
{
    int i = 0;


    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
        i++;
    }
    return true;
}


bool isCommand(USER_DATA* data, const char strCommand[],uint8_t minArguments)
{
    char* fieldA = getFieldString(data,0);
    if(!(strCompare(strCommand, fieldA)))
    {
        return false;
    }

    if((data->fieldCount -1) < minArguments)
    {
        return false;
    }

    return true;
}


void clearBuffer(USER_DATA* data)
{

    uint8_t i;
    for (i = 0; i < MAX_CHARS; i++)
    {
        data->buffer[i] = '\0';
    }


    data->fieldCount = 0;
}


//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
int main(void)
{
    USER_DATA data;
    float Resistance;
    float Capacitance;
    float Inductance;
    char str[50];

    initHw();
    //initgpio();
    initcomp();
    inittimer();


    initUart0();
    setUart0BaudRate(115200, 40e6);
    COMP_ACMIS_R |= COMP_ACMIS_IN0;

    while (true)
    {
        putsUart0(">"); // Display the prompt at the start of each loop
        getsUart0(&data);  // Get input from UART
        putcUart0('\n');
        putsUart0(data.buffer);
        putcUart0('\n');
        parseFields(&data);



        if (isCommand(&data, "r", 0))
        {
            //COMP_ACINTEN_R =ADC_DCISC_DCINT0;
            HIGHSIDE_R = 0;
            MEAS_C =0;
            INTEGRATE =1;
            MEAS_LR = 0;
            LOWSIDE_R = 1;
            waitMicrosecond(10000);
            LOWSIDE_R = 0;
            MEAS_LR = 1;
            TIMER1_TAV_R = 0;

            success = false;
            COMP_ACINTEN_R |= COMP_ACINTEN_IN0;
            while(!success);
            success = false;
            snprintf(str, 50, "Ticks = %d\n", timerValue);
            putsUart0(str);
            Resistance = ((float)timerValue / 40000000.0) / (1.379 * 0.000001);
            snprintf(str,sizeof(str), "Resistance = %f\n", Resistance);
            putsUart0(str);


        }
        else if (isCommand(&data, "c", 0))
        {

                        MEAS_LR =0;
                        INTEGRATE=0;
                        MEAS_C = 1;
                        HIGHSIDE_R= 1;
                        LOWSIDE_R = 1;
                        waitMicrosecond(1000000);
                        LOWSIDE_R = 0;
                        COMP_ACMIS_R |= COMP_ACMIS_IN0;
                        TIMER1_CTL_R |= TIMER_CTL_TAEN;
                        TIMER1_TAV_R = 0;
                        success = 0;
                        COMP_ACINTEN_R |= COMP_ACINTEN_IN0;
                        while(!success);
                        success =false;
                        snprintf(str, 50, "Ticks = %d\n", timerValue);
                        putsUart0(str);
                        Capacitance = ((float)timerValue / 40000000.0) / (1.379 * 100000);
                        snprintf(str,sizeof(str), "Capacitance = %f\n", Capacitance);
                        putsUart0(str);
        }

        else if (isCommand(&data, "l", 0))
        {
                                    HIGHSIDE_R=0;
                                    MEAS_C = 0;
                                    INTEGRATE = 0;
                                    success = 0;
                                    LOWSIDE_R = 1;
                                    COMP_ACMIS_R |= COMP_ACMIS_IN0;
                                    TIMER1_TAV_R = 0;
                                    TIMER1_CTL_R |= TIMER_CTL_TAEN;
                                    MEAS_LR =1;
                                    COMP_ACINTEN_R |= COMP_ACINTEN_IN0;
                                    while(!success);
                                    success = 0;
                                    snprintf(str, 50, "Ticks = %d\n", timerValue);
                                    putsUart0(str);
                                    Inductance = ((float)timerValue / 40000000.0) * (33 / 1.379);
                                    snprintf(str,sizeof(str), "Inductance = %f\n", Inductance);
                                    putsUart0(str);
        }

        else if (isCommand(&data, "measc", 0))
        {
            HIGHSIDE_R=0;
            MEAS_C = 1;
            INTEGRATE = 0;
            LOWSIDE_R = 1;
            MEAS_LR =0;
        }

        else if (isCommand(&data, "measlr", 0))
                {
                    HIGHSIDE_R=0;
                    MEAS_C = 0;
                    INTEGRATE = 0;
                    LOWSIDE_R = 0;
                    MEAS_LR =1;
                }

        else if (isCommand(&data, "highside", 0))
                {
                    HIGHSIDE_R=1;
                    MEAS_C = 0;
                    INTEGRATE = 0;
                    LOWSIDE_R = 0;
                    MEAS_LR =0;
                }

        else if (isCommand(&data, "lowside", 0))
                {
                    HIGHSIDE_R=0;
                    MEAS_C = 0;
                    INTEGRATE = 0;
                    LOWSIDE_R = 1;
                    MEAS_LR =0;
                }

        else if (isCommand(&data, "integrate", 0))
                {
                    HIGHSIDE_R=0;
                    MEAS_C = 0;
                    INTEGRATE = 1;
                    LOWSIDE_R = 0;
                    MEAS_LR =0;
                }

        else
        {
            putsUart0("Invalid Command\n");
            putcUart0('\n');
        }
        clearBuffer(&data);

    }


}
