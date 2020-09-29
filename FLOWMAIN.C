#include "flow.h"

int main(int argc, char* argv[])
{
   double rotometer;  /* reading from the flowmeter in mm */
   double temp; /* prob in degrees C */
   double press; /*ambient pressure */
   double pressdrop; /* drop in pressure over a filter prob in inches of h2o */
   char choice;  /* (y)es or (n)o */

   if (argc > 1)  /* if any command line parameters were entered... */
   {
      if ((strcmp("/?",argv[1]) == 0) || (strcmp("-?",argv[1]) == 0))  /* ussage screen */
      {
         printf("Flow.exe\nBy: Maxwell Bottiger\nCopyright 1999\n");
         printf("Version 1.0\n");
         printf("Switches: -? or /?, displays this help screen\n");
         printf("          -1 or /1, turns on subroutine for Q-80-50289-001-1 rotometer.\n");
         printf("          -2 or /2, turns on subroutine for Q-80-50289-001-2 rotometer.\n");
         return 0;
      }
      else
      {
         if ((strcmp("/1",argv[1]) == 0) || (strcmp("-1",argv[1]) == 0)) /* solve for the 1-1 rotometer */
            rotometer=curve1();
         if ((strcmp("/2",argv[1]) == 0) || (strcmp("-2",argv[1]) == 0)) /* solve for the 1-2 rotometer */
            rotometer=curve2();
         printf("\nCalculations are complete for STP, would you like to correct for\n");
         printf("a pressure drop?  This is reccomended if the pressure drop was \n");
         printf("greater than 20 inches of water.\n");
         printf("(y)es or (n)o:  ");
         scanf("    %c",&choice);

         if (choice != 'y' && choice != 'Y')  /* if the program is just used for unit conversion, end here */
         {
            printf("The flow rate is : %f LPM\n",rotometer);
            return 0;
         }
      }
   }
   else    /* get user value if the velocity in LPM is already known */
      rotometer = nocurve();

   press = getpress();  /* pressure in PSI */
   pressdrop = getpressdrop();  /* pressuredrop in PSI */
   temp = gettemp();  /* temprature in degrees F */
   rotometer = correction(press, pressdrop, temp, rotometer);
   printf("The flow rate is : %f LPM\n",rotometer);
   return 0;
}

