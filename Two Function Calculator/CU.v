module CU
(
	input trig,
	input Clk,
	input ClrE,
	input ClrA,
	input [3	:0] value,

	output reg Reset,
	output reg LoadA,
	output reg LoadB,
	output reg AddSub,
	output reg LoadR,
	output reg IUAU,
	output [2:0] debug
);

	reg [2:0] state;
	wire OneHz_sig;
	parameter S0 = 3'b000, S1 = 3'b001, S2 = 3'b010, S3 = 3'b011, S4 = 3'b100, S5 = 3'b101, S6 = 3'b110;
	
	assign debug = state;

	
	OneHzClock OneHzClock_inst
(
	.clock(Clk) ,	// input  clock_sig
	.reset(~Reset) ,	// input  reset_sig
	.OneHz(OneHz_sig) 	// output  OneHz_sig
);
	always @ (posedge Clk, negedge ClrA) // Sequential Block
		if (ClrA == 0) state <= S0;
		else begin
			case (state)
				S0: state <= S1;
				S1: if (value == 4'hA) begin AddSub =0;state <= S2;end else if (value == 4'hB) begin AddSub =1;state <= S2;end else begin state <= S1;end
				S2: state <= S3;
				S3: state <= S4;
				S4: if (value == 4'hF) begin state <=S5; end else begin state <= S4; end
				S5: state <= S6;
				S6: state <= S6;
			endcase
		end
		
	always @ (*) // Combinational
		case(state)
			S0:begin
				Reset =0; LoadA =1; LoadB = 1;LoadR = 1; IUAU = 0;
				end
			S1:begin
				Reset =1; LoadA =1; LoadB = 1;LoadR = 1; IUAU = 0;
				end
				
			S2:begin
				Reset =1; LoadA =0; LoadB = 1;LoadR = 1; IUAU = 0;
				end
				
			S3:begin
				Reset =0; LoadA =1; LoadB = 1;LoadR = 1; IUAU = 0;
				end
			S4:begin
				Reset =1; LoadA =1; LoadB = 1;LoadR = 1; IUAU = 0;
				end
				
			S5:begin
				Reset =1; LoadA =1; LoadB = 0;LoadR = 1; IUAU = 0;
				end
			S6:begin
				Reset =1; LoadA =1; LoadB = 1; LoadR = 0; IUAU = 1;
				end
		endcase

endmodule

