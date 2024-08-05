C_SOURCE_FILES += $(wildcard ./src/*.c, ./lib/include/*.c ./lib/*.c)

C_INCLUDES += ./src ./lib ./lib/include

include ./cc-with-test.mk
