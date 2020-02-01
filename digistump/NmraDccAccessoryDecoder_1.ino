#include <EEPROM.h>
#include <NmraDcc.h>

// This Example shows how to use the library as a DCC Accessory Decoder or a DCC Signalling Decoder
// It responds to both the normal DCC Turnout Control packets and the newer DCC Signal Aspect packets 
// You can also print every DCC packet by uncommenting the "#define NOTIFY_DCC_MSG" line below

NmraDcc  Dcc ;
DCC_MSG  Packet ;

struct CVPair
{
  uint16_t  CV;
  uint8_t   Value;
};

CVPair FactoryDefaultCVs [] =
{
  {CV_ACCESSORY_DECODER_ADDRESS_LSB, 1},
  {CV_ACCESSORY_DECODER_ADDRESS_MSB, 0},
};

uint8_t FactoryDefaultCVIndex = 0;

#define TURN_ON_SPEED 15
#define TURN_OFF_SPEED -20

long when = millis () + 10;
uint8_t brightness;

struct Light {
  uint8_t pwm;
  int8_t speed;
} Lights [2];

uint8_t cachedState = 0;

void SetLight (uint8_t l, uint8_t on) {
  if (on) {
    Lights [l].pwm = 0;
    Lights [l].speed = TURN_ON_SPEED;
  } else {
    Lights [l].pwm = 255;
    Lights [l].speed = TURN_OFF_SPEED;
  }
}


void notifyCVResetFactoryDefault()
{
  // Make FactoryDefaultCVIndex non-zero and equal to num CV's to be reset 
  // to flag to the loop() function that a reset to Factory Defaults needs to be done
  FactoryDefaultCVIndex = sizeof(FactoryDefaultCVs)/sizeof(CVPair);
};

//const int DccAckPin = 3 ;

// This function is called by the NmraDcc library when a DCC ACK needs to be sent
// Calling this function should cause an increased 60ma current drain on the power supply for 6ms to ACK a CV Read 
void notifyCVAck(void)
{
  Serial.println("notifyCVAck") ;
  
//  digitalWrite( DccAckPin, HIGH );
//  delay( 6 );  
//  digitalWrite( DccAckPin, LOW );
}

// Uncomment to print all DCC Packets
//#define NOTIFY_DCC_MSG
#ifdef  NOTIFY_DCC_MSG
void notifyDccMsg( DCC_MSG * Msg)
{

  if ((Msg->Data[0] != 255) && (Msg->Data[1] != 0)) {
    
  Serial.print("notifyDccMsg: ") ;
  Serial.print(Msg->Size,DEC);
  Serial.print(':');
  for(uint8_t i = 0; i < Msg->Size; i++)
  {
    Serial.print(Msg->Data[i], HEX);
    Serial.write(' ');
  }
  Serial.println();
  }
}
#endif

// This function is called whenever a normal DCC Turnout Packet is received and we're in Board Addressing Mode
//void notifyDccAccTurnoutBoard( uint16_t BoardAddr, uint8_t OutputPair, uint8_t Direction, uint8_t OutputPower )
//{
//  Serial.print("notifyDccAccTurnoutBoard: ") ;
//  Serial.print(BoardAddr,DEC) ;
//  Serial.print(',');
//  Serial.print(OutputPair,DEC) ;
//  Serial.print(',');
//  Serial.print(Direction,DEC) ;
//  Serial.print(',');
//  Serial.println(OutputPower, HEX) ;
//}

// This function is called whenever a normal DCC Turnout Packet is received and we're in Output Addressing Mode
//void notifyDccAccTurnoutOutput( uint16_t Addr, uint8_t Direction, uint8_t OutputPower )
//{
//  Serial.print("notifyDccAccTurnoutOutput: ") ;
//  Serial.print(Addr,DEC) ;
//  Serial.print(',');
//  Serial.print(Direction,DEC) ;
//  Serial.print(',');
//  Serial.println(OutputPower, HEX) ;
//}

// This function is called whenever a DCC Signal Aspect Packet is received
void notifyDccSigOutputState( uint16_t Addr, uint8_t State)
{
//  Serial.print("notifyDccSigOutputState: ") ;
//  Serial.print(Addr,DEC) ;
//  Serial.print(',');
//  Serial.println(State, HEX) ;

  if (cachedState != State) {
    cachedState = State;  

    switch (State) {
    case 0:
      SetLight (0, 1);
      SetLight (1, 0);
      break;
    case 1:
      SetLight (0, 0);
      SetLight (1, 1);
      break;
    case 2:
      SetLight (0, 1);
      SetLight (1, 1);
      break;
    case 3:
      SetLight (0, 0);
      SetLight (1, 0);
      break;
    }
  }
}

//void notifyDccSigState( uint16_t Addr, uint8_t OutputIndex, uint8_t State) 
//{
//  Serial.print("notifyDccSigState: ") ;
//  Serial.print(Addr,DEC) ;
//  Serial.print(',');
//  Serial.println(State, HEX) ;
//}

void setup()
{
  Serial.begin(115200);
  
  // Configure the DCC CV Programing ACK pin for an output
//  pinMode( DccAckPin, OUTPUT );

  pinMode (0, OUTPUT);
  pinMode (1, OUTPUT);

  Serial.println("NMRA DCC Example 1");
  
  // Setup which External Interrupt, the Pin it's associated with that we're using and enable the Pull-Up 
  Dcc.pin(0, 2, 1);
  
  // Call the main DCC Init function to enable the DCC Receiver
  Dcc.init( MAN_ID_DIY, 10, CV29_ACCESSORY_DECODER | CV29_OUTPUT_ADDRESS_MODE, 0 );

  Serial.println("Init Done");
}

void loop()
{
  // You MUST call the NmraDcc.process() method frequently from the Arduino loop() function for correct library operation
  Dcc.process();
  
  if( FactoryDefaultCVIndex && Dcc.isSetCVReady())
  {
    FactoryDefaultCVIndex--; // Decrement first as initially it is the size of the array 
    Dcc.setCV( FactoryDefaultCVs[FactoryDefaultCVIndex].CV, FactoryDefaultCVs[FactoryDefaultCVIndex].Value);
  }



  // Update LEDs
  if (millis () >= when) {
    when = millis () + 20;
//    analogWrite (5, brightness);
//    analogWrite (6, 255-brightness);
//    if (brightness > SPEED)
//      brightness -= SPEED;
//    else
//      brightness = 255;

    uint8_t i;
    for (i = 0; i < 2; i++) {
      if (Lights [i].speed != 0) {        
        if (Lights [i].speed > 0) {          
          if (Lights [i].pwm <= (255 - Lights[i].speed))
            Lights [i].pwm += Lights [i].speed;
          else {
            Lights [i].speed = 0;
            Lights [i].pwm = 255;
          }
        } 
        else {
          if (Lights [i].speed + Lights [i].pwm >= 0)
            Lights [i].pwm += Lights [i].speed;
          else {
            Lights [i].speed = 0;
            Lights [i].pwm = 0;
          }
        }

        analogWrite (0+i, Lights [i].pwm);
      }
      
    }

    
  }
}
