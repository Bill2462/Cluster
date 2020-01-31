# Cluster

Linux application for image clustering.

### Build

Compile dependences:

```
cd extLibs
mkdir build
cd build
cmake ..
make
```

Compile application:

```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH:STRING=PATH_TO_QT_INSTALLATION ..
make
```

### Dependences
- cmake
- OpenCV
- Eigen
