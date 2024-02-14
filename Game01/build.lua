project "Game01"
   kind "ConsoleApp"
   language "C++"
   toolset "clang"
   targetdir "../bin/%{cfg.buildcfg}"
   includedirs { "../vendor/include/" }
   libdirs { "../vendor/lib/**" }
   

   files { "**.h", "**.cpp", "**.hpp" }

   filter "configurations:Debug"
      defines { "DEBUG", "SFML_STATIC" }
      symbols "On"
      links {
         "sfml-graphics-s-d",
         "sfml-window-s-d",
         "sfml-audio-s-d",
         "sfml-network-s-d",
         "sfml-system-s-d",
         "opengl32", "freetype", "winmm", "gdi32"
      }


   filter "configurations:Release"
      defines { "NDEBUG", "SFML_STATIC" }
      optimize "On"
      links {
         "sfml-graphics-s",
         "sfml-window-s",
         "sfml-audio-s",
         "sfml-network-s",
         "sfml-system-s",
         "opengl32", "freetype", "winmm", "gdi32"
      }