`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:29:06 PM
// Design Name: 
// Module Name: MUX2x1
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


module MUX2x1(a, b, sel, d);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    input sel;
    output reg [DATAWIDTH - 1 : 0] d;
        
    initial begin
        d <= 0;
    end
    
    always @(a, b, sel) begin
        if (sel == 1'b0) begin
            d <= a;
        end
        else begin
            d <= b;
        end
    end   
 
endmodule


module SMUX2x1(a, b, sel, d);
    parameter DATAWIDTH = 8;
    input signed [DATAWIDTH - 1 : 0] a, b;
    input sel;
    output reg signed [DATAWIDTH - 1 : 0] d;
        
    initial begin
        d <= 0;
    end
    
    always @(a, b, sel) begin
        if (sel == 1'b0) begin
            d <= a;
        end
        else begin
            d <= b;
        end
    end   
 
endmodule
