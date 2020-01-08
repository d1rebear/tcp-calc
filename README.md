# tcp-calc
Simple cross-platform single-threaded asynchronous client-server calculator (boost::asio TCP sockets)

This project might be useful if you are looking for a simple example of:
- boost::asio TCP sockets client-server application;
- math expressions parsing (Dijkstra's shunting-yard algorithm);
- math expressions evaluation.

Thirdparty dependencies: STATIC Boost (system, chrono, program_options). Tested with version 1.72.

To build, do:
```
cd /path/to/build/dir
cmake -DBOOST_ROOT=/path/to/boost/root -DCMAKE_INSTALL_PREFIX=/path/to/install/dir /path/to/tcp-calc/CMakeLists.txt
make
make install
```

Artifacts repo: https://github.com/d1rebear/tcp-calc-build
