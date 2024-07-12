/*
 * Title:			basic floating point example
 * Author:			Paul Cawte
 * Created:			1978 by K&R
 * Last Updated:	08/06/2023 
 *
 * Modinfo:
 *  Copied from Fahrenheit-Celsius floating point example from K&R
 *  Adapted to ANSI C
 */
 
#include <stdio.h>

int main(void)
{
    float fahr, celcius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celcius = (5.0/9.0) * (fahr-32);
        printf("%3.0f %6.1f\n\r", fahr, celcius);
        fahr = fahr + step;
    }
	return 0;
}