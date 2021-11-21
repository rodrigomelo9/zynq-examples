#!/usr/bin/make

VHDL = $(sort $(wildcard *.vhdl))
VLOG = $(sort $(wildcard *.v))

BUILD  = build
PWD    = $(shell pwd)

DOCKER = docker run --rm -v $(PWD)/..:$(PWD)/.. -w $(PWD)
IMAGE  = hdlc/ghdl:yosys

all: vhdl vlog

vhdl:
	@$(foreach FILE, $(VHDL), $(DOCKER) $(IMAGE) yosys -m ghdl -p "ghdl $(FILE) -e; synth")

vlog:
	@$(foreach FILE, $(VLOG), $(DOCKER) $(IMAGE) yosys -p "read_verilog -defer $(FILE); synth")

clean:
	$(DOCKER) $(IMAGE) rm -fr $(BUILD)
