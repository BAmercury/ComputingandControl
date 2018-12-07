using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RJCP.IO.Ports;
using System.Text.RegularExpressions;
using System.IO;

namespace UltraSonicLogger
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPortStream port = find_ports();
            List<List<double>> data = new List<List<double>>();
            data = begin_test(port);
            Console.WriteLine("Done Collecting Data, what should the file be called?: ");
            string file_name = Console.ReadLine();
            write_file(data, file_name);
            Console.WriteLine("Press any key to exit");
            Console.ReadKey(true);
        }


        public static List<List<double>> begin_test(SerialPortStream port)
        {
            port.Open();
            Console.WriteLine("Press any button to begin");
            Console.ReadKey(true);
            port.Write("<1>");
            List<List<double>> data = new List<List<double>>();
            bool collecting_data = true;
            while (collecting_data)
            {
                if (port.BytesToRead > 0)
                {
                    string s = port.ReadLine();
                    s = Regex.Replace(s, @"\r", string.Empty);
                    if (s == "done")
                    {
                        collecting_data = false;
                        break;
                    }
                    string[] message = s.Split(',');
                    List<double> temp = new List<double>();
                    foreach (string element in message)
                    {
                        double value = Convert.ToDouble(element);
                        temp.Add(value);
                        Console.WriteLine(element);
                        
                    }
                    data.Add(temp);
                }

            }

            return data;
        }

        public static void write_file(List<List<double>> data, string file_name)
        {
            using (StreamWriter sw = new StreamWriter(file_name + ".csv"))
            {
                foreach (List<double> datalist in data)
                {
                    foreach (double value in datalist)
                    {
                        sw.Write(value);
                        sw.Write(",");
                    }
                    sw.WriteLine();
                }
            }
            Console.WriteLine("Wrote data to file");

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
