cd build

cmake ..

msbuild radiation_shielding.sln

cd release

.\radiation_shielding run.mac

cd ..
cd ..
