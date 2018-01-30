namespace Server_http
{
    //
    // DHT_Sensor
    //
    public class DHT_Sensor
    {
        private double humidity;
        private double temperature;

        public double Humidity
        {
            get { return humidity; }
            set { humidity = value; }
        }

        public double Temperature
        {
            get { return temperature; }
            set { temperature = value; }
        }

        public DHT_Sensor()
        {
            humidity = 0.0;
            temperature = 0.0;
        }
    }

    //
    // PIR_Sensor
    //
    public class PIR_Sensor
    {
        private double start_motion;
        private double end_motion;

        public PIR_Sensor()
        {
            start_motion = 0.0;
            end_motion = 0.0;
        }

        public double End_motion { get => end_motion; set => end_motion = value; }
        public double Start_motion { get => start_motion; set => start_motion = value; }
    }

    public class GAS_Sensor
    {
        public GAS_Sensor()
        {
        }
    }

    //
    // SensorData
    //
    class SensorData
    {
        public DHT_Sensor dht_sensor;
        public PIR_Sensor pir_sensor;
        public GAS_Sensor gas_sensor;

        public SensorData()
        {

        }
    }

}
