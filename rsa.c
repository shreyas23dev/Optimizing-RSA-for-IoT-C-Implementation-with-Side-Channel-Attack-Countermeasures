#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) {
        return 0; // Not prime
    }
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return 0; // Not prime
        }
    }
    return 1; // Prime
}

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to calculate the modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist
}

// Function to generate public and private keys
void generateKeys(int *e, int *d, int *n) {
    int p, q;
    
    // User input for prime numbers
    do {
        printf("Enter the first prime number: ");
        scanf("%d", &p);
    } while (!isPrime(p));
    
    do {
        printf("Enter the second prime number (not equal to the first): ");
        scanf("%d", &q);
    } while (!isPrime(q) || p == q);

    *n = p * q; // Calculate n
    int phi = (p - 1) * (q - 1); // Calculate Euler's totient function

    // Choose a random public exponent e such that 1 < e < phi and gcd(e, phi) = 1
    do {
        *e = rand() % (phi - 2) + 2;
    } while (*e <= 1 || *e >= phi || gcd(*e, phi) != 1);

    *d = modInverse(*e, phi); // Calculate d
}

// Function to perform modular exponentiation
int modPow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to encrypt a message
int encrypt(int message, int e, int n) {
    return modPow(message, e, n);
}

// Function to decrypt a message
int decrypt(int cipher, int d, int n) {
    return modPow(cipher, d, n);
}

int main() {
    int e, d, n;

    // Generate public and private keys
    generateKeys(&e, &d, &n);

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    // User input for the message
    int message;
    printf("Enter a message to encrypt: ");
    scanf("%d", &message);

    // Encryption
    int cipher = encrypt(message, e, n);
    printf("Encrypted Message: %d\n", cipher);

    // Decryption
    int decryptedMessage = decrypt(cipher, d, n);
    printf("Decrypted Message: %d\n", decryptedMessage);

    return 0;
}
