if [ -d "./build" ]; then
# Control will enter here if $DIRECTORY doesn't exist.
  rm -r ./build/*
fi
if [ ! -d "./build" ]; then
  # Control will enter here if $DIRECTORY  exist.
  mkdir ./build/
fi
cd ./build
cmake .. -G "MSYS Makefiles"
make
make install
cd ..
