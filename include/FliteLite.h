#pragma once
#include <memory>
#include <string>
#include <vector>
class FestivalSpeechData;

class FliteLite {
public:
	FliteLite(const std::string &sentence, bool insertSilence = true);
	virtual ~FliteLite();
	
	int getSentenceDurationInSamples() const;

	void setPitch(float pitch);
	void setFormantShift(float shift);
	void setSpeed(float sp);
	void audioOut(std::vector<float> &outs);
	void setLooping(bool _looping) { looping = _looping; }

	// TODO: not threadsafe!
	void getMceps(double *mceps);
	static int getNumMceps();

	static std::vector<double> convertMcepsToSpectrum(const std::vector<double> &mceps);
private:
	void createParams(const std::string &sentence, bool insertSilence = true);
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
