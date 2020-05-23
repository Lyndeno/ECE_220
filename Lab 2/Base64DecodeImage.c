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
	FILE* f_key = fopen("SecretKey.dat", "r");
	FILE* f_decode = fopen("Image.jpg", "w+");
	FILE* f_encode = fopen("SecretImage.dat", "r");

	// Check for file errors
	if (f_key == NULL || f_decode == NULL || f_encode == NULL) { 
		printf("Oof");
		return ERR;
	}

	// Open key file
	if (fread(&base64_key, 1, 64, f_key) != 64) {
		printf("Oof, this key is invalid");
		return ERR;
	}

	//loop through file until the very end
	while (!file_end) {
		// Declare some temporary variables
		uint8_t char_length = 0;
		int8_t char_data[4] = { 0, 0, 0,0};
		uint8_t out_char[3];
		uint8_t fillbit = 0;
		uint8_t out_byte = 3;

		// read
		while (char_length < 4) {
			char_data[char_length] = fgetc(f_encode);
			
			if (char_data[char_length] == EOF) {
				if(char_length == 0) { no_write = true; }
				file_end = true;
				// Change EOF character to 0 to avoid messing up decoding
				char_data[char_length] = 0;
				printf("Reached end of file");
				break;
			}

			if(char_data[char_length] == '=') {
				printf("Found filler character");
				//char_data[char_length] = 0;
				out_byte--;
			}

			// Check if end of file
			if(char_data[char_length] != space && char_data[char_length] != newline)
			{
				char_length++; // increase char index
			}
			else {
				printf("Skipping over space or newline character");
			}

			

			
		}

		if (!no_write) {

			uint8_t temp_char[4] = {0,0,0,0};

			for(int i = 0; i < 4; i++) {
				// Place the Key indices in the temp char
				for (int j = 0; j < 64; j++) {
					if (char_data[i] == base64_key[j]) {
						temp_char[i] = j;
						break;
					}
				}

				if(out_byte <= 2) {
					temp_char[3] = 0;
				}
				if(out_byte == 1) {
					temp_char[2] = 0;
				}

				// bitshift time
				out_char[0] = (temp_char[0] << 2) + (temp_char[1] >> 4);
				out_char[1] = (temp_char[1] << 4) + (temp_char[2] >> 2);
				out_char[2] = (temp_char[2] << 6) + (temp_char[3]);

			}


			// Write converted characters to file
			fwrite(&out_char, sizeof(uint8_t), out_byte, f_decode);
		}
	}

	// Close files
	fclose(f_decode);
	fclose(f_key);
	fclose(f_encode);

	return 0;
}