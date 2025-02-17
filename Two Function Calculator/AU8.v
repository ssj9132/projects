module AU8
(
	input [7:0] X,											// (DO NOT MODIFY LINE)
	input InA, InB, Out, Clear, Add_Subtract,		// (DO NOT MODIFY LINE)
	output [7:0] S,									// (DO NOT MODIFY LINE)
	output [3:0] Flags,									// (DO NOT MODIFY LINE)
	output [0:6] HEX2, HEX1, HEX0	,
	output [7:0]Aout// (DO NOT MODIFY LINE)
);

wire [7:0] Bout, Rout;							// (DO NOT MODIFY LINE)
wire [3:0] Fout;											// (DO NOT MODIFY LINE)

// * Instantiate 8-bit NBitRegister (RegisterA) using X *
	NBitRegister #(4'd8) regA //8-bit
	(
		.D(X) , // Register A input
		.CLK(InA) , // Register A load
		.CLR(Clear) , // Register A clear
		.Q(Aout) // Register A output
	);
// * Instantiate 8-bit NBitRegister (RegisterB) using X *
	NBitRegister #(4'd8) regB //8-bit
	(
		.D(X) , // Register B input
		.CLK(InB) , // Register B load
		.CLR(Clear) , // Register B clear
		.Q(Bout) // Register B output
	);

// * Instantiate 8-bit RippleCarryAdderStructural (RCA) *
	RippleCarryAdder RippleCarryAdder_inst
	(
		.A(Aout) ,	// input [7:0] A_sig
		.B(Bout) ,	// input [7:0] B_sig
		.Add_Subtract(Add_Subtract) ,	// input  Add_Subtract_sig
		.S(S) ,	// output [7:0] S_sig
		.Flags(Flags) 	// output [3:0] Flags_sig
	);

// * Instantiate 4-bit NBitRegister (RegisterCC) using Flags *
	NBitRegister #(3'd4) regCC //4-bit register
	(
	.D(Flags) , // Register CC input
	.CLK(Out) , // Register CC load
	.CLR(Clear) , // Register CC clear
	.Q(Fout) // Register CC output
	);
// * Instantiate 8-bit NBitRegister (RegisterR) using Result *
	NBitRegister #(4'd8) regR //8-bit
	(
		.D(S) , // Register R input
		.CLK(Out) , // Register R load
		.CLR(Clear) , // Register R clear
		.Q(Rout) // Register R output
	);
// * Instantiate 4-bit to 1-hex bin2sev using Rout[3:0] *
	binary2seven binary1
	(
		.BIN(Rout[3:0]) ,	// input [3:0] BIN_sig
		.SEV(HEX0) 	// output [0:6] SEV_sig
	);
// * Instantiate 4-bit to 1-hex bin2sev using Rout[7:4] *
	binary2seven binary2
	(
		.BIN(Rout[7:4]) ,	// input [3:0] BIN_sig
		.SEV(HEX1) 	// output [0:6] SEV_sig
	);
// * Instantiate 4-bit to 1-hex bin2sev using Fout *
	binary2seven binary3
	(
		.BIN(Fout) ,	// input [3:0] BIN_sig
		.SEV(HEX2)	 	// output [0:6] SEV_sig
	);
endmodule
