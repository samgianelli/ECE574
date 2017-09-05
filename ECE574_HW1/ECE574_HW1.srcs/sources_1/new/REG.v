`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 02:35:56 PM
// Design Name: 
// Module Name: REG
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


module REG(d, Clk, Rst, q);
    parameter DATAWIDTH = 8;
    input [DATAWIDTH - 1 : 0] d;
    input Clk, Rst;
    output reg [DATAWIDTH - 1 : 0] q;
        
    initial begin
        q <= 0;
    end
    
    always @(posedge Clk) begin
        if (Rst == 1'b1) begin
            q <= {DATAWIDTH{1'b0}};
        end
        else begin
            q <= d;
        end
    end   

endmodule
