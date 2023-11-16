#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"
#include "AudioLibs/AudioSourceLittleFS.h"
#include "AudioCodecs/CodecMP3Helix.h"

using namespace audio_tools;  

//const char *startFilePath="/mp3_192k";
const char *startFilePath="/mp3_32k";
const char* ext="mp3";

AudioSourceLittleFS source(startFilePath, ext);

A2DPStream out;
MP3DecoderHelix decoder;
AudioPlayer player(source, out, decoder);

void setup() {
  Serial.begin(115200);

  //setCpuFrequencyMhz(240);
  Serial.print("CPU Freq = ");
  Serial.print(getCpuFrequencyMhz());
  Serial.println(" MHz");
  Serial.print("XTAL Freq = ");
  Serial.print(getXtalFrequencyMhz());
  Serial.println(" MHz");
  Serial.print("APB Freq = ");
  Serial.print(getApbFrequency());
  Serial.println(" Hz");
  
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);
  
  auto cfg = out.defaultConfig(TX_MODE);
  cfg.name = "Totally Real Speaker";
  out.begin(cfg);

  decoder.setMaxFrameSize(107);  //  improves 32k

  // setup player
  //player.setSilenceOnInactive(true);
  player.setAutoFade(false);
  player.setVolume(0.8);
  player.begin();

}

void loop() {
  player.copy();
}
