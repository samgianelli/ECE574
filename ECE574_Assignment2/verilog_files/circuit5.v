module circuit5(clk, rst, a, b, c, z, x);

	input clk, rst;
	input signed [63:0] a;
	input signed [63:0] b;
	input signed [63:0] c;
	output signed [31:0] z;
	output signed [31:0] x;
	wire signed [63:0] d;
	wire signed [63:0] e;
	wire signed [63:0] f;
	wire signed [63:0] g;
	wire signed [63:0] h;
	wire signed  dLTe;
	wire signed  dEQe;
	wire signed [63:0] xrin;
	wire signed [63:0] zrin;
	wire signed [63:0] greg;
	wire signed [63:0] hreg;

	SADD #(64)ADD_0($signed(a), $signed(b), d);
	SADD #(64)ADD_1($signed(a), $signed(c), e);
	SSUB #(64)SUB_2($signed(a), $signed(b), f);
	SCOMP #(64)EQ_3($signed(d), $signed(e), , ,dEQe);
	SCOMP #(64)LT_4($signed(d), $signed(e), ,dLTe, );
	SMUX2x1 #(64)MUX_5(d, d, dLTe, g);
	SMUX2x1 #(64)MUX_6(g, g, dEQe, h);
	SREG #(64)REG_7($signed(g), clk, rst, greg);
	SREG #(64)REG_8($signed(h), clk, rst, hreg);
	SSHL #(64)SHL_9($signed(hreg), $signed(dLTe), xrin);
	SSHR #(64)SHR_10($signed(greg), $signed(dEQe), zrin);
	SREG #(32)REG_11($signed(xrin), clk, rst, x);
	SREG #(32)REG_12($signed(zrin), clk, rst, z);

endmodule

