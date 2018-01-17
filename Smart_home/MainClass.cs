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
        // serial port
        //
        SerialPort _serial_port = new SerialPort("COM3", 9600, Parity.None, 8, StopBits.One);

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
            new Main();

            for (; ; );


            //Stop method should be called before exit.
            myServer.Stop();

        }

        private MainClass()
        {
            //Set the datareceived event handler
            _serial_port.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);
            //Open the serial port
            _serial_port.Open();
            //Read from the console, to stop it from closing.
            Console.Read();
        }

        private void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //Write the serial port data to the console.
            Console.Write(_serial_port.ReadExisting());
        }
    }
}
