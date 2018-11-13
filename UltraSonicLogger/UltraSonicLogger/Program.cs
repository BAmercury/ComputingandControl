using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ArduinoDriver;
using ArduinoUploader;
using RJCP.IO.Ports;


namespace UltraSonicLogger
{
    class Program
    {
        static void Main(string[] args)
        {
        }



        SerialPortStream find_ports()
        {
            string port_name = "COM9";
            var searched_ports = SerialPortStream.GetPortNames();
            var distinct_ports = searched_ports.Distinct().ToList();

            if (distinct_ports.SingleOrDefault() != null)
            {
                port_name = distinct_ports.Single();
            }

            SerialPortStream port = new SerialPortStream(port_name, 115200);




            return port;
        }
    }
}
