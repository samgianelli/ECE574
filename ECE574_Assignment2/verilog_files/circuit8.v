module circuit8(clk, rst, a, b, c, zero, z);

	input clk, rst;
	input signed [63:0] a;
	input signed [63:0] b;
	input signed [63:0] c;
	input signed [63:0] zero;
	output signed [63:0] z;
	wire signed [63:0] e;
	wire signed [63:0] f;
	wire signed [63:0] g;
	wire signed [63:0] zwire;
	wire signed  gEQz;

	SDEC #(64)DEC_0($signed(a), e);
	SINC #(64)INC_1($signed(c), f);
	SMOD #(64)MOD_2($signed(a), $signed(c), g);
	SCOMP #(64)EQ_3($signed(g), $signed(zero), , ,gEQz);
	SMUX2x1 #(64)MUX_4(e, e, gEQz, zwire);
	SREG #(64)REG_5($signed(zwire), clk, rst, z);

endmodule

