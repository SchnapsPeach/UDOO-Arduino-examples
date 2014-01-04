#!/usr/bin/make
# makefile for the arduino due.
#
# USAGE: put this file in the same dir as your .ino file is.
# configure the PORT variable and ADIR at the top of the file
# to match your local configuration.
# Type make upload to compile and upload.
# Type make monitor to watch the serial port with gnu screen.
#
# TODO: split into user specific settings and the rest
#
# LICENSE: GPLv2 or later (at your option)
#
# This file can be found at https://github.com/pauldreik/arduino-due-makefile
#
# By Paul Dreik 20130503 http://www.pauldreik.se/


#user specific settings:
#where to find the IDE
ARDDIR:=/opt/arduino-1.5.4
ADIR:=$(ARDDIR)/hardware
# port name for bossa (predefined port on UDOO)
BOSSA_PORT:=ttymxc3
PORT:=/dev/$(BOSSA_PORT)
#if we want to verify the bossac upload, define this to -v
VERIFY:=-v

#then some general settings. They should not be necessary to modify.
CXX:=$(ADIR)/tools/arm-none-eabi/bin/arm-none-eabi-g++
CC:=$(ADIR)/tools/arm-none-eabi/bin/arm-none-eabi-gcc
C:=$(CC)
SAM:=arduino/sam
CMSIS:=arduino/sam/system/CMSIS
LIBSAM:=arduino/sam/system/libsam
TMPDIR:=$(PWD)/build
AR:=$(ADIR)/tools/arm-none-eabi/bin/arm-none-eabi-ar 

# external libraries 
# libraries in th home folder
HOMELIBS:=/home/olga/Arduino/libraries
# libraries in the arduino folder
ARDLIBS:=$(ARDDIR)/libraries
# include path of all libraries from the arduino folder
ARDLIBINC:=$(addprefix -I,$(addsuffix src,$(shell ls -d $(ARDLIBS)/*/))) $(addprefix -I,$(addsuffix arch/sam,$(shell ls -d $(ARDLIBS)/*/))) $(addprefix -I,$(shell ls -d $(ADIR)/$(SAM)/libraries/*/))
EXTLIBINC:=$(addprefix -I,$(shell ls -d $(HOMELIBS)/*/))
# all library includes for arduino (libs in home folder and libs in arduino folder)
ARDUINOLIBINC:=$(ARDLIBINC) $(EXTLIBINC)


#all these values are hard coded and should maybe be configured somehow else,
#like olikraus does in his makefile.
DEFINES:=-Dprintf=iprintf -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON

INCLUDES:=-I$(ADIR)/$(LIBSAM) -I$(ADIR)/$(CMSIS)/CMSIS/Include/ -I$(ADIR)/$(CMSIS)/Device/ATMEL/ -I$(ADIR)/$(SAM)/cores/arduino -I$(ADIR)/$(SAM)/variants/arduino_due_x $(ARDUINOLIBINC)

#also include the current dir for convenience
INCLUDES += -Iinclude

#compilation flags common to both c and c++
COMMON_FLAGS:=-g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -mcpu=cortex-m3  -mthumb -Wall -Wextra -pedantic

CFLAGS:=$(COMMON_FLAGS)
CXXFLAGS:=$(COMMON_FLAGS) -fno-rtti -fno-exceptions 

#let the results be named after the project
PROJNAME:=$(shell basename *.ino .ino)

#we will make a new mainfile from the ino file.
NEWMAINFILE:=$(TMPDIR)/$(PROJNAME).ino.cpp

#our own sourcefiles is the (converted) ino file and any local cpp files
MYSRCFILES:=$(NEWMAINFILE) $(shell ls *.cpp 2>/dev/null) $(LIBSRC)
MYOBJFILES:=$(addsuffix .o,$(addprefix $(TMPDIR)/,$(notdir $(MYSRCFILES))))

#These source files are the ones forming core.a
CORESRCXX:=$(shell ls ${ADIR}/${SAM}/cores/arduino/*.cpp ${ADIR}/${SAM}/cores/arduino/USB/*.cpp  ${ADIR}/${SAM}/variants/arduino_due_x/variant.cpp)
CORESRC:=$(shell ls ${ADIR}/${SAM}/cores/arduino/*.c)

#convert the core source files to object files. assume no clashes.
COREOBJSXX:=$(addprefix $(TMPDIR)/core/,$(notdir $(CORESRCXX)) )
COREOBJSXX:=$(addsuffix .o,$(COREOBJSXX))
COREOBJS:=$(addprefix $(TMPDIR)/core/,$(notdir $(CORESRC)) )
COREOBJS:=$(addsuffix .o,$(COREOBJS))

# library sources: all sources from home folder and arduino folder, but only the SAM source
ARDUINOLIBSRC:=$(shell find $(HOMELIBS) -name *.cpp) $(shell find $(ARDLIBS) -not -path "*/arch/avr/*" -a -name *.cpp)
# this libs are not yet supportet for arduino due, so we have to exclude them to prevent compiling errors
ARDUINOLIBSRC:=$(patsubst /opt/arduino-1.5.4/libraries/TFT/%,,$(ARDUINOLIBSRC))
ARDUINOLIBSRC:=$(patsubst /opt/arduino-1.5.4/libraries/Esplora/%,,$(ARDUINOLIBSRC))
ARDUINOLIBSRC:=$(patsubst /opt/arduino-1.5.4/libraries/Robot_Motor/%,,$(ARDUINOLIBSRC))
ARDUINOLIBSRC:=$(patsubst /opt/arduino-1.5.4/libraries/RobotIRremote/%,,$(ARDUINOLIBSRC))
ARDUINOLIBSRC:=$(patsubst /opt/arduino-1.5.4/libraries/SpacebrewYun/%,,$(ARDUINOLIBSRC))
ARDUINOLIBSRC:=$(patsubst /opt/arduino-1.5.4/libraries/Bridge/%,,$(ARDUINOLIBSRC))
# library object list
ARDUINOOBJS:=$(addprefix $(TMPDIR)/libraries/,$(notdir $(ARDUINOLIBSRC)) )
ARDUINOOBJS:=$(addsuffix .o,$(ARDUINOOBJS))

default:
	@echo default rule, does nothing. Try make compile or make upload.

#This rule is good to just make sure stuff compiles, without having to wait
#for bossac.
compile: $(TMPDIR)/$(PROJNAME).elf

#This is a make rule template to create object files from the source files.
# arg 1=src file
# arg 2=object file
# arg 3= XX if c++, empty if c
define OBJ_template
$(2): $(1)
	$(C$(3)) -MD -c $(C$(3)FLAGS) $(DEFINES) $(INCLUDES) $(1) -o $(2)
endef
#now invoke the template both for c++ sources
$(foreach src,$(CORESRCXX), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/core/,$(notdir $(src)))),XX) ) )
#...and for c sources:
$(foreach src,$(CORESRC), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/core/,$(notdir $(src)))),) ) )

# and the library sources
$(foreach src,$(ARDUINOLIBSRC), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/libraries/,$(notdir $(src)))),) ) )

#and our own c++ sources
$(foreach src,$(MYSRCFILES), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/,$(notdir $(src)))),XX) ) )


clean:
	test ! -d $(TMPDIR) || rm -rf $(TMPDIR)

.PHONY: upload default

$(TMPDIR):
	mkdir -p $(TMPDIR)

$(TMPDIR)/core:
	mkdir -p $(TMPDIR)/core

$(TMPDIR)/libraries:
	mkdir -p $(TMPDIR)/libraries

#creates the cpp file from the .ino file
$(NEWMAINFILE): $(PROJNAME).ino
	#cat $(ADIR)/arduino/sam/cores/arduino/main.cpp > $(NEWMAINFILE)
	cat $(PROJNAME).ino > $(NEWMAINFILE)
	echo 'extern "C" void __cxa_pure_virtual() {while (true);}' >> $(NEWMAINFILE)

#include the dependencies for our own files
-include $(MYOBJFILES:.o=.d)

#create the core library from the core objects. 
$(TMPDIR)/core.a: $(TMPDIR)/core $(COREOBJS) $(COREOBJSXX)
	$(AR) rcs $(TMPDIR)/core.a $(COREOBJS) $(COREOBJSXX) 

# create the external libraries as one library
$(TMPDIR)/libarduino.a: $(TMPDIR)/libraries $(ARDUINOOBJS)
	$(AR) rcs $(TMPDIR)/libarduino.a $(ARDUINOOBJS)

#link our own object files with core and the external libraries to form the elf file
$(TMPDIR)/$(PROJNAME).elf: $(TMPDIR)/core.a $(TMPDIR)/core/syscalls_sam3.c.o $(MYOBJFILES) $(TMPDIR)/libarduino.a 
	$(CXX) -Os -Wl,--gc-sections -mcpu=cortex-m3 -T$(ADIR)/$(SAM)/variants/arduino_due_x/linker_scripts/gcc/flash.ld -Wl,-Map,$(NEWMAINFILE).map -o $@ -L$(TMPDIR) -lm -lgcc -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group $(TMPDIR)/core/syscalls_sam3.c.o $(MYOBJFILES) $(ADIR)/$(SAM)/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a $(TMPDIR)/core.a -Wl,--end-group -larduino

# strip all debug symbols and create the much smaller bin file
$(TMPDIR)/$(PROJNAME).bin: $(TMPDIR)/$(PROJNAME).elf 
	$(ADIR)/tools/arm-none-eabi/bin/arm-none-eabi-objcopy -O binary $< $@

#upload to the arduino by first resetting it (stty) and the running bossac
upload: $(TMPDIR)/$(PROJNAME).bin
	stty -F $(PORT) cs8 1200 hupcl
	$(ADIR)/tools/bossac -p $(BOSSA_PORT) -U false -e -w $(VERIFY) -b $(TMPDIR)/$(PROJNAME).bin -R

#to view the serial port with minicom.
monitor:
	minicom -D $(PORT)

test:
	make upload
	make monitor

