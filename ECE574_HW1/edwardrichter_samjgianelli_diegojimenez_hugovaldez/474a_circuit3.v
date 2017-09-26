`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 05:25:21 PM
// Design Name: 
// Module Name: Circuit3
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


module Circuit3(clk, rst, a, b, c, d, e, f, g, h, sa, avg);
    
    input clk, rst;
    input [15:0] a, b, c, d, e, f, g, h;
    input [7:0] sa;
    output [15:0] avg;
    
    wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;
    
    ADD #(16) add_1 (
        .a(a),
        .b(b),
        .sum(l00)
    );
    
    ADD #(16) add_2 (
        .a(c),
        .b(d),
        .sum(l01)
    );
    
    ADD #(16) add_3 (
        .a(e),
        .b(f),
        .sum(l02)
    );
    
    ADD #(16) add_4 (
        .a(g),
        .b(h),
        .sum(l03)
    );
    
    ADD #(16) add_5 (
        .a(l00),
        .b(l01),
        .sum(l10)
    );
    
    ADD #(16) add_6 (
        .a(l02),
        .b(l03),
        .sum(l11)
    );
    
    ADD #(16) add_7 (
        .a(l11),
        .b(l10),
        .sum(l2)
    );
    
    SHR #(32) shr_1 (
        .a(l2), 
        .sh_amt(sa), 
        .d(l2div2)
    );
    
    SHR #(32) shr_2 (
        .a(l2div2), 
        .sh_amt(sa), 
        .d(l2div4)
    );
    
    SHR #(32) shr_3 (
        .a(l2div4), 
        .sh_amt(sa), 
        .d(l2div8)
    );
    
    REG #(32) reg_1 (
        .d(l2div8), 
        .Clk(clk), 
        .Rst(rst), 
        .q(avg)
    );
    
    
     
endmodule
