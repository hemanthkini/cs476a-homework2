
#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Drum.h"
#include <string>

// Note and frequency mappings. Used to programatically build buttons.
std::string notes[] = { "A2", "C3", "D3", "E3", "G3", "A3", "C4", "D4" };
float frequencies[] = { 110.000, 130.813, 146.832, 164.814, 195.998, 220.000, 261.626, 293.665 };

class TronLookAndFeel : public LookAndFeel_V3
{
public:
	TronLookAndFeel()
	{

	}
	// Make a TRON slider.
	void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider &s) override {
		// Outline
		g.setColour(Colours::limegreen);
		float centery = y + ((float)height / 2.0);
		float height_of_slider_index = 0.8; //Fill up 0.3 of our available height space for the slider.
		float top_left = centery - (((float)height / 2.0) * height_of_slider_index);
		float height_of_slider = height_of_slider_index * height;
		g.drawRect((float)x, top_left, (float)width, height_of_slider);

		// Fill in the slider.
		g.fillRect((float)x, top_left, sliderPos - minSliderPos, height_of_slider);


	}

	// Make a TRON button
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override {
		Rectangle<int> buttonArea = button.getLocalBounds();
		g.setColour(Colours::limegreen);
		g.drawRect(buttonArea);
		
		// Fill the button in when pressed.
		if (isButtonDown) {
			g.fillRect(buttonArea);
		}
	}
};

//==============================================================================




//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class MainContentComponent :
	public AudioAppComponent,
	private Slider::Listener,
	private TextButton::Listener
{
public:
	//==============================================================================
	MainContentComponent()
	{
		// Initialize frequency and harmonicdecay sliders.

		filterFreqSlider.setSliderStyle(Slider::LinearHorizontal);
		filterFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		addAndMakeVisible(filterFreqSlider);
		filterFreqSlider.setRange(200.0, 400.0);
		filterFreqSlider.addListener(this);
		filterFreqSlider.setLookAndFeel(&otherLookAndFeel);

		
		harmonicDecaySlider.setSliderStyle(Slider::LinearHorizontal);
		harmonicDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		addAndMakeVisible(harmonicDecaySlider);
		harmonicDecaySlider.addListener(this);
        
        harmonicDecaySlider.setRange(0.1, 0.8);
		harmonicDecaySlider.setLookAndFeel(&otherLookAndFeel);

        // Set the text to be white.
		otherLookAndFeel.setColour(noteButtons[0].textColourOffId, Colours::white);
		otherLookAndFeel.setColour(noteButtons[0].textColourOnId, Colours::white);

        // Programatically build all text buttons.
		for (int i = 0; i < 8; i++) {
            noteText[i] = notes[i];
            Logger::outputDebugString(noteText[i]);
			noteButtons[i].setButtonText(noteText[i]);
			addAndMakeVisible(noteButtons[i]);
			noteButtons[i].setLookAndFeel(&otherLookAndFeel);
			noteButtons[i].addListener(this);
		}


		nChans = 2;
		setAudioChannels(0, nChans); // no inputs, two outputs
		setSize(600, 430);

		audioBuffer = new float*[nChans];
	}

	~MainContentComponent()
	{

		shutdownAudio();

		delete[] audioBuffer;
	}

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
	{
		samplingRate = sampleRate;
		blockSize = samplesPerBlockExpected;

		drum.init(sampleRate); // initializing the Faust module
		drum.buildUserInterface(&drumControl); // linking the Faust module to the controler

        // Print the list of parameters address of "drum"
        // To get the current (default) value of these parameters, drumControl.getParamValue("paramPath") can be used
		for (int i = 0; i<drumControl.getParamsCount(); i++) {
			Logger::outputDebugString(drumControl.getParamAdress(i));
			Logger::outputDebugString("\n");
		}
        
        // Initialize gain, and a 'nice-sounding' q value.
        drumControl.setParamValue("/Inst/FM/gain", 1.0);
        drumControl.setParamValue("/Inst/filter/filterq", 1.5);
	}

	void releaseResources() override
	{
	}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		// getting the audio output buffer to be filled
		audioBuffer[0] = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

		drum.compute(blockSize, NULL, audioBuffer); // computing one block with Faust
        
        // Hacky way of ensuring our buttons work
        drumControl.setParamValue("/Inst/FM/gate", 0.0);
	}

	void resized() override
	{
		// placing the UI elements in the main window
		// getWidth has to be used in case the window is resized by the user
		const int sliderLeft = 10;
		filterFreqSlider.setBounds(sliderLeft, 10, getWidth() - sliderLeft - 20, 60);
		harmonicDecaySlider.setBounds(sliderLeft, 90, getWidth() - sliderLeft - 20, 60);
        
        // Programmatically create two rows of buttons
		for (int i = 0; i < 4; i++) {
			noteButtons[i].setBounds(sliderLeft + i * 150 + 9, 180, 100, 100);
			noteButtons[i + 4].setBounds(sliderLeft + i * 150 + 9, 310, 100, 100);
		}

	}
    // Set the filter and harmonic decay slider values.
	void sliderValueChanged(Slider* slider) override
	{
        if (slider == &filterFreqSlider) {
            drumControl.setParamValue("/Inst/filter/filterfreq", slider->getValue());
        
        } else if (slider == &harmonicDecaySlider) {
            drumControl.setParamValue("/Inst/FM/harmonicdecay", slider->getValue());
        }
	}

	void buttonClicked(Button* button) override
	{

        // Programmatically identify which button was pressed...
        int index;
        for (index = 0; index < 8; index++) {
            if (button->getButtonText().equalsIgnoreCase(noteText[index])) {
                break;
            }
        }

        // ...and set the frequency of that button.
        drumControl.setParamValue("/Inst/FM/freq", frequencies[index]);
        
        // Activate the drum synth.
        drumControl.setParamValue("/Inst/FM/gate", 1.0);
        
        
	}


private:
	Drum drum; // the Faust module (Drum.h)
	MapUI drumControl; // used to easily control the Faust module (Drum.h)

	// UI Elements
	TronLookAndFeel otherLookAndFeel;
	Slider filterFreqSlider;
	Slider harmonicDecaySlider;
	TextButton noteButtons[8];
    String noteText[8];

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)

	// Global variables
	float gain;
	int onOff, samplingRate, nChans, detuneModSwitch, blockSize;


	float** audioBuffer; // multichannel audio buffer used both for input and output

};

Component* createMainContentComponent() { return new MainContentComponent(); }

#endif  // MAINCOMPONENT_H_INCLUDED
