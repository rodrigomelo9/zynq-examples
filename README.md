# Zynq examples

[![License](https://img.shields.io/github/license/rodrigomelo9/zynq-examples.svg?longCache=true)](https://github.com/rodrigomelo9/zynq-examples/blob/main/LICENSE)
[![HDL status](https://img.shields.io/github/workflow/status/rodrigomelo9/zynq-examples/hdl?longCache=true&label=hdl)](https://github.com/rodrigomelo9/zynq-examples/actions/workflows/hdl.yml)

Here you will find general-purpose examples about Zynq 7000 and Zynq UltraScale+ devices from Xilinx.
These examples will be related to features of the devices or how to perform certain tasks with Vivado/Vitis (not the old SDK).
The examples are based on ZYBO (not the newest Zynq Z7, see [here](https://digilent.com/reference/programmable-logic/zybo-z7/migration-guide) for more details) and the ZCU102 board, basically because are the boards that I have. However, most of them should be easily adaptable.

## Reasons for this repository?

There are a lot of resources related to these devices in the network. A few examples:
* [Xilinx](https://www.xilinx.com/search/site-keyword-search.html#q=zynq)
* [The MicroZed Chronicles](http://www.microzedchronicles.com)
* [The Zynq Book](http://www.zynqbook.com)

So why another one?
Well, I have been working with these devices since 2015.
Moreover, I was the instructor in some related workshops ([smr3249](https://indico.ictp.it/event/8342), [smr3289](http://indico.ictp.it/event/8680), [smr3557](http://indico.ictp.it/event/9644) and [smr3562](http://indico.ictp.it/event/9443)).
So I already have or create new examples time-to-time (see [here](https://github.com/INTI-CMNB-FPGA/fpga_examples), [here](https://github.com/rodrigomelo9/zynq-pl-ps) or [here](https://gitlab.com/rodrigomelo9/core-comblock)).
Finally, I am sometimes asked for help/examples.
These reasons made me think that is a good idea to have this space.

Please, take into account that I do not have a roadmap and could happen months between updates.

## What am I doing in Continuous Integration?

It is not legal to use vendor tools in public runners, neither easy nor convenient in general (can you imagine downloading around 50 GB and installing it before each run?).
Fortunately, there exist FLOSS (Free/Libre and Open Source Software) and I am a user (and sometimes contributor).
You can see my presentation [FOSS-for-FPGAs](https://rodrigomelo9.github.io/FOSS-for-FPGAs) for an overview.

So, I am using the [Yosys](https://github.com/YosysHQ/yosys) synthesizer, which supports Verilog, and the [ghdl-yosys-plugin](https://github.com/ghdl/ghdl-yosys-plugin), which adds VHDL support, to verify that I providing working HDL code.
For that purpose, I take advantage of [Docker](https://en.wikipedia.org/wiki/Docker_(software)) and containers from [hdl/container](https://github.com/hdl/containers).
