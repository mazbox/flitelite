#pragma once
#include <memory>
#include <string>
#include <vector>
class FestivalSpeechData;

class FliteLite {
public:
	FliteLite();
	virtual ~FliteLite();
	void createParams(const std::string &sentence);
	int getSentenceDurationInSamples() const;

	void setPitch(float pitch);
	void setFormantShift(float shift);
	void setSpeed(float sp);
	void audioOut(std::vector<float> &outs);
	void setLooping(bool _looping) { looping = _looping; }

	// TODO: not threadsafe!
	void getMceps(double *mceps);
	int getNumMceps();

private:
	float speed	   = 1;
	bool backwards = false;
	void readNextBufferAndUpsample();
	int getInternalFrameSize() const;
	void getNextFrame(std::vector<float> &frame);
	void setSampleRate(double sampleRate);
	int currFrame = 0;
	bool looping  = false;
	std::unique_ptr<FestivalSpeechData> data;
	int upsampleRatio = 3;
	std::vector<float> upsampled, synthOut;
};