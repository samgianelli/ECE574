module mixed_circuit2(clk, rst, a, b, c);

	input clk, rst;
	input signed [7:0] a;
	input [15:0] b;
	output signed [31:0] c;
	wire signed [31:0] cwire;

	SADD #(32)ADD_0($signed(a), $signed(b), cwire);
	SREG #(32)REG_1($signed(cwire), clk, rst, c);

endmodule

