/*
* Main.c
*
*  Created on: Sep 6, 2017
*  Author: Vinay Divakar
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "SPI.h"

/* Enable SPI Debug */
#define SPI_DBG

const int busSpeedHz = 100000;
const int csDelay = 0; // how long to delay after the last bit transfer before deselecting the device 
const int wordLength = 8;

int main()
{ 
    int i = 0;
    if (SPI_DEV1_init(0, busSpeedHz, SPI_SS_LOW,
                      csDelay, wordLength,
                      SPI_MODE3) == -1)
        printf("(Main)spidev1.0 initialization failed\r\n");

    else
        printf("(Main)spidev1.0 initialized - READY\r\n");

#ifdef SPI_DBG
    while (1)

    {
        int transmissionLength = 4;
	unsigned char Tx_spi[transmissionLength];
	unsigned char Rx_spi[transmissionLength];
        Tx_spi[0] = 0xff;
        Tx_spi[1] = 0x22;
        Tx_spi[2] = 0xff;
        Tx_spi[3] = 0x0;

        if (SPIDEV1_transfer(Tx_spi, Rx_spi, transmissionLength) == 0)
        {
            printf("(Main)spidev1.0: Transaction Complete. Sent %d bytes, received: ", transmissionLength);
	    int n = 0;
            for(n = 0; n < transmissionLength; ++n)
            {
                printf("%#02x ", Rx_spi[n]);
            }
            printf("\n");
        }

        else
            printf("(Main)spidev1.0: Transaction Failed\r\n");
        usleep(100000);
        printf("%d\r\n", ++i);
    }
#endif
}

