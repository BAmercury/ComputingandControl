using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ArduinoDriver;
using ArduinoUploader;
using RJCP.IO.Ports;
using System.Text.RegularExpressions;
using System.IO;


namespace UltraSonicLogger
{
    class Program
    {

        public static List<List<double>> data = new List<List<double>>();

        public static string directory = "C:\\Desktop";


        static void Main(string[] args)
        {
            SerialPortStream port = find_ports();
            Begin_Test(port);
            Console.WriteLine("What would you like to call the file?: ");
            string file_name = Console.ReadLine();
            string path = generate_file_path(file_name);
            Write_File(data, path);

        }




        public static void Begin_Test(SerialPortStream port)
        {
            port.Write("<begin>");

            bool test_in_progress = true;
            while (test_in_progress)
            {

                string s = port.ReadLine();
                s = Regex.Replace(s, @"\r", string.Empty);
                if (s == "done")
                {
                    test_in_progress = false;
                    break;
                }
                string[] message = s.Split(',');
                if (message.Length > 1)
                {
                    //string pulse = message[0];
                    //string distance = message[1];
                    //string timestamp = message[2];

                    List<double> temp = new List<double>();


                    foreach (string element in message)
                    {
                        double value = Convert.ToDouble(element);
                        temp.Add(value);
                    }
                    data.Add(temp);
                }
            }
        }


        public static void Write_File(List<List<double>> data, string file_path)
        {

            using (StreamWriter tv = new StreamWriter(file_path))
            {

                foreach (List<double> member in data)
                {
                    foreach (double value in member)
                    {
                        tv.Write(value);
                        tv.Write(",");
                    }
                    tv.WriteLine();
                }

            }
            Console.WriteLine("Done writing the file");

        }


        public static string generate_file_path(string file_name)
        {
            string file_path = directory + file_name;

            return file_path;
        }



        public static SerialPortStream find_ports()
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
