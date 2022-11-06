What's created.
1. STFT(Short-Time-Fourier-Transform) and Spectrogram Implementation based MATLAB(Radix2 DIT)
2. FFT modeling based C
3. Software Version Spectrogram GUI Implementation based Qt(Now, we find some errors, It will be re-uploaded after fixed).
4. binaryConverter, boundaryGenerator, Resmapler, TwiddleGenerator Implementation for Data Processing with C/MATLAB
5. Hardware Version Spectrogram GUI Implementation based Qt(FPGA communicate with PC for UART).
6. RTL level INPLACE_FFT Architecture Implementation based Verilog HDL and We use Quartus IP for FPU.

In-Place FFT Architecture are designed by L. G. Johnson's Conflict Free Memory Addressing for Dedicated FFT Hardware.
Johnson handled DIT architecture but we implemented DIF architecture.
Compared two architecture(johnson's and Our's), you can understand In-Place very well.

Now, Our architecture is setted on FFT-Point : 32, Radix : 2
If you want to more FFT-Point, Just convert some parameters and change ADDRgen.v(initiate more ADDRgen_element module)
