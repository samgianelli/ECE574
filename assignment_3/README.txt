1) Name and NetIDs
Eddie Richter - edwardrichter
Sam Gianelli  - samjgianelli
Diego Jimenez - diegojimenez
Hugo Valdez   - hugovaldez

2) Course
Eddie Richter - 474a
Sam Gianelli  - 574a
Diego Jimenez - 474a
Hugo Valdez   - 474a

3) Brief Description

program usage: hlsyn cFile latency verilogFile
	cFile - The path to the netlist you wish to convert
	latency - How long the graph has to be scheduled
	verilogFile - The path to for the output verilogFile

Our program generates a graph representing an input netlist file, displaying how all modules and operations relate to
each other during execution.  Modules/operations are represented as the nodes of the graph and an IOWire class is used
for edges between operations (the wires within a .v file).
Once the graph has been created, The operations in the graph are shceduled using Force Directed Scheduling (FDS).
First, the time frames are calculated for all operations, graphs are generated, then all operations are shceduled given
the input latency constraint.
Finally, once the entire graph has been scheduled, the scheduled operations are written to a verilog file (.v) as an
HLSM.  This file consists of a large switch case statement where each case represents a time in the schedule diagram.
All generated HLSMs are synthesizable verilog files.



4) Individual Contributions
	All group members worked together on debugging, testing, and implementing the functionality of the assignment. Below
	is the individual contributions of each member:
	- Sam Gianelli
		- Verified FDS scheduling functionality
		- If statement parsing and edge cases
		- Verified output files to function in verilog 

	- Eddie Richter
		- If statement to mux generation in graph
		- Error Detection for FDS functionality
		- FDS scheduling (Time Frames)

	- Diego Jimenez
		- Generating Verilog code for output
		- If statement parsing
		- FDS debugging

	- Hugo Valdez
		- Constructed framework for FDS Scheduling (Graph generation)
		- If statement edge case verification
		- Error detection for parser and If statements