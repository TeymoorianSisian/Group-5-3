#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>

int main() {
    int total_days_on_trip;
    int departure_time;
    int arrival_time;

    double total_expenses = 0;
    double total_allowable_expenses = 0;
    double total_reimbursement = 0;
    double total_amount_saved = 0;
    
    getTotalDaysOnTrip(&total_days_on_trip); 
    getDepartureAndArrivalTimes(&departure_time, &arrival_time);
    getRoundTripAirfare(&total_expenses);
    getCarRentals(&total_expenses);
    getPrivateVehicleUsed(&total_expenses);
    getParkingFees(&total_days_on_trip,
                   &total_expenses, 
                   &total_allowable_expenses, 
                   &total_reimbursement, 
                   &total_amount_saved);
    getTaxiFees(&total_days_on_trip, 
                &total_expenses, 
                &total_allowable_expenses, 
                &total_reimbursement, 
                &total_amount_saved);

    getConferenceAndRegistrationFees(&total_expenses);

    getHotelFees(&total_days_on_trip,
                 &total_expenses, 
                 &total_allowable_expenses, 
                 &total_reimbursement, 
                 &total_amount_saved);
                 
    getMealFees(&total_days_on_trip,
                &departure_time, 
                &arrival_time,
                &total_expenses,
                &total_allowable_expenses, 
                &total_reimbursement, 
                &total_amount_saved);       
    
    displayTotals(total_days_on_trip,     
                  departure_time, 
                  arrival_time, 
                  total_expenses, 
                  total_allowable_expenses, 
                  total_reimbursement, 
                  total_amount_saved);
    
    return 0;

}

