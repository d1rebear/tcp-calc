# tcp-calc
Simple cross-platform single-threaded asynchronous client-server calculator (boost::asio TCP sockets)

This project might be useful if you are looking for a simple example of:
- boost::asio TCP sockets client-server application;
- math expressions parsing (Dijkstra's shunting-yard algorithm);
- math expressions evaluation.

Thirdparty dependencies: Boost (system, chrono, program_options). Tested with version 1.72.

To build, do:
```
cd /path/to/build/dir
cmake /path/to/tcp-calc/sources
make
make install
```

## TODO:
- [ ] refactor
