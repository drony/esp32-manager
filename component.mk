#
# Main Makefile. This is basically the same as a component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_SRCDIRS := . ./src
COMPONENT_ADD_INCLUDEDIRS := . ./include

COMPONENT_EMBED_FILES := res/style.min.css