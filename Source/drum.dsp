import("stdfaust.lib");


frequency = hslider("freq",100,100,400, 0.01) : si.smoo;
freqRatio = 1, 1.3, 1.6, 1.85, 2.14, 2.8, 3.17;
gain = 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4;
harmDec = hslider("harmonicdecay",0.5, 0.1, 0.9, 0.01) : si.smoo;
level = hslider("gain",0.7,0,1,0.01) : si.smoo;
filterfreq = hslider("filterfreq", 440, 100, 1000, 0.01) : si.smoo;
filterq = hslider("filterq", 0.5, 0.5, 3, 0.01);
onoff = button("gate");
filter = fi.resonlp(filterfreq, filterq, 0.5);
oscgroup = hgroup("FM",sy.additiveDrum( frequency, freqRatio, gain, harmDec, 0.01, 0.17, onoff) * level);
filtgroup = hgroup("filter", filter);
process = oscgroup : filtgroup;
