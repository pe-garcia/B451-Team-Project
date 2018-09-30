# B451-Team-Project
Team project for B451 Security in Computing

C++ code that does the following:

    Read in a password of 16 characters and the name of a text file from the user

    Encrypt the plaintext from the given text file using the 128-bit AES encryption algorithm (in the ECB
mode), with the 128-bit secret key being the password entered by the user. Use the PKCS#5 standard for
padding the plaintext.
    
    Write the ciphertext to another text file in the following format: The nth line contains the nth ciphertext
block as a list of 16 decimal numbers corresponding to the values of the 16 bytes in the ciphertext block.
Each decimal number is output with a width of 4. (See the cipher_data.txt file for an example)
