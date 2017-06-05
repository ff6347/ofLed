#include <PacketSerial.h>
PacketSerial serial;


#include <OctoWS2811.h>

const int ledsPerStrip = 144  ;
const byte numStrips= 1;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);


void setup()
{
  // We must specify a packet handler method so that
  serial.setPacketHandler(&onPacket);
  serial.begin(115200);
  leds.begin();
  initTest();
}


void loop()
{
  // Do other things here.
  
  // The update() method attempts to read in
  // any incoming serial data and emits packets via
  // the user's onPacket(const uint8_t* buffer, size_t size) 
  // method registered with the setPacketHandler() method.  
  //
  // The update() method should be called at the end of the loop().
  serial.update(); 
}

// This is our packet callback.
// The buffer is delivered already decoded.
void onPacket(const uint8_t* buffer, size_t size)
{
  // Make a temporary buffer.
  uint8_t tmp[size]; 
  
  // Copy the packet into our temporary buffer.
  memcpy(tmp, buffer, size); 
  
  // Reverse our temporaray buffer.
  reverse(tmp, size);
  
  // Send the reversed buffer back.
  // The send() method will encode the buffer
  // as a packet, set packet markers, etc.
  serial.send(tmp, size);
}

/// \brief A simple array reversal method.
void reverse(uint8_t* buffer, size_t size)
{
  uint8_t tmp;
  
  for (int i=0; i < size / 2; i++)
  {
    tmp = buffer[i];
    buffer[i] = buffer[size-i-1];
    buffer[size-i-1] = tmp;
  }
}

void initTest()
{
  for (int i = 0 ; i < ledsPerStrip * numStrips ; i++)
    leds.setPixel(i, 20, 0, 0);
  leds.show();
  delay(500);
  for (int i = 0 ; i < ledsPerStrip * numStrips  ; i++)
    leds.setPixel(i, 0, 20, 0);
  leds.show();
  delay(500);
  for (int i = 0 ; i < ledsPerStrip * numStrips  ; i++)
    leds.setPixel(i, 0, 0, 20);
  leds.show();
  delay(500);
  for (int i = 0 ; i < ledsPerStrip * numStrips  ; i++)
    leds.setPixel(i, 0, 0, 0);
  leds.show();
}

