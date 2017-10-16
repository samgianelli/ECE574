`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 11:12:20 AM
// Design Name: 
// Module Name: MOD
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


module MOD(a, b, rem);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    output reg [DATAWIDTH - 1 : 0] rem;
    
    always @(a, b) begin
        rem <= a % b;
    end
    
endmodule


module SMOD(a, b, rem);
    parameter DATAWIDTH = 8;
    input signed [DATAWIDTH - 1 : 0] a, b;
    output reg signed [DATAWIDTH - 1 : 0] rem;
    
    always @(a, b) begin
        rem <= a % b;
    end
    
endmodule
