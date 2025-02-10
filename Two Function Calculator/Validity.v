module Validity
(
	input [15:0] KP, // {[15:12], [11:8], [7:4], [3:0]} BCD
	output reg LED
);
// x > 127
// (KP[11:8] > 1 && KP[]

always @(*)
	begin
		 
		 if(KP[11:8] > 1)
			   LED = 1;
				
		 else if(KP[11:8] == 1)
			begin if(KP[7:4] > 2)
				LED = 1;
			else if(KP[7:4] == 2)
				begin if(KP[3:0] > 7)
					LED = 1;
				else
					LED = 0; end
			
			else
				LED = 0; end

		 else 
			LED = 0;
		 
		 
			

	end

endmodule