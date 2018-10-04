/*
 -----------------------------------------------------------------------------------
 Laboratoire : <01>
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
#include <string.h> // <string> ? cpp lib instead of c lib

using namespace std;

/*
 * 
 */
int main() {

   double const VAT = 0.08; // 8% 

   string const UBERX_DISPLAY_NAME = "UBERX";
   double const UBERX_BASE_FARE = 3.00;
   double const UBERX_MINIMUM_FARE = 6.00;
   double const UBERX_PER_MINUTE_FEE = 0.30;
   double const UBERX_PER_KM_FEE = 1.80;
   double const UBERX_CANCELLATION_FEE = 6.00;

   string const UBERBLACK_DISPLAY_NAME = "UBERBLACK";
   double const UBERBLACK_BASE_FARE = 8.00;
   double const UBERBLACK_MINIMUM_FARE = 15.00;
   double const UBERBLACK_PER_MINUTE_FEE = 0.60;
   double const UBERBLACK_PER_KM_FEE = 3.60;
   double const UBERBLACK_CANCELLATION_FEE = 10.00;

   string const UBERPOP_DISPLAY_NAME = "UBERPOP";
   double const UBERPOP_BASE_FARE = 3.00;
   double const UBERPOP_MINIMUM_FARE = 6.00;
   double const UBERPOP_PER_MINUTE_FEE = 0.30;
   double const UBERPOP_PER_KM_FEE = 1.35;
   double const UBERPOP_CANCELLATION_FEE = 6.00;

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

   cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK " << endl;
   unsigned short int serviceType;
   cin >> serviceType;

   if (serviceType == 1) {
      displayName = UBERX_DISPLAY_NAME;
      baseFee = UBERX_BASE_FARE;
      minimumFee = UBERX_MINIMUM_FARE;
      perMinuteFee = UBERX_PER_MINUTE_FEE;
      perKmFee = UBERX_PER_KM_FEE;
      cancellationFee = UBERX_CANCELLATION_FEE;
   } else if (serviceType == 2) {
      displayName = UBERPOP_DISPLAY_NAME;
      baseFee = UBERPOP_BASE_FARE;
      minimumFee = UBERPOP_MINIMUM_FARE;
      perMinuteFee = UBERPOP_PER_MINUTE_FEE;
      perKmFee = UBERPOP_PER_KM_FEE;
      cancellationFee = UBERPOP_CANCELLATION_FEE;
   } else if (serviceType == 3) {
      displayName = UBERBLACK_DISPLAY_NAME;
      baseFee = UBERBLACK_BASE_FARE;
      minimumFee = UBERBLACK_MINIMUM_FARE;
      perMinuteFee = UBERBLACK_PER_MINUTE_FEE;
      perKmFee = UBERBLACK_PER_KM_FEE;
      cancellationFee = UBERBLACK_CANCELLATION_FEE;
   }

   cout << "Combien de minutes ecoulees? " << endl;
   double fareDurationMinute;
   cin >> fareDurationMinute;


   if (fareDurationMinute <= 0) {
      totalFee = cancellationFee;
      totalFeeVatValue = totalFee - totalFee / (1 + VAT); // 1 = 100%
   }
   else {
      //ask for fare km
      cout << "Combien de kilometres parcourus?" << endl;
      cin >> fareKm;
      // round to the nearest 0.X (eg: 0.14 => 0.1 ; 0.16 => 0.2)
      fareKm = round(fareKm * 10) / 10;

      // calc sub total
      totalDistanceFee = fareKm * perKmFee;
      totalDurationFee = ceil(fareDurationMinute) * perMinuteFee;

      totalFee = subTotalFee = baseFee + totalDistanceFee + totalDurationFee;
      // AFFICHER CONTENU FACTURE
      if (subTotalFee < minimumFee) {
         totalFee = minimumFee;
         //AFFICHER LIGNE SUPP SI PRIX MINIMUM PAS DEPASSER
      }
      totalFeeVatValue = totalFee - totalFee / (1 + VAT);
   }

   // Displaying far bill
   const char CORNER = 'o';
   const char TOP_BORDER = '-';
   const char BOTTOM_BORDER = TOP_BORDER;
   const char LEFT_BORDER = '|';
   const char RIGHT_BORDER = LEFT_BORDER;
   const char COLUMN_SEPARATOR = ':';
  
   const int CANVAS_TOTAL_WIDTH = 30; // Include border characters
   const float CANVAS_INSIDE_WIDTH = CANVAS_TOTAL_WIDTH - 2; // Without border characters 
   const int CANVAS_INSIDE_COL_2_WIDTH = 1; // COL_2 is the ":" => 1 character
   const int CANVAS_INSIDE_COL_1_WIDTH = 2 * roundf((CANVAS_INSIDE_WIDTH - CANVAS_INSIDE_COL_2_WIDTH) / 3); // COL_1 is the 2/3 (-1 => ":") of the CANVAS_INSIDE_WIDTH
   const int CANVAS_INSIDE_COL_3_WIDTH = CANVAS_INSIDE_WIDTH - (CANVAS_INSIDE_COL_1_WIDTH + CANVAS_INSIDE_COL_2_WIDTH); // COL_3 is the 1/3 of the CANVAS_INSIDE_WIDTH

   // HEADER
   cout << setfill(TOP_BORDER);
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CORNER << setw(CANVAS_TOTAL_WIDTH / 2) << right << CORNER << endl;
   cout << setfill(' ');
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << LEFT_BORDER << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl; 
   cout << setw(CANVAS_TOTAL_WIDTH / 2 - displayName.length() / 2) << left << LEFT_BORDER << setw(displayName.length()) << left << displayName << setw(CANVAS_TOTAL_WIDTH - (CANVAS_TOTAL_WIDTH / 2 - displayName.length() / 2 + displayName.length())) << right << RIGHT_BORDER << endl; 
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << LEFT_BORDER << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl; 
   
   if (fareDurationMinute <= 0) {
      // DISPLAY CANCELLATION FEE
       cout << fixed << setprecision(2); // A VOIR (DUPLICATION)
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Frais annulation" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << cancellationFee << " " << RIGHT_BORDER << endl;
   }
   else{
      // Affichage ILIAS
      cout << fixed << setprecision(2); // A VOIR (DUPLICATION)
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Distance" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 4) << right << fareKm << " km " << RIGHT_BORDER << endl;
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " temps ecoule" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 5) << right << fareDurationMinute << " min " << RIGHT_BORDER << endl;
      cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << LEFT_BORDER << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl; 
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Prix de base" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << baseFee << " " << RIGHT_BORDER << endl;
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Prix distance" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << totalDistanceFee << " " << RIGHT_BORDER << endl;
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Prix temps" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << totalDurationFee << " " << RIGHT_BORDER << endl;
      cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Total" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << subTotalFee << " " << RIGHT_BORDER << endl;
      
      if (subTotalFee < minimumFee) {
         cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << LEFT_BORDER << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl; 
         cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Course minimale" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << minimumFee << " " << RIGHT_BORDER << endl;
      }
   }
  
   // FOOTER
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << LEFT_BORDER << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl; 
   cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " Prix" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << totalFee << " " << RIGHT_BORDER << endl;
   cout << LEFT_BORDER << setw(CANVAS_INSIDE_COL_1_WIDTH) << left << " (incl. TVA)" << setw(CANVAS_INSIDE_COL_2_WIDTH) << COLUMN_SEPARATOR << setw(CANVAS_INSIDE_COL_3_WIDTH - 1) << right << totalFeeVatValue << " " << RIGHT_BORDER << endl;
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << LEFT_BORDER << setw(CANVAS_TOTAL_WIDTH / 2) << right << RIGHT_BORDER << endl; 
   cout << setfill(BOTTOM_BORDER);
   cout << setw(CANVAS_TOTAL_WIDTH / 2) << left << CORNER << setw(CANVAS_TOTAL_WIDTH / 2) << right << CORNER << endl;



   return 0;
}

