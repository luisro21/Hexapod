/************************** Configuration ***********************************/

#include "config.h"

/************************ Example Starts Here *******************************/

int count = 0;

#define RXD2 16
#define TXD2 17


#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;


AdafruitIO_Feed *counter = io.feed("counter");

void setup() {

  // start the serial connection
  Serial.begin(1000000);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  counter->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  counter->get();

  //************Serial 2***************
  Serial2.begin(1000000, SERIAL_8N1, RXD2, TXD2);

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    // save count to the 'counter' feed on Adafruit IO

    /*
    Serial.print("sending -> ");
    Serial.println(count);
    counter->save(count);
    */

    // after publishing, store the current time
    lastUpdate = millis();
  }

  /*
  if(Serial2.available()){
    Serial2.write((char) count);//send data coming from USB to Serial2
  }
  */
}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  //Serial.print("received <- ");
  Serial.println(data->value());
  Serial2.write(data->value());

}
