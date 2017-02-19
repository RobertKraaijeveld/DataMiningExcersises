# CPP_FILES := $(wildcard *.cpp) $(wildcard **/*.cpp)
# OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

# main.exe: $(OBJ_FILES)
# 	g++ -static-libgcc -static-libstdc++ $(LD_FLAGS) -o  $@ $^

# %.o: %.cpp
# 	g++ -static-libgcc -static-libstdc++ $(CC_FLAGS) -c -o  $@ $<

#todo: Make this so that it automatically takes cpp files
ccsrc = $(wildcard src/*.cpp) \
        $(wildcard src/CustomTypes/*.cpp) \
        $(wildcard src/Parser/*.cpp)

obj = $(ccsrc:.cpp=.o)

LDFLAGS = -std=c++11 -static-libgcc -static-libstdc++ 

main: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)