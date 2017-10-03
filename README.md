# Firefly : Module gui #

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
Cmake is the building tools used for this project, with a minimum version of 2.8.
If you don"t have Cmake, you can download it at http://www.cmake.org/.

The project need multiple library, some are just linked via git, but somme (Assimp) are quite heavy. So I zip it in the lib folder.

#### Unix:

      $ mkdir build
      $ cd build
      $ cmake ..
      $ make

  
## Acknowledgment:
Firefly is based on the Assimp and the GLM Library. You can get them at :

    Assimp : http://www.assimp.org/
    GLM : http://glm.g-truc.net/
    OpenMesh : https://www.openmesh.org/
  
