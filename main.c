#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE     (10)   /* Each record has 4 unsigned chars */

void UpdateBufferStore (char *readbufptr, unsigned int *storebufptr);
void DumpBufferStore (unsigned int FlushArray[BUFFER_SIZE][4]);

int main()
{
    char rx_buffer[8] = { 0x03, 0x23, 0x04, 0x24, 0x05, 0x25, 0x06, 0x26 };
    unsigned int FlushBuffer[BUFFER_SIZE][4] = { 0 };
    unsigned char BufIdx = 0;

    /* Pretend to receive something */
    while(1)
    {
        if(BufIdx == BUFFER_SIZE)
        {
            DumpBufferStore(FlushBuffer);
            BufIdx = 0;
        }
        else
        {
            UpdateBufferStore(rx_buffer, FlushBuffer[BufIdx]);
            BufIdx++;
        }
    }


    printf("Hello world!\n");
    return 0;
}

void UpdateBufferStore (char *readbufptr, unsigned int *storebufptr)
{
    unsigned char Result;
    unsigned int WheelValue1, WheelValue2, WheelValue3, WheelValue4;

    WheelValue1 = (readbufptr[1] * 256) + readbufptr[0];
    WheelValue2 = (readbufptr[3] * 256) + readbufptr[2];
    WheelValue3 = (readbufptr[5] * 256) + readbufptr[4];
    WheelValue4 = (readbufptr[7] * 256) + readbufptr[6];
    storebufptr[0] = WheelValue1;
    storebufptr[1] = WheelValue2;
    storebufptr[2] = WheelValue3;
    storebufptr[3] = WheelValue4;
}

void DumpBufferStore (unsigned int FlushArray[BUFFER_SIZE][4])
{
    unsigned char Index;
    for(Index = 0; Index < BUFFER_SIZE; Index++)
    {
        printf("%u,%u,%u,%u\n\r", FlushArray[Index][0], FlushArray[Index][1], FlushArray[Index][2], FlushArray[Index][3]);
    }
}
