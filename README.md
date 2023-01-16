# 3D Mesh

## Features

+ Load .obj file
+ Phong Shading
+ Trackball Rotation

### Demo

<img src="https://i.imgur.com/Yt4EjSc.png" style="zoom:45%;" />

<img src="https://i.imgur.com/Iv1CaiH.png" style="zoom:50%;" />

### Compile

Copy the command below and paste on command line.

```shell
g++ -g -std=c++17 -I ./include -L ./lib -I ./src/"Game Logic" ./src/"Game Logic"/"Basic Logic"/*.cpp ./src/"Game Logic"/"System"/*.cpp main.cpp -o main -lglad glfw3.dll
./main.exe
```

### Input

+ Hold down left mouse button and drag it to change dinosaur rotation.