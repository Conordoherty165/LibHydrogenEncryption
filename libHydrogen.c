#include "hydrogen.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CONTEXT "Examples"

int main(int argc, char **argv) {
    // Check that hydrogen can do encryption
	if (hydro_init() != 0 || argc != 2) {
        printf("Error initializing Hydrogen or wrong number of arguments passed (expected %d, got %d)\n", 1, argc - 1);
        return EXIT_FAILURE;
	}

    // Get the command line argument
    char *message = argv[1];
    int len = strlen(message);
    int cipher_len = hydro_secretbox_HEADERBYTES + len;

    // Initialize array memory space
    uint8_t *key = malloc(hydro_secretbox_KEYBYTES * sizeof(char));
    uint8_t *ciphertext = malloc(cipher_len * sizeof(char));
    uint8_t *decrypted = malloc(len * sizeof(char));

    // Generate the key
	hydro_secretbox_keygen(key);

    // Try to encrypt the message with our key, exit on failure
    if (hydro_secretbox_encrypt(ciphertext, message, len, 0, CONTEXT, key) != 0) {
        printf("Error encrypting");
        return EXIT_FAILURE;
    }

    // Try to decrypt the cipher text with our key, exit on failure
    // Print everything on success to show message was successfully encrypted/decrypted
	if (hydro_secretbox_decrypt(decrypted, ciphertext, cipher_len, 0, CONTEXT, key) != 0) {
        printf("Error decrypting, message is not authentic\n");
        return EXIT_FAILURE;
	} else {
		printf("Original message: %s\nEncrypted: %s\nDecrypted: %s\n", message, ciphertext, decrypted);
	}
	return EXIT_SUCCESS;
}
