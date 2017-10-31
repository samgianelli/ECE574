module mixed_circuit1(clk, rst, a, b, c);

	input clk, rst;
	input signed [7:0] a;
	input [7:0] b;
	output signed [7:0] c;
	wire signed [7:0] cwire;

	SADD #(8)ADD_0($signed(a), $signed(b), cwire);
	SREG #(8)REG_1($signed(cwire), clk, rst, c);

endmodule

