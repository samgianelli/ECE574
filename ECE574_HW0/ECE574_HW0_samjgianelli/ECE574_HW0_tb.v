`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: TosiCorp
// Engineer: Sam Gianelli
// 
// Create Date: 08/26/2017 05:52:14 PM
// Design Name: 
// Module Name: ECE574_HW0_tb
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


module ECE574_HW0_tb();
    reg H1, H2, B1, B2;
    wire P_structural, P_procedural;
    
    structuralDesign structuralDesign_tb(H1, H2, B1, B2, P_structural);
    proceduralDesign proceduralDesign_tb(H1, H2, B1, B2, P_procedural);
    
    initial begin
            H1 <= 0; H2 <= 0; B1 <= 0; B2 <= 0;
        #10 H1 <= 0; H2 <= 0; B1 <= 0; B2 <= 1;
        #10 H1 <= 0; H2 <= 0; B1 <= 1; B2 <= 0;
        #10 H1 <= 0; H2 <= 0; B1 <= 1; B2 <= 1;
        #10 H1 <= 0; H2 <= 1; B1 <= 0; B2 <= 0;
        #10 H1 <= 0; H2 <= 1; B1 <= 0; B2 <= 1;
        #10 H1 <= 0; H2 <= 1; B1 <= 1; B2 <= 0;
        #10 H1 <= 0; H2 <= 1; B1 <= 1; B2 <= 1;
        #10 H1 <= 1; H2 <= 0; B1 <= 0; B2 <= 0;
        #10 H1 <= 1; H2 <= 0; B1 <= 0; B2 <= 1;
        #10 H1 <= 1; H2 <= 0; B1 <= 1; B2 <= 0;
        #10 H1 <= 1; H2 <= 0; B1 <= 1; B2 <= 1;
        #10 H1 <= 1; H2 <= 1; B1 <= 0; B2 <= 0;
        #10 H1 <= 1; H2 <= 1; B1 <= 0; B2 <= 1;
        #10 H1 <= 1; H2 <= 1; B1 <= 1; B2 <= 0;
        #10 H1 <= 1; H2 <= 1; B1 <= 1; B2 <= 1;
    end

endmodule
