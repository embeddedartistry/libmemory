# you can set this to 1 to see all commands that are being run
export VERBOSE := 0

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

BUILDRESULTS?=buildresults

all: libmemory

groundwork:
	$(Q) mkdir -p $(BUILDRESULTS)
	$(Q) meson $(BUILDRESULTS)

.PHONY: libmemory
libmemory: groundwork
	$(Q)cd $(BUILDRESULTS); ninja

.PHONY: docs
docs: groundwork
	$(Q)cd $(BUILDRESULTS); ninja docs

.PHONY: format
format:
	$(Q)tools/clang-format-libmemory.sh

.PHONY : format-diff
format-diff :
	$(Q)tools/format/clang-format-git-diff.sh

.PHONY : format-check
format-check :
	$(Q)tools/clang-format-libmemory-patch.sh

.PHONY: analyze
analyze: groundwork
	$(Q) cd $(BUILDRESULTS); ninja scan-build

.PHONY: clean
clean:
	$(Q)echo Cleaning Build Output
	$(Q)rm -rf $(BUILDRESULTS)/

.PHONY: test
test: libmemory
	$(Q)cd $(BUILDRESULTS); ./test/libmemory_freelist_test

