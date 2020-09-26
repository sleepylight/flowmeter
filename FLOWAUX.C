#include "flow.h"

/* ------------ Pressure functions ------------- */
double WaterToPsi(double x)
{
   return x / 27.84;
}

double MmhgToPsi(double x)
{
   return x / 51.71;
}

double getpress(void)
{
   double value;
   char choise;

   printf("\nWhat is the ambient pressure?  Please enter the coefficent followed by\n");
   printf("an 'I' for inches of Water\n");
   printf("   'M' for milimeters of mercury\n");
   printf("   'P' for pounds per square inch.\n");
   scanf("    %lf %c",&value,&choise);
   if (choise == 'I' || choise == 'i')  /* if given in Inches of water */
      value = WaterToPsi(value);    /* convert to PSI */
   else if (choise == 'M' || choise == 'm')  /* if given in mercury */
      value = MmhgToPsi(value);  /* change to PSI */
   else if (choise != 'P' && choise != 'p')  /* check for PSI */
      return getpress();
   return value;
}


double getpressdrop(void)
{
   double value;
   char choise;

   printf("\nWhat is the pressure drop?  Please enter the coefficent followed by\n");
   printf("an  'I' for inches of Water\n");
   printf("    'M' for milimeters of mercury\n");
   printf("    'P' for pounds per square inch.\n");
   scanf("      %lf     %c",&value,&choise);

   if (choise == 'I' || choise == 'i')  /* if given in Inches of water */
      value = WaterToPsi(value);    /* convert to PSI */
   else if (choise == 'M' || choise == 'm')  /* if given in mercury */
      value = MmhgToPsi(value);  /* change to PSI */
   else if (choise != 'P' && choise != 'p')  /* check for PSI */
      return getpressdrop();
   return value;
}

double CelToFah(double x)
{
   return (x * (9/5)) + 32;
}

double KelToFah(double x)
{
     x = x - 273.15;
     return CelToFah(x);
}

double gettemp(void)
{
   double value;
   char choise;

   printf("\nWhat is the ambient temperature?  Please enter the coefficent followed\n");
   printf("by a 'C' for Celcius\n");
   printf("     'F' for Farenheit\n");
   printf("     'K' for Kelvin\n");
   scanf("     %lf     %c",&value,&choise);
   if (choise == 'C' || choise == 'c')  /* if given in Inches of water */
     value = CelToFah(value);    /* convert to PSI */
   else if (choise == 'K' || choise == 'k')  /* if given in mercury */
      value = KelToFah(value);  /* change to PSI */
   else if (choise != 'F' && choise != 'f')  /* check for PSI */
      return gettemp();
   return value;
}

/* ------------------ Rotometer Functions ---------------- */
double getrotoheight(void)
{
   double value;

   printf("What is the float height on the rotometer?  ");
   scanf("   %lf",&value);
   return value;
}

double CfmToLpm(double x)
{
   return 28.32 * x;
}

double correction(double press, double pressdrop, double temp, double rotometer)
{
   press = 14.7 / (press - pressdrop);
   temp = (460 + temp) / 530;
   return rotometer / ( sqrt(press) * sqrt(temp) * sqrt(1));
}

double curve1(void)
{
   double x;
   x = getrotoheight();  /* rotometer is now in mm */
   x = (x*x*x)*0.00000000076871 + (x*x)*0.0000003579 + x*0.0014445 + -0.00039112;
   x = CfmToLpm(x); /* converts to LPM, now ready for correction */
   return x;
}

double curve2(void)
{
   double x;
   x = getrotoheight();  /* rotometer is now in mm */
   x = (x*x*x)*0.00000000034376 + (x*x)*0.0000007354 + x*0.0014573 + 0.014510;
   x = CfmToLpm(x); /* converts to LPM, now ready for correction */
   return x;
}

double nocurve(void)
{
   double rotometer;
   char choise;

   printf("What is the rotometer velocity for correction?\n");
   printf("Please type the coefficient followed by:\n");
   printf("    L for Liters Per Minute,\n");
   printf("    F for Starndard Cubic Feet per Minute\n");
   scanf("   %lf   %c", &rotometer, &choise);
   if (choise == 'f' || choise == 'F')
      rotometer = CfmToLpm(rotometer);
   else if (choise != 'L' && choise != 'l')
     return nocurve();
   return rotometer;
}

