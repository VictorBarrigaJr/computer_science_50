/**
 *CS50, CS50 Study, Functions
 *accumilatin_interest
 *Victor Barriga
 *victorbarriga@live.com
 *Implement a function with prototype :
 *double accumulate_interest(double balance, double rate);
 *it takes two as input blanace & apr outputs balance after 1 year of interest accrued
 *Starting balane: 100
 *Annual interest rate: 0.05
 *Updated balance: 105 
 */
 
 #include <cs50.h>
 #include <stdio.h>
 
 // TODO: function prototype
 double accumulate_interest(double balance, double rate);
  
 int main (void)
 {
    printf("Starting balance: ");
    double start = GetDouble();
    printf("Annual interest rate: ");
    double interest = GetDouble();
    double updated = accumulate_interest(start, interest);// TODO: call your function
    printf("Updated balance: %.2f\n", updated);
 }
 
 // TODO:  function definition
 double accumulate_interest(double balance, double rate) 
 {
    // multiply starting balance by interest rate
    double accrued = balance * rate;
    // add interst to starting balance
    double updated = balance + accrued;
    // return updated blance
    return updated;
 }

