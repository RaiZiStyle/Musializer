# Table of Contents : 
- [Table of Contents :](#table-of-contents-)
- [Musializer from Tsoding Daily](#musializer-from-tsoding-daily)
- [How it work :](#how-it-work-)
  - [Code structure :](#code-structure-)
  - [Todo :](#todo-)


# Musializer from [Tsoding Daily](https://www.youtube.com/watch?v=Xdbk1Pr5WXU&list=PLpM-Dvs8t0Vak1rrE2NJn8XYEJ5M7-BqT&ab_channel=TsodingDaily)

References : 
- Music : https://www.youtube.com/@nu11_ft
- Raylib
- Veritasium Video on FFT https://www.youtube.com/watch?v=nmgFG7PUHfo&ab_channel=Veritasium

__Current Timestamps video :__ https://youtu.be/Xdbk1Pr5WXU?t=5268

# How it work : 

We have chanel and sample.
We have a pointer (I think it's `*bufferData` but not sure) that contain a string of sample with 2 chanel   
We take either one of the chanel with `int16_t sample = *(int16_t *)&global_frames[i];` since global_frames contain the value we will render/save.   
__Update__ : Starting to use a struct for the string that contain the sample with 2 chanel. We only take the left one.

Example of the string :   
[16][16][16][16][16][16][16][16][16]   
^---^---^---^   
L---R---L---R   

L: Left chanel
R : Right Chanel

## Code structure : 
`main.c` : The code for the application   
`fft.c` : An example on how to implement FFT. Cf Vertasium Video   
`build.sh` : Script to build with or without the debug info for `musializer`   
`*.ogg` : Sample of soung found on the internet.   
`.vscode/` : Folder for Vscode to launch the `build.sh` and debug the ELF


## Todo : 

__VScode Settings__ : 
- [x] Set X11 Variable in the launch to get the windows.
- [ ] Set Debugger work with X11