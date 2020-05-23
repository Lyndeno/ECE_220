#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#define ERR -1

int main(void) {
	uint8_t base64_key[64];
	bool file_end = false;
	uint8_t group_index = 0, line_index = 0;
	bool no_write = false;
	uint8_t space = ' ';
	uint8_t newline = '\n';

	// Open files and check for errors
	FILE* f_key = fopen("Key.dat", "r");
	FILE* f_raw = fopen("Raw.dat", "r");
	FILE* f_encode = fopen("Encoded.dat", "w+");

	// Check for file errors
	if (f_key == NULL || f_raw == NULL || f_encode == NULL) { 
		printf("Oof\n");
		return ERR;
	}

	// Open key file
	if (fread(&base64_key, 1, 64, f_key) != 64) {
		printf("Oof, this key is invalid\n");
		return ERR;
	}

	//loop through file until the very end
	while (!file_end) {
		// Declare some temporary variables
		uint8_t char_length = 0;
		int8_t char_data[3] = { 0, 0, 0};
		uint8_t out_char[4];
		uint8_t fillbit = 0;
		//uint8_t out_length = 0;

		// read
		while (char_length < 3) {
			char_data[char_length] = fgetc(f_raw);
			printf("Found %c, %d\n", char_data[char_length], char_data[char_length]);
			
			// Check if end of file
			if (char_data[char_length] == EOF) {
				printf("Reached end of file\n");
				if(char_length == 0){
					no_write = true; // If EOF is beginning of group, don't write anymore
					printf("No more writing needed\n");
				}
				else if ( char_length == 1) {
					fillbit = 2; // if EOF is second character in group, fill with two =
					printf("Adding two fillers\n");
				}
				else if ( char_length == 2) {
					fillbit = 1; // if EOF is last in group, only one =
					printf("Adding one filler\n");
				}
				file_end = true;
				// Change EOF character to 0 to avoid messing up encoding
				char_data[char_length] = 0;
				break;
			}
			char_length++; // increase char index

		}

		if (!no_write) {

			uint8_t temp_char[4]; // define a temporary char
			
			// Do bitwise operations for base64 conversion
			temp_char[0] = char_data[0] >> 2;
			temp_char[1] = ((char_data[0] << 4) & (uint8_t)48) + (char_data[1] >> 4);
			temp_char[2] = ((char_data[1] << 2) & (uint8_t)60) + (char_data[2] >> 6);
			temp_char[3] = char_data[2] & (uint8_t)63;

			


			// Go through values and move bits around
			for (int i = 0; i < 4; i++) {
				out_char[i] = base64_key[temp_char[i]];
				printf("Found indice %d, with a value of %c\n", i, out_char[i]);
			}
			
			
			// Apply our filler character
			if ( fillbit >= 1) {
				out_char[3] = '=';
				printf("Added filler character\n");
			}
			if ( fillbit == 2) {
				out_char[2] = '=';
				printf("Added filler character\n");
			}

			if (group_index >= 2) { // Add space when needed
				fwrite(&space, sizeof(uint8_t), 1, f_encode);
				printf("Adding spacer\n");
				group_index = 0;
			}
			if (line_index >= 12) { // start newline when needed
				fwrite(&newline, sizeof(newline), 1, f_encode);
				printf("Adding newline\n");
				line_index = 0;
			}

			printf("Writing final value of %c %c %c %c\n", out_char[0], out_char[1], out_char[2], out_char[3]);
			// Write converted characters to file
			fwrite(&out_char, sizeof(uint8_t), 4, f_encode);

			// increment group and line count
			group_index++;
			line_index++;
		}
	}

	// Close files
	fclose(f_raw);
	fclose(f_key);
	fclose(f_encode);

	return 0;
}