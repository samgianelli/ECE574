module circuit3(clk, rst, a, b, c, d, e, f, g, h, sa, avg);

	input clk, rst;
	input signed [15:0] a;
	input signed [15:0] b;
	input signed [15:0] c;
	input signed [15:0] d;
	input signed [15:0] e;
	input signed [15:0] f;
	input signed [15:0] g;
	input signed [15:0] h;
	input signed [7:0] sa;
	output signed [15:0] avg;
	wire signed [31:0] l00;
	wire signed [31:0] l01;
	wire signed [31:0] l02;
	wire signed [31:0] l03;
	wire signed [31:0] l10;
	wire signed [31:0] l11;
	wire signed [31:0] l2;
	wire signed [31:0] l2div2;
	wire signed [31:0] l2div4;
	wire signed [31:0] l2div8;

	SADD #(32)ADD_0($signed(a), $signed(b), l00);
	SADD #(32)ADD_1($signed(c), $signed(d), l01);
	SADD #(32)ADD_2($signed(e), $signed(f), l02);
	SADD #(32)ADD_3($signed(g), $signed(h), l03);
	SADD #(32)ADD_4($signed(l00), $signed(l01), l10);
	SADD #(32)ADD_5($signed(l02), $signed(l03), l11);
	SADD #(32)ADD_6($signed(l10), $signed(l11), l2);
	SSHR #(32)SHR_7($signed(l2), $signed(sa), l2div2);
	SSHR #(32)SHR_8($signed(l2div2), $signed(sa), l2div4);
	SSHR #(32)SHR_9($signed(l2div4), $signed(sa), l2div8);
	SREG #(16)REG_10($signed(l2div8), clk, rst, avg);

endmodule

