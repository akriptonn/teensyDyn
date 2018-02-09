#include <Arduino.h>
#include <packetHandler.hpp>
#define UART_TXRTSE (2)
#define UART_TXRTSPOL (4)
#define BAUD_RATE 1000000

uint8_t starts;

namespace std {
  void __throw_bad_alloc()
  {
    //Serial.println("Unable to allocate memory");
  }

  void __throw_length_error( char const*e )
  {
    //Serial.print("Length Error :");
    //Serial.println(e);
  }
}


void setup() {
    // put your setup code here, to run once:
    Serial.begin(BAUD_RATE);
    Serial2.begin(BAUD_RATE);
    // enable PIN 6 as hardware transmitter RTS with active HIGH.
    //CORE_PIN22_CONFIG = PORT_PCR_MUX(3);
    //UART1_MODEM = UART_TXRTSE | UART_TXRTSPOL; 
    Serial2.transmitterEnable(6);
    starts = 1;
}


void loop() {
    // put your main code here, to run repeatedly:
        //code
    if ((Serial.available())&&(1))
    {
        std::vector <unsigned char> test;
        test.push_back(0x18);
        test.push_back(0x01);
        DynamixelPacket *gg = new DynamixelPacket(0xFE,0x03,test);
        //eof
        starts = 0;
        gg -> transaction();
        delay(1000);
        delete gg;
        Serial.println();
        while (Serial2.available()){
            Serial.printf("%x ",Serial2.read());
        }
        
        Serial.println();
        std::vector <unsigned char> test2;
        test2.push_back(0x1E);
        test2.push_back(0x00);
        test2.push_back(0x08);
        DynamixelPacket *vgg = new DynamixelPacket(0xFE,0x03,test2);
        vgg -> transaction();
        delay(500);
        delete vgg;
        Serial.println();
          while (Serial2.available()){
            Serial.printf("%x ",Serial2.read());
        }
        std::vector <unsigned char> test3;
        test3.push_back(0x1E);
        test3.push_back(0xC4);
        test3.push_back(0x09);
        vgg = new DynamixelPacket(0xFE,0x03,test3);
        vgg -> transaction();
        delay(500);
        delete vgg;
        Serial.println();
          while (Serial2.available()){
            Serial.printf("%x ",Serial2.read());
        }
        Serial.flush();
    }
}

