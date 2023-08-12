#------------------------------------------------------------------------------
#- Compiler and Utilities                                                     -
#------------------------------------------------------------------------------
CC = i686-w64-mingw32-clang
CXX = i686-w64-mingw32-clang++
MKDIR = mkdir -p
RM = rm -r -f
PRINTF = printf

#------------------------------------------------------------------------------
#- Source Files                                                               -
#------------------------------------------------------------------------------
SOURCES = \
	src/init_funcs.cpp \
	src/launch_helper.cpp \
	src/main.cpp \
	# <- Add more files here
OBJECTS = ${SOURCES:%.cpp=$(OBJS_DIR)/%.o}

#------------------------------------------------------------------------------
#- Settings                                                                   -
#------------------------------------------------------------------------------
TARGET = MissingCameo.dll
REVISION=$(shell git log -1 --pretty=format:"%H")
OBJS_DIR = .objs

RELEASE ?= 0
ifeq (${RELEASE}, 1)
	CFLAGS = -DNDEBUG -O3
	LDFLAGS = -s -flto
else
	TARGET = MissingCameo_debug.dll
	CFLAGS = -DDEBUG -O0 -g
	LDFLAGS =
endif

#------------------------------------------------------------------------------
#- Compiler Flags                                                             -
#------------------------------------------------------------------------------
CFLAGS += -DSYR_VER=2 -c -fms-extensions -std=c17
CXXFLAGS = ${CFLAGS} -std=c++20
LDFLAGS += -shared -static

#------------------------------------------------------------------------------
#- Rules                                                                      -
#------------------------------------------------------------------------------
.PHONY: all clean

all: clean version.h ${TARGET}

version.h:
	@${PRINTF} '\033[0;32mGenerating\033[0m version.h ...\n' $<
	@${PRINTF} '#pragma once\n\nconstexpr const char *k_revision = \"%s\";\n' ${REVISION} > src/version.h

${OBJECTS}: ${OBJS_DIR}/%.o: %.cpp
	@${PRINTF} '\033[0;32mBuilding\033[0m %s ...\n' $<
	@${MKDIR} $(@D)
	@${CXX} ${CXXFLAGS} -o $@ $<

${TARGET}: ${OBJECTS}
	@${PRINTF} '\033[0;32mLinking\033[0m %s ...\n' $@
	@${CXX} ${LDFLAGS} -o $@ $^
	@${PRINTF} '\033[0;32mConstruction complete!\033[0m\n'
	
clean:
	@${RM} src/version.h
	@${RM} .objs/
	@${RM} *.dll
