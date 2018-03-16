cat > Code/.gitignore << EOF
*.user
*.suo
*.ncb
Build
Release
build
.parasoft.dat
*.sdf
*.opensdf
ipch
EOF

cat > Code/Ace/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/ApiDocs/.gitignore << EOF
*.user
EOF

cat > Code/Aster/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/Cem/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/CompileSettings/.gitignore << EOF
*.pyc
EOF

cat > Code/DgFormats/.gitignore << EOF
.sconsign
*.user
EOF

cat > Code/Elm/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/Iarr/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/KMeans/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/Landsat/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/Mnf/.gitignore << EOF
*.user
EOF

cat > Code/Ndvi/.gitignore << EOF
.sconsign
*.user
EOF

cat > Code/Plotting/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/RangeProfile/.gitignore << EOF
*.user
EOF

cat > Code/Resampler/.gitignore << EOF
*.user
EOF

cat > Code/Rx/.gitignore << EOF
*.user
EOF

cat > Code/Sam/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/Signature/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/SignatureWindow/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/SpectralLibrary/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/SpectralLibraryMatch/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/SpectralUtilities/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/Tad/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Code/WangBovik/.gitignore << EOF
.sconsign
*.user
*.suo
*.ncb
EOF

cat > Dependencies/.gitignore << EOF
32
64
staging
source
EOF

cat > Installer/.gitignore << EOF
AebOutput
EOF

git add -A
git commit -S "Added missing .gitignore"
git push
