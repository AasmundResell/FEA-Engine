workspace "FEA_Engine"
    architecture "x64"
    startproject "Sandbox"

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
IncludeDir["glm"] = "FEA_Engine/vendor/glm"
IncludeDir["stb_image"] = "FEA_Engine/vendor/stb_image"
IncludeDir["eigen"] = "FEA_Engine/vendor/eigen"

group "Dependencies"
    include "FEA_Engine/vendor/GLFW"	
    include "FEA_Engine/vendor/Glad"
    include "FEA_Engine/vendor/imgui"
group ""

project "FEA_Engine"
    location "FEA_Engine"
    kind "StaticLib"
    language "C++" 
    cppdialect "C++17"  
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "feepch.h"
    pchsource "FEA_Engine/src/feepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/eigen/Eigen/Dense",
        "%{prj.name}/vendor/eigen/Eigen/Sparse"
    }

    defines 
    {   
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}", 
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.eigen}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
 
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS",
            "FEE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug" 
        defines "FEE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FEE_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"


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
        "FEA_Engine/src",
        "FEA_Engine/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.eigen}"
    }

    links
    {
        "FEA_Engine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "FEE_DEBUG"
       runtime "Debug"
       symbols "on"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        runtime "Release"
        optimize "on"
 
    filter "configurations:Dist"
        defines "FEE_DIST"
        runtime "Release"
        optimize "on"


project "FEA_Solver"
    location "FEA_Solver"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"


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
        "FEA_Engine/src",
        "FEA_Engine/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.eigen}"
    }

    links
    {
        "FEA_Engine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "FEE_DEBUG"
       runtime "Debug"
       symbols "on"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        runtime "Release"
        optimize "on"
 
    filter "configurations:Dist"
        defines "FEE_DIST"
        runtime "Release"
        optimize "on"