`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 05:53:51 PM
// Design Name: 
// Module Name: Circuit4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Circuit4(clk, rst, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, final);
    
    input clk, rst;
    input [7:0] a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
    output [31:0] final;
    
    wire [31:0] t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    
    ADD #(8) add_1 (
        .a(a),
        .b(b),
        .sum(t1)
    );

    ADD #(32) add_2 (
        .a(t1),
        .b({24'b0, c}),
        .sum(t2)
    );

    ADD #(32) add_3 (
        .a(t2),
        .b({24'b0, d}),
        .sum(t3)
    );

    ADD #(32) add_4 (
        .a(t3),
        .b({24'b0, e}),
        .sum(t4)
    );

    ADD #(32) add_5 (
        .a(t4),
        .b({24'b0, f}),
        .sum(t5)
    );

    ADD #(32) add_6 (
        .a(t5),
        .b({24'b0, g}),
        .sum(t6)
    );

    ADD #(32) add_7 (
        .a(t6),
        .b({24'b0, h}),
        .sum(t7)
    );

    ADD #(32) add_8 (
        .a(t7),
        .b({24'b0, i}),
        .sum(t8)
    );

    ADD #(32) add_9 (
        .a(t8),
        .b({24'b0, j}),
        .sum(t9)
    );

    ADD #(32) add_10 (
        .a(t9),
        .b({24'b0, l}),
        .sum(t10)
    );

    ADD #(32) add_11 (
        .a(t10),
        .b({24'b0, m}),
        .sum(t11)
    );

    ADD #(32) add_12 (
        .a(t11),
        .b({24'b0, n}),
        .sum(t12)
    );

    ADD #(32) add_13 (
        .a(t12),
        .b({24'b0, o}),
        .sum(t13)
    );

    ADD #(32) add_14 (
        .a(t13),
        .b({24'b0, p}),
        .sum(t14)
    );
    
    REG #(32) reg_1 (
        .d(t14), 
        .Clk(clk), 
        .Rst(rst), 
        .q(final)
    );    

    
endmodule
