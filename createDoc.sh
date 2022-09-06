#!/bin/sh
mkdir docs
GITREPO=https://github.com/GalaxyGamingBoy/P2_SDKManager
cd docs
git clone $GITREPO
cd P2_SDKManager
git checkout -b docs
mkdir web
mv docsRedirect.html index.html
git add *
git commit -m "chore: Update Doxygen Docs"
git push --force $GITREPO docs
cd ../..
rm -rf docs