#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/box.o \
	${OBJECTDIR}/hud.o \
	${OBJECTDIR}/juegoHud.o \
	${OBJECTDIR}/mainHudPlayers.o \
	${OBJECTDIR}/player.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libsfml-graphics.so /usr/lib/x86_64-linux-gnu/libsfml-system.so /usr/lib/x86_64-linux-gnu/libsfml-window.so libbox2d.a libtinyxml.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival: /usr/lib/x86_64-linux-gnu/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival: /usr/lib/x86_64-linux-gnu/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival: libbox2d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival: libtinyxml.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/box.o: box.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/box.o box.cpp

${OBJECTDIR}/hud.o: hud.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hud.o hud.cpp

${OBJECTDIR}/juegoHud.o: juegoHud.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/juegoHud.o juegoHud.cpp

${OBJECTDIR}/mainHudPlayers.o: mainHudPlayers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mainHudPlayers.o mainHudPlayers.cpp

${OBJECTDIR}/player.o: player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player.o player.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazy-carnival

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
