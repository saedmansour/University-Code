(*
	==================================================
		Homework #2 Test Examples
	==================================================
*)


(*<test subject="functions type">*)
count_one;
count_three;
curry;
uncurry;
(*</test>*)



fun is_morning(hour)  = (hour >= 6 andalso hour <= 11);
fun is_night(hour)	  = (hour >= 20 andalso  hour <=24);
fun is_midnight(hour) = (hour = 24);

fun divides_by_two(number)   	 = (number mod 2 = 0);
fun divides_by_three(number)     = (number mod 3 = 0); 
fun divides_by_five(number) 	 = (number mod 5 = 0); 

(*<test subject="count_one">*)
count_one is_morning;
it(7);
count_one is_night;
it(22);
count_one is_midnight;
it(24);

count_one is_morning;
it(16);
count_one is_night;
it(12);
count_one is_midnight;
it(23);
(*</test>*)



(*<test subject="count_three">*)
val check_division = count_three divides_by_two divides_by_three divides_by_five;

check_division(2*3*5);
check_division(2*3*7);
check_division(7*13);
check_division(3*5);
check_division(2*17);
(*</test>*)



(*<test subject="curry">*)
fun product(x, y) 		= x * y;
fun add(x, y) 		= x + y;
fun concatenate(str_a, str_b) = str_a ^ str_b;

curry(product);
it 7 6;
curry(add);
it 2 3;
curry(concatenate);
it "Hello, " "World";
(*</test>*)



(*<test subject="uncurry">*)
val product_curried = curry(product);
val add_curried = curry(add);
val concatenate_curried = curry(concatenate);

uncurry(product_curried);
it(7, 6);
uncurry(add_curried);
it(2, 3);
uncurry(concatenate_curried);
it("Hello, ","World");
(*</test>*)




(*
	==================================================
		EXPECTED OUTPUT 
	==================================================
//Notation: "//" means a comment and it is not a real output

//The output is the Expected Output and it is also
//the real test we ran on the program.

	//Questions 1+2 functions test
	//count_one
	val it = fn : (int -> bool) -> int -> int
	//count_three
	val it = fn : (int -> bool) -> (int -> bool) -> (int -> bool) -> int -> int
	//curry
	val it = fn : ('a * 'b -> 'c) -> 'a -> 'b -> 'c
	//uncurry
	val it = fn : ('a -> 'b -> 'c) -> 'a * 'b -> 'c
	
	val is_morning = fn : int -> bool
	val is_night = fn : int -> bool
	val is_midnight = fn : int -> bool
	val divides_by_two = fn : int -> bool
	val divides_by_three = fn : int -> bool
	val divides_by_five = fn : int -> bool
	
	//count_one test
	val it = fn : int -> int
	val it = 1 : int
	val it = fn : int -> int
	val it = 1 : int
	val it = fn : int -> int
	val it = 1 : int
	val it = fn : int -> int
	val it = 0 : int
	val it = fn : int -> int
	val it = 0 : int
	val it = fn : int -> int
	val it = 0 : int
	val check_division = fn : int -> int
	
	//count_three test
	val it = 3 : int
	val it = 2 : int
	val it = 0 : int
	val it = 2 : int
	val it = 1 : int
	
	val product = fn : int * int -> int
	val add = fn : int * int -> int
	val concatenate = fn : string * string -> string
	
	//curry test
	val it = fn : int -> int -> int
	val it = 42 : int
	val it = fn : int -> int -> int
	val it = 5 : int
	val it = fn : string -> string -> string
	val it = "Hello, World" : string
	
	//uncurry test
	val product_curried = fn : int -> int -> int
	val add_curried = fn : int -> int -> int
	val concatenate_curried = fn : string -> string -> string
	val it = fn : int * int -> int
	val it = 42 : int
	val it = fn : int * int -> int
	val it = 5 : int
	val it = fn : string * string -> string
	val it = "Hello, World" : string

*)