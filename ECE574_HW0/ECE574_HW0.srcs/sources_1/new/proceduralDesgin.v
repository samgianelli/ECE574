`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: TosiCorp
// Engineer: Sam Gianelli
// 
// Create Date: 08/26/2017 05:39:54 PM
// Design Name: 
// Module Name: proceduralDesgin
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


module proceduralDesign(H1, H2, B1, B2, P);
    input H1, H2, B1, B2;
    output reg P;
    
    always @(H1, H2, B1, B2) begin
        P <= ((H1 | H2) & (B1 | B2));
    end
endmodule