sources := DXVector.cpp
objects := $(subst .c,.o,$(sources))
library := DXMath.a

include ../common.mk
