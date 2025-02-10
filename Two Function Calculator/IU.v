module IU
(
	input clock, clear,
	input [3:0] Row,
	output [3:0] Col,
	output [7:0] LEDR,
	output [3:0] Val,
	output LED, trig
);

wire [15:0] KP;
wire [7:0] SM;
keypad_input keypad_input_inst
(
	.clk(clock) ,	// input  clk_sig
	.reset(clear) ,	// input  reset_sig
	.row(Row) ,	// input [3:0] row_sig
	.col(Col) ,	// output [3:0] col_sig
	.out(KP) ,	// output [DIGITS*4-1:0] out_sig
	.trig(trig),
	.value(Val)
);
BCD2BinarySM BCD2BinarySM_inst
(
	.BCD(KP) ,	// input [15:0] BCD_sig
	.binarySM(SM) 	// output [N-1:0] binarySM_sig
);
twoSIGN twoSIGN_inst
(
	.A(SM) ,	// input [N-1:0] A_sig
	.B(LEDR[6:0]) 	// output [N-1:0] B_sig
);
Validity Validity_inst
(
	.KP(KP) ,	// input [15:0] KP_sig
	.LED(LED) 	// output  LED_sig
);

assign LEDR[7] = SM[7];
endmodule
