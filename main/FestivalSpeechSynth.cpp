#include "FestivalSpeechSynth.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "cst_cg.h"
#include "flite.h"
#ifdef __cplusplus
}
#endif /* __cplusplus */

class VoiceSynthFifo {
public:
	explicit VoiceSynthFifo(size_t capacity)
		: buffer(capacity)
		, head(0)
		, tail(0)
		, size(0)
		, capacity(capacity) {}

	void resize(size_t capacity) {
		this->capacity = capacity;
		buffer.resize(capacity);
	}
	// Write data from a std::vector<float> to the buffer
	void write(const std::vector<float> &data) {
		if (data.size() > availableWriteSpace()) {
			throw std::runtime_error("Not enough space to write to buffer");
		}

		for (float sample: data) {
			buffer[head] = sample;
			head		 = (head + 1) % capacity;
			++size;
		}
	}

	// Get the number of available samples for consuming
	size_t availableToConsume() const { return size; }

	// Consume a number of items and copy to the provided float pointer
	void consume(size_t count, float *out) {
		if (count > size) {
			throw std::runtime_error("Not enough data to consume from buffer");
		}

		for (size_t i = 0; i < count; ++i) {
			out[i] = buffer[tail];
			tail   = (tail + 1) % capacity;
			--size;
		}
	}

private:
	std::vector<float> buffer;
	size_t head; // Write position
	size_t tail; // Read position
	size_t size; // Current number of elements in the buffer
	size_t capacity; // Maximum capacity of the buffer

	// Calculate the available write space
	size_t availableWriteSpace() const { return capacity - size; }
};

class FestivalSpeechData {
public:
	cst_utterance *u = nullptr;
	cst_voice *voice = nullptr;

	StreamingSynthContext *ctx = nullptr;
	VoiceSynthFifo fifo;
	FestivalSpeechData()
		: fifo(64) {}
};

FestivalSpeechSynth::FestivalSpeechSynth() {
	data		= std::make_unique<FestivalSpeechData>();
	data->voice = flite_voice_select(nullptr);
}
FestivalSpeechSynth::~FestivalSpeechSynth() {
	if (data->u != nullptr) {
		delete_utterance(data->u);
	}
}

void FestivalSpeechSynth::createParams(const std::string &sentence) {
	data->u = new_utterance();
	utt_set_input_text(data->u, sentence.c_str());

	utt_init(data->u, data->voice);

	utt_synth(data->u);
	data->ctx = prepareForStreamingSynth(data->u);
	setSampleRate(48000);
	synthOut.resize(getInternalFrameSize());
	upsampled.resize(synthOut.size() * upsampleRatio);
	data->fifo.resize(8192);
}

void FestivalSpeechSynth::setPitch(float pitch) {
	data->ctx->sing	 = true;
	data->ctx->pitch = pitch;
}
void FestivalSpeechSynth::setFormantShift(float shift) {
	// 0.6 to 1.4
	float norm				= shift * 0.5f + 0.5;
	data->ctx->formantShift = 0.6f + (1.f - 0.6f) * norm;
}
void FestivalSpeechSynth::readNextBufferAndUpsample() {
	getNextFrame(synthOut);
	upsampled.resize(synthOut.size()*upsampleRatio);
	for (int i = 0; i < synthOut.size(); i++) {
		for (int k = 0; k < upsampleRatio; k++) {
			upsampled[i * upsampleRatio + k] = synthOut[i];
		}
	}
}
void FestivalSpeechSynth::audioOut(std::vector<float> &outs) {
	while (data->fifo.availableToConsume() < outs.size()) {
		readNextBufferAndUpsample();
		data->fifo.write(upsampled);
	}
	data->fifo.consume(outs.size(), outs.data());
}

void FestivalSpeechSynth::setSpeed(float sp) {
	backwards = sp < 0;
	speed	  = std::clamp(std::abs(sp), 0.01f, 10.f);
}
int FestivalSpeechSynth::getInternalFrameSize() const {
	return data->ctx->frameSizeSamples * speed;
}
void FestivalSpeechSynth::getNextFrame(std::vector<float> &outs) {
	int numFrames = data->ctx->params->num_frames;

	if (currFrame >= numFrames) {
		memset(outs.data(), 0, sizeof(float) * outs.size());
		return;
	}
	data->ctx->vs.fprd = getInternalFrameSize();
	outs.resize(data->ctx->vs.fprd);
	int cf = currFrame;
	if (backwards) {
		cf = numFrames - currFrame - 1;
	}
	synthesizeFrame(data->ctx, cf, outs.data());
	currFrame++;
	if (looping) currFrame %= numFrames;
}

int FestivalSpeechSynth::getSentenceDurationInSamples() const {
	return data->ctx->params->num_frames * getInternalFrameSize() * upsampleRatio;
}
void FestivalSpeechSynth::setSampleRate(double sampleRate) {
	upsampleRatio = std::round(sampleRate / data->ctx->cg_db->sample_rate);
}
