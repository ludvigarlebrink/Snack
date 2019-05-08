function WinSDKVersion()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

function IncludeAssimp()
    includedirs "ThirdParty/assimp/Include"
end

function LinkAssimp()
    libdirs "ThirdParty/assimp/Lib/Win64/"
    filter "kind:not StaticLib"
        links { "Assimp" }
    filter {}
end

function IncludeSDL()
    includedirs "ThirdParty/SDL/Include"
end

function LinkSDL()
    libdirs "ThirdParty/SDL/Lib/Win64/"
    filter "kind:not StaticLib"
        links { "SDL2", "SDL2main" }
    filter {}
end

function IncludeSTB()
    includedirs "ThirdParty/STB/Include"
end

function IncludeGLM()
    includedirs "ThirdParty/glm/Include"
end

function IncludeFreeType()
    includedirs "ThirdParty/freetype/Include"
end

function LinkFreeType()
    libdirs "ThirdParty/freetype/Lib/Win64/"
    filter { "kind:not StaticLib" }
        links { "freetype" }
    filter {}
end

function IncludeCereal()
    includedirs "ThirdParty/cereal/Include"
end

function IncludeSol()
    includedirs "ThirdParty/sol/Include"
end

function IncludeLua()
    includedirs "ThirdParty/lua/Include"
end

function LinkLua()
    libdirs "ThirdParty/lua/Lib/Win64/"
    filter { "kind:not StaticLib" }
        links { "lua53" }
    filter {}
end

function UseUtils()
    includedirs { "Source/Utils/Public" }
    defines { "UTILS_API=__declspec(dllimport)" }

    IncludeGLM()
    IncludeSDL()
    LinkSDL()

    filter { "kind:not StaticLib" }
        links { "Utils" }
    filter {}
end

function UsePlatform()
    includedirs { "Source/Platform/Public" }
    defines { "PLATFORM_API=__declspec(dllimport)" }

    UseUtils()
    
    filter { "kind:not StaticLib" }
        links { "Platform" }
    filter {}
end

function UseRenderCore()
    includedirs { "Source/RenderCore/Public" }
    defines { "RENDER_CORE_API=__declspec(dllimport)" }

    IncludeFreeType()
    LinkFreeType()
    IncludeSTB()
    UsePlatform()

    filter { "kind:not StaticLib" }
        links { "RenderCore" }
    filter {}
end

function UseShadeRaid()
    include { "Source/ShadeRaid/Public" }
    defines { "SHADE_RAID_API=__declspec(dllimport)" }

    UseRenderCore()

    filter { "kind:not StaticLib" }
        links { "ShadeRaid" }
    filter {}
end

function UseSketch()
    includedirs { "Source/Sketch/Public" }
    defines { "SKETCH_API=__declspec(dllimport)" }

    UseRenderCore()

    filter { "kind:not StaticLib" }
        links { "Sketch" }
    filter {}
end

function UseEngine()
    includedirs { "Source/Engine/Public" }
    defines { "ENGINE_API=__declspec(dllimport)" }

    IncludeCereal()
    IncludeSol()
    IncludeLua()
    LinkLua()
    UseSketch()
    
    filter { "kind:not StaticLib" }
        links { "Engine" }
    filter {}
end

function UseEditor()
    includedirs { "Source/Editor/Public" }
    defines { "EDITOR_API=__declspec(dllimport)" }

--    IncludeAssimp()
--    LinkAssimp()
    UseEngine()

    filter { "kind:not StaticLib" }
        links { "Editor" }
    filter {}
end

workspace "SnackEngine"
    location "Solution"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    configurations { "Debug", "Debug_Editor", "Release", "Release_Editor" }

    startproject "Main"

    filter { "configurations:Debug", "system:windows", "action:vs*"}
        symbols "On"
        targetdir "Builds/Debug"
        systemversion(WinSDKVersion() .. ".0")
        defines { "SPY_DEBUG" }
        objdir "Builds/Debug/obj/%{prj.name}/%{cfg.longname}"

    filter { "configurations:Debug_editor", "system:windows", "action:vs*"}
        symbols "On"
        targetdir "Builds/Debug"
        systemversion(WinSDKVersion() .. ".0")
        defines { "SPY_DEBUG", "SPY_EDITOR" }
        objdir "Builds/Debug/obj/%{prj.name}/%{cfg.longname}"

    filter { "configurations:Release", "system:windows", "action:vs*"}
        optimize "On"
        targetdir "Builds/Release"
        defines { "SPY_RELEASE" }
        systemversion(WinSDKVersion() .. ".0")
        objdir "builds/Debug/obj/%{prj.name}/%{cfg.longname}"

    filter { "configurations:Release_Editor", "system:windows", "action:vs*"}
        optimize "On"
        targetdir "Builds/Release"
        defines { "SPY_RELEASE", "SPY_EDITOR" }
        systemversion(WinSDKVersion() .. ".0")
        objdir "builds/Debug/obj/%{prj.name}/%{cfg.longname}"
    filter {}

    -- Copy files.
    filter { "system:windows" }
        os.execute("mkdir \"Builds/Debug\"")
        os.execute("mkdir \"Builds/Release\"")

        -- Assimp
        os.copyfile("ThirdParty/assimp/Lib/Win64/assimp.dll", "Builds/Debug/assimp.dll")
        os.copyfile("ThirdParty/assimp/Lib/Win64/assimp.dll", "Builds/Release/assimp.dll")

        -- SDL
        os.copyfile("ThirdParty/SDL/Lib/Win64/SDL2.dll", "Builds/Debug/SDL2.dll")
        os.copyfile("ThirdParty/SDL/Lib/Win64/SDL2.dll", "Builds/Release/SDL2.dll")

        -- FreeType
        os.copyfile("ThirdParty/freetype/Lib/Win64/freetype.dll", "Builds/Debug/freetype.dll")
        os.copyfile("ThirdParty/freetype/Lib/Win64/freetype.dll", "Builds/Release/freetype.dll")

        -- Lua
        os.copyfile("ThirdParty/lua/Lib/Win64/lua53.dll", "Builds/Debug/lua53.dll")
        os.copyfile("ThirdParty/lua/Lib/Win64/lua53.dll", "Builds/Release/lua53.dll")
    filter {}

group "Engine"
project "Utils"
    kind "SharedLib"
    location "Source/Utils"
    defines { "UTILS_API=__declspec(dllexport)" }
    files {
        "Source/Utils/**.hpp",
        "Source/Utils/**.cpp"
    }
    includedirs { "Source/Utils/Public" }

    IncludeGLM()
    IncludeSDL()
    LinkSDL()

project "Platform"
    kind "SharedLib"
    location "Source/Platform"
    defines { "PLATFORM_API=__declspec(dllexport)" }
    files {
        "Source/Platform/**.hpp",
        "Source/Platform/**.cpp"
    }
    includedirs { "Source/Platform/Public" }

    UseUtils()

project "RenderCore"
    kind "SharedLib"
    location "Source/RenderCore"
    defines { "RENDER_CORE_API=__declspec(dllexport)" }
    files {
        "Source/RenderCore/**.hpp",
        "Source/RenderCore/**.cpp",
        "Source/RenderCore/Private/glad/*.h",
        "Source/RenderCore/Private/glad/*.c",
    }
    includedirs { "Source/RenderCore/Public" }

    IncludeFreeType()
    LinkFreeType()
    IncludeSTB()

    UsePlatform()

project "ShadeRaid"
    kind "SharedLib"
    location "Source/ShadeRaid"
    defines { "SHADE_RAID_API=__declspec(dllexport)" }
    files {
        "Source/ShadeRaid/**.hpp",
        "Source/ShadeRaid/**.cpp"
    }
    includedirs { "Source/ShadeRaid/Public" }

    UseRenderCore()

project "Sketch"
    kind "SharedLib"
    location "Source/Sketch"
    defines { "SKETCH_API=__declspec(dllexport)" }  
    files {
        "Source/Sketch/**.hpp",
        "Source/Sketch/**.cpp",
        "Source/Sketch/Private/imgui/*.h",
    }
    includedirs { "Source/Sketch/Public" }

    UseRenderCore()

project "Engine"
    kind "SharedLib"
    location "Source/Engine"
    defines { "ENGINE_API=__declspec(dllexport)" }
    files {
        "Source/Engine/**.hpp",
        "Source/Engine/**.cpp"
    }
    includedirs { "Source/Engine/Public" }

    IncludeCereal()
    IncludeSol()
    IncludeLua()
    LinkLua()
    UseSketch()

project "Editor"
    kind "SharedLib"
    location "Source/Editor"
    defines { "EDITOR_API=__declspec(dllexport)" }
    files {
        "Source/Editor/**.hpp",
        "Source/Editor/**.cpp"
    }
    includedirs { "Source/Editor/Public" }

--    IncludeAssimp()
--    LinkAssimp()
    UseEngine()

project "Main"
    kind "ConsoleApp"
    location "Source/Main"
    
    files {
        "Source/Main/**.hpp",
        "Source/Main/**.cpp"
    }

    filter { "configurations:Debug" }
        UseEngine()
        targetname "SnackEngine"
    filter { "configurations:Release" }
        UseEngine()
        targetname "SnackEngine"
    filter { "configurations:Debug_Editor" }
        UseEditor()
        targetname "SnackEditor"
    filter { "configurations:Release_Editor" }
        UseEditor()
        targetname "SnackEditor"
    filter {}

    filter { "system:windows", "action:vs*" }
        file = io.open("Source/Main/resources.rc", "w");
        file:write("MAIN ICON \"Icon.ico\"")
        file:close();
        files { "Source/Main/resources.rc" }
    filter {}    
