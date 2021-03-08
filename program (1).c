//COS 430 Project 1
//Group: Brian Couture, Ryan Handlon, Travis Tovey
//Programmed in C
//This program takes a given iv, plaintext and ciphertext and finds the correct key out of a word file.

#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{	//This is the encryption function
	
	EVP_CIPHER_CTX *ctx;
	int len;
	int ciphertext_len;
	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
	EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
	ciphertext_len = len;
	EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
	ciphertext_len += len;
	EVP_CIPHER_CTX_free(ctx);
	return ciphertext_len;
	
}






int main(void){
	
	FILE *file = fopen("words.txt", "r");
	int len = 16;
	unsigned char line[len];

	ssize_t read;
	unsigned char *plaintext = (unsigned char *)"This report is confidential.";
	unsigned int ciphertext[] = {0xa5, 0xfa, 0xe8, 0x7b, 0xd5, 0xf6, 0x03, 0x7a, 0x0a, 0x6f, 0x64, 0x8c, 0xeb, 0x13, 0x49, 0x1e, 0xcc, 0x3f, 0x4a, 0xc3, 0x9a, 0xca, 0x75, 0x9f, 0xf0, 0x1b, 0xf8, 0x28, 0x29, 0x81, 0x6c, 0x00};
	unsigned char iv[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
	unsigned char *key = (unsigned char *)"";
	unsigned char ciphertext2[32];	

	
	while(fgets(line, 16, file)) {	//Loops through each line in the text file
		unsigned char line2[len];
		strcpy(line2, line);
		for(int i = 0; i < (sizeof line / sizeof line[0]); i++) {	//Adds "#" buffer at the end of each word

			if (line[i] == 10) {
				for (int j = i; j < (sizeof line / sizeof line[0]); j++){
					line[j] = '#';
				}
			}	
		}

		
		int ciphertext_len;
		ciphertext_len = encrypt(plaintext, strlen ((char *)plaintext), line, iv, ciphertext2); 

		unsigned int intctext2;
		for(int i = 0; i < ciphertext_len; i++){			//compare loop
			intctext2 = (unsigned int)ciphertext2[i];
			if(ciphertext[i] != intctext2)			//compares each character
				break;
			if(i == (ciphertext_len-1)){			//If complete match
				printf("The key is %s\n", line2);
				printf("Given ciphertext: ");
				for(int j = 0; j < ciphertext_len; j++){
					printf("%x",ciphertext[j]);
				}
				printf("\n");
				printf("Encrypted text: ");
				for(int k = 0; k < ciphertext_len; k++){
					printf("%x",ciphertext2[k]);
				}
				printf("\n");
			}
		}
		
	}	

	fclose(file);
	return 0;


}
