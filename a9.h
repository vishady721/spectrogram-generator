#ifndef A10_H_PHUDVTKB
#define A10_H_PHUDVTKB
#include <iostream>
#include <cmath>
#include <complex>  
#include "AudioFile.h"
#include "Image.h"

using namespace std;

// Write your declarations here, or extend the Makefile if you add source
// files
vector<complex<double>> get_samples(string path);
vector<complex<double>> hanning_window(int N);
vector<vector<float>> stft(int hop_size, int window_size, vector<complex<double>> signal);
void fft(vector<complex<double>>& x);
Image bitmap_to_spectrogram(vector<vector<float>> imaginfo);


#endif /* end of include guard: A10_H_PHUDVTKB */

