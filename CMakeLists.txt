cmake_minimum_required(VERSION 3.14)
project(poly)


add_executable(poly 
src/main.cpp
src/generation.cpp
src/parser.cpp
src/tokenizer.cpp
)