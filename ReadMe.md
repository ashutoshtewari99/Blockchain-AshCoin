To run the file type in terminal: g++ sha256.cpp Blockchain.cpp -o sha256_example && ./sha256_example
In the earlier version of this Blockchain it used the standard hashing library of C++ 
which used to create random hashes of different sizes
But now that it uses SHA 256 hashing algorithm, it is far more secure 
and exactly 64 characters long.
More about it can be read on: http://www.zedwood.com/article/cpp-sha256-function
