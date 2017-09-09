`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 04:14:21 PM
// Design Name: 
// Module Name: Circuit1
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


module Circuit1(clk, rst, a, b, c, z, x);

    input clk, rst;
    input [7:0] a, b, c;
    output [7:0] z;
    output [15:0] x;
    
    wire [7:0] d, e;
    wire [15:0] f, g, xwire;
    
    ADD #(8) add_1 (
        .a(a),
        .b(b),
        .sum(d)
    );
    
    ADD #(8) add_2 (
        .a(a),
        .b(c),
        .sum(e)
    );
    
    COMP #(8) comp_1 (
        .a(d), 
        .b(e), 
        .gt(g), 
        .lt(), 
        .eq()
    );
     
    MUX2x1 #(8) mux_1 (
        .a(d), 
        .b(e), 
        .sel(g), 
        .d(z)
    );
     
    MUL #(8) mul_1 (
        .a(a), 
        .b(c), 
        .prod(f)
    );
    
    SUB #(16) sub_1 (
        .a(f), 
        .b({8'b0, d}), 
        .diff(xwire)
    );
    
    REG #(16) reg_1(
        .d(xwire), 
        .Clk(clk), 
        .Rst(rst), 
        .q(x)
    );
    
    
endmodule
