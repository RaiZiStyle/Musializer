# Musializer from [Tsoding Daily](https://www.youtube.com/watch?v=Xdbk1Pr5WXU&list=PLpM-Dvs8t0Vak1rrE2NJn8XYEJ5M7-BqT&ab_channel=TsodingDaily)

References : 
- Music : https://www.youtube.com/@nu11_ft
- Raylib
- Veritasium Video on FFT https://www.youtube.com/watch?v=nmgFG7PUHfo&ab_channel=Veritasium

__Current Timestamps video :__ https://youtu.be/Xdbk1Pr5WXU?t=5268

# How it work : 

We have chanel and sample.
We have a pointer (I think it's `*bufferData` but not sure) that contain a string of sample with 2 chanel 
We take either one of the chanel with `int16_t sample = *(int16_t *)&global_frames[i];` since global_frames contain the value we will render/save
__Update__ : Starting to use a struct for the string that contain the sample with 2 chanel

Example of the string :
[16][16][16][16][16][16][16][16][16]
^---^---^---^
L---R---L---R

L: Left chanel
R : Right Chanel

## Todo : 

__VScode Settings__ : 
- [x] Set X11 Variable in the launch to get the windows.
- [ ] Set Debugger work with X11