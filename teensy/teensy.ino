//http://forum.arduino.cc/index.php?topic=396450.0


#include <OctoWS2811.h>

const int ledsPerStrip = 144  ;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);







const byte numBytes = (unsigned char)435;
unsigned char receivedBytes[numBytes];
unsigned char numReceived = 0;

boolean newData = false;

void setup() {
  leds.begin();
  leds.show();
  
  Serial.begin(57600);
  //Serial.println("<Arduino is ready>");
}

void loop() {
  recvBytesWithStartEndMarkers();
  handleNewData();
}

void recvBytesWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    byte startMarker = 0x3C;
    byte endMarker = 0x3E;
    byte rb;
   

    while (Serial.available() > 0 && newData == false) {
        rb = Serial.read();

        if (recvInProgress == true) {
            if (rb != endMarker) {
                receivedBytes[ndx] = rb;
                ndx++;
                if (ndx >= numBytes) {
                    ndx = numBytes - 1;
                }
            }
            else {
                receivedBytes[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                numReceived = ndx;  // save the number for use when printing
                ndx = 0;
                newData = true;
            }
        }

        else if (rb == startMarker) {
            recvInProgress = true;
        }
    }
}

void handleNewData() {
    if (newData == true) {
        int p = 0;
        for (unsigned char i = 0 ; i < sizeof(receivedBytes); i += 3 ) {
        //for (unsigned char i = 0 ; i < 185; i += 3 ) {
          leds.setPixel(p, receivedBytes[i], receivedBytes[i+1], receivedBytes[i+2]);
          p++;
        }
        //Serial.print(receivedBytes[180]);
        //Serial.print(6, DEC);
        //leds.setPixel(61, 0, 12, 0);
        leds.show();
        newData = false;
        /*
        long value;
        value = receivedBytes[0];

        Serial.print("$");
        leds.setPixel(value, receivedBytes[1], receivedBytes[2], receivedBytes[3]);
        leds.show();
  
        newData = false;
        */
    }
}
