/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLWIMI7t5A"
#define BLYNK_TEMPLATE_NAME "WEMOS"
#define BLYNK_AUTH_TOKEN "23j-3x7257MwHv1-y50rB6bfipW0TiWl"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// constants won't change. Used here to set a pin number:
const int TRNASISTOR =  14;// the number of the LED pin

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Skylark";
char pass[] = "HOSO2765637";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void measureADs1115()
{
  

  //Blynk.virtualWrite(V0, adc0 );
}
void blynkSetup(){
   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, measureADs1115);
}
void setup()
{
  // Debug console
  Serial.begin(115200);
    pinMode(14, OUTPUT);
    //blynkSetup();

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
   ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }  
}


void loop() {
    //measureADs1115();
        digitalWrite(14, HIGH);
    Serial.println("TRANSDUCER ON");
  delay(1000);


  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int16_t adc0;
  float volts0;
  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);

  Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  digitalWrite(14, LOW);
    delay(1000);

  Serial.println("TRANSDUCER OFF");
   //Blynk.run();
  //timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

  //delay(1000);
}
