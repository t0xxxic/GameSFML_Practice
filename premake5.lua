-- premake5.lua
workspace "GameSFML"
   configurations { "Debug", "Release" }
   platforms { "x64" }

   filter "system:x64"
      architecture "x64"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

include "Game01/build.lua"