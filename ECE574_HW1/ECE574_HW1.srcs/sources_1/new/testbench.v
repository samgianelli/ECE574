`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/15/2017 11:40:56 AM
// Design Name: 
// Module Name: testbench
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


module testbench();
    parameter DATAWIDTH = 8;
    reg Clk, Rst, sel;
    reg [DATAWIDTH - 1:0] a, b, sa, sb;
    wire [DATAWIDTH - 1:0] add, sadd, sub, ssub, register, sregister, shl, sshl, shr, sshr, mux, smux, div, sdiv, mod, smod, dec, sdec, inc, sinc;
    wire [2 * DATAWIDTH - 1:0] mul, smul;
    wire lt, gt, eq, slt, sgt, seq;
    
    initial begin
        Clk <= 1'b0;
        forever #50 Clk <= ~Clk;
    end 
    
    ADD#(DATAWIDTH) ADD_0(a, b, add);
    SADD#(DATAWIDTH) SADD_0(a, b, sadd);
    SUB#(DATAWIDTH) SUB_0(a, b, sub);
    SSUB#(DATAWIDTH) SSUB_0(a, b, ssub);
    REG#(DATAWIDTH) REG(a, Clk, Rst, register);
    SREG#(DATAWIDTH) SREG(a, Clk, Rst, sregister);
    COMP#(DATAWIDTH) COMP_0(a, b, gt, lt, eq);
    SCOMP#(DATAWIDTH) SCOMP_0(a, b, sgt, slt, seq);
    MUL#(DATAWIDTH) MUL_0(a, b, mul);
    SMUL#(DATAWIDTH) SMUL_0(a, b, smul);
    SHL#(DATAWIDTH) SHL_0(a, b, shl);
    SSHL#(DATAWIDTH) SSHL_0(a, b, sshl);
    SHR#(DATAWIDTH) SHR_0(a, b, shr);
    SSHR#(DATAWIDTH) SSHR_0(a, b, sshr);
    MUX2x1#(DATAWIDTH) MUX2x1_0(a, b, sel, mux);
    SMUX2x1#(DATAWIDTH) SMUX2x1_0(a, b, sel, smux);
    DIV#(DATAWIDTH) DIV_0(a, b, div);
    SDIV#(DATAWIDTH) SDIV_0(a, b, sdiv);
    MOD#(DATAWIDTH) MOD(a, b, mod);
    SMOD#(DATAWIDTH) SMOD(a, b, smod);
    DEC#(DATAWIDTH) DEC(a, dec);
    SDEC#(DATAWIDTH) SDEC(a, sdec);
    INC#(DATAWIDTH) INC(a, inc);
    SINC#(DATAWIDTH) SINC(a, sinc);
    
    always@(*) begin
        sa = a;
        sb = b;
    end
    
    initial begin
        a = 10;
        b = 2;
        sel = 0;
        #200;
        a = -10;
        b = 2;
        #200;
        a = 10;
        b = -100;
        sel = 1;
        #200;
        a = -90;
        b = -70;
       
        
        
        
    end
    
endmodule
