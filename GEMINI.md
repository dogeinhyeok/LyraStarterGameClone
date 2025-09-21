# Project Overview

This project is a clone of the Lyra Starter Game, an official sample project from Epic Games for Unreal Engine. It's intended as a learning exercise to understand the advanced features and best practices of Unreal Engine 5.6. The project is being developed using C++ and Blueprints.

## Building and Running

The following commands are used to build and run the project. These commands should be executed from the project's root directory using PowerShell.

### Generate Visual Studio Project Files

This command should be run whenever the folder structure is changed.

```powershell
& "C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" -projectfiles -project="$PWD\LyraStarterGameClone.uproject" -game -rocket -progress
```

### Development Build

```powershell
& "C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" LyraStarterGameCloneEditor Win64 Development "$PWD\LyraStarterGameClone.uproject" -waitmutex
```

### Clean Build

```powershell
& "C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" LyraStarterGameCloneEditor Win64 Development "$PWD\LyraStarterGameClone.uproject" -clean -waitmutex
```

### Run the Editor

```powershell
& "C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\Win64\UnrealEditor.exe" "$PWD\LyraStarterGameClone.uproject"
```

## Development Conventions

- The project uses a combination of C++ and Blueprints.
- Detailed instructions for setting up different development environments (Visual Studio, VSCode, Cursor) are available in the `README.md` file.
- The project uses a number of plugins, including `ModularGameplay`, `GameFeatures`, and `GameplayAbilities`.
- Code documentation and style guidelines are located in the `.cursor/rules/` directory.
