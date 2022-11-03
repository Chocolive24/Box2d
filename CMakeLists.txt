# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Solution
project ("SAE921-GRP4100-Box2D")

# Each sub-project
set(EXECUTABLE_CUSTOM_NAME "00-Box2DStart")
add_subdirectory ("00-Box2DStart")

set(EXECUTABLE_CUSTOM_NAME "01-FormativeSpaceShooter")
add_subdirectory ("01-FormativeSpaceShooter")

set(EXECUTABLE_CUSTOM_NAME "GPR922_GPR4-1_Box2d-main")
add_subdirectory ("GPR922_GPR4-1_Box2d-main")

