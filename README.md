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

For correct installation and further use of the system, access to the files of the QT module, the C++ compiler and the Cmake program is required.
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

License for QT: https://www.qt.io/terms-conditions

License for Cmake: https://gitlab.kitware.com/cmake/cmake/raw/master/Copyright.txt

## What is available in Historical-ciphers-app.

Currently available in the Historical-ciphers-app are: 
- Affine ciphers and simple substitution cipher; 
- Hill ciphers; 
- Vigener ciphers; 
- Magma cipher.
