`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 04:53:39 PM
// Design Name: 
// Module Name: Circuit2
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


module Circuit2(clk, rst, a, b, c, z, x);

    input clk, rst;
    input [31:0] a, b, c;
    output [31:0] z, x;
    
    wire [31:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [31:0] zwire, xwire;
    
    ADD #(32) add_1 (
        .a(a),
        .b(b),
        .sum(d)
    );
    
    ADD #(32) add_2 (
        .a(a),
        .b(c),
        .sum(e)
    );
    
    SUB #(32) sub_1 (
        .a(a),
        .b(b),
        .diff(f)
    );
    
    COMP #(32) comp_1 (
        .a(d), 
        .b(e), 
        .gt(), 
        .lt(), 
        .eq(dEQe)
    );
    
    COMP #(32) comp_2 (
        .a(d), 
        .b(e), 
        .gt(), 
        .lt(dLTe), 
        .eq()
    );
    
    MUX2x1 #(32) mux_1 (
        .a(d), 
        .b(e), 
        .sel(dLTe), 
        .d(g)
    );

    MUX2x1 #(32) mux_2 (
        .a(g), 
        .b(f), 
        .sel(dEQe), 
        .d(h)
    );
    
    SHL #(32) shl_1 (
        .a(g), 
        .sh_amt(dLTe), 
        .d(xwire)
    );

    SHR #(32) shr_1 (
        .a(h), 
        .sh_amt(dEQe), 
        .d(zwire)
    );
    
    REG #(32) reg_1 (
        .d(xwire), 
        .Clk(clk), 
        .Rst(rst), 
        .q(x)
    );

    REG #(32) reg_2 (
        .d(zwire), 
        .Clk(clk), 
        .Rst(rst), 
        .q(z)
    );    
    
endmodule
