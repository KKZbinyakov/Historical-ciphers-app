![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)

# Historical-ciphers-app

##  What is it?

This is an application implemented in the C++ programming language to work with historical and outdated ciphers.

## The Latest Version

Details of the latest version can be found on the [Historical-ciphers-app
server project page](https://github.com/KKZbinyakov/Historical-ciphers-app/tree/main).

## Documentation

The documentation available as of the date of this release is
included in HTML format in the docs/manual/ directory.  The most
up-to-date documentation can be found at
[main](https://github.com/KKZbinyakov/Historical-ciphers-app/tree/main).

## Installation

For correct installation and further use of the system, access to the files of the QT module, the C++ compiler and the Cmake program is required. Cmake Installation Instructions [here](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Getting%20Started.html).

Installation on Windows:
On Windows, you can use one of the package managers.

- vcpkg

For example, installing Qt6 through the vcpkg manager:

```vcpkg install qt```

Installing only the basic package

```vcpkg install qtbase```

- MSYS2/Packman

Installing Qt via MSYS using the pacman package manager:

```pacman -S mingw-w64-x86_64-qt6```

Basic package only

```pacman -S mingw-w64-x86_64-qt6-base```

Installing Qt Creator

```pacman -S mingw-w64-x86_64-qt-creator```

- chocolatey

Installing Qt6 with Qt Creator via chocolatey manager:

```choco install -y qt6-base-dev cmake qtcreator```

- winget

Installing Qt6 via the winget manager:

```winget install --id=miurahr.aqtinstall  -e```


## Licensing

License for QT you can find [here](https://www.qt.io/terms-conditions).

License for Cmake you can find [here](https://gitlab.kitware.com/cmake/cmake/raw/master/Copyright.txt).

License for GNU you can find [here](https://www.gnu.org/licenses/licenses.ru).

## What is available in Historical-ciphers-app.

Currently available in the Historical-ciphers-app are: 
- Affine ciphers;
- Simple substitution cipher; 
- Hill ciphers; 
- Vigener ciphers; 
- Magma cipher.

## How the program works.

- At the very beginning, the user is presented with a choice of the cipher he wants to use:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/begin_interface.jpg?raw=true)
- Next, the user selects the type of cipher that he wants to use (or the mode of operation for the gamma cipher):
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a simple substitution cipher, the user enters the alphabet, a permutation of the alphabet, and the text he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For an affine cipher, the user enters the alphabet, the keys a and b, and the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For an affine recurrent cipher, the user enters the alphabet, the keys a1, a2, b1, b2, the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For the Hill cipher, the user enters the size of the key matrix, the key matrix, the alphabet and the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a recurrent Hill cipher, the user enters the size of the key matrices, two key matrices, the alphabet, and the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For the Vigener cipher with the repetition of a short slogan, the user enters the key, the alphabet and the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a Vision cipher with a self-keyed ciphertext, the user enters the key, the alphabet, and the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a Vision cipher with a self-key in plaintext, the user enters the key, the alphabet, and the text that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a magma cipher with a normal mode of operation, the user enters the key and the data that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted data:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a magma cipher with a gamma mode of operation, the user enters the key, the sync link, and the data that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted data:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
- For a magma cipher with feedback gamma mode, the user enters the key, the sync link, and the data that he wants to encrypt/decrypt. At the exit, the user receives an encrypted/decrypted text:
![Netu kartinki](https://github.com/KKZbiniakov/Historical-ciphers-app/blob/main/pics/img-53391-15897027866640.jpg?raw=true)
