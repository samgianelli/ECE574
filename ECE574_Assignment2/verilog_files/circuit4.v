module circuit4(clk, rst, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, final);

	input clk, rst;
	input signed [7:0] a;
	input signed [7:0] b;
	input signed [7:0] c;
	input signed [7:0] d;
	input signed [7:0] e;
	input signed [7:0] f;
	input signed [7:0] g;
	input signed [7:0] h;
	input signed [7:0] i;
	input signed [7:0] j;
	input signed [7:0] k;
	input signed [7:0] l;
	input signed [7:0] m;
	input signed [7:0] n;
	input signed [7:0] o;
	input signed [7:0] p;
	output signed [31:0] final;
	wire signed [31:0] t1;
	wire signed [31:0] t2;
	wire signed [31:0] t3;
	wire signed [31:0] t4;
	wire signed [31:0] t5;
	wire signed [31:0] t6;
	wire signed [31:0] t7;
	wire signed [31:0] t8;
	wire signed [31:0] t9;
	wire signed [31:0] t10;
	wire signed [31:0] t11;
	wire signed [31:0] t12;
	wire signed [31:0] t13;
	wire signed [31:0] t14;

	SADD #(32)ADD_0($signed(a), $signed(b), t1);
	SADD #(32)ADD_1($signed(t1), $signed(c), t2);
	SADD #(32)ADD_2($signed(t2), $signed(d), t3);
	SADD #(32)ADD_3($signed(t3), $signed(e), t4);
	SADD #(32)ADD_4($signed(t4), $signed(f), t5);
	SADD #(32)ADD_5($signed(t5), $signed(g), t6);
	SADD #(32)ADD_6($signed(t6), $signed(h), t7);
	SADD #(32)ADD_7($signed(t7), $signed(i), t8);
	SADD #(32)ADD_8($signed(t8), $signed(j), t9);
	SADD #(32)ADD_9($signed(t9), $signed(l), t10);
	SADD #(32)ADD_10($signed(t10), $signed(m), t11);
	SADD #(32)ADD_11($signed(t11), $signed(n), t12);
	SADD #(32)ADD_12($signed(t12), $signed(o), t13);
	SADD #(32)ADD_13($signed(t13), $signed(p), t14);
	SREG #(32)REG_14($signed(t14), clk, rst, final);

endmodule

