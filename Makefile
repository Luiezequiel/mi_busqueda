.PHONY: all build run clean rebuild

all: build

build:
	@if not exist build mkdir build
	@cd build && cmake .. -G "MinGW Makefiles" && mingw32-make
	@echo Build complete. Run 'make run' to execute.

run: build
	@cd build && .\mi_busqueda.exe

clean:
	@if exist build rmdir /s /q build
	@echo Clean complete.

rebuild: clean build

.DEFAULT_GOAL := all
