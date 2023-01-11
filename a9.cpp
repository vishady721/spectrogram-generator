#include <iostream>
#include "AudioFile.h"
#include "a9.h"

using namespace std;

// Write your implementations here, or extend the Makefile if you add source
// files

vector<complex<double>> get_samples(string path) {
    AudioFile<double> audioFile;
    audioFile.load(path);
    int numSamples = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();
    vector<complex<double>> samples;
    for (int i = 0; i < numSamples; i++) {
        double avg = 0;
        for (int j = 0; j < numChannels; j++) {
            avg += audioFile.samples[j][i];
        }
        samples.push_back(complex<double>(avg/(numChannels), 0));
    }
    return samples;
}

vector<complex<double>> hanning_window(int N) {
    vector<complex<double>> window;
    for (int i = 0; i < N; i++) {
        double hann = 0.5*(1 - cos(M_PI*2*((1.0*i)/N)));
        window.push_back(complex<double>(hann, 0));
    }
    return window;
}

vector<vector<float>> stft(int hop_size, int window_size, vector<complex<double>> signal) {
    vector<complex<double>> hann = hanning_window(window_size);
    vector<vector<float>> imag_info;
    int range_i = ceil(signal.size()/hop_size);
    for (int i = 0; i <= range_i; i++) {
        vector<complex<double>> windowed;
        for (int j = 0; j < window_size; j++) {
            if (i*hop_size + j < signal.size()) {
                windowed.push_back(hann[j]*signal[i*hop_size + j]);
            }
        }
        fft(windowed);
        vector<float> logmagnitudes;
        for (int k = 0; k < hop_size; k++) {
            float logmag = 10*log10(pow(real(windowed[k]), 2) + pow(10, -5));
            logmagnitudes.push_back(logmag);

        }
        imag_info.push_back(logmagnitudes);
    }
    return imag_info;
}

void fft(vector<complex<double>>& x) {
    const size_t N = x.size();
    if (N <= 1) return;

    vector<complex<double>> even;
    vector<complex<double>> odd;
    for (int i = 0; i < N-1; i+=2) {
        even.push_back(x[i]);
        odd.push_back(x[i+1]);
    }
    fft(even);
    fft(odd);

    for (size_t k = 0; k < N/2; ++k) {
        complex<double> t = polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

Image bitmap_to_spectrogram(vector<vector<float>> imaginfo) {
    vector<float> all1;
    for (int i = 0; i < imaginfo.size(); i++) {
        for (int j = 0; j < imaginfo[i].size(); j++) {
            all1.push_back(imaginfo[i][j]);
        }
    }
    sort(all1.begin(), all1.end());
    Image spectrogram = Image(imaginfo.size(), imaginfo[0].size()/2, 3);
    for (int x = 0; x < imaginfo.size(); x++) {
        for (int y = 0; y < imaginfo[x].size()/2; y++) {
            if (imaginfo[x][y] <= all1[2*floor(all1.size()/7)]) {
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 0) = 0;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 1) = 0;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 2) = 0;
                
            }
            else if (imaginfo[x][y] <= all1[4*floor(all1.size()/7)]) {
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 0) = 219/255;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 1) = 204/255;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 2) = 255/255;
            }
            else if (imaginfo[x][y] <= all1[6*floor(all1.size()/7)]) {
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 0) = 255/255;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 1) = 227/255;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 2) = 251/255;
            }
            
            else {
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 0) = 1;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 1) = 1;
                spectrogram(x, imaginfo[x].size()/2 - 1 - y, 2) = 1;
            }
            
        }
    }
    return spectrogram;
}



