
.PHONY: clean

all: proto

clean:
	rm ./src/Proto.cpp || true

proto: src/Proto.cpp src/Proto.hpp

src/Proto.cpp src/Proto.hpp: lib/proto/mindspy.proto lib/proto/mindspy.options
	$(MAKE) -C lib/proto Proto.cpp
	mv lib/proto/Proto.[ch]pp src/


