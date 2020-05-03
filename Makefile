# Top-level Makefile
#
# Copyright 2020 Michael Bazzinotti (Bazz)
# https://bazz1.com
#
# The top-level Makefile first builds the snes apu driver, does the
# intermediary steps of importing the SPC RAM locations to C/C++, and then builds
# the Tracker.
#
#
#     1. Top-level Makefile
#           /           \
#          /             \
#         /               \
#        /                 \
#  2. snesdriver/      3. pc/

# Regarding WLAPREFIX, you must include a trailing slash
# This is done so that this variable may also be used blank (for example
# when using binaries that are already in your PATH)
WLAPREFIX :=
WLASPC700 := $(WLAPREFIX)wla-spc700

# INTERNAL FROM THIS POINT ON
SPCDRIVER_FILENAME := tracker.spc
SPCDRIVER_RELPATH := pc/bin/$(SPCDRIVER_FILENAME)
APURAM_HEADER := pc/tracker/apuram.h

ifeq (,$(WLAPREFIX))
$(warning WARNING: WLAPREFIX left blank. If wla-dx binaries are not in PATH, \
	you will face fatal errors. Consider specifying WLAPREFIX in the top-level Makefile)
endif

all: $(SPCDRIVER_RELPATH) snes_driver/spc.sym \
pc/tracker/apuram.h pc/bin/snestracker snes_driver/Makefile

# optional
env.sh: Makefile
	echo "export PATH=\"$(WLAPREFIX):\$$PATH\"" > env.sh

# little dirty. Technically we depend on spc.bin but since the sym file
# has the FORCE rule, we'll use that to make sure it is re-assembled if
# necessary
$(SPCDRIVER_RELPATH): snes_driver/spc.sym snes_driver/gen_spc.sh Makefile snes_driver/template.spc
	cd snes_driver && wlaprefix=$(WLAPREFIX) ./gen_spc.sh ../$(SPCDRIVER_RELPATH)

snes_driver/spc.sym: FORCE Makefile snes_driver/Makefile
	make -C snes_driver

snes_driver/Makefile: snes_driver/genmake Makefile
	cd snes_driver ; wlaprefix=$(WLAPREFIX) ./genmake > Makefile

$(APURAM_HEADER): snes_driver/spc.sym Makefile \
		snes_driver/conv_public_syms_to_C.sh $(SPCDRIVER_RELPATH)
	cd snes_driver && ./conv_public_syms_to_C.sh > ../$(APURAM_HEADER)
	echo "#define SPCDRIVER_FILENAME \"$(SPCDRIVER_FILENAME)\"" >> $(APURAM_HEADER)
	printf "#define SPCDRIVER_CODESIZE 0x%x\n" $$(ls -l snes_driver/spc.bin | awk "{print \$$5}") >> $(APURAM_HEADER)
	$(WLASPC700) -t snes_driver/apu/memorymap_defs.i 2>/dev/null >> $(APURAM_HEADER) ; true
	echo >> $(APURAM_HEADER)
	$(WLASPC700) -t snes_driver/apu/playbackengine.i 2>/dev/null >> $(APURAM_HEADER) ; true
	echo >> $(APURAM_HEADER)
	$(WLASPC700) -t snes_driver/apu/commands.i 2>/dev/null >> $(APURAM_HEADER) ; true
	# the 'true' at the end is because the compilation will actually fail
	# since this is not a fully defined file for compilation.. but it's
	# enough to print out the definition
	# Now that I've figured out how to get the local definition into the
	# symbols file (export it), here's another way it can be done:
	# printf "#define SPCDRIVER_CODESTART 0x%x\n" $((0x$(grep -m1 "SPC_CODE_START" spc.sym | cut -f1 -d' ')))
	# but I guess I'll keep it non-global..?

pc/bin/snestracker: FORCE pc/tracker/apuram.h
	make -C pc

FORCE: ;

clean:
	# remove generated files
	rm -f $(APURAM_HEADER)
	rm -f $(SPCDRIVER_RELPATH)
	make -C pc clean
	make -C snes_driver clean
