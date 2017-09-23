#include <stdio.h>
#include <stdint.h>
//#include "mesh.h"
#include "utilities.h"
#include "io.hpp"
#include "wireless.h"
#include "lpc_pwm.hpp"
#include <stdio.h>
#include "gpio.hpp"
#include "utilities.h"

//Main code for Tabitha
int main(void)
{
    char a = 'K';
    int i = 0;
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
    //Test to see if the controller is in range.
    wireless_send(115, mesh_pkt_nack, "P", 1, 1 );
    mesh_service();
    mesh_packet_t pkt1;
    if (wireless_get_rx_pkt(&pkt1, 2000)){
    if (pkt1.data[0] == 'K'){
        goto meme;
    }
    }
    else{
        return -1;
    }
    meme:
    //Arming Complete.Spinning up.
    motor1.set(37);
    delay_ms(700);
    motor2.set(37);
    delay_ms(700);
    motor3.set(37);
    delay_ms(700);
    motor4.set(37);
    delay_ms(700);
    for (int d = 36; d < 46; d++)
    {
        motor1.set(d);
        motor2.set(d);
        motor3.set(d);
        motor4.set(d);
        LD.setNumber(d);
        delay_ms(500);
    }
    motor1.set(36);
    motor2.set(36);
    motor3.set(36);
    motor4.set(36);

    while (1)
    {

        if (SW.getSwitch(1))
        {
            motor1.set(57);
            motor2.set(57);
            motor3.set(57);
            motor4.set(57);
        }
        if (SW.getSwitch(2))
        {
            motor1.set(36);
            motor2.set(36);
            motor3.set(36);
            motor4.set(36);
        }
        delay_ms(200);
    }
    bool b = false;
    while (1)
    {

        mesh_service();
        mesh_packet_t pkt;
        printf("Going in\n");
        if (wireless_get_rx_pkt(&pkt, 1))
        {
            if (b)
            {
                motor1.set(37);
                b = false;
            }
            else
            {
                motor1.set(30);
                b = true;
            }
            printf("Going out\n");
            i++;
            LD.setNumber(i);
            /* Check if we were asked for an application ACK */
            if (mesh_is_ack_required(&pkt))
            {
                wireless_send(115, mesh_pkt_ack_rsp, 0, 0, 1);
                printf("sent\n");
            }
        }
    }
}


