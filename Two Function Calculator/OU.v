module OU
(
	input [7:0] TC,
	output [0:6] HEX0,
	output [0:6] HEX1,
	output [0:6] HEX2,
	output HEX3_g
);

wire Sign;
wire [7:0] SM;
wire [3:0] ONES, TENS;
wire [1:0] HUNDREDS;

assign HEX3_g = ~TC[7];

twoSIGN twoSIGN_inst
(
	.A(TC) ,	// input [N-1:0] A_sig
	.B(SM) 	// output [N-1:0] B_sig
);

binary2bcd binary2bcd_inst
(
	.A(SM) ,	// input [7:0] A_sig
	.ONES(ONES) ,	// output [3:0] ONES_sig
	.TENS(TENS) ,	// output [3:0] TENS_sig
	.HUNDREDS(HUNDREDS) 	// output [1:0] HUNDREDS_sig
);

binary2seven Hex0
(
	.BIN(ONES) ,	// input [3:0] BIN_sig
	.SEV(HEX0) 	// output [0:6] SEV_sig
);

binary2seven Hex1
(
	.BIN(TENS) ,	// input [3:0] BIN_sig
	.SEV(HEX1) 	// output [0:6] SEV_sig
);

binary2seven Hex2
(
	.BIN(HUNDREDS) ,	// input [3:0] BIN_sig
	.SEV(HEX2) 	// output [0:6] SEV_sig
);

endmodule