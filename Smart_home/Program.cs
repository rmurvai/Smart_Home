using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server_http
{
    class Program
    {
        static void Main(string[] args)
        {

            string myFolder = @"E:\Licenta_februarie2018\Source\web_root";
            SimpleHTTPServer myServer;

            //create server with auto assigned port
            myServer = new SimpleHTTPServer(myFolder);


            //Creating server with specified port
            //myServer = new SimpleHTTPServer(myFolder, 8085);


            //Now it is running:
            Console.WriteLine("Server is running on this port: " + myServer.Port.ToString());

            for (; ; );


            //Stop method should be called before exit.
            myServer.Stop();

        }
    }
}
