/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : main.cpp
 Auteur(s)   : Loïc Dessaules, Ilias Goujgali, Doran Kayoumi
 Date        : 26.09.2018

 But         : Génération de facture pour des conducteurs Uber

 Compilateur : MinGW-g++ <6.3.0>
 -----------------------------------------------------------------------------------
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip> 
#include <string>

using namespace std;

int main() {

   const double VAT = 0.08; // 8%

   const string UBERX_DISPLAY_NAME = "uberX";
   const double UBERX_BASE_FARE = 3.00;
   const double UBERX_MINIMUM_FARE = 6.00;
   const double UBERX_PER_MINUTE_FEE = 0.30;
   const double UBERX_PER_KM_FEE = 1.80;
   const double UBERX_CANCELLATION_FEE = 6.00;

   const string UBERBLACK_DISPLAY_NAME = "uberBLACK";
   const double UBERBLACK_BASE_FARE = 8.00;
   const double UBERBLACK_MINIMUM_FARE = 15.00;
   const double UBERBLACK_PER_MINUTE_FEE = 0.60;
   const double UBERBLACK_PER_KM_FEE = 3.60;
   const double UBERBLACK_CANCELLATION_FEE = 10.00;

   const string UBERPOP_DISPLAY_NAME = "uberPOP";
   const double UBERPOP_BASE_FARE = 3.00;
   const double UBERPOP_MINIMUM_FARE = 6.00;
   const double UBERPOP_PER_MINUTE_FEE = 0.30;
   const double UBERPOP_PER_KM_FEE = 1.35;
   const double UBERPOP_CANCELLATION_FEE = 6.00;

   string displayName;
   double baseFee;
   double minimumFee;
   double perMinuteFee;
   double perKmFee;
   double cancellationFee;
   double totalDistanceFee;
   double totalDurationFee;
   double fareKm;
   double subTotalFee;
   double totalFee;
   double totalFeeVatValue;

   cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK" << endl;
   unsigned short int serviceType;
   cin >> serviceType;

   enum ServiceType {
      UBERX = 1,
      UBERPOP = 2,
      UBERBLACK = 3
   };

   // set service values depending on the chosen service
   switch (serviceType) {
      case UBERX:
         displayName = UBERX_DISPLAY_NAME;
         baseFee = UBERX_BASE_FARE;
         minimumFee = UBERX_MINIMUM_FARE;
         perMinuteFee = UBERX_PER_MINUTE_FEE;
         perKmFee = UBERX_PER_KM_FEE;
         cancellationFee = UBERX_CANCELLATION_FEE;
         break;
      case UBERPOP:
         displayName = UBERPOP_DISPLAY_NAME;
         baseFee = UBERPOP_BASE_FARE;
         minimumFee = UBERPOP_MINIMUM_FARE;
         perMinuteFee = UBERPOP_PER_MINUTE_FEE;
         perKmFee = UBERPOP_PER_KM_FEE;
         cancellationFee = UBERPOP_CANCELLATION_FEE;
         break;
      case UBERBLACK:
         displayName = UBERBLACK_DISPLAY_NAME;
         baseFee = UBERBLACK_BASE_FARE;
         minimumFee = UBERBLACK_MINIMUM_FARE;
         perMinuteFee = UBERBLACK_PER_MINUTE_FEE;
         perKmFee = UBERBLACK_PER_KM_FEE;
         cancellationFee = UBERBLACK_CANCELLATION_FEE;
         break;
   }
   cout << "Combien de minutes ecoulees?" << endl;
   double fareDurationMinute;
   cin >> fareDurationMinute;

   // Check if the fare was canceled
   // A time of 0 or smaller means that it was cancelled
   if (fareDurationMinute <= 0) {
      totalFee = cancellationFee;
      totalFeeVatValue = totalFee - totalFee / (1 + VAT); // 1 = 100%
   } else {
      cout << "Combien de kilometres parcourus?" << endl;
      cin >> fareKm;
      // Round to the nearest 0.X (eg: 0.14 => 0.1 ; 0.16 => 0.2)
      fareKm = round(fareKm * 10) / 10;

      // Calculate fee for the distance and time it took
      totalDistanceFee = fareKm * perKmFee;
      totalDurationFee = ceil(fareDurationMinute) * perMinuteFee;

      totalFee = subTotalFee = baseFee + totalDistanceFee + totalDurationFee;
      // Check if the course cost is lower than the minimum price
      // If it is, set the total fee to the minimum vakue
      if (subTotalFee < minimumFee) {
         totalFee = minimumFee;
      }
      totalFeeVatValue = totalFee - totalFee / (1 + VAT);
   }

   // Displaying fare bill
   const char CANVAS_CORNER = '+';
   const char CANVAS_TOP_BORDER = '-';
   const char CANVAS_BOTTOM_BORDER = '-';
   // Adding the space after the border helps when the bill is being displayed.
   const string CANVAS_LEFT_BORDER = "| ";
   // Adding the space before the border helps when the bill is being displayed.
   const string RIGHT_BORDER = " |";
   const char CANVAS_COLUMN_SEPARATOR = ':';
   
   const int CANVAS_WIDTH_COLUMN_1 = 19;
   const int CANVAS_WIDTH_COLUMN_2 = 1;
   const int CANVAS_WIDTH_COLUMN_3 = 10;
   // To have a everything certered and aligned, CANVAS_TOTAL_WIDTH needs to be an event number. 
   const int CANVAS_TOTAL_WIDTH = CANVAS_WIDTH_COLUMN_1
                                 + CANVAS_WIDTH_COLUMN_2
                                 + CANVAS_WIDTH_COLUMN_3;
   const string CANVAS_SUFFIX_KM = " km";
   const string CANVAS_SUFFIX_TIME = " min";
   // 2 = 0.xx | 3 = 0.xxx
   const int BILL_VALUE_PRECISION = 2;
   
   cout << endl;
   // Displaying the header part
   cout << setfill(CANVAS_TOP_BORDER);
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CANVAS_CORNER
         << setw(CANVAS_TOTAL_WIDTH / 2) << right << CANVAS_CORNER << endl;

   cout << setfill(' ');

   cout << setw(CANVAS_TOTAL_WIDTH - CANVAS_LEFT_BORDER.length())
         << left << CANVAS_LEFT_BORDER << right << RIGHT_BORDER << endl;

   cout << setw(CANVAS_TOTAL_WIDTH / 2 - displayName.length() / 2)
         << left << CANVAS_LEFT_BORDER << setw(displayName.length())
         << left << displayName
         << setw(CANVAS_TOTAL_WIDTH
                  - (CANVAS_TOTAL_WIDTH / 2 - displayName.length() / 2
                  + displayName.length()))
         << right << RIGHT_BORDER << endl;

   cout << setw(CANVAS_TOTAL_WIDTH - CANVAS_LEFT_BORDER.length())
         << left << CANVAS_LEFT_BORDER << right << RIGHT_BORDER << endl;
   
   // Displaying the content for when thr far was cancelled
   if (fareDurationMinute <= 0) {
      cout << fixed << setprecision(BILL_VALUE_PRECISION);
      
      cout << CANVAS_LEFT_BORDER
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "Frais annulation" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
            << right << cancellationFee << RIGHT_BORDER << endl;
   }
   // Displaying the bill details
   else {
      cout << CANVAS_LEFT_BORDER
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "Distance" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3
                     - CANVAS_SUFFIX_KM.length()
                     - RIGHT_BORDER.length())
            << right << fareKm << CANVAS_SUFFIX_KM << RIGHT_BORDER << endl;
      
      cout << CANVAS_LEFT_BORDER 
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "temps ecoule" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3
                     - CANVAS_SUFFIX_TIME.length()
                     - RIGHT_BORDER.length())
            << right << ceil(fareDurationMinute) << CANVAS_SUFFIX_TIME
            << RIGHT_BORDER << endl;
      
      cout << fixed << setprecision(BILL_VALUE_PRECISION);
      
      cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CANVAS_LEFT_BORDER
            << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl;
      
      cout << CANVAS_LEFT_BORDER
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "Prix de base" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
            << right << baseFee << RIGHT_BORDER << endl;
      
      cout << CANVAS_LEFT_BORDER
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "Prix distance" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
            << right << totalDistanceFee << RIGHT_BORDER << endl;
      
      cout << CANVAS_LEFT_BORDER
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "Prix temps" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
            << right << totalDurationFee << RIGHT_BORDER << endl;
      
      cout << CANVAS_LEFT_BORDER
            << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
            << left << "Total" << setw(CANVAS_WIDTH_COLUMN_2)
            << CANVAS_COLUMN_SEPARATOR
            << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
            << right << subTotalFee << RIGHT_BORDER << endl;
      
      // Displaying the minimal fee
      if (subTotalFee < minimumFee) {
         cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CANVAS_LEFT_BORDER
               << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl;
      
         cout << CANVAS_LEFT_BORDER
               << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
               << left << "Course mimimale" << setw(CANVAS_WIDTH_COLUMN_2)
               << CANVAS_COLUMN_SEPARATOR
               << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
               << right << minimumFee << RIGHT_BORDER << endl;
      }
   }
   
   // Displaying the footer part (total and VAT)
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CANVAS_LEFT_BORDER
         << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl;
   
   cout << CANVAS_LEFT_BORDER
         << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
         << left << "Prix" << setw(CANVAS_WIDTH_COLUMN_2) << CANVAS_COLUMN_SEPARATOR
         << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
         << right << totalFee << RIGHT_BORDER << endl;
   
   cout << CANVAS_LEFT_BORDER
         << setw(CANVAS_WIDTH_COLUMN_1 - CANVAS_LEFT_BORDER.length())
         << left << "(incl. TVA)" << setw(CANVAS_WIDTH_COLUMN_2)
         << CANVAS_COLUMN_SEPARATOR
         << setw(CANVAS_WIDTH_COLUMN_3 - RIGHT_BORDER.length())
         << right << totalFeeVatValue << RIGHT_BORDER << endl;
   
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CANVAS_LEFT_BORDER
         << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl;
   
   cout << setfill(CANVAS_BOTTOM_BORDER);
   
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CANVAS_CORNER
         << setw(CANVAS_TOTAL_WIDTH / 2) << right << CANVAS_CORNER << endl;
   
   cout << endl;
   
   return 0;
}