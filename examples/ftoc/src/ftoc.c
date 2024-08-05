/*
 * Title:			while loop example
 * Author:			Paul Cawte
 * Created:			1978 by K&R
 * Last Updated:	08/06/2023 
 *
 * Modinfo:
 *  Copied Fahrenheit-Celsius example from K&R
 *  Adapted to ANSI C
 */
 
#include <stdio.h>

int main(void)
{
    int fahr, celcius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celcius = 5 * (fahr-32) / 9;
        printf("%d\t%d\n\r", fahr, celcius);
        fahr = fahr + step;
    }
	return 0;
}