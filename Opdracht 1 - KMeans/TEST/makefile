CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

main.exe: $(OBJ_FILES)
	g++ -static-libgcc -static-libstdc++ $(LD_FLAGS) -o  $@ $^

%.o: %.cpp
	g++ -static-libgcc -static-libstdc++ $(CC_FLAGS) -c -o  $@ $<
