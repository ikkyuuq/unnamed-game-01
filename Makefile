all: build

build:
	cmake -G Ninja -B build
	cmake --build build -j8

rebuild:
	rm -rf build
	make build
