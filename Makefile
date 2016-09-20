#
# Burst/Makefile
#
NAME := burst

ROOT := ${CURDIR}
TEST := ${ROOT}/Test

_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include
_OUT := ${ROOT}/Build
_OBJ := ${_OUT}/obj
_BIN := ${_OUT}/bin

BINARY_TARGET := ${_BIN}/${NAME}

SAMPLE_FILES := $(shell find ${TEST} -type f -name "*.burst")
SOURCE_FILES := $(shell find ${_SRC} -type f -name "*.c")
OBJECT_FILES := $(patsubst ${_SRC}/%.c, ${_OBJ}/%.o, ${SOURCE_FILES})

CC := gcc
CC_FLAGS := -Wall -Werror -ggdb -std=gnu99 -I${_INC}

VAL := valgrind
VAL_FLAGS := --leak-check=yes --track-origins=yes

.PHONY: all
all: prepare clean compile

prepare:
	if [ ! -d ${_OUT} ]; then mkdir ${_OUT}; fi
	if [ ! -d ${_OBJ} ]; then mkdir ${_OBJ}; fi
	if [ ! -d ${_BIN} ]; then mkdir ${_BIN}; fi

clean:
	rm -rf ${_OBJ}/*
	rm -rf ${_BIN}/*

compile: compile_objects compile_binary
compile_objects: ${OBJECT_FILES}
compile_binary:
	${CC} ${CC_FLAGS} -o ${BINARY_TARGET} ${OBJECT_FILES}
	chmod +x ${BINARY_TARGET}

run:
	${BINARY_TARGET} ${SAMPLE_FILES}

${VAL}:
	${VAL} ${VAL_FLAGS} ${BINARY_TARGET} ${SAMPLE_FILES}

${_OBJ}/%.o: ${_SRC}/%.c
	mkdir -p $(dir $@)
	${CC} ${CC_FLAGS} -c $^ -o $@