-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.

-- For reference, please refer to the premake wiki:
-- https://github.com/premake/premake-core/wiki

local arch_ = require "build/modules/arch"

local ROOT = "./"
local RESULTSROOT = ROOT .. "buildresults/%{cfg.platform}_%{cfg.buildcfg}/"

--------------------------------
--  WORKSPACE CONFIGURATION   --
--------------------------------
workspace "Embedded Artistry libmalloc"
  configurations { "debug", "release" }
  platforms      { "x86_64", "x86_32" }

  -- _ACTION is the argument you passed into premake5 when you ran it.
  local project_action = "UNDEFINED"
  if _ACTION ~= nill then project_action = _ACTION end

  -- Where the project/make files are output
  location(ROOT .. "build/gen")

-----------------------------------
-- Global Compiler/Linker Config --
-----------------------------------
  filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
  filter "configurations:Release"  defines { "NDEBUG" } optimize "On"

  filter { "platforms:x86_32" }
    architecture "x86"

  filter { "platforms:x86_64" }
    architecture "x86_64"

  -- Global settings for building makefiles
  filter { "action:gmake" }
    flags { "C++11" }

  -- Global settings for building make files on mac specifically
  filter { "system:macosx", "action:gmake"}
    toolset "clang"

  filter {} -- clear filter when you know you no longer need it!

  project "libmemory_freelist"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "freelist")
    targetname "memory"

    local SourceDir = ROOT .. "src/";
    local LibDir = ROOT .. "dependencies/lib/"
    files
    {
      SourceDir .. "**.h",
      LibDir .. "**.h",
      SourceDir .. "malloc_freelist.c",
      SourceDir .. "aligned_malloc.c"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      ROOT .. "include",
      LibDir,
      "/usr/local/opt/llvm/include",
      "/usr/local/opt/llvm/include/c++/v1/"
    }

    libdirs
    {

    }

    links
    {

    }

  project "libmemory_threadx"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "threadx")
    targetname "memory"

    local SourceDir = ROOT .. "src/";
    local LibDir = ROOT .. "dependencies/lib/"
    files
    {
      SourceDir .. "**.h",
      LibDir .. "**.h",
      SourceDir .. "malloc_threadx.c",
      SourceDir .. "aligned_malloc.c"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      ROOT .. "include/",
      LibDir,
      ROOT .. "dependencies/rtos/",
      "/usr/local/opt/llvm/include",
      "/usr/local/opt/llvm/include/c++/v1/"
    }

    libdirs
    {

    }

    links
    {

    }

  project "libmemory_freertos"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "freertos")
    targetname "memory"

    local SourceDir = ROOT .. "src/";
    local LibDir = ROOT .. "dependencies/lib/"

    files
    {
      SourceDir .. "**.h",
      LibDir .. "**.h",
      SourceDir .. "malloc_freertos.c",
      SourceDir .. "aligned_malloc.c"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      ROOT .. "include/",
      LibDir,
      ROOT .. "dependencies/rtos/",
      "/usr/local/opt/llvm/include",
      "/usr/local/opt/llvm/include/c++/v1/"
    }

    libdirs
    {

    }

    links
    {

    }

project "libmemory_freelist_UnitTests"
    kind "ConsoleApp"
    language "C"
    targetdir (RESULTSROOT .. "test/")
    targetname "libmemory_freelist.bin"

    --Temporary
    removeplatforms { "X86_32" }

    local SourceDir = ROOT .. "test/";

    files
    {
      SourceDir .. "**.h",
      SourceDir .. "**.c",
    }

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      ROOT .. "include",
      ROOT .. "test/cmocka/",
      LibDir,
      "/usr/local/opt/llvm/include",
      "/usr/local/opt/llvm/include/c++/v1/"
    }

    -- Library Dependencies
    libdirs
    {
      arch_.lib() .. "cmocka"
    }

    links
    {
      "libmemory_freelist",
      "cmocka"
    }
