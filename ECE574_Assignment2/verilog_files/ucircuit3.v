module ucircuit3(clk, rst, a, b, c);

	input clk, rst;
	input [31:0] a;
	input [15:0] b;
	output [7:0] c;
	wire [7:0] cwire;

	ADD #(8)ADD_0(a, b, cwire);
	REG #(8)REG_1(cwire, clk, rst, c);

endmodule

