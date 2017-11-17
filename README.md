# Firefly #

## About the Project
Firefly is a rendering engine I create for my Informatics courses. It's prone to be enhanced in a short lapse of time.

The end goal of this project is to enable the quick addition of module to test or observe the differencies between different
rendering technique.

### Work done :
#### Render :
	- Forward render with Z pre-pass and an physically based shader
	- SSAO

#### Animation :
	- Simple kinetic animation
	- linear skinning

#### Modelisation :
	- Loop Subdivision for triangular meshes

### To do :
#### Gui :
	- Create an material gui linked with the Render pass
	- Create a link between the ambient occlusion and the world pannel

#### Render :
	- Link the SSAO with the render (for the moment he's just here to show off)
	- Make other Material/Shader couple
	- Extend the interface to make composite shader possible

#### Geometry :
	- Simplification ?

#### Animation :
	- Inverse kinetic
	- dual quaternion skinning

## Building Firefly
Cmake 2.8 is the minimum building tools required for this project. You can grab it at http://www.cmake.org/.

The project need multiple library, some are just linked via git, but somme (Assimp) are so huge I preffered to compress them in the lib folder. Think to unzip them before building the project.

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
  
