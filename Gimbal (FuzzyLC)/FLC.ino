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

void initiallizeRule()
{
//------------ row 1 --------//
output[0][0]=CC;
output[1][0]=CC;
output[2][0]=CC;
output[3][0]=CL;
output[4][0]=D;
//------------- row 2--------//
output[0][1]=CC;
output[1][1]=CC;
output[2][1]=CL;
output[3][1]=D;
output[4][1]=CCL;
//------------- row 3----------//
output[0][2]=CC;
output[1][2]=CL;
output[2][2]=D; 
output[3][2]=CCL;
output[4][2]=CCC;
//------------- row 4---------//
output[0][3]=CL;
output[1][3]=D;
output[2][3]=CCL;
output[3][3]=CCC;
output[4][3]=CCC;
//------------- row 5---------//
output[0][4]=D;
output[1][4]=CCL;
output[2][4]=CCC;
output[3][4]=CCC;
output[4][4]=CCC;
}

void defuzzy()
{
defuzz=0;
S_alpha=0;
  for (uint8_t i=0;i<5;i++)
   {
     for(uint8_t j=0;j<5;j++)
     {
        defuzz= defuzz+(alpha[i][j]*output[i][j]);
          S_alpha=S_alpha+alpha[i][j];
     }
   }
   defuzz=defuzz/S_alpha;

}

//
int FLControl(double error,double last)
{
  double delerror =last-error;
  // Serial.print(delerror); Serial.print("\t");

  //--------------fuzzifikasi error-------------//
  
  fuzzError[NB]=FATrapesium1(error,-10,-5);
  fuzzError[NK]=FASegitiga(error,-10,-5,0);
  fuzzError[Z]=FASegitiga(error,-5,0,5);
  fuzzError[PK]=FASegitiga(error,0,5,10);
  fuzzError[PB]=FATrapesium2(error,5,10);
  
  
  
  //--------------fuzzifikasi delta error-------------//
  fuzzDelError[NB]=FATrapesium1(delerror,-2,-1);
  fuzzDelError[NK]=FASegitiga(delerror,-2,-1,0);
  fuzzDelError[Z]=FASegitiga(delerror,-1,0,1);
  fuzzDelError[PK]=FASegitiga(delerror,0,1,2);
  fuzzDelError[PB]=FATrapesium2(delerror,1,2);
  
  //---------------------implikasi/rule evaluation----------------//
  for (uint8_t i=0;i<5;i++)
   {
    for (uint8_t j=0;j<5;j++)
      {
        alpha[i][j]=min(fuzzError[i],fuzzDelError[j]);
 
      }
   }
   initiallizeRule();
  //-----------------defuzzifikasi---------------//
   defuzzy();
   return defuzz;
}
