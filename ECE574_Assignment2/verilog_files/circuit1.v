module circuit1(clk, rst, a, b, c, z, x);

	input clk, rst;
	input signed [7:0] a;
	input signed [7:0] b;
	input signed [7:0] c;
	output signed [7:0] z;
	output signed [15:0] x;
	wire signed [7:0] d;
	wire signed [7:0] e;
	wire signed [15:0] f;
	wire signed [15:0] g;
	wire signed [15:0] xwire;

	SADD #(8)ADD_0($signed(a), $signed(b), d);
	SADD #(8)ADD_1($signed(a), $signed(c), e);
	SCOMP #(16)GT_2($signed(d), $signed(e), g, , );
	SMUX2x1 #(8)MUX_3(d, d, g, z);
	SMUL #(16)MUL_4($signed(a), $signed(c), f);
	SSUB #(16)SUB_5($signed(f), $signed(d), xwire);
	SREG #(16)REG_6($signed(xwire), clk, rst, x);

endmodule

