#include "mbed.h"
#include "Dht11.h"
#include "Servo.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "TextLCD.h"

TextLCD lcd = TextLCD(PTE20,PTE21,PTE22,PTE23,PTE29,PTE30,TextLCD::LCD16x2);
Dht11 d(D6);
Servo servoFood(D7);
Servo servoDoor(D3);
AnalogIn moisture(A0);

DigitalOut p2(D9);
DigitalOut myled(LED1);
DigitalIn PIR(D8);
DigitalIn wifi(D2);
const char f = 'f';

int main(){
    int PIR_sensor;
    int feedThePet;
    float value = 0.0f;
    servoDoor.Enable(500, 20000);
    servoFood.Enable(500, 20000);
    Serial s(USBTX, USBRX);
    Serial c(PTE0, PTE1);
    s.baud(9600);
    c.baud(115500);
    while(1){  
        value = moisture;
        wait(1.0f);
        d.read();
        int temp = d.getCelsius();
        int humidity = d.getHumidity();
        char str2[10];
        char str[10];
        sprintf(str, "%d", temp);
        sprintf(str2, "%d", humidity);
        s.printf(str);
        s.printf(str2);
        PIR_sensor = PIR;
        feedThePet = wifi;
        char str3[10];
        sprintf(str3, "%d", feedThePet);
        s.printf(str3);
        myled =! PIR_sensor;
        wait(0.1f);
        wait(1);
        lcd.cls();
        wait(0.001);
        lcd.printf("T: ");
        lcd.printf(str);
        lcd.printf(" C H: ");
        lcd.printf(str2);
        wait(0.01);
        if (PIR_sensor == 1){
            lcd.locate(0,1);
            lcd.printf("Pet is Moving");
            wait(0.01);
            }
           if (temp >= 30){
                    p2.write(1);
                    wait(2);
                    servoDoor.SetPosition(1500);
                    c.putc(f);
                }
             if (value <= 0.6){
                    p2.write(1);
                    wait(2);
                    servoDoor.SetPosition(1500);
                    c.putc(f);
                }
            if (feedThePet == 1 ) {
                    servoFood.SetPosition(2500);
                }
           if (feedThePet == 0){
                    servoFood.SetPosition(1500);
                } else {
                    p2.write(0);
                    }
        }
    }