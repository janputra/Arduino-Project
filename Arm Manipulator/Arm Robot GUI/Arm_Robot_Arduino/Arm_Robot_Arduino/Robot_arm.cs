using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arm_Robot_Arduino
{
    class Robot_arm
    {
        public int L2, L3, L4;
        public int EF_deg;
        public double x, y, z;
        public double[] itheta = new double[4];

        public Robot_arm(int inL2,int inL3, int inL4, int ef_deg ) 
        {
            L2 = inL2;
            L3 = inL3;
            L4 = inL4;
            EF_deg = ef_deg;
        }

        double deg2rad(int degree)
        {
            
            return (degree * Math.PI)/180;
        }

        double rad2deg(double rad)
        {
            return (rad *180) /Math.PI;
        }
      

        public void forward_kinematic(int[] theta)
        {
            double p_x;
            double[] r_theta= new double[4];

            for (int x = 0; x < 4; x++) 
            {
               r_theta[x] = deg2rad(theta[x]);
            }
  
            
            p_x = L2 * Math.Cos(r_theta[1]) + L3 * Math.Cos((r_theta[1] + r_theta[2])) + L4 * Math.Cos((r_theta[1] + r_theta[2] + r_theta[3]));
            z = L2 * Math.Sin(r_theta[1]) + L3 * Math.Sin((r_theta[1] + r_theta[2])) + L4 * Math.Sin((r_theta[1] + r_theta[2] + r_theta[3]));

            x = p_x * Math.Cos(r_theta[0]);
            y = p_x * Math.Sin(r_theta[0]);
            
        }


        public void inverse_kinematic(double x, double y, double z)
        {
                        
            double p_x, xn, zn, dummy, dummy1;
            double[] theta = new double[4];
            double orient = deg2rad(EF_deg);
            double k2, k3;
            p_x = Math.Sqrt((x*x)+(y*y));
            theta[0] = Math.Atan((y / x));
            xn = p_x - (L4 * Math.Cos(orient));
            zn = z - (L4 * Math.Sin(orient));

            dummy = (xn * xn) + (zn * zn) - (L2 * L2) - (L3 * L3);
            dummy = dummy / (2 * L2 * L3);

            dummy1 = 1 - (dummy*dummy);
            dummy1 =Math.Abs(Math.Sqrt(dummy1));
            theta[2] = Math.Atan2(dummy1,dummy);

            k2 = L2 + L3 * Math.Cos(theta[2]);
            k3 = L3 * Math.Sin(theta[2]);

            theta[1] = Math.Atan2(zn, xn)-Math.Atan2(k3,k2);
             
            theta[3] = orient - (theta[1] + theta[2]);
            for (int i = 0; i < 4; i++) 
            {
                itheta[i] = rad2deg(theta[i]);
            }
        }
    }
}
