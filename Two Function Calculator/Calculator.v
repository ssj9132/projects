module Calculator 
(
	input ClearE,
	input ClearA,
	input Clk,
	input [3:0] A,
	output [3:0] B,
	output V,
	output [3:0] F,
	output [0:6] HEX0,
	output [0:6] HEX1,
	output [0:6] HEX2,
	output HEX3,
	output [7:0] debug
	
);
wire Reset;
wire [7:0] Out;
wire [7:0] X; 
wire [7:0] S;
wire [3:0] Val;
wire LdA;
wire LdB;
wire LdR;
wire AddSub;
wire IUAU;
wire trig; 
IU IU_inst
(
	.clock(Clk) ,	// input  clock_sig
	.clear(Reset & ClearE) ,	// input  clear_sig
	.Row(A) ,	// input [3:0] Row_sig
	.Col(B) ,	// output [3:0] Col_sig
	.LEDR(X) ,	// output [7:0] LEDR_sig
	.LED(V),	// output  LED_sig
	.trig(trig),
	.Val(Val)
);


AU8 AU8_inst
(
	.X(X) ,	// input [7:0] X_sig
	.InA(~LdA) ,	// input  InA_sig
	.InB(~LdB) ,	// input  InB_sig
	.Out(~LdR) ,	// input  Out_sig
	.Clear(ClearA) ,	// input  Clear_sig
	.Add_Subtract(AddSub) ,	// input  Add_Subtract_sig
	.S(S) ,	// output [7:0] S_sig
	.Flags(F) ,	// output [3:0] Flags_sig
	.Aout()
);

OU OU_inst
(
	.TC(Out) ,	// input [7:0] TC_sig
	.HEX0(HEX0) ,	// output [0:6] HEX0_sig
	.HEX1(HEX1) ,	// output [0:6] HEX1_sig
	.HEX2(HEX2) ,	// output [0:6] HEX2_sig
	.HEX3_g(HEX3) 	// output  HEX3_g_sig
);

CU CU_inst
(
	.Clk(Clk) ,	// input  Clk_sig
	.ClrE(ClearE) ,	// input  ClrE_sig
	.ClrA(ClearA) ,	// input  ClrA_sig
	.value(Val) ,	// input [3:0] value_sig
	.Reset(Reset) ,	// output  Reset_sig
	.LoadA(LdA) ,	// output  LoadA_sig
	.LoadB(LdB) ,	// output  LoadB_sig
	.AddSub(AddSub) ,	// output  AddSub_sig
	.LoadR(LdR) ,	// output  LoadR_sig
	.IUAU(IUAU) ,	// output  IUAU_sig
	.debug(debug)
);
assign Out = IUAU? S: X;
endmodule 