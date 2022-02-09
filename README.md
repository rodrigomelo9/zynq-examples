# Zynq examples

[![License](https://img.shields.io/github/license/rodrigomelo9/zynq-examples.svg?longCache=true)](https://github.com/rodrigomelo9/zynq-examples/blob/main/LICENSE)
[![HDL status](https://img.shields.io/github/workflow/status/rodrigomelo9/zynq-examples/hdl?longCache=true&label=hdl)](https://github.com/rodrigomelo9/zynq-examples/actions/workflows/hdl.yml)

Here you will find general-purpose examples about Zynq 7000 and Zynq UltraScale+ devices from Xilinx.
These examples will be related to features of the devices or how to perform certain tasks with Vivado/Vitis (not the old SDK).
The examples are based on ZYBO (not the newest [Zybo Z7](https://digilent.com/reference/programmable-logic/zybo-z7/migration-guide)) and the ZCU102 boards, basically because these are the platforms that I have, but most should be easily adaptable.
In the Programmable Logic (PL) side, you will find HDLs and/or block designs (Tcl), while for the Processor System (PS), baremetal/standalone firmware (C code).

Under the [doc](doc) directory you will find some very simple, step-by-step guides (practical recipes, without much theory).
Then, you will find directories related to a particular topic (I can imagine *axidma*, *ps*, *pl*, *emio*, *transceivers*, among others), and one or more examples inside, with instructions to easily reproduce them.
The idea is to provide a simple starting point, that you can see in action, to quickly start playing with.

Take into account that I try to maintain each example/guide as simple as possible, with a few or no images at all, and minimal instructions.
It is because time-to-time, there is a *refresh* of the graphical interface, so images (and sometimes text) are automatically outdated.
It is the reason why I include a note at the beginning, informing the last version where tested.

## Reasons for this repository?

There are several good resources from [Xilinx](https://www.xilinx.com/search/site-keyword-search.html#q=zynq) ([Zynq-7000 SoC: Embedded
Design Tutorial](https://github.com/Xilinx/Embedded-Design-Tutorials)), awesome blogs ([The MicroZed Chronicles](http://www.microzedchronicles.com)),
sites with projects ([Hackster Xilinx community](https://www.hackster.io/xilinx/projects)) and courses ([SoC Course with Reference Designs](https://ohwr.org/project/soc-course/wikis/home)), books ([The Zynq Book](http://www.zynqbook.com/)), and several more things about these devices around the net... So why another one?

I started with FPGAs in 2006, but I have been working with Zynq devices since 2015.
I was one of the instructors in some related workshops ([smr3249](https://indico.ictp.it/event/8342), [smr3289](http://indico.ictp.it/event/8680), [smr3557](http://indico.ictp.it/event/9644) and [smr3562](http://indico.ictp.it/event/9443)).
So I already have or create new examples time-to-time (see [here](https://github.com/INTI-CMNB-FPGA/fpga_examples), [here](https://github.com/rodrigomelo9/zynq-pl-ps) or [here](https://gitlab.com/rodrigomelo9/core-comblock)).
Finally, I am sometimes asked for help/examples.
These reasons made me think that is a good idea to have this space.

Please, take into account that I do not have a clear [roadmap](https://github.com/rodrigomelo9/zynq-examples/issues/5) and could happen months between updates.

## What am I doing in Continuous Integration?

It is not legal to use vendor tools in public runners, neither easy nor convenient in general (can you imagine downloading more than 50 GB and installing it before each run?).
Fortunately, there exist FLOSS (Free/Libre and Open Source Software) and I am a user (and sometimes contributor).
You can see my presentation [FOSS-for-FPGAs](https://rodrigomelo9.github.io/FOSS-for-FPGAs) for an overview.

So, I am using the [Yosys](https://github.com/YosysHQ/yosys) synthesizer, which supports Verilog, and the [ghdl-yosys-plugin](https://github.com/ghdl/ghdl-yosys-plugin), which adds VHDL support, to verify that I am providing working HDL code.
For that purpose, I take advantage of [Docker](https://en.wikipedia.org/wiki/Docker_(software)) and [hdl/containers](https://github.com/hdl/containers).
