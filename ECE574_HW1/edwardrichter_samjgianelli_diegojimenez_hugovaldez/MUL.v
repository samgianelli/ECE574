`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:20:16 PM
// Design Name: 
// Module Name: MUL
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


module MUL(a, b, prod);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    output reg [DATAWIDTH - 1 : 0] prod;
        
    initial begin
        prod <= 0;
    end
    
    always @(a, b) begin
        prod <= a * b;
    end   
     
endmodule
