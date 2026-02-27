# Simple C Calculator

Build and run using the existing VS Code task or with `gcc`:

Windows (MinGW):

```powershell
gcc -g helloworld.c -o helloworld.exe
.\helloworld.exe
```

The program is a simple menu-driven calculator supporting add, subtract, multiply, divide, integer-power, and integer modulo. Enter numbers when prompted. Division/modulo by zero is checked.

Notes:
- The power operation uses an integer exponent function (no libm required).
