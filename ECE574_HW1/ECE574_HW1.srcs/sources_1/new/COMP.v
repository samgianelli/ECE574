`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:24:29 PM
// Design Name: 
// Module Name: COMP
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


module COMP(a, b, gt, lt, eq);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    output reg gt, lt, eq;
    
    initial begin
        gt <= 0; lt <= 0; eq <= 0;
    end
    
    always @(*) begin
        if (a > b) begin
            gt <= 1;
        end
        else if (a == b) begin
            eq <= 1;
        end
        else begin
            lt <= 1;
        end
    end   

endmodule


module SCOMP(a, b, gt, lt, eq);
    parameter DATAWIDTH = 8;
    input signed [DATAWIDTH - 1 : 0] a, b;
    output reg gt, lt, eq;
    
    initial begin
        gt <= 0; lt <= 0; eq <= 0;
    end
    
    always @(*) begin
        if (a > b) begin
            gt <= 1;
        end
        else if (a == b) begin
            eq <= 1;
        end
        else begin
            lt <= 1;
        end
    end   

endmodule
