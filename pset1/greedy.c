/***
 * greedy.c (c) by Victor Barriga
 * 
 * greedy.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * greedy.c 
 * Computer Science 50
 * Problem Set 1 
 * 
 * Usage: ./greedy
 *
 * Proram receives input from the user by asking how much change is owed.
 * The program returns the minimum number of number of coins, largest to 
 * smallest, yielding the fewest coins possible.
 *
 **/

#include <cs50.h>
#include <stdio.h>
#include <math.h>
 

int main(int argc, string argv[])
{
    // declare variables for change owed, and convert it to all cents
    int change_owed;
    int total_coins;
    
    // get input from user, amount due
    do
    {
        printf("How much change is owed?: ");
        change_owed = (GetFloat() + 0.005) * 100;
    }
    while (change_owed < 0);
    
    //check if change is due
    while (change_owed > 0)
    {
        // check for quarters
        int remaining_change = (change_owed % 25);
        int total_quarters = (change_owed / 25);
        
        // check for dimes
        change_owed = (remaining_change % 10);
        int total_dimes = (remaining_change / 10);
        
        // check for nickles
        remaining_change = (change_owed % 5);
        int total_nickles = (change_owed / 5);
        // check for pennies
        change_owed = (remaining_change % 1);
        int total_pennies = (remaining_change / 1);
        
        // totals the coins
        total_coins = (total_quarters + total_dimes + total_nickles + total_pennies);
        change_owed = (0);
    }

    printf("%i\n", total_coins);

    return 0;
}
