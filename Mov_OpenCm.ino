/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#include <DynamixelWorkbench.h>

#define DXL_BUS_SERIAL1 "1"            //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 "2"            //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 "3"            //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define DXL_BUS_SERIAL4 "/dev/ttyUSB0" //Dynamixel on Serial3(USART3)  <-OpenCR

#define BAUDRATE  1000000

#define DXL_ID18    18
#define DXL_ID1    1
#define DXL_ID2    2
#define DXL_ID3    3
#define DXL_ID4    4
#define DXL_ID5    5
#define DXL_ID6    6
#define DXL_ID7    7
#define DXL_ID8    8
#define DXL_ID9    9
#define DXL_ID10   10
#define DXL_ID11   11

#define DXL_ID12    12
#define DXL_ID13    13
#define DXL_ID14    14
#define DXL_ID15    15
#define DXL_ID16    16
#define DXL_ID17    17

#define vel_ax 400
#define vel_xl 400
#define acc_ax 0
#define acc_xl 0

#define sop_xl_set 412
#define sop_xl_arriba 172
#define sop_xl_abajo  292

#define ext_xl_set 512
#define ext_xl_arriba 0
#define ext_xl_abajo  782

String ser = "0";     //Variable de movimiento
String P = "9";       //Reset
String stand = "1";   //Posicion lista para moverse
String walk = "2";    //Caminar
String back = "3";     //Retroceder
String right = "4";    //Girar a la derecha
String left = "5";     //Girar a la izquierda
String stopall = "6";  //Parar sin reset



DynamixelWorkbench dxl_wb0, dxl_wb1, dxl_wb2, dxl_wb3, dxl_wb4, dxl_wb5;

void setup()
{
  Serial.begin(1000000);
  Serial2.begin(BAUDRATE);
  //while(!Serial); // Open a Serial Monitor
  
  dxl_wb0.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb0.ping(DXL_ID12);
  dxl_wb0.jointMode(DXL_ID12,vel_ax,acc_ax);
  dxl_wb0.ping(DXL_ID18);
  dxl_wb0.jointMode(DXL_ID18,vel_xl,acc_xl);
  dxl_wb0.ping(DXL_ID1);
  dxl_wb0.jointMode(DXL_ID1,vel_xl,acc_xl);

  dxl_wb1.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb1.ping(DXL_ID13);
  dxl_wb1.jointMode(DXL_ID13,vel_ax,acc_ax);
  dxl_wb1.ping(DXL_ID2);
  dxl_wb1.jointMode(DXL_ID2,vel_xl,acc_xl);
  dxl_wb1.ping(DXL_ID3);
  dxl_wb1.jointMode(DXL_ID3,vel_xl,acc_xl);

  dxl_wb2.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb2.ping(DXL_ID14);
  dxl_wb2.jointMode(DXL_ID14,vel_ax,acc_ax);
  dxl_wb2.ping(DXL_ID4);
  dxl_wb2.jointMode(DXL_ID4,vel_xl,acc_xl);
  dxl_wb2.ping(DXL_ID5);
  dxl_wb2.jointMode(DXL_ID5,vel_xl,acc_xl);

  dxl_wb3.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb3.ping(DXL_ID15);
  dxl_wb3.jointMode(DXL_ID15,vel_ax,acc_ax);
  dxl_wb3.ping(DXL_ID6);
  dxl_wb3.jointMode(DXL_ID6,vel_xl,acc_xl);
  dxl_wb3.ping(DXL_ID7);
  dxl_wb3.jointMode(DXL_ID7,vel_xl,acc_xl);

  dxl_wb4.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb4.ping(DXL_ID16);
  dxl_wb4.jointMode(DXL_ID16,vel_ax,acc_ax);
  dxl_wb4.ping(DXL_ID8);
  dxl_wb4.jointMode(DXL_ID8,vel_xl,acc_xl);
  dxl_wb4.ping(DXL_ID9);
  dxl_wb4.jointMode(DXL_ID9,vel_xl,acc_xl);

  dxl_wb5.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb5.ping(DXL_ID17);
  dxl_wb5.jointMode(DXL_ID17,vel_ax,acc_ax);
  dxl_wb5.ping(DXL_ID10);
  dxl_wb5.jointMode(DXL_ID10,vel_xl,acc_xl);
  dxl_wb5.ping(DXL_ID11);
  dxl_wb5.jointMode(DXL_ID11,vel_xl,acc_xl);

  
  

}

void loop()
{
  /*
  if (Serial.available() > 0) {
    ser = Serial.readString();
    ser.trim();
    Serial.println(ser);
  }
  */
  
  if(Serial2.available()> 0){
    ser = (char) Serial2.read();
    Serial.println("Prueba");
    Serial.println(ser); //send data coming from Serial2 to USB(PC)
  }

  if (ser == P) {
    Serial.write("Reset \n");
    dxl_wb0.ping(DXL_ID1);
    dxl_wb0.goalPosition(DXL_ID1, sop_xl_set);
    delay(500);
    dxl_wb1.ping(DXL_ID2);
    dxl_wb1.goalPosition(DXL_ID2, sop_xl_set);
    delay(500);
    dxl_wb2.ping(DXL_ID4);
    dxl_wb2.goalPosition(DXL_ID4, sop_xl_set);
    delay(500);
    dxl_wb3.ping(DXL_ID6);
    dxl_wb3.goalPosition(DXL_ID6, sop_xl_set);
    delay(500);
    dxl_wb4.ping(DXL_ID8);
    dxl_wb4.goalPosition(DXL_ID8, sop_xl_set);
    delay(500);
    dxl_wb5.ping(DXL_ID10);
    dxl_wb5.goalPosition(DXL_ID10, sop_xl_set);
    delay(500);
    dxl_wb0.ping(DXL_ID12);
    dxl_wb0.goalPosition(DXL_ID12, 372);
    delay(500);
    dxl_wb0.ping(DXL_ID18);
    dxl_wb0.goalPosition(DXL_ID18, ext_xl_set);
    delay(500);
    dxl_wb1.ping(DXL_ID13);
    dxl_wb1.goalPosition(DXL_ID13, 512);
    delay(500);
    dxl_wb1.ping(DXL_ID3);
    dxl_wb1.goalPosition(DXL_ID3, ext_xl_set);
    delay(500);
    dxl_wb2.ping(DXL_ID14);
    dxl_wb2.goalPosition(DXL_ID14, 652);
    delay(500);
    dxl_wb2.ping(DXL_ID5);
    dxl_wb2.goalPosition(DXL_ID5, ext_xl_set);
    delay(500);
    dxl_wb3.ping(DXL_ID15);
    dxl_wb3.goalPosition(DXL_ID15, 372);
    delay(500);
    dxl_wb3.ping(DXL_ID7);
    dxl_wb3.goalPosition(DXL_ID7, ext_xl_set);
    delay(500);
    dxl_wb4.ping(DXL_ID16);
    dxl_wb4.goalPosition(DXL_ID16, 512);
    delay(500);
    dxl_wb4.ping(DXL_ID9);
    dxl_wb4.goalPosition(DXL_ID9, ext_xl_set);
    delay(500);
    dxl_wb5.ping(DXL_ID17);
    dxl_wb5.goalPosition(DXL_ID17, 652);
    delay(500);
    dxl_wb5.ping(DXL_ID11);
    dxl_wb5.goalPosition(DXL_ID11, ext_xl_set);
    delay(500);
    
    ser = "0";
  }

  if (ser == stand) {
    Serial.write("Stand \n");
        // Posicionamos todas las patas
        dxl_wb0.ping(DXL_ID1);
        dxl_wb1.ping(DXL_ID2);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb5.ping(DXL_ID10);

        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo-80);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo-80);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo-80);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo-80);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo-80);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo-80);
        
        dxl_wb0.ping(DXL_ID18);
        dxl_wb1.ping(DXL_ID3);
        dxl_wb2.ping(DXL_ID5);
        dxl_wb3.ping(DXL_ID7);
        dxl_wb4.ping(DXL_ID9);
        dxl_wb5.ping(DXL_ID11);

        dxl_wb0.goalPosition(DXL_ID18, ext_xl_abajo);
        dxl_wb1.goalPosition(DXL_ID3, ext_xl_abajo);
        dxl_wb2.goalPosition(DXL_ID5, ext_xl_abajo);
        dxl_wb3.goalPosition(DXL_ID7, ext_xl_abajo);
        dxl_wb4.goalPosition(DXL_ID9, ext_xl_abajo+20);
        dxl_wb5.goalPosition(DXL_ID11, ext_xl_abajo+20);

        //Levantamos
        dxl_wb0.ping(DXL_ID1);
        dxl_wb1.ping(DXL_ID2);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb5.ping(DXL_ID10);
        
        
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo);
        

    ser = "0";
  }

  if (ser == walk) {
    Serial.write("Walk \n");

        //Patas 1,3,5 se levantan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_arriba);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_arriba);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372+30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652+30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512-30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512-30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652+30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372+30);
        delay(100);
        
        //Patas 1,3,5 bajan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo);
        delay(25);
        
        //Patas 2,4,6 se levantan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_arriba);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_arriba);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372-30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512+30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652-30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512+30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652-30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372-30);
        delay(100);

        //Patas 2,4,6 bajan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo);
        delay(300);
        
  }

  if (ser == back) {
    Serial.write("Back \n");

        //Patas 1,3,5 se levantan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_arriba);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_arriba);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372-30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652-30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512+30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512+30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652-30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372-30);
        delay(100);
        
        //Patas 1,3,5 bajan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo);
        delay(25);
        
        //Patas 2,4,6 se levantan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_arriba);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_arriba);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372+30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512-30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652+30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512-30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652+30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372+30);
        delay(100);

        //Patas 2,4,6 bajan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo);
        delay(300);
        
  }

  if (ser == right) {
    Serial.write("Right \n");

        //Patas 1,3,5 se levantan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_arriba);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_arriba);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372-30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652+30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512+30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512-30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652-30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372+30);
        delay(100);
        
        //Patas 1,3,5 bajan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo);
        delay(25);
        
        //Patas 2,4,6 se levantan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_arriba);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_arriba);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372+30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512+30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652-30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512-30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652+30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372-30);
        delay(100);

        //Patas 2,4,6 bajan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo);
        delay(300);
        
  }

  if (ser == left) {
    Serial.write("Left \n");

        //Patas 1,3,5 se levantan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_arriba);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_arriba);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372+30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652-30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512-30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512+30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652+30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372-30);
        delay(100);
        
        //Patas 1,3,5 bajan
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo);
        delay(25);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo);
        delay(25);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo);
        delay(25);
        
        //Patas 2,4,6 se levantan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_arriba);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_arriba);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_arriba);
        delay(30);
        
        //Todas las patas avanzan
        dxl_wb0.ping(DXL_ID12);
        delay(15);
        dxl_wb0.goalPosition(DXL_ID12, 372-30);
        delay(40);
        dxl_wb4.ping(DXL_ID16);
        delay(15);
        dxl_wb4.goalPosition(DXL_ID16, 512-30);
        delay(40);
        dxl_wb5.ping(DXL_ID17);
        delay(15);
        dxl_wb5.goalPosition(DXL_ID17, 652+30);
        delay(40);
        dxl_wb1.ping(DXL_ID13);
        delay(15);
        dxl_wb1.goalPosition(DXL_ID13, 512+30);
        delay(40);
        dxl_wb2.ping(DXL_ID14);
        delay(15);
        dxl_wb2.goalPosition(DXL_ID14, 652-30);
        delay(40);
        dxl_wb3.ping(DXL_ID15);
        delay(15);
        dxl_wb3.goalPosition(DXL_ID15, 372+30);
        delay(100);

        //Patas 2,4,6 bajan
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo);
        delay(25);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo);
        delay(25);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo);
        delay(300);
        
  }

  if (ser == stopall) {
    Serial.write("Stop all \n");
        delay(600);
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo-80);
        delay(50);
        dxl_wb0.ping(DXL_ID12);
        dxl_wb0.goalPosition(DXL_ID12, 372);
        delay(50);
        dxl_wb0.ping(DXL_ID18);
        dxl_wb0.goalPosition(DXL_ID18, ext_xl_abajo);
        delay(50);
        dxl_wb0.ping(DXL_ID1);
        dxl_wb0.goalPosition(DXL_ID1, sop_xl_abajo);
        delay(200);

        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo-80);
        delay(50);
        dxl_wb4.ping(DXL_ID16);
        dxl_wb4.goalPosition(DXL_ID16, 512);
        delay(50);
        dxl_wb4.ping(DXL_ID9);
        dxl_wb4.goalPosition(DXL_ID9, ext_xl_abajo+20);
        delay(50);
        dxl_wb4.ping(DXL_ID8);
        dxl_wb4.goalPosition(DXL_ID8, sop_xl_abajo);
        delay(200);

        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo-80);
        delay(50);
        dxl_wb2.ping(DXL_ID14);
        dxl_wb2.goalPosition(DXL_ID14, 652);
        delay(50);
        dxl_wb2.ping(DXL_ID5);
        dxl_wb2.goalPosition(DXL_ID5, ext_xl_abajo);
        delay(50);
        dxl_wb2.ping(DXL_ID4);
        dxl_wb2.goalPosition(DXL_ID4, sop_xl_abajo);
        delay(200);

        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo-80);
        delay(50);
        dxl_wb5.ping(DXL_ID17);
        dxl_wb5.goalPosition(DXL_ID17, 652);
        delay(50);
        dxl_wb5.ping(DXL_ID11);
        dxl_wb5.goalPosition(DXL_ID11, ext_xl_abajo+20);
        delay(50);
        dxl_wb5.ping(DXL_ID10);
        dxl_wb5.goalPosition(DXL_ID10, sop_xl_abajo);
        delay(200);

        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo-80);
        delay(50);
        dxl_wb1.ping(DXL_ID13);
        dxl_wb1.goalPosition(DXL_ID13, 512);
        delay(50);
        dxl_wb1.ping(DXL_ID3);
        dxl_wb1.goalPosition(DXL_ID3, ext_xl_abajo);
        delay(50);
        dxl_wb1.ping(DXL_ID2);
        dxl_wb1.goalPosition(DXL_ID2, sop_xl_abajo);
        delay(200);


        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo-80);
        delay(50);
        dxl_wb3.ping(DXL_ID15);
        dxl_wb3.goalPosition(DXL_ID15, 372);
        delay(50);
        dxl_wb3.ping(DXL_ID7);
        dxl_wb3.goalPosition(DXL_ID7, ext_xl_abajo);
        delay(50);
        dxl_wb3.ping(DXL_ID6);
        dxl_wb3.goalPosition(DXL_ID6, sop_xl_abajo);
        delay(200);
        
        

    ser = "0";
  }
 
}
