.PHONY: build

build:
	mkdir -p ./build
	CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -B ./build -S . -G Ninja
	ninja -C ./build

run: build
	mkdir -p ./run
	cp ./build/vulkan ./run/vulkan
	./run/vulkan

clean:
	rm -rf ./build
	rm -rf ./run