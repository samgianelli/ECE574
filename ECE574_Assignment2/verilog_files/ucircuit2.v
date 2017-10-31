module ucircuit2(clk, rst, a, b, c);

	input clk, rst;
	input [7:0] a;
	input [15:0] b;
	output [31:0] c;
	wire [31:0] cwire;

	ADD #(32)ADD_0(a, b, cwire);
	REG #(32)REG_1(cwire, clk, rst, c);

endmodule

