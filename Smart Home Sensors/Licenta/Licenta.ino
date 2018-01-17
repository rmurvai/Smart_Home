/*
 Name:		Licenta.ino
 Created:	11/12/2017 8:17:58 PM
 Author:	robert.murvai
*/

//Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>;

/////////////////////////////////////////////////////////////////////////////////////////
//
// Constants
//
/////////////////////////////////////////////////////////////////////////////////////////
#define DHTPIN  7       // set the pin for the temperature sensor
#define DHTTYPE DHT22   // set the type of the temperature sensor => DHT 22  (AM2302)

/////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize DHT sensor for normal 16mhz Arduino
//
/////////////////////////////////////////////////////////////////////////////////////////
DHT dht( DHTPIN, DHTTYPE );  // init


/////////////////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//
/////////////////////////////////////////////////////////////////////////////////////////
float   dht_humidity_value;        //Stores humidity value
float   dht_temperature_value;     //Stores temperature value
int     dht_calibration_time = 30; //the time we give the sensor to calibrate (10-60 secs according to the datasheet)


long unsigned int pir_low_In;           //the time when the sensor outputs a low impulse
long unsigned int pir_pause_time = 5000;//the amount of milliseconds the sensor has to be low before we assume all motion has stopped
int               pir_Pin = 3;          //the digital pin connected to the PIR sensor's output
boolean           pir_lock_Low = true;  //control variable for low impulse
boolean           pir_take_Low_time;    //control variable for low time
int               pir_control_led_Pin = 13;// the pin where our pir led is connected


//
// Calibration pir sensor
//
void CalibratePirSensor()
{
    //give the sensor some time to calibrate
    Serial.print("Start calibrating movement sensor ");
    for (int i = 0; i < dht_calibration_time; i++)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" End calibrating movement sensor");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//SETUP
//
/////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
    Serial.begin( 9600 );
    
    //
    // start monitoring humidity and temperature sensor
    //
    dht.begin();

    //
    // pir movement sensor setup
    //
    pinMode( pir_control_led_Pin, OUTPUT );
    pinMode( pir_Pin, INPUT );
    digitalWrite( pir_Pin, LOW );

    //
    // calibrate the pir sensor
    //
    CalibratePirSensor();


}

/////////////////////////////////////////////////////////////////////////////////////////
//
//LOOP
//
/////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
    //
    // check data for pir sensor
    //
    if ( digitalRead( pir_Pin ) == HIGH )
    {
        digitalWrite( pir_control_led_Pin, HIGH );   // the led visualizes the sensors output pin state
        if ( pir_lock_Low )
        {
            //
            // makes sure we wait for a transition to LOW before any further output is made:
            //
            pir_lock_Low = false;
            Serial.println( "---" );
            Serial.print( "motion detected at " );
            Serial.print( millis() / 1000 );
            Serial.println( " sec" );
            delay( 50 );
        }
        pir_take_Low_time = true;
    }

    if ( digitalRead( pir_Pin ) == LOW )
    {
        digitalWrite( pir_control_led_Pin, LOW );  // the led visualizes the sensors output pin state

        if ( pir_take_Low_time )
        {
            pir_low_In        = millis();    // save the time of the transition from high to LOW
            pir_take_Low_time = false;       // make sure this is only done at the start of a LOW phase
        }

        //
        // if the sensor is low for more than the given pause, we assume that no more motion is going to happen
        //
        if ( !pir_lock_Low && millis() - pir_low_In > pir_pause_time )
        {
            //
            //makes sure this block of code is only executed again after a new motion sequence has been detected
            //
            pir_lock_Low = true;
            Serial.print( "motion ended at " );      //output
            Serial.print( ( millis() - pir_pause_time ) / 1000 );
            Serial.println( " sec" );
            delay( 50 );
        }
    }

    //
    // get data from the dht sensor
    //
    delay( 2000 ); // wait 2 sec to get data from sensor 

    //
    // read data and store it to variables dht_humidity_value and dht_temperature_value
    //
    dht_humidity_value    = dht.readHumidity();
    dht_temperature_value = dht.readTemperature();

    //
    // Print temp and humidity values to serial monitor
    //
    Serial.print( "Humidity: " );
    Serial.print( dht_humidity_value );
    Serial.print( " %, Temp: " );
    Serial.print( dht_temperature_value );
    Serial.println( " Celsius" );

}

