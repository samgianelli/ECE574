`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:17:43 PM
// Design Name: 
// Module Name: ADD
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


module ADD(a, b, sum);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    output reg [DATAWIDTH - 1 : 0] sum;
        
    initial begin
        sum <= 0;
    end
    
    always @(a, b) begin
        sum <= a + b;
    end   
     
endmodule
