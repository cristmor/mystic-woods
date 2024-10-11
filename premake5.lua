workspace("Game")
configurations({ "Debug", "Release" })

project("Game")
kind("ConsoleApp")
language("C++")

targetdir("bin/%{cfg.buildcfg}")
objdir("bin/%{cfg.buildcfg}/obj/")

files({ "src/**.hpp", "src/**.cpp" })
includedirs({ "src/" })

links({ "sfml-graphics", "sfml-window", "sfml-system" })

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("ON")
