# Firefly #

## About the Project
Firefly is a rendering engine I create for my Informatics courses. It's prone to be enhanced in a short lapse of time.
At this day, he can upload and render simple mesh with a Cook-Torrence shader.

## Module gui branch
This branch is an enhancement of the original project. In this part I try to create a fully customable and interactive gui for the rendering pypeline. This branch is prone to quick update.

### Thing done :
      - Creating an modulable gui library with Qt

### To do :
      - Adjust the pipeline with the node interface
            - Create a direct shading pipeline.
            - Create a deffered shading pipeline.
      - Make a visually better interface

## Building Firefly
Cmake is the building tools used for this project, with a minimum version of 2.8.
If you don"t have Cmake, you can download it at http://www.cmake.org/.

First Step : To maximize space, the library are compressed. Think to unzip them before building !

#### Unix:

      $ mkdir build
      $ cd build
      $ cmake ..
      $ make

#### Windows:
  Don't know yet how it can work... I think Mingw or Cmake can do the job
  
## Acknowledgment:
Firefly is based on the Assimp and the GLM Library. You can get them at :

    Assimp : http://www.assimp.org/
    GLM : http://glm.g-truc.net/
  
