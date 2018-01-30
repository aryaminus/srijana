# Srijana
A C++ and OpenGL based game made for 5th semester Graphics Project and Neural Network working.

**Currently in alpha state**

[![Flowmaker features](https://i.imgur.com/FIacJUP.gif)](https://youtu.be/ySW2ejs6f84)

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
- [ ] Fix gluPerspective from glOrtho when moving from welcome() to DrawNeural()
- [ ] When clicked User/Play_Neural, resize is needed which needs to be fixed
- [ ] Implementation of better algorithm than Q-learning
- [ ] Setup for Keyboard press to navigate snake

-----------------------------------------------------------------------------------------------------------

## Contributing

1. Fork it (<https://github.com/aryaminus/srijana/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

**Enjoy!**

