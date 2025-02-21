cmake_minimum_required(VERSION 3.30)
project(hermit)

enable_testing()

add_executable ( hp src/main.c src/error.c src/server.c )

#Tests
# add_executable ()

# add_test()
