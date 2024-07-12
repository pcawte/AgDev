/*
 * Title:			Hello World - C example
 * Author:			Dean Belfield
 * Created:			22/06/2022
 * Last Updated:	22/11/2022
 *
 * Modinfo:
 */
 
#include <stdio.h>

// Parameters:
// - argc: Argument count
// - argv: Pointer to the argument string - zero terminated, parameters separated by spaces
//

int main(int argc, char * argv[])
//int main(void)
{
	printf("Hello World!\n\r");

	printf("Arguments:\n\r");
	printf("- argc: %d\n\r", argc);
	
	for(int i = 0; i < argc; i++)
	{
		printf("- argv[%d]: %s\n\r", i, argv[i]);
	}
	return 0;
}