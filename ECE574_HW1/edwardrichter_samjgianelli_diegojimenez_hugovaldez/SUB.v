`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:19:17 PM
// Design Name: 
// Module Name: SUB
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


module SUB(a, b, diff);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    output reg [DATAWIDTH - 1 : 0] diff;
    
    always @(a) begin
        diff <= a - b;
    end   
     
endmodule
