# Nebula
Nebula is an ECS 2D Game Engine written in C++ with a Lua API. Nebula is heavily inspired by [LOVE2D](https://github.com/love2d/love), [flecs](https://github.com/SanderMertens/flecs/tree/master), [bevy](https://github.com/bevyengine/bevy/tree/main) and [Lotus](https://github.com/zenialexandre/lotus/tree/main).

## Documentation
Please check the [documentation](https://github.com/maumafra/nebula/tree/main/documentation) page.

## Download
Check the latest verions at [Releases](https://github.com/maumafra/nebula/releases).

## VSCode Extension
Nebula has it's own VSCode Extension!  

<img width="1188" height="623" alt="image" src="https://github.com/user-attachments/assets/3f8dc291-4cb7-49f4-a2cd-e1d58dc7b816" />

---
Make sure to configure the extension before using:  

<img width="879" height="290" alt="image" src="https://github.com/user-attachments/assets/c03583a8-6860-4a13-8270-a6e4f1ae5ae2" />

**Notes:** While developing your game, you can point the Engine Executable Path to the **nebula_console.exe**, as it will print the game output in the VSCode Terminal.  

---

With everything set, a green button should appear in your main.lua file:

<img width="1503" height="570" alt="image" src="https://github.com/user-attachments/assets/053fc959-915e-458e-ab2a-6a4cb11d8f1a" />

---

## Building the Game Engine Code
If there is a download option for your platform on [Download](https://github.com/maumafra/nebula/releases), you can skip this section.  

This project use CMakeLists for building the code, so choose a C++ compiler and let's build it.

---

**Building on Debug mode:**
```bash
cmake -B build
```
This should create a build folder. Then:
```bash
cmake --build build
```

---

**Building on Release mode:**
```bash
cmake -B release -DCMAKE_BUILD_TYPE=Release
```
This should create a release folder. Then:
```bash
cmake --build release --config Release
```

---


## Architecture
<img width="645" height="684" alt="image" src="https://github.com/user-attachments/assets/83d7e2bf-efcd-4e98-8044-fd3415808f12" />
