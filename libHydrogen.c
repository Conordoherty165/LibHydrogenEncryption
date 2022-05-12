#include "hydrogen.h"
#include <stdint.h>
#include <stdio.h>
#define CONTEXT "Examples"
#define MESSAGE "Hello World!"
#define MESSAGE_LEN 12
#define CIPHERTEXT_LEN (hydro_secretbox_HEADERBYTES + MESSAGE_LEN)

uint8_t key[hydro_secretbox_KEYBYTES];
uint8_t ciphertext[CIPHERTEXT_LEN];
char decrypted[MESSAGE_LEN];

int main(int argc, char **argv) {
	if (hydro_init() != 0) {
	        abort();
	    }
	hydro_secretbox_keygen(key);
	hydro_secretbox_encrypt(ciphertext, MESSAGE, MESSAGE_LEN, 0, CONTEXT, key);

	if (hydro_secretbox_decrypt(decrypted, ciphertext, CIPHERTEXT_LEN, 0, CONTEXT, key) != 0) {
	    /* message forged! */
	}
	else{
		printf("message: %s \n  ciphertext: %s \n  decrypted: %s \n",MESSAGE,ciphertext,decrypted);
	}
	return 0;
}
