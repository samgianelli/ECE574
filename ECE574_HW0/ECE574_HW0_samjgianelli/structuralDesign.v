`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: TosiCorp
// Engineer: Sam Gianelli 
// 
// Create Date: 08/26/2017 05:39:54 PM
// Design Name: 
// Module Name: structuralDesign
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


module structuralDesign(H1, H2, B1, B2, P);
    input H1, H2, B1, B2;
    wire Hikers, Basketballers;
    output wire P;
    
    OR2Gate OR2Gate_H(H1, H2, Hikers);
    OR2Gate OR2Gate_B(B1, B2, Basketballers);
    AND2Gate AND2Gate_P(Hikers, Basketballers, P);
    
endmodule

module AND2Gate(X, Y, F);
    input X, Y;
    output reg F;
    
    always @(X, Y) begin
        F <= X & Y;
    end
    
endmodule

module OR2Gate(X, Y, F);
    input X, Y;
    output reg F;
    
    always @(X, Y) begin
        F <= X | Y;
    end
    
endmodule