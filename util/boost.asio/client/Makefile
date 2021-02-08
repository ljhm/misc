# Generic Makefile
#
# 1. Prerequisites on header files generated
# 2. Out of source tree build
# 3. Source files in folders with Makefile or below

OUT      = a.out
DIR      = ./.build
SRC      = $(shell find . -type f -name "*.cpp")
OBJ      = $(addprefix $(DIR)/,$(SRC:.cpp=.o))
DEP      = $(OBJ:.o=.d)

CXXFLAGS = -std=c++2a -Wall -W -pedantic -g # -O3
CPPFLAGS = -MMD -MP -DNDEBUG -I ../../boost_1_73_0
LDFLAGS  = -L ../../boost_1_73_0/stage/
LDLIBS   = -lpthread

# build shared library
#OUT       = ../lib/libhello.so
#CXXFLAGS += -fPIC
#LDFLAGS  += -shared

.PHONY : all clean

all : $(OUT)

$(OUT) : $(OBJ)
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(DIR)/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

-include $(DEP)

clean :
	rm -fr $(OUT) $(DIR)
