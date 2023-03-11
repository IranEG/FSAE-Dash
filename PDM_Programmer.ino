/*
 * Florida International University
 * Formula SAE PDM Programmer & Diagnostic Software
 * By: Iran E. Garcia
 * c 2018 FIU FSAE
 */
 
#include <SPI.h>
#include <mcp_can.h>
#include <stdint.h>

#define PDM_SA_ADDR 0x1E
#define PROG_SIZE 18

#define SPI_CS_PIN 3

uint32_t CAN_ID = 0x14EF1E11;

uint8_t data[14][8] = {
  {248,241,255,255,252,255,0,145}, // Injector Pwr
  {248,242,255,255,252,255,0, 65}, // Brake Light
  {248,243,255,255,252,255,0, 49}, // Starter
  {248,244,255,255,252,255,0,145}, // GCS Solenoids
  {248,245,255,255,252,255,0,129}, // ECU
  {248,246,255,255,252,255,0,145}, // GCU
  {248,247,255,255,252,255,0,113}, // Fans
  {248,248,255,255,252,255,0,145}, // Wideband
  {248,249,255,255,252,255,0,145}, // Dash
  {248,250,255,255,252,255,0,145}, // Ignition Coil
  {248,251,255,255,252,255,0,145}, // 
  {248,252,255,255,252,255,0,145}, // Fuel Pump
  
  {254,44,28,108,12,76,12,255},
  {255,44,44,28,92,12,108,255}
};

MCP_CAN CAN(SPI_CS_PIN); 

void setup() {
  Serial.begin(115200);
  
  while (CAN_OK != CAN.begin(CAN_250KBPS, MCP_8MHz))
  {
    Serial.println("CAN BUS Shield init fail");
    Serial.println("Init CAN BUS Shield again");
    delay(100);
  }
  Serial.println("CAN Bus Shield Init OK!");
}

void loop() {
  uint8_t len = 0;
  uint8_t buf[8];

  for (int i = 0; i < 14; i++) {
    
    CAN.sendMsgBuf(CAN_ID, 1, 8, data[i]);

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned int canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Get data from ID: 0x");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
    }
   }
}
