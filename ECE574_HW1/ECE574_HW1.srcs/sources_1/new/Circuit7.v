`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/23/2017 06:31:22 PM
// Design Name: 
// Module Name: Circuit7
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


module Circuit7(clk, rst, a, b, c, d, zero, z);
    input clk, rst;
    input [63:0] a, b, c, d, zero;
    output [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire gEQz;
    
    DIV #(64) div_1 (
        .a(a),
        .b(b),
        .quot(e)
    );
    
    DIV #(64) div_2 (
        .a(c),
        .b(d),
        .quot(f)
    );
    
    MOD #(64) mod_1 (
        .a(a),
        .b(b),
        .rem(g)
    );
    
    COMP #(64) comp_1 (
        .a(g),
        .b(zero),
        .eq(gEQz)
    );
    
    MUX #(64) mux_1 (
        .a(e),
        .b(f),
        .sel(gEQz),
        .d(zwire)
    );
    
    REG #(64) reg_1 (
        .d(zwire),
        .Clk(clk),
        .Rst(rst),
        .q(z)
    );

endmodule
