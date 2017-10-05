# Firefly #

## About the Project
Firefly is a rendering engine I create for my Informatics courses. It's prone to be enhanced in a short lapse of time.

The end goal of this project is to enable the quick addition of module to test or observe the differencies between different
rendering technique.


### To do :
	  - Add Animation and simple mesh deformation (needed for the class)
      - Add Tonemapping nodes
      - Add Ambient occlusion
      - Add a way to switch between the "Test version" and an "Optimized version"

## Building Firefly
Cmake 2.8 is the minimum building tools required for this project. You can grab it at http://www.cmake.org/.

The project need multiple library, some are just linked via git, but somme (Assimp) are quite heavy. So I zip it in the lib folder, it just need to be unzip to build.

#### Unix:

      $ mkdir build
      $ cd build
      $ cmake ..
      $ make

  
## Acknowledgment:
Firefly is based on some tierce library. You can get them at :

    Assimp : http://www.assimp.org/
    GLM : http://glm.g-truc.net/
    OpenMesh : https://www.openmesh.org/
  
