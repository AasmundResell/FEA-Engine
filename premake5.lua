workspace "FEA_Engine"
    architecture "x64"

    configurations
    {
    "Debug",
    "Release",
    "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FEA_Engine"
    location "FEA_Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS",
            "FEE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "FEE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "FEE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FEE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "FEE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FEE_RELEASE"
        optimize "On"
 
    filter "configurations:Dist"
        defines "FEE_DIST"
        optimize "On"