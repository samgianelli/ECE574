`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:34:57 PM
// Design Name: 
// Module Name: SHL
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


module SHL(a, sh_amt, d);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, sh_amt;
    output reg [DATAWIDTH - 1 : 0] d;
        
    initial begin
        d <= 0;
    end
    
    always @(a, sh_amt) begin
        d <= a << sh_amt;
    end   

endmodule

module SSHL(a, sh_amt, d);
    parameter DATAWIDTH = 8;
    input signed [DATAWIDTH - 1 : 0] a, sh_amt;
    output reg signed [DATAWIDTH - 1 : 0] d;
        
    initial begin
        d <= 0;
    end
    
    always @(a, sh_amt) begin
        d <= a << sh_amt;
    end   

endmodule
