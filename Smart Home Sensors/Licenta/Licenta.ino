/*
 Name:		Licenta.ino
 Created:	11/12/2017 8:17:58 PM
 Author:	robert.murvai
*/

//Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>;

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht( DHTPIN, DHTTYPE ); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

/////////////////////////////
//VARS
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;

//the time when the sensor outputs a low impulse
long unsigned int lowIn;

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;


/////////////////////////////
//SETUP
void setup()
{
    Serial.begin( 9600 );
    //////////////////////////////////////////////
    // humidity & temp sensor
    dht.begin();

    //////////////////////////////////////////////
    // pir movement sensor setup
    pinMode( pirPin, INPUT );
    pinMode( ledPin, OUTPUT );
    digitalWrite( pirPin, LOW );

    //give the sensor some time to calibrate
    Serial.print( "calibrating sensor " );
    for ( int i = 0; i < calibrationTime; i++ )
    {
        Serial.print( "." );
        delay( 1000 );
    }
    Serial.println( " done" );
    Serial.println( "SENSOR ACTIVE" );
    delay( 50 );
}

////////////////////////////
//LOOP
void loop()
{

    if ( digitalRead( pirPin ) == HIGH )
    {
        digitalWrite( ledPin, HIGH );   //the led visualizes the sensors output pin state
        if ( lockLow )
        {
            //makes sure we wait for a transition to LOW before any further output is made:
            lockLow = false;
            Serial.println( "---" );
            Serial.print( "motion detected at " );
            Serial.print( millis() / 1000 );
            Serial.println( " sec" );
            delay( 50 );
        }
        takeLowTime = true;
    }

    if ( digitalRead( pirPin ) == LOW )
    {
        digitalWrite( ledPin, LOW );  //the led visualizes the sensors output pin state

        if ( takeLowTime )
        {
            lowIn = millis();          //save the time of the transition from high to LOW
            takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
        //if the sensor is low for more than the given pause, 
        //we assume that no more motion is going to happen
        if ( !lockLow && millis() - lowIn > pause )
        {
            //makes sure this block of code is only executed again after 
            //a new motion sequence has been detected
            lockLow = true;
            Serial.print( "motion ended at " );      //output
            Serial.print( ( millis() - pause ) / 1000 );
            Serial.println( " sec" );
            delay( 50 );
        }
    }

    // delay( 2000 );
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print( "Humidity: " );
    Serial.print( hum );
    Serial.print( " %, Temp: " );
    Serial.print( temp );
    Serial.println( " Celsius" );
    //delay( 10000 ); //Delay 2 sec.

}

