`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 11:12:20 AM
// Design Name: 
// Module Name: DIV
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


module DIV(a, b, quot);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] a, b;
    output reg [DATAWIDTH - 1 : 0] quot;
    
    always @(a, b) begin
        quot <= a / b;
    end
    
endmodule
