cmake_minimum_required(VERSION 3.7)
project(TrabalhoAED)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp No.cpp No.h Lista.cpp Lista.h Tabela.cpp Tabela.h Leitor_Arquivo.cpp Leitor_Arquivo.h Banco.cpp Banco.h)
add_executable(TrabalhoAED ${SOURCE_FILES} Leitor_Arquivo.cpp Leitor_Arquivo.h Banco.cpp Banco.h)