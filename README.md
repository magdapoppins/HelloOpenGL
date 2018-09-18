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

## PART 4: Vertex Buffers and Drawing a Triangle
- a **vertex buffer** is just a memorybuffer, an array of bytes of memory, a blob of memory into which we can push bytes
- because it's in OpenGL, it's in our GPU in our video RAM (?)

What happens is:
1) I define a bunch of data
2) I put it in my GPU's VRAM
3) I issue a draw call on that bunch ("Read from it like this (insert definition of how to read it) and draw it on the screen like this (some info about this, too)")

- so we need to tell the GPU what to do with a program, and that program is called a **shader**
- a shader is just a program that runs on the GPU
- OpenGL operates as a **state machine** - you set a series of state, and everything is very contextual
- what it needs to draw a triangle is part of the state ("Select this buffer", "Select this shader", "Draw me (based on the prev stuff) a triangle")
- a vertex buffer is generated with the method `glGenBuffers()` that takes in the number of buffers and a pointer to an unsigned int (which will become the integer id of the generated buffer)
- after creating it, select the buffer by `glBindBuffer()`
- after this, you can insert data into the buffer by `glBufferData()`
- the size of the data would be for example a float array (called `positoins`) with 6 floating point numbers, which would make the buffer size `sizeof(positions)` or `6*sizeof(float)`
- [docs.gl](docs.gl) is a great resource for finding info about these methods
- sidenote: the embedded systems versions of opengl are the ones used in mobile devices
- the vertexbuffer can be static or dynamic (are we changing the shape we are drawing?)
- you also need to specify how to draw the data - `glDrawArrays(GL_TRIANGLES, startindex, nrOfIndicesToBeRendered)`
- if we have an index buffer we can use `glDrawElements()`

## PART 5: Vertex Atrributes and Layouts in OpenGL
1) Supply graphics card with data
2) Store memory with data on GPU
3) Use a shader to read data and write it on screen

- when the shader starts reading the specified data it needs to know what data it is
- so we need to tell OpenGL what the data in the memory is
- --> `glVertexAttribPointer()` 
- in case our data would look like this: 
```cpp
float positions[6] = {
  0.5f, 0.5f, // Vertex 1 (has 2 attributes, 2 positions)
  0.0f, 0.0f, // Vertex 2
  -0.5f, -0.5f  // Vertex 3
}
```
- `glVertexAttribPointer(0 (first position attribute), 2 (floats per vertex), GL_FLOAT (type), GL_FALSE (normalized), 2*sizeof(float) (stride = length of one vertex in buffer), 0 (pointer = pointer to attrib inside vertex))`
- stride = distance in bytes to next vertex
- pointer = distance in size to second attribute
- a vertex == a point in our coordinate system (not a position, since it can contain way more info such as texture, normals, tangents...) for position, **vertex position** is a  better term
- after all of this we still need to enable our vertex attribute by calling `glEnableVertexAttribArray(0)`

## PART 6: Shaders in OpenGL
- a shader - a program that runs on our GPU, not CPU like everything else
- written as a string and given to the graphics card
- the GPU is made for graphics and dows some things way better than the CPU
- vertex and fragment (pixel) shaders are by far the most popular shader types
- now we ae processing the draw call and turning data into patterns on the screen

When we issue a draw call:
1) The vertex shader is called (called once for each vertex and tells the GPU **where in your window you want that vertex to be**)
2) The fragment shader is called (called once per pixel and rasterize the area that is to be filled in with the determined color) 
3) We see stuff on the screen

## PART 7: Writing Shaders
- one way of making a simple shader is to have two functions, `CreateShader()` that takes strings for vertex- and fragmentshaders as params and `CompileShader()` that also takes in a string and a type integer and calls `glCreateShader()`

**CreateShader(vertexShader, fragmentShader)**  
0) Create a program (`glCreateProgram()`) that will store the shaders
1) Call CompileShader for vertex shader
2) Call CompileShader for fragment shader
3) Attach these shaders to our program so we can use both of them
4) Link the program
5) Validate program
6) Detatch shaders since they are now attached to the program

**CompileShader(type, source)**
1) Create shader and store id
2) Set shader source
3) Compile shader








