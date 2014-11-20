
V := 0
M_0 := @
M_1 :=
M = $(M_$(V)

OUTDIR ?= build
CXXFLAGS := -std=gnu++11
CPPFLAGS := -Wall -pedantic -O0 -ggdb

.PHONY: clean

all: proto main

rebuild: clean all ;

clean:
	rm ./src/Proto.cpp $(OUTDIR)/* -fr || true

proto: src/Proto.cpp src/Proto.hpp

src/Proto.cpp src/Proto.hpp: lib/proto/mindspy.proto lib/proto/mindspy.options
	$(MAKE) -C lib/proto Proto.cpp
	mv lib/proto/Proto.[ch]pp src/

$(OUTDIR)/%.cpp.o: src/%.cpp 
	@echo "Compiling <" `basename $<`
	$Mmkdir -p $(dir $@)
	$M$(COMPILE.cpp) -o $@ $<

main: $(OUTDIR)/main.cpp.o $(OUTDIR)/Subprocess.cpp.o $(OUTDIR)/CodedStream.cpp.o $(OUTDIR)/MatchingStream.cpp.o $(OUTDIR)/Proto.cpp.o
	@echo "Linking" `basename $@` "<" $?
	$M$(CXX) $? -o $(OUTDIR)/$@ -lstdc++ -lgcc -lprotobuf -lusb -pthread




