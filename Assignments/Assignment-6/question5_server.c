// This is server code, we will create the .so file of this server

int unknown_function(int);   // declaration ONLY (as mordern GCC does not allow)

int addition(int a, int b)
{
    return a + b;
}

int substraction(int a, int b)
{
    return a - b;
}

int broken(int a)
{
    return unknown_function(a);   // unresolved symbol on purpose
}
