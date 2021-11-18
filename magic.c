#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>

#define uint unsigned int

static char message[] = "Hello World";

int main(void) {

  // Get the individual alphabet of the message
  char alphabet[sizeof(message)] = {};
  {
    // find the number occurrences of each character in the message
    char ascii[256] = {};
    for (uint j = 0; j < sizeof(message)-1; ++j) {
      ascii[(int)message[j]]+=1;
    }
    int idx = 0;
    for (uint i = 0; i < sizeof(ascii); ++i) {
      if (ascii[i] > 0) {
        alphabet[idx++] = i;
      }
    }
    // this asserts alphabet will be null terminated
    alphabet[idx] = 0;
  }

  // create a table of indices of each letter
  int indx[sizeof(message)-1] = {};
  {
      for (uint i = 0; i < sizeof(message)-1; ++i) {
        char c = message[i];
        for (uint j = 0; alphabet[j]; ++j) {
          if (alphabet[j] == c) {
            indx[i] = j;
          }
        }
      }
  }

  // encode the indices
  uint64_t encoded_indx = 0;
  // each indice is a 4bit number, so we can put two indices in a single byte
  // this will result in a len(indx)/2 bytes long number.
  for (uint i = 0; i < sizeof(message) - 1; ++i) {
    encoded_indx |= (uint64_t)indx[i] << 4*i;
  }
  encoded_indx <<= 4;

  // encode the alphabet
  unsigned long encoded_alphabet = 0;
  // the alphabet is 8 characters long
  // each character is 7 bits long but we will use 8 bits to represent them
  for (uint i = 0; i < sizeof(alphabet)-1; ++i) {
    encoded_alphabet |= (uint64_t)alphabet[i] << 8*i;
  }

  printf("alphabet: \"%s\"\n", alphabet);
  printf("indx: {");
  for (uint i = 0; i < sizeof(message)-1; ++i) {
    printf("%d,", indx[i]);
  }
  printf("}\n");
  printf("encoded_indx: 0x%"PRIX64"\n", encoded_indx);
  printf("encoded_alphabet: 0x%"PRIX64"\n", encoded_alphabet);

  return 0;
}
