/**
 *CS50, CS50 Study, Maths
 *temperature_conversion
 *Victor Barriga
 *victorbarriga@live.com
 *Program uses input from user temperature in Fahrenheit
 *converts to Celsius, prints out the result w/ one decimal place
 */

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // ask user for temperature
    printf("Please enter a temperature in Fahrenheit: ");
    float fahrenheit_temp = GetFloat();
     
    // convert F to C
    float celsius = (5.0 / 9.0) * (fahrenheit_temp - 32.0);
    
    // display result
    printf("Temperature in Celsius: %.1f\n", celsius);

}
