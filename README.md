# Workshop Prototype 

Unreal Engine blueprint/visual script based concept for overwatch workshop. Actuall does not generate workshop scripts (not yet, maybe soon)

# Example

<img src="https://i.imgur.com/pd0M8bI.png" />

# Showcase

<a href="https://www.youtube.com/watch?v=IAdcKTDnMNE">Youtube Video</a>

# How to build.
1. Download and install VS2022 with C++ Desktop Development Support
2. Download and prepare VCPKG.
3. Configure VPCKG to integrate globally into VS2022 using command `vcpkg integrate install` (so any dependencies used with VCPKG will be auto linked with our app)
4. Install these packages in vcpkg: `vcpkg install <package>` where `package`:<br>
	1.1. imgui: `imgui`<br>
	1.2. imgui sdl2: `imgui[sdl2-binding]`<br>
	1.3. imgui sdl2 renderer: `imgui[sdl2-renderer-binding]`<br><br>

6. Clone repository.
7. Open `workshop.sln` into your visual studio.
8. Hit `Build` to compile.
9. Grab executable file in `C:/path/to/repo/bin/Debug`
	
### With these steps you be able to compile and test current prototype!