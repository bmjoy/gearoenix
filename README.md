# Gearoenix Game Engine

Yet another cross-platform C++ 3D game engine.

[![codecov](https://codecov.io/gh/Hossein-Noroozpour/gearoenix/branch/master/graph/badge.svg)](https://codecov.io/gh/Hossein-Noroozpour/gearoenix)
[![CircleCI](https://circleci.com/gh/Hossein-Noroozpour/gearoenix.svg?style=svg)](https://circleci.com/gh/Hossein-Noroozpour/gearoenix)

## Features

- It is cross-platform.
- It is Lightweight.
- Highly multithreaded architecture.
- It has a runtime abtraction over Graphic API backends (e.g. `OpenGL ES2`, `OpenGL ES3`,
  `OpenGL 3.3`, `OpenGL 4.3`, `Directx11(WIP)` and `Vulkan(WIP)`).
- It can automatically choose the highest available backend and in addition in your build you can
  off an API backend so it will not compile that API and then your binary size will be reduced.
- It has its own file format for importing scenes data in to game. This file
  format help the engine to have better performance in loading a scene and
  reduce the size of the data hence It make smaller publishable binaries.
- It has its own
  [blender file exporter](https://github.com/Hossein-Noroozpour/gearoenix-blender)
  that try to force best practices in data creation and have control
  over content creation.
- Asset management that cache assets for reducing load time and making the reuse of assets
  more efficient.
- Multithreaded rendering.
- Supports variety of textures:
  - 2D texture
  - 3D texture (WIP, Implemented in blender part, but it is not developed in
    engine yet)
  - Cube texture
- Painlessly cross-platform and very fast mathematic structures.
- Lighting
- Shadowing
- Skyboxing
- Fast font displaying mechanism.
- Different type of cameras: Perspective, Orthographic
- Graphic pipeline management to cache and reduce number of switches and
  increasing performance.
- Multithreaded occlusion culling.
- Multithreaded mathematic works for increasing performance.
- Pbr Material.
- Ability to create customized and or special materials/effects with special behaviors.
- Adaptive cascaded shadow mapping (WIP)

## Demos

In this section I need contribution.

- [This is WebAssembly demo (Firefox shows better)](https://hossein-noroozpour.github.io/gearoenix-static-files/web-demo/index.html)
- [This is Android demo](https://hossein-noroozpour.github.io/gearoenix-static-files/android/android.7z)
- [This is Linux demo](https://hossein-noroozpour.github.io/gearoenix-static-files/linux/linux.7z)

## How to Build

- Star this project (:D)
- Download zip of master branch.
- Execute the setup.py with your python3 compiler. (This script provide a simple way of gathering
  dependencies of project and organizing the work space.)

### Desktop OSs

- Create a build directory and cd it. (e.g. 'build')
- Do camke on it. (like: ```cmake -DCMAKE_BUILD_TYPE=Release ..```)
- Build it. (like: ```cmake --build . --config Release```)
- If you have a problem to initialize the environment,
  you either can use the provided docker images in docker hub or
  look at the provided **Dockerfile** file in project ci part.

### Android

- You have to have the latest android studio version and ndk installed
- Open the android folder with android studio.
- Run and enjoy.

### iOS

- You must have the latest XCode and iOS sdk installed
- Create a build directory and cd it. (e.g. 'build')
- Do camke on it. (like: ```cmake -DCMAKE_BUILD_TYPE=Release .. -DCMAKE_SYSTEM_NAME=iOS```)
- Open the XCode project.
- Connect your iOS device (currently there is a bug in one of the static library of ios-simulator that prevents the build for it)
- Sign the project with your ios-developer team
- Run and enjoy.

### Webassembly

- Support for webassembly is very complete but due to [this issue in Emscripten](https://github.com/emscripten-core/emscripten/issues/6009) you can not run the your build file, however building for webassembly is as follow.
- Create a build directory and cd it. (e.g. 'wasm-build')
- Your console must have emscripten sdk in its environment.
- ```emconfigure cmake -DCMAKE_BUILD_TYPE=Release ..```
- ```cmake --build . --config Release```
- If you have python3 in your path do ```python3 -m http.server 8080``` or if you have python2 ```python -m SimpleHTTPServer 8080```
- Open your browser and go to ```http://localhost:8080/examples/<name-of-example>```

## Contribution

- Test coverage is not very well and I don't have time for it,
  if you want to contribute in it this is the best place you can start.
- 3D content development.
- Promotion of this project.
- Donating to this project.

## License

You can do whatever you want to do with it as long as you take responsibility
of all of
its consequences, **But** If you used it and it was useful for you, please make
an acknowledgment and promotion for this project and me, I'm currently seeking
for a job in the graphic and game-engine fields.
