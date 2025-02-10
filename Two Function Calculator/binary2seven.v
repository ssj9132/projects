module binary2seven (
input [3:0] BIN,
output reg [0:6] SEV);
always @ (BIN) begin
case (BIN)
4'b0000: SEV = 7'b0000001; //0
4'b0001: SEV = 7'b1001111; //1
4'b0010: SEV = 7'b0010010; //2
4'b0011: SEV = 7'b0000110; //3
4'b0100: SEV = 7'b1001100; //4
4'b0101: SEV = 7'b0100100; //5
4'b0110: SEV = 7'b0100000; //6
4'b0111: SEV = 7'b0001111; //7
4'b1000: SEV = 7'b0000000; //8
4'b1001: SEV = 7'b0001100; //9
4'b1010: SEV = 7'b0001000; //A
4'b1011: SEV = 7'b1100000; //b
4'b1100: SEV = 7'b0110001; //C
4'b1101: SEV = 7'b1000010; //d
4'b1110: SEV = 7'b0110000; //E
4'b1111: SEV = 7'b0111000; //F
endcase
end
endmodule
