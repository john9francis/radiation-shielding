# Radiation Shielding App

Radiation Shielding App consists of a vacuum world with a single particle gun and a single water phantom. The particles shoot at the phantom, and the phantom records the energy deposited. 

The user can control the type of particle and it's energy. The user can also create a rectangular shield of varying thickness up to 1.5 m. The user can also change the shield to any material found in the [Geant4 NIST materials database](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html). 

This app is useful for testing materials and how well they shield against any type of particle and energy.

# How to download

Executable (Recommended): It is necessary to have Geant4 installed correctly to run the executable.

Docker: coming soon

Compiling source code: Use CMake to build the project. There is a CMakeLists.txt file in the root directory. Here's how to configure cmake:
```
mkdir build
cd build
cmake . .
```
and to compile, it will be different for different platforms. For windows, open up the project in [Visual Studio](https://visualstudio.microsoft.com/) and run:
```
msbuild radiation_shielding.sln
```
This creates an executable in the release/ directory.

Note: You must have [Root](https://root.cern/) installed to open up any graphs found in the .root files generated.

# How to use

Radiation Shielding comes with all the basic Geant4 ui commands, as well as a new directory called: `/shield/`. The commands in the `/shield/` directory are as follows:
- `/shield/enable` Puts the shield into the world. Note: by default, the shield is already in the world.
- `/shield/disable` Changes the shield's material to vacuum. Note: the shield will still be visible in the world, but it won't affect the particle's path in any way. Note: the material of the shield before the `disable` command is saved, and can be restored with `enable`.
- `/shield/setMaterial <Geant4 NIST Material name>` Changes the shield's material to what the user enters. Note: that material must be found in the [Geant4 NIST materials database](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html), otherwise the material will not be changed.
- `/shield/setThickness <New thickness value> <unit (default=cm)>` Changes the shield's thickness in the Z direction.

Using the Geant4 particle gun class, you can change the particle type or energy etc. Here are some helpful commands:
- `/gun/particle <particleName>` Sets a new particle to be shot
- `/gun/energy <newEnergy> <unit=GeV>` Sets a new particle energy. Default unit is GeV but can be specified.

Using the analysis UI messenger, we can open a root file to store our output graphs. Here are some (not all) of the analysis commands.
- `/analysis/openFile <fileName>` Opens the output file to start recording the graphs.
- `/analysis/write` Writes the graphs in the file
- `/analysis/closeFile` Closes the file after the data has been recorded.

# Goals
- [x] Allow for any material and (almost) any thickness for a shield
- [ ] Allow for to change energy distribution of primaries with messenger
