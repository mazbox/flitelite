
#include <stdio.h>
#include "wavio.h"
#include "FestivalSpeechSynth.h"

int main(int argc, char **argv) {
	printf("flite lite\n");

	for (int i = 0; i < 1; i++) {
		FestivalSpeechSynth speaky;
		speaky.createParams("Potato potato. Peanut peanut peanut!");
		//		speaky.createParams(
		//			"ahhee'm a condoor, flying high, Flapping wings across the sky, Got no worries, no, not I, Cause I eat snacks that are old and dry!");
		FloatBuffer buff;
		FloatBuffer outs;
		outs.resize(256);
		speaky.setPitch(50);
		speaky.setSpeed(1);
		speaky.setLooping(true);
		speaky.setFormantShift(-0.5);
		for (int t = 0; t < speaky.getSentenceDurationInSamples() * 4; t += outs.size()) {
			speaky.audioOut(outs);
			buff.insert(buff.end(), outs.begin(), outs.end());
		}
		saveWav("out.wav", buff, 1, 48000);
	}

	return 0;
}
