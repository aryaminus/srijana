# Srijana
A C++ and OpenGL based game made for 5th semester Graphics Project and Neural Network working.

**Currently in alpha state**

[![Srijana features](https://i.imgur.com/6hHWMm7.gif)](https://github.com/aryaminus/srijana)

**Note:**
Make sure you have opengl, freeglut3-dev & libgl1-mesa-dev 

## Installation

Clone the source locally:
```
$ git clone https://github.com/aryaminus/srijana
$ cd srijana
$ make run
```
***else***
```
$ git clone https://github.com/aryaminus/srijana
$ cd srijana
$ g++ main.cpp -lGL -lglut -lGLU -o main
$ ./main
```

For Codeblocks:

- Open local source file main.cpp from Srijana directory

- **Before Build&Run**, goto:
-> Settings / Compiler / Global Compiler Settings / Linker Settings

- in Other linker options:
```
-lGL -lglut -lGLU
```

### TODO:
- [] Fix gluPerspective from glOrtho when moving from welcome() to DrawNeural()
- [x] When clicked User/Play_Neural, resize is needed which needs to be fixed
- [ ] Implementation of better algorithm than Q-learning
- [ ] Setup for Keyboard press to navigate snake

## Packages:
1. <a href="https://github.com/Shanta-chan/Snake" target="_blank">snake</a>
2. <a href="https://github.com/Ilyomix/Snake_Unix" target="_blank">snake-unix</a>
3. <a href="https://github.com/arpithank/Computer-Graphics-Airplane-Game" target="_blank">airplane-game</a>
4. <a href="https://github.com/inf0-warri0r/q_snake" target="_blank">q_snake</a>


-----------------------------------------------------------------------------------------------------------

## Contributing

1. Fork it (<https://github.com/aryaminus/srijana/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

**Enjoy!**

