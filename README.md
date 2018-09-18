# Hello OpenGL - Intro to Graphics Programming
Memos from the OpenGL course by TheChernoProject. Course playlist can be found [here](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2).

## PART 1: What is OpenGL?
- a graphics API
- allows us to do graphics with our GPU
- OpenGL is one of the many apis that allow us to access the graphics card control it
- other similar apis are Direct3D, Vulcan, Metal...
- NOT a library or engine, just a specification
- this spec is not downloaded, but implemented in our GPUs by the GPU manufacturers such as nvidia in their drivers
- AMD, intel, nvidia all have their own implementations of this specification
- because of slight differences in this implemenmtation the different GPU:s can render the same graphics is slightly different ways
- OpenGL is not open source (the code implementing it is made by the gpu manufacturers and they certainly don't give it away)
- OpenGL is cross-platform (runs on windows, mac, linux, android) but often the non-general options (for example metal for ios are "better" since they are native to that device
- game engines implement multiple graphics apis
- OpenGL is very simple, which makes it a good grapics API for learning
- modern OpenGL vs legacy OpenGL: in the 90s when OpenGL was released the graphics cards where not even nearly as good as now, and OpenGL has evolved to give much more control over what the GPU does than it did back then
- Legacy OpenGL is really easy to use since it only has a small set of presets (`lightning: True`) in comparison to modern OpenGL
- the biggest difference is that modern OpenGL implements programmable shaders (code that runs on the GPU) 

## PART 2: Setting up OpenGL and Creating a Window in C++
- windowing is not the same in the different operating systems -> multiplatform support

| Graphics API | OS |
|---------------|----|
| Direct3D/DirectX | Windows |
| X Window/Xlib | Linux |
| Quartz2D/CoreGraphics | MacOS |

- implementation of appropriate platform layer: for example [GLFW](https://www.glfw.org/) (create window, create context, give us access to input)
- after downloading GLFW (precompiled binaries for Windows, 32) one can simply check the implementation in the docs
- about the binaries: "I'm running 64 bit Windows so I take the 64 one" --> NO! the architecture that matters is what you're building for, i.e. are you set Visual Studio building for win32/x32, you need the 32 bit one (what matters is how you compile your application, not which operating system you use)
- we started by drawing a triangle by legacy OpenGL to check that OpenGL is up and running

## PART 3: Modern OpenGL
- getting new OpenGL functions on Windows in our C++ code, we need to (to use any functoinality that is newer than OpenGL 1.1) we need to "pull the functions out of the drivers" >> acces the driver DLL files and retrieve function pointers to them (for example access Win32 drivers)
- this could be done manually but then it wouldn't be cross-platform (and there are many, many functions in there)
- [GLEW (OpenGl Extension Wrangler)](https://en.wikipedia.org/wiki/OpenGL_Extension_Wrangler_Library) is a library that provides the OpenGL declarations (the actual implementation goes into the library, identifies your graphics driver, finds the appropriate `.dll`-file and then loads all of the function pointers
- in other words these libraries don't implement the functions, they just access them on your computer in their binary form
- worth reading the GLEW documentation since it isn't totally obvious (for example `glewInit()` and the requirement of having a valid OpenGL rendering context before getting started)
- Now you can access OpenGL => 4.4.0





