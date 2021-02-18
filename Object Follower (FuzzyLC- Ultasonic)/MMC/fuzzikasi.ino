double FASegitiga(double s, double a, double b, double c)
{
  double output;
         if (s < a || s > c)
           {
                output = 0;
            }
            else if (s >= a && s <= b)
            {
               output = (s - a) / (b - a);
            }
            else if (s > b && s <= c)
            {
                output = (c - s) / (c - b);
            }
return output;
}

double FATrapesium1(double s, double a, double b)
{
  double output;
         if (s < a)
           {
                output = 1;
            }
           
            else if (s > a && s <= b)
            {
                output = (b - s) / (b - a);
            }
            else if (s>b)
            {
              output=0;
          
            }
return output;
}

double FATrapesium2(double s, double a, double b)
{
  double output;
         if ( s < a)
           {
                output = 0;
            }
            else if (s >= a && s <= b)
            {
               output = (s - a) / (b - a);
            }
              else if (s>b)
            {
              output=1;
          
            }
         
return output;
}

