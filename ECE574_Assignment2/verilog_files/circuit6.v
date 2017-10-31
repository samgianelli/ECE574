module circuit6(clk, rst, a, b, c, d, e, f, g, h, num, avg);

	input clk, rst;
	input signed [15:0] a;
	input signed [15:0] b;
	input signed [15:0] c;
	input signed [15:0] d;
	input signed [15:0] e;
	input signed [15:0] f;
	input signed [15:0] g;
	input signed [15:0] h;
	input signed [15:0] num;
	output signed [15:0] avg;
	wire signed [15:0] r1;
	wire signed [15:0] r2;
	wire signed [15:0] r3;
	wire signed [15:0] r4;
	wire signed [15:0] r5;
	wire signed [15:0] r6;
	wire signed [15:0] r7;
	wire signed [15:0] avgwire;
	wire signed [31:0] t1;
	wire signed [31:0] t2;
	wire signed [31:0] t3;
	wire signed [31:0] t4;
	wire signed [31:0] t5;
	wire signed [31:0] t6;
	wire signed [31:0] t7;

	SADD #(32)ADD_0($signed(a), $signed(b), t1);
	SREG #(16)REG_1($signed(t1), clk, rst, r1);
	SADD #(32)ADD_2($signed(r1), $signed(c), t2);
	SREG #(16)REG_3($signed(t2), clk, rst, r2);
	SADD #(32)ADD_4($signed(r2), $signed(d), t3);
	SREG #(16)REG_5($signed(t3), clk, rst, r3);
	SADD #(32)ADD_6($signed(r3), $signed(e), t4);
	SREG #(16)REG_7($signed(t4), clk, rst, r4);
	SADD #(32)ADD_8($signed(r4), $signed(f), t5);
	SREG #(16)REG_9($signed(t5), clk, rst, r5);
	SADD #(32)ADD_10($signed(r5), $signed(g), t6);
	SREG #(16)REG_11($signed(t6), clk, rst, r6);
	SADD #(32)ADD_12($signed(r6), $signed(h), t7);
	SREG #(16)REG_13($signed(t7), clk, rst, r7);
	SDIV #(16)DIV_14($signed(r7), $signed(num), avgwire);
	SREG #(16)REG_15($signed(avgwire), clk, rst, avg);

endmodule

