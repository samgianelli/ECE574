`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/23/2017 06:31:22 PM
// Design Name: 
// Module Name: Circuit6
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


module Circuit6(clk, rst, a, b, c, d, e, f, g, h, num, avg);
    input clk, rst;
    input [15:0] a, b, c, d, e, f, g, h, num;
    output [15:0] avg;
    
    wire [15:0] avgwire;
    wire [31:0] t1, t2, t3, t4, t5, t6, t7;  // arithmetic wires
    wire [15:0] r1, r2, r3, r4, r5, r6, r7;  // regs
    
    ADD #(32) add_1 (
        .a(a),
        .b(b),
        .sum(t1)
    );
    
    REG #(16) reg_1 (
        .d(t1), 
        .Clk(clk), 
        .Rst(rst), 
        .q(r1)
    );
    
    ADD #(32) add_2 (
        .a(r1),
        .b(c),
        .sum(t2)
    );
    
    Reg #(16) reg_2 (
        .d(t2),
        .Clk(clk),
        .Rst(rst),
        .q(r2)
    );
    
    ADD #(32) add_3 (
        .a(r2),
        .b(d),
        .sum(t3)
    );
    
    Reg #(16) reg_3 (
        .d(t3),
        .Clk(clk),
        .Rst(rst),
        .q(r3)
    );

    ADD #(32) add_4 (
        .a(r3),
        .b(e),
        .sum(t4)
    );
    
    Reg #(16) reg_4 (
        .d(t4),
        .Clk(clk),
        .Rst(rst),
        .q(r4)
    );
    
    ADD #(32) add_5 (
        .a(r4),
        .b(f),
        .sum(t5)
    );
    
    Reg #(16) reg_5 (
        .d(t5),
        .Clk(clk),
        .Rst(rst),
        .q(r5)
    );
    
    ADD #(32) add_6 (
        .a(r5),
        .b(g),
        .sum(t6)
    );
    
    Reg #(16) reg_6 (
        .d(t6),
        .Clk(clk),
        .Rst(rst),
        .q(r6)
    );
    
    ADD #(32) add_7 (
        .a(r6),
        .b(h),
        .sum(t7)
    );
    
    Reg #(16) reg_7 (
        .d(t7),
        .Clk(clk),
        .Rst(rst),
        .q(r7)
    );
    
    DIV #(16) div_1 (
        .a(r7),
        .b(num),
        .quot(avgwire)
    ); 
    
    Reg #(16) reg_8 (
        .d(avgwire),
        .Clk(clk),
        .Rst(rst),
        .q(avg)
    );
    
    
    
    
    
endmodule
