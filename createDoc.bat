@echo off
mkdir docs
set gitRepo=https://github.com/GalaxyGamingBoy/P2_SDKManager
cd docs
git clone %gitRepo%
cd P2_SDKManager
git checkout -b docs
mkdir web
cd web