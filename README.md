# safe-chat

This is an implementation of AES-256 in C, done from scratch for my school project.

The program takes 5 arguments:
 1. The mode of operation (encoding / decoding).
 2. The name of the input file.
 3. The name of the output file.
 4. The key.
 5. The initialization vector (iv).

4, 5 are in base64.

The program runs AES using the above arguments.
