@echo off
mkdir docs
set gitRepo=https://github.com/GalaxyGamingBoy/P2_SDKManager
cd docs
git clone %gitRepo%
cd P2_SDKManager
git checkout -b docs
doxygen
mkdir web
mv docsRedirect.html index.html
git add *
git commit -m "chore: Update Doxygen Docs"
git push --force %gitRepo% docs
cd ..\..
rm -rf docs