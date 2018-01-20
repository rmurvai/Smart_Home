using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server_http
{

    class MainClass
    {
        //
        // Global serial port
        //
        SerialPort _serial_port = new SerialPort("COM3", 9600, Parity.None, 8, StopBits.One);
        SensorData sensor_data;

        //
        // Constructor
        //
        private MainClass()
        {
            //
            //Set the datareceived event handler
            //
            _serial_port.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);
            
            //
            //Open the serial port
            //
            _serial_port.Open();

            //
            //Read from the console, to stop it from closing.
            //
            Console.Read();
        }

        //
        //sp_DataReceived
        //
        private void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //
            // if we have data
            //
            string str_serial = _serial_port.ReadExisting();

            //
            // DEBUG  Write the serial port data to the console
            //
            Console.Write(str_serial);

            //
            // compare data
            // 
            if(str_serial.StartsWith("1-1<"/*temperature*/,StringComparison.OrdinalIgnoreCase))
            {
                //
                // parse the serialized data
                //

            }
            else if (str_serial.StartsWith("1-2<"/*humidity*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("2-1<"/*pir calibration started*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("2-2<"/*pir calibration ended*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("2-3<"/*pir movment detected*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("2-4<"/*pir movment ended*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("3-1<"/*mq2 lpg*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("3-2<"/*mq2 co*/, StringComparison.OrdinalIgnoreCase))
            {

            }
            else if (str_serial.StartsWith("3-3<"/*mq2 smoke*/, StringComparison.OrdinalIgnoreCase))
            {

            }

        }

        //
        // Main entry
        //
        static void Main(string[] args)
        {

            string myFolder = @"E:\Licenta_februarie2018\Source\web_root";
            SimpleHTTPServer myServer;

            //create server with auto assigned port
            myServer = new SimpleHTTPServer(myFolder);

            //
            // usage http://127.0.0.1:port/(html file)
            //


            //Creating server with specified port
            //myServer = new SimpleHTTPServer(myFolder, 8085);


            //Now it is running:
            Console.WriteLine("Server is running on this port: " + myServer.Port.ToString());

            //Open the Program function
            new MainClass();

            for (; ; );


            //Stop method should be called before exit.
            myServer.Stop();

        }
    }
}
