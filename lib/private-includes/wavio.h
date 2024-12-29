#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include <vector>
using FloatBuffer = std::vector<float>;
#include <vector>
#include <string>

static void ma_pcm_f32_to_s16(void *dst, const void *src, uint64_t count) {
	uint64_t i;

	int16_t *dst_s16	 = (int16_t *) dst;
	const float *src_f32 = (const float *) src;

	for (i = 0; i < count; i += 1) {
		float x = src_f32[i];
		x		= ((x < -1) ? -1 : ((x > 1) ? 1 : x)); /* clip */

		/* The fast way. */
		x = x * 32767.0f; /* -1..1 to -32767..32767 */

		dst_s16[i] = (int16_t) x;
	}
}

bool saveWav(const std::string &path, const FloatBuffer &buff, int numChannels, int sampleRate) {
	drwav outfile;
	drwav_data_format fmt;
	fmt.container	  = drwav_container_riff;
	fmt.format		  = DR_WAVE_FORMAT_PCM;
	fmt.channels	  = numChannels;
	fmt.sampleRate	  = sampleRate;
	fmt.bitsPerSample = 16;
	int numFrames	  = buff.size() / numChannels;
	drwav_init_write_sequential_pcm_frames(&outfile, &fmt, numFrames, nullptr, nullptr, nullptr);
	drwav_init_file_write(&outfile, path.c_str(), &fmt, nullptr);

	std::vector<int8_t> pcmOut(numFrames * numChannels * fmt.bitsPerSample / 8);
	ma_pcm_f32_to_s16(pcmOut.data(), buff.data(), numFrames * numChannels);
	drwav_write_pcm_frames(&outfile, numFrames, pcmOut.data());
	drwav_uninit(&outfile);
	return true;
}

bool loadWav(const std::string &path,
			 FloatBuffer &buff,
			 int *outNumChannels = nullptr,
			 int *outSampleRate	 = nullptr) {
	drwav infile;

	if (!drwav_init_file(&infile, path.c_str(), nullptr)) {
		printf("Can't open file %s for reading\n", path.c_str());
		return false;
	}

	if (outNumChannels) *outNumChannels = infile.fmt.channels;
	if (outSampleRate) *outSampleRate = infile.fmt.sampleRate;

	buff.resize(infile.totalPCMFrameCount * infile.fmt.channels);
	auto totalNumFramesRead = drwav_read_pcm_frames_f32(&infile, infile.totalPCMFrameCount, buff.data());

	drwav_uninit(&infile);
	return totalNumFramesRead == infile.totalPCMFrameCount;
}
