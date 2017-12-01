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
Our program will generate a graph topography representing the control data flow graph of the netlist. The edges of the 
graph are instances of the IOWire class, which correspond to an input, output, wire, or register in Verilog. The nodes
of the graph are instances of the Module class, which correspond to the different components in the netlist. The edges
keep a reference of the two nodes it is connection, as well as it's bit width, and whether it is signed or unsigned. 
The nodes keep an instance of what type of module they are, if they are signed or unsigned, the input and output edges,
the bit width, and the delay of that given module. We first traverse the graph and print the module instances so they 
will be synthesizable in verilog. Then, we recursively traverse the graph from every possible output to find the maximum 
delay of the circuit.

4) Individual Contributions
	All group members worked together on debugging, testing, and implementing the functionality of the assignment. Below
	is the individual contributions of each member:
	- Sam Gianelli
		- Graph initialization.
		- Created initial parser.
		- Created critical path functionality.

	- Eddie Richter
		- Error detection.
		- Module parser.
		- Printing the output verilog to the console. 

	- Diego Jimenez
		- Printing the verilog to a file.
		- Generating the signed modules.
		- Signed padding through $signed()

	- Hugo Valdez
		- Register equal to computation functionality.
		- Signed and unsigned module creation.