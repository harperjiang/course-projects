program main(input, output);
var a,b,c : integer;
	procedure a1;
	var x : integer;
		procedure b1;
		var a,b,c: integer;
			procedure c1;
			var a,b,c: integer;
			begin (* c1 *)
				
			end;  (* c1 *)
		begin (* b1 *)
			
		end;  (* b1 *)
	begin (* a1 *)
	    a := 105
	end;  (* a1 *)

	procedure a2;
	var b,c: integer;
		procedure b2;
		var a,b,c: integer;
			procedure c2;
			var a,b,c: integer;
			begin (* c2 *)
			     a1	
			end;  (* c2 *)
		begin  (* b2 *)
		    c2
		end;   (* b2 *)
	begin   (* a2 *)
	    a := 300;
	    b2
	end;	(* a2 *)

begin (* main *)
	a2;
	write(a)
end.  (* main *)
