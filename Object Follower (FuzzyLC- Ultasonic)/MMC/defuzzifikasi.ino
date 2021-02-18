void defuzzy()
{
defuzz=0;
S_alpha=0;
  for (i=0;i<5;i++)
   {
     for(j=0;j<5;j++)
     {
        defuzz= defuzz+(alpha[i][j]*output[i][j]);
          S_alpha=S_alpha+alpha[i][j];
     }
   }
   defuzz=defuzz/S_alpha;
}
