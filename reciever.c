#include <stdio.h>
#include <stdint.h>
//#include "mesh.h"
#include "utilities.h"
#include "io.hpp"
#include "wireless.h"
#include "gpio.hpp"
#include "lpc_pwm.hpp"

int main(void)
{
    PWM motor1(PWM::pwm1, 300);
    PWM motor2(PWM::pwm2, 300);
    PWM motor3(PWM::pwm3, 300);
    PWM motor4(PWM::pwm4, 300);
    //    motor1.set(45);
    //    delay_ms(1500);
    //Arm the ESCs
    motor1.set(57);
    motor2.set(57);
    motor3.set(57);
    motor4.set(57);
    delay_ms(2000);
    motor1.set(36);
    motor2.set(36);
    motor3.set(36);
    motor4.set(36);
    delay_ms(2000);
    int d = 0;
    char a, b, c = ' ';
    while (1)
    {

        mesh_packet_t pkt;
        mesh_service();
        if (wireless_get_rx_pkt(&pkt, 100))
        {
            a = (pkt.data[0]);
            b = (pkt.data[1]);
            c = (pkt.data[2]);
            if (c == 'U')
            {
                motor1.set(41);
                motor2.set(41);
                motor3.set(41);
                motor4.set(41);
            }
            else if (c == 'D')
            {
                motor1.set(36);
                motor2.set(36);
                motor3.set(36);
                motor4.set(36);
                break;
            }
            
            else if (b == 'L')
            {
                motor1.set(38);
                motor2.set(41);
                motor3.set(41);
                motor4.set(38);
            }
            else if (b == 'R')
            {
                motor1.set(41);
                motor2.set(38);
                motor3.set(38);
                motor4.set(41);
            }
            
            else if (a == 'F')
            {
                motor1.set(41);
                motor2.set(41);
                motor3.set(38);
                motor4.set(38);
            }
            else if (a == 'B')
            {
                motor1.set(38);
                motor2.set(38);
                motor3.set(41);
                motor4.set(41);
            }
            else
            {
                motor1.set(38);
                motor2.set(38);
                motor3.set(38);
                motor4.set(38);
            }
            d++;
            LD.setNumber(d);
            /* Check if we were asked for an application ACK */
        }
    }
}

