/*
 * Sketch using a modified Mozzi SampleHuffman class to play an audio sample
 * at the press of the button (when pin D4 is held low.)
 *
 * Plays classic Wilhelm scream https://en.wikipedia.org/wiki/Wilhelm_scream
 * Downloaded from https://archive.org/details/WilhelmScreamSample
 * Downsampled using Audacity to fit within flash memory of an Arduino
 *
 * Mozzi library released by Tim Barrass under CC-BY-NC-SA
 * This sketch released by Roger Cheng under MIT License
 */

#include <MozziGuts.h>
#include "SampleHuffman.h"
#include "wilhelm.h"

SampleHuffman wilhelm(wilhelm_scream_SOUNDDATA,wilhelm_scream_HUFFMAN,wilhelm_scream_SOUNDDATA_BITS);

#define PLAY_PIN 4

boolean playing;

void setup() {
  pinMode(PLAY_PIN, INPUT_PULLUP);

  playing = false;
}

// If playing, stop playing if sample is complete.
void updateControl(){
  if (playing) {
    if (wilhelm.complete()) {
      playing = false;
      stopMozzi();
    }
  }
}

int updateAudio(){
  return wilhelm.next();
}

void loop() {
  if (playing) {
    audioHook();
  } else {
    if (digitalRead(PLAY_PIN) == LOW) {
      // As soon as we see pin low, we start playing.
      // Since we don't check again until sample is done,
      // duration of sample is effectively our debounce period.
      wilhelm.start();
      playing = true;
      startMozzi();
    }
  }
}
