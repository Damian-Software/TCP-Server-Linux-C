#************************************************************************
#*
#* Copyright (C) 2024 Damian-Software
#* All rights reserved.
#*
#* Author: Damián Zelený
#* Contact: Damian-Software (dzeleny@recvsoftware.com)
#*
#************************************************************************
#
cmake_minimum_required (VERSION 3.8)

# Pokud je to podporováno, povolte Opětovné načítání za provozu pro kompilátory MSVC.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RecvWorkGuard-Server" VERSION 1.0.0)

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (RecvWorkGuard-Server "main.cpp" "common.h")

# Povolte standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (${CMAKE_VERSION} VERSION_GREATER 3.12)
  set_property(TARGET RecvWorkGuard-Server PROPERTY CXX_STANDARD 20)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CPACK_PACKAGE_NAME "RecvGuard Server")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "Recv-Guard")
set(CPACK_PACKAGE_CONTACT "dzeleny@recvsoftware.com")











