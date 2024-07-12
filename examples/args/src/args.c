/*
 * Title:			args - argc and argv example
 * Author:			Paul Cawte
 * Created:			22/06/2022
 * Last Updated:	08/06/2023 - adapted from example by Dean Belfield
 *
 * Modinfo:
 */
 
#include <stdio.h>

// Parameters:
// - argc: Argument count
// - argv: Pointer to the argument string - zero terminated, parameters separated by spaces
//

int main(int argc, char * argv[])
{
	printf("Args example:\n\r");

	printf("Arguments:\n\r");
	printf("- argc: %d\n\r", argc);
	
	for(int i = 0; i < argc; i++)
	{
		printf("- argv[%d]: %s\n\r", i, argv[i]);
	}
	printf("Press any key to quit\n\r");
	getchar();
	return 0;
} 