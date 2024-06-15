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
Установка на Windows:
На Windows можно использовать один из пакетных менеджеров.

- vcpkg

Например, установка Qt6 через менеджер vcpkg:

```vcpkg install qt```

Установка только базового пакета

```vcpkg install qtbase```

- MSYS2/Packman

Установка Qt через MSYS с помощью пакетного менеджера packman:

```pacman -S mingw-w64-x86_64-qt6```

Только базовый пакет

```pacman -S mingw-w64-x86_64-qt6-base```

Установка Qt Creator

```pacman -S mingw-w64-x86_64-qt-creator```

- chocolatey

Установка Qt6 с Qt Creator через менеджер chocolatey:

```choco install -y qt6-base-dev cmake qtcreator```

- winget

Установка Qt6 через менеджер winget:

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
