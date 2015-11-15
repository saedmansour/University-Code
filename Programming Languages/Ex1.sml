fun count_one f = fn f_param => if(f(f_param:int)) then 1 else 0;

fun count_three fun1 fun2 fun3 = fn param => count_one fun1 param + count_one fun2 param + count_one fun3 param;

fun curry(f) = fn param1 => fn param2 => f(param1, param2);

fun uncurry(f) = fn (param1, param2) => f param1 param2;