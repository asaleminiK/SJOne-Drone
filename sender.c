#include <stdio.h>
#include <stdint.h>
//#include "mesh.h"
#include "utilities.h"
#include "io.hpp"
#include "wireless.h"
#include "adc0.h"
#include "gpio.hpp"
#include "utilities.h"


int main(void)
{
    GPIO UP(P2_0);
    UP.enablePullUp();
    GPIO DOWN(P2_1);
    DOWN.enablePullUp();
    LPC_PINCON->PINSEL1 |= (1 << 20); //y
    LPC_PINCON->PINSEL3 |= (3 << 28); // x
    char command[4] = " ";
    while (1)
    {
        if(adc0_get_reading(3) > 2200) command[0] = 'F';
        else if(adc0_get_reading(3) < 2200) command[0] = 'B';
        else command [0] = 'N';

        if(adc0_get_reading(4) > 2200) command[0] = 'R';
        else if(adc0_get_reading(4) < 2200) command[0] = 'L';
        else command [1] = 'N';
        mesh_packet_t pkt;
        if (!(UP.read()))
        command[2] = 'U';
        else if (!(DOWN.read())) command[2] = 'D';
        else command[2] = 'N';
        wireless_send(110, mesh_pkt_nack, command, 4, 1);
        delay_ms(100);
    }
}

