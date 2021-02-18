using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing.Drawing2D;

namespace Arm_Robot_Arduino
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        bool serial;
        string[] ports;
        byte[] servo_data= new byte[6];
        int[] angle = new int[6];
        public delegate void myDelegate(string sData);
        public int tarX, tarY, tarZ,i, orient;
        private void Form1_Load(object sender, EventArgs e)
        {
            ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);

            }
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
            richTextBox1.HideSelection = false;

            angle[0] = tb_Ser0.Value;
            txt_Ser0.Text = tb_Ser0.Value.ToString();

            angle[1] = tb_Ser1.Value;
            txt_Ser1.Text = tb_Ser1.Value.ToString();

            angle[2] = tb_Ser2.Value;
            txt_Ser2.Text = tb_Ser2.Value.ToString();

            angle[3] = tb_Ser3.Value;
            txt_Ser3.Text = tb_Ser3.Value.ToString();

            angle[4] = tb_Ser4.Value;
            txt_Ser4.Text = tb_Ser4.Value.ToString();

            angle[5] = tb_Ser5.Value;
            txt_Ser5.Text = tb_Ser5.Value.ToString();

            tarX = 150;
            tarY = 150;
            tarZ = 100;
            orient = 0;
            tar_disp();
            Robot_op();

            button4.Text = char.ConvertFromUtf32(8593);
            button5.Text = char.ConvertFromUtf32(8595);
            button6.Text = char.ConvertFromUtf32(8592);
            button7.Text = char.ConvertFromUtf32(8594);
            button8.Text = char.ConvertFromUtf32(8599);
            button9.Text = char.ConvertFromUtf32(8601);

            radioButton3.Checked = true;

            tb_Ser4.Enabled = false;
            tb_Ser5.Enabled = false;

            tb_Ser1.Enabled = false;
            tb_Ser0.Enabled = false;
            tb_Ser2.Enabled = false;
            tb_Ser3.Enabled = false;


            button4.Enabled = true;
            button5.Enabled = true;
            button6.Enabled = true;
            button7.Enabled = true;
            button8.Enabled = true;
            button9.Enabled = true;
            OR_bar.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (this.serialPort1.IsOpen)
            {

                this.serialPort1.Close();
                button1.Text = "Connect";
                serial = false;
                
            }
            else
            {
                this.serialPort1.PortName = comboBox1.Text;
                this.serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                this.serialPort1.Open();
                button1.Text = "Disconnect";
                serial = true;

            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                button2.Enabled = false;
            }
            else
            {
                button2.Enabled = true;
            }
        }

        private void tb_Ser0_Scroll(object sender, EventArgs e)
        {
            txt_Ser0.Text = tb_Ser0.Value.ToString();
            angle[0] = tb_Ser0.Value;
            
            if (checkBox1.Checked)
            {
                if (serial)
                {
                    servo_data[0] = Convert.ToByte(angle[0]);
                    serialPort1.Write(servo_data, 0, 4);
                }
            }
            angle_con();
        }

        private void button2_Click(object sender, EventArgs e)
        {

            if (serial)
            {
                serialPort1.Write(servo_data, 0, 4);
            }
            


        }

        private void tb_Ser1_Scroll(object sender, EventArgs e)
        {
            txt_Ser1.Text = tb_Ser1.Value.ToString();
            angle[1] = tb_Ser1.Value;
            
            if (checkBox1.Checked)
            {
                if (serial)
                {
                    servo_data[1] = Convert.ToByte(angle[1]);
                    serialPort1.Write(servo_data, 0, 4);
                };
            }
            angle_con();
        }

        private void tb_Ser2_Scroll(object sender, EventArgs e)
        {
            txt_Ser2.Text = tb_Ser2.Value.ToString();
            angle[2] = tb_Ser2.Value;
            
            if (checkBox1.Checked)
            {
                if (serial)
                {
                    servo_data[2] = Convert.ToByte(angle[2]+90);
                    serialPort1.Write(servo_data, 0, 4);
                }
            }
            angle_con();
        }

        private void tb_Ser3_Scroll(object sender, EventArgs e)
        {
            txt_Ser3.Text = tb_Ser3.Value.ToString();
            angle[3] = tb_Ser3.Value;
            
            if (checkBox1.Checked)
            {
                  if (serial)
                {
                    servo_data[3] = Convert.ToByte(angle[3]);
                    serialPort1.Write(servo_data, 0, 4);
                }
            }
            angle_con();
        }

        private void tb_Ser4_Scroll(object sender, EventArgs e)
        { 
            /*
            txt_Ser4.Text = tb_Ser4.Value.ToString();
            angle[4] = tb_Ser4.Value;
            servo_data[4] = Convert.ToByte(angle[4]);
            if (checkBox1.Checked)
            {
                serialPort1.Write(servo_data, 0, 5);
            }
            */
        }

        private void tb_Ser5_Scroll(object sender, EventArgs e)
        {
            /*
            txt_Ser5.Text = tb_Ser5.Value.ToString();
            angle[5] = tb_Ser5.Value;
            servo_data[5] = Convert.ToByte(angle[5]);
            if (checkBox1.Checked)
            {
                serialPort1.Write(servo_data, 0, 6);
            }
            */
        }

           private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int[] sData = new int[4];
           
            while (serialPort1.BytesToRead > 0)
            {
                
                    for (int a = 0; a < 4; a++)
                    {
                        sData[a] = serialPort1.ReadByte();
                    }

                    string temp= sData[0].ToString() + " " + sData[1].ToString() + " " + sData[2].ToString() + " " + sData[3].ToString() +"\n"; //+ " " + sData[4].ToString()+" " + sData[5].ToString()+


                this.BeginInvoke((new myDelegate(Text_Out)), temp);                      
                                            
            }
        }

        private void Text_Out(string sData)
        {
            richTextBox1.AppendText(sData);

        }

        private void txt_Ser0_TextChanged(object sender, EventArgs e)
        {
            
            tb_Ser0.Value = Convert.ToInt32(txt_Ser0.Text);

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            angle_con();

        }

        void angle_con() 
        {
            int ef;
            ef = angle[3] + angle[2] + angle[1];
           

            Robot_arm robot = new Robot_arm(150, 150, 40, ef);

            robot.forward_kinematic(angle);

            txtX.Text = Convert.ToString(robot.x);
            txtY.Text = Convert.ToString(robot.y);
            txtZ.Text = Convert.ToString(robot.z);

            robot.inverse_kinematic(robot.x, robot.y, robot.z);

            txt_T0.Text = Convert.ToString(robot.itheta[0]);
            txt_T1.Text = Convert.ToString(robot.itheta[1]);
            txt_T2.Text = Convert.ToString(robot.itheta[2]);
            txt_T3.Text = Convert.ToString(robot.itheta[3]);

        }

        private void button7_Click(object sender, EventArgs e)
        {
            conditions();
            tarX = tarX + i;
            tar_disp();
            Robot_op();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            conditions();
            tarX = tarX - i;
            tar_disp();
            Robot_op();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            conditions();
            tarZ = tarZ + i;
            tar_disp();
            Robot_op();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            conditions();
            tarZ = tarZ - i;
            tar_disp();
            Robot_op();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            conditions();
            tarY = tarY + i;
            tar_disp();
            Robot_op();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            conditions();
            tarY = tarY - i;
            tar_disp();
            Robot_op();
        }

        void conditions()
        {
            
            if (radioButton1.Checked)
            {
                i = 100;
            }
            else if (radioButton2.Checked)
            {
                i = 10;
            }
            else if (radioButton3.Checked)
            {
                i = 1;
            }

                    
        }

        void tar_disp() 
        {

            txtTarX.Text = tarX.ToString();
            txtTarY.Text = tarY.ToString();
            txtTarZ.Text = tarZ.ToString();
            txt_OR.Text = orient.ToString();

        
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            orient = OR_bar.Value;
            tar_disp();
            Robot_op();
        }

        private void button10_Click(object sender, EventArgs e)
        {

            tb_Ser0.Value = 0;
            tb_Ser1.Value = 0;
            tb_Ser2.Value = 0;
            tb_Ser3.Value = 0;
            tb_Ser4.Value = 0;
            tb_Ser5.Value = 0;



            angle[0] = tb_Ser0.Value;
            txt_Ser0.Text = tb_Ser0.Value.ToString();

            angle[1] = tb_Ser1.Value;
            txt_Ser1.Text = tb_Ser1.Value.ToString();

            angle[2] = tb_Ser2.Value;
            txt_Ser2.Text = tb_Ser2.Value.ToString();

            angle[3] = tb_Ser3.Value;
            txt_Ser3.Text = tb_Ser3.Value.ToString();

            angle[4] = tb_Ser4.Value;
            txt_Ser4.Text = tb_Ser4.Value.ToString();

            angle[5] = tb_Ser5.Value;
            txt_Ser5.Text = tb_Ser5.Value.ToString();
            angle_con();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            tb_Ser1.Enabled = true;
            tb_Ser0.Enabled = true;
            tb_Ser2.Enabled = true;
            tb_Ser3.Enabled = true;


            button4.Enabled = false;
            button5.Enabled = false;
            button6.Enabled = false;
            button7.Enabled = false;
            button8.Enabled = false;
            button9.Enabled = false;
            OR_bar.Enabled = false;

        }

        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            tb_Ser1.Enabled = false;
            tb_Ser0.Enabled = false;
            tb_Ser2.Enabled = false;
            tb_Ser3.Enabled = false;


            button4.Enabled = true;
            button5.Enabled = true;
            button6.Enabled = true;
            button7.Enabled = true;
            button8.Enabled = true;
            button9.Enabled = true;
            OR_bar.Enabled = true;
        }

        private void label25_Click(object sender, EventArgs e)
        {

        }

        void Robot_op() 
        {
            try
            {
                int[] ctheta = new int[4];
                byte[] btheta = new byte[4];
                Robot_arm robot = new Robot_arm(150, 150, 40, orient);


                robot.inverse_kinematic(tarX, tarY, tarZ);

                txt_T0.Text = Convert.ToString(robot.itheta[0]);
                txt_T1.Text = Convert.ToString(robot.itheta[1]);
                txt_T2.Text = Convert.ToString(robot.itheta[2]);
                txt_T3.Text = Convert.ToString(robot.itheta[3]);

                for (int j = 0; j < 4; j++)
                {
                    ctheta[j] = Convert.ToInt32(robot.itheta[j]);
                }

                robot.forward_kinematic(ctheta);

                txtX.Text = Convert.ToString(robot.x);
                txtY.Text = Convert.ToString(robot.y);
                txtZ.Text = Convert.ToString(robot.z);
                if (serial)
                {

                    for (int j = 0; j < 4; j++)
                    {
                        if (robot.itheta[j] < 0)
                        {
                            robot.itheta[j] = robot.itheta[j] + 90;
                        }
                        btheta[j] = Convert.ToByte(robot.itheta[j]);
                    }

                    serialPort1.Write(btheta, 0, 4);
                }
            }
            catch (Exception e) 
            {

                string message = e.ToString();
                string title = "Error";
                MessageBox.Show(message, title);
            }
        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }
    }
    
}
