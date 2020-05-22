workspace "FEA_Engine"
    architecture "x64"

    configurations
    {
    "Debug",
    "Release",
    "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {} 
IncludeDir["GLFW"] = "FEA_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "FEA_Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "FEA_Engine/vendor/imgui"

include "FEA_Engine/vendor/GLFW"	
include "FEA_Engine/vendor/Glad"
include "FEA_Engine/vendor/imgui"

project "FEA_Engine"
    location "FEA_Engine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "feepch.h"
    pchsource "FEA_Engine/src/feepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}", 
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
 
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS",
            "FEE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "FEE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "FEE_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "FEA_Engine/vendor/spdlog/include",
        "FEA_Engine/src"
    }

    links
    {
        "FEA_Engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "FEE_DEBUG"
       runtime "Debug"
       symbols "On"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        runtime "Release"
        optimize "On"
 
    filter "configurations:Dist"
        defines "FEE_DIST"
        runtime "Release"
        optimize "On"