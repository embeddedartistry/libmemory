# This makefile is used to provide convenient access to the generated  makefile

# Export all args to act as a passthrough
export

all: build test doc

.PHONY: build_gen
build_gen:
	@build/bin/premake5 --file=premake5.lua gmake

.PHONY: build
build: build_gen
	@make -C build/gen/

.PHONY: help
help: build_gen
	@make -C build/gen/ help

.PHONY: clean
clean:
ifeq ("$(wildcard build/gen/)","")
	@echo "No generated build files: skipping clean"
else
	@make -C build/gen/ clean
	@rm -rf buildresults/
endif

.PHONY: purify
purify:
	@rm -rf build/gen
	@rm -rf buildresults/

.PHONY: regen
regen:
	@build/bin/premake5 --file=premake5.lua gmake

.PHONY: doc
doc:
	@doxygen docs/Doxyfile

.PHONY: format
format:
	@tools/clang-format-libmemory.sh

.PHONY : format-diff
format-diff :
	@tools/format/clang-format-git-diff.sh

.PHONY : format-check
format-check :
	@tools/clang-format-libmemory-patch.sh

.PHONY: test
test: build
ifeq ("$(wildcard buildresults/testresults/)","")
	@mkdir -p buildresults/testresults
else
	@rm -f buildresults/testresults/*
endif
	@CMOCKA_XML_FILE=buildresults/testresults/%g.xml buildresults/x86_64_debug/test/libmemory_freelist.bin
