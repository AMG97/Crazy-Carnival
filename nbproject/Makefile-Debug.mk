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
	${OBJECTDIR}/EstadoAyuda.o \
	${OBJECTDIR}/EstadoJuego.o \
	${OBJECTDIR}/EstadoMenu.o \
	${OBJECTDIR}/EstadoMenuPartidas.o \
	${OBJECTDIR}/EstadosManager.o \
	${OBJECTDIR}/Input.o \
	${OBJECTDIR}/Juego.o \
	${OBJECTDIR}/Recursos.o \
	${OBJECTDIR}/Reloj.o \
	${OBJECTDIR}/SpriteM.o \
	${OBJECTDIR}/Texto.o \
	${OBJECTDIR}/Ventana.o \
	${OBJECTDIR}/box.o \
	${OBJECTDIR}/hud.o \
	${OBJECTDIR}/juegoHud.o \
	${OBJECTDIR}/main.o \
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

${OBJECTDIR}/EstadoAyuda.o: EstadoAyuda.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EstadoAyuda.o EstadoAyuda.cpp

${OBJECTDIR}/EstadoJuego.o: EstadoJuego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EstadoJuego.o EstadoJuego.cpp

${OBJECTDIR}/EstadoMenu.o: EstadoMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EstadoMenu.o EstadoMenu.cpp

${OBJECTDIR}/EstadoMenuPartidas.o: EstadoMenuPartidas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EstadoMenuPartidas.o EstadoMenuPartidas.cpp

${OBJECTDIR}/EstadosManager.o: EstadosManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EstadosManager.o EstadosManager.cpp

${OBJECTDIR}/Input.o: Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/Juego.o: Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Juego.o Juego.cpp

${OBJECTDIR}/Recursos.o: Recursos.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Recursos.o Recursos.cpp

${OBJECTDIR}/Reloj.o: Reloj.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Reloj.o Reloj.cpp

${OBJECTDIR}/SpriteM.o: SpriteM.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpriteM.o SpriteM.cpp

${OBJECTDIR}/Texto.o: Texto.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Texto.o Texto.cpp

${OBJECTDIR}/Ventana.o: Ventana.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ventana.o Ventana.cpp

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

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -IBox2D -Itinyxml -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
