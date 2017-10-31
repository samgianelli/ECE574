module circuit2(clk, rst, a, b, c, z, x);

	input clk, rst;
	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	output signed [31:0] z;
	output signed [31:0] x;
	wire signed [31:0] d;
	wire signed [31:0] e;
	wire signed [31:0] f;
	wire signed [31:0] g;
	wire signed [31:0] h;
	wire signed  dLTe;
	wire signed  dEQe;
	wire signed [31:0] zwire;
	wire signed [31:0] xwire;

	SADD #(32)ADD_0($signed(a), $signed(b), d);
	SADD #(32)ADD_1($signed(a), $signed(c), e);
	SSUB #(32)SUB_2($signed(a), $signed(b), f);
	SCOMP #(32)EQ_3($signed(d), $signed(e), , ,dEQe);
	SCOMP #(32)LT_4($signed(d), $signed(e), ,dLTe, );
	SMUX2x1 #(32)MUX_5(d, d, dLTe, g);
	SMUX2x1 #(32)MUX_6(g, g, dEQe, h);
	SSHL #(32)SHL_7($signed(g), $signed(dLTe), xwire);
	SSHR #(32)SHR_8($signed(h), $signed(dEQe), zwire);
	SREG #(32)REG_9($signed(xwire), clk, rst, x);
	SREG #(32)REG_10($signed(zwire), clk, rst, z);

endmodule

