`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/12/2017 09:57:29 AM
// Design Name: 
// Module Name: Circuit5
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


module Circuit5(clk, rst, a, b, c, z, x);

    input clk, rst;
    input [63:0] a, b, c;
    output [31:0] z, x;
    
    wire [63:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [63:0] xrin, zrin;
    wire [63:0] greg, hreg;
    
    ADD #(64) add_1 (
        .a(a),
        .b(b),
        .sum(d)
    );
    
    ADD #(64) add_2 (
    .a(a),
    .b(c),
    .sum(e)
    );
    
    SUB #(64) sub_1 (
    .a(a),
    .b(b),
    .diff(f)
    );
    
    COMP #(64) comp_1 (
        .a(d), 
        .b(e), 
        .gt(), 
        .lt(), 
        .eq(dEQe)
    );
    
    COMP #(64) comp_2 (
        .a(d), 
        .b(e), 
        .gt(), 
        .lt(dLTe), 
        .eq()
    );
    
    MUX2x1 #(64) mux_1 (
        .a(e), 
        .b(d), 
        .sel(dLTe), 
        .d(g)
    );
    
    MUX2x1 #(64) mux_2 (
        .a(f), 
        .b(g), 
        .sel(dEQe), 
        .d(h)
    );
    
        
    REG #(64) reg_1 (
        .d(g), 
        .Clk(clk), 
        .Rst(rst), 
        .q(greg)
    );
    
    REG #(64) reg_2 (
        .d(h), 
        .Clk(clk), 
        .Rst(rst), 
        .q(hreg)
    );
    
    SHL #(64) shl_1 (
        .a(hreg), 
        .sh_amt(dLTe), 
        .d(xrin)
    );
 
    SHR #(64) shr_1 (
        .a(greg), 
        .sh_amt(dEQe), 
        .d(zrin)
    );   
    
    REG #(64) reg_3 (
        .d(xrin), 
        .Clk(clk), 
        .Rst(rst), 
        .q(x)
    );
    
    REG #(64) reg_4 (
        .d(zrin), 
        .Clk(clk), 
        .Rst(rst), 
        .q(z)
    );
    
    
endmodule
