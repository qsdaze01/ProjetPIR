all: aubiopitch

aubiopitch : aubiopitch.o utils.o pitch.o
	gcc -Wall aubiopitch.o utils.o pitch.o -o aubiopitch

a_weighting.o : a_weighting.c lib/a_weighting.h lib/aubio_priv.h lib/types.h lib/fvec.h lib/lvec.h lib/filter.h
	gcc -Wall -c a_weighting.c -o a_weighting.o

awhitening.o : awhitening.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/awhitening.h
	gcc -Wall -c awhitening.c -o awhitening.o

beattracking.o : beattracking.c lib/aubio_priv.h lib/fvec.h lib/mathutils.h lib/beattracking.h
	gcc -Wall -c beattracking.c -o beattracking.o

biquad.o : biquad.c lib/biquad.h lib/aubio_priv.h lib/fvec.h lib/lvec.h lib/filter.h
	gcc -Wall -c biquad.c -o biquad.o

cvec.o : cvec.c lib/aubio_priv.h lib/cvec.h
	gcc -Wall -c cvec.c -o cvec.o

c_weighting.o : c_weighting.c lib/c_weighting.h lib/aubio_priv.h lib/types.h lib/fvec.h lib/lvec.h lib/filter.h
	gcc -Wall -c c_weighting.c -o c_weighting.o

dct.o : dct.c lib/dct.h lib/aubio_priv.h lib/fvec.h
	gcc -Wall -c dct.c -o dct.o

fft.o : fft.c lib/fft.h lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h
	gcc -Wall -c fft.c -o fft.o

filter.o : filter.c lib/filter.h lib/aubio_priv.h lib/fvec.h lib/lvec.h lib/mathutils.h
	gcc -Wall -c filter.c -o filter.o

filterbank.o : filterbank.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/cvec.h lib/vecutils.h lib/filterbank.h lib/mathutils.h
	gcc -Wall -c filterbank.c -o filterbank.o

filterbank_mel.o : filterbank_mel.c lib/aubio_priv.h lib/fmat.h lib/fvec.h lib/cvec.h lib/filterbank.h lib/filterbank_mel.h lib/mathutils.h
	gcc -Wall -c filterbank_mel.c -o filterbank_mel.o

fmat.o : fmat.c lib/fmat.h lib/aubio_priv.h
	gcc -Wall -c fmat.c -o fmat.o

fvec.o : fvec.c lib/fvec.h lib/aubio_priv.h
	gcc -Wall -c fvec.c -o fvec.o

hist.o : hist.c lib/aubio_priv.h lib/fvec.h lib/scale.h lib/mathutils.h lib/hist.hist
	gcc -Wall -c hist.c -o hist.o

ioutils.o : ioutils.c lib/aubio_priv.h lib/fmat.hist
	gcc -Wall -c ioutils.c -o ioutils.o

jackio.o : jackio.c lib/aubio.h lib/config.h lib/utils.h lib/jackio.h lib/aubio_priv.h
	gcc -Wall -c jackio.c -o jackio.o

log.o : log.c lib/aubio_priv.h lib/log.h 
	gcc -Wall -c log.c -o log.o

lvec.o : lvec.c lib/aubio_priv.h lib/lvec.h
	gcc -Wall -c lvec.c -o lvec.o

mfcc.o : mfcc.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/cvec.h lib/mathutils.h lib/vecutils.h lib/fft.h lib/filterbank.h lib/filterbank_mel.h lib/dct.h lib/mfcc.h
	gcc -Wall -c mfcc.c -o mfcc.o

musicutils.o : musicutils.c lib/aubio_priv.h lib/musicutils.h
	gcc -Wall -c musicutils.c -o musicutils.o

notes.o : notes.c lib/aubio_priv.h lib/fvec.h lib/pitch.h lib/onset.h lib/notes.h 
	gcc -Wall -c notes.c -o notes.o

onset.o : onset.o lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/specdesc.h lib/phasevoc.h lib/awhitening.h lib/peakpicker.h lib/mathutils.h lib/onset.h
	gcc -Wall -c onset.c -o onset.o

parameter.o : parameter.c lib/aubio_priv.h lib/parameter/h
	gcc -Wall -c parameter.c -o parameter.o 

peakpicker.o : peakpicker.c lib/aubio_priv.h lib/fvec.h lib/mathutils.h lib/lvec.h lib/filter.h lib/biquad.h lib/peakpicker.h 
	gcc -Wall -c peakpicker.c -o peakpicker.o

phasevoc.o : phasevoc.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/fft.h lib/phasevoc.h 
	gcc -Wall -c phasevoc.c -o phasevoc.o

pitch.o : pitch.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/lvec.h lib/mathutils.h lib/musicutils.h lib/phasevoc.h lib/filter.h lib/c_weighting.h lib/pitchmcomb.h lib/pitchyin.h lib/pitchfcomb.h lib/pitchschmitt.h lib/pitchyinfft.h lib/pitchyinfast.h lib/pitchspecacf.h lib/pitch.h 
	gcc -Wall -c pitch.c -o pitch.o 

pitchfcomb.o : pitchfcomb.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/musicutils.h lib/fft.h lib/pitchfcomb.h 
	gcc -Wall -c pitchfcomb.c -o pitchfcomb.o 

pitchmcomb.o : pitchmcomb.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/pitchmcomb.h 
	gcc -Wall -c pitchmcomb.c -o pitchmcomb.o

pitchschmitt.o : pitchschmitt.c lib/aubio_priv.h lib/fvec.h lib/pitchschmitt.h
	gcc -Wall -c pitchschmitt.c -o pitchschmitt.o

pitchspecacf.o : pitchspecacf.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/fft.h lib/pitchspecacf.h 
	gcc -Wall -c pitchspecacf.c -o pitchspecacf.o 

pitchyin.o : pitchyin.c lib/aubio_priv.h lib/fvec.h lib/mathutils.h lib/pitchyin.h 
	gcc -Wall -c pitchyin.c -o pitchyin.o 

pitchyinfast.o : pitchyinfast.c lib/aubio_priv.h lib/fvec.h lib/mathutils.h lib/cvec.h lib/fft.h lib/pitchyinfast.h 
	gcc -Wall -c pitchyinfast.c -o pitchyinfast.o 

pitchyinfft.o : pitchyinfft.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/fft.h lib/pitchyinfft.h
	gcc -Wall -c pitchyinfft.c -o pitchyinfft.o 

resampler.o : resampler.c lib/aubio_priv.h lib/fvec.h lib/resampler.h
	gcc -Wall -c resampler.c -o resampler.o

sampler.o : sampler.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/source.h lib/sampler.h 
	gcc -Wall -c sampler.c -o sampler.o 

scale.o : scale.c lib/aubio_priv.h lib/fvec.h lib/scale.h 
	gcc -Wall -c scale.c -o scale.o 

sink.o : sink.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/sink.h lib/sink_apple_audio.h lib/sink_sndfile.h lib/sink_wavwrite.h 
	gcc -Wall -c sink.c -o sink.o 

sink_apple_audio.o : sink_apple_audio.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/sink_apple_audio.h lib/ioutils.h 
	gcc -Wall -c sink_apple_audio.c -o sink_apple_audio.o 

sink_sndfile.o : sink_sndfile.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/sink_sndfile.h lib/ioutils.h 
	gcc -Wall -c sink_sndfile.c -o sink_sndfile.o 

sink_wavwrite.o : sink_wavwrite.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/sink_wavwrite.h lib/ioutils.h 
	gcc -Wall -c sink_wavwrite.c -o sink_wavwrite.o 

source.o : source.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/source.h lib/source_avcodec.h lib/source_apple_audio.h lib/source_sndfile.h lib/source_wavread.h 
	gcc -Wall -c source.c -o source.o 

source_apple_audio.o : source_apple_audio.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/ioutils.h lib/source_apple_audio.h 
	gcc -Wall -c source_apple_audio.c -o source_apple_audio.o 

source_avcodec.o : source_avcodec.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/ioutils.h lib/source_avcodec.h 
	gcc -Wall -c source_avcodec.c -o source_avcodec.o 

source_sndfile.o : source_sndfile.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/ioutils.h lib/source_sndfile.h lib/resampler.h 
	gcc -Wall -c source_sndfile.c -o source_sndfile.o 

source_wavread.o : source_wavread.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/ioutils.h lib/source_wavread.h 
	gcc -Wall -c source_wavread.c -o source_wavread.o 

specdesc.o : specdesc.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/fft.h lib/specdesc.h lib/mathutils.h lib/hist.h 
	gcc -Wall -c specdesc.c -o specdesc.o 

tempo.o : tempo.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/specdesc.h lib/beattracking.h lib/phasevoc.h lib/peakpicker.h lib/mathutils.h lib/tempo.h 
	gcc -Wall -c tempo.c -o tempo.o

tss.o : tss.c lib/aubio_priv.h lib/fvec.h lib/cvec.h lib/mathutils.h lib/tss.h 
	gcc -Wall -c tss.c -o tss.o 

vecutils.o : vecutils.c lib/aubio_priv.h lib/types.h lib/fvec.h lib/cvec.h lib/vecutils.h 
	gcc -Wall -c vecutils.c -o vecutils.o 

wavetable.o : wavetable.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/parameter.h lib/wavetable.h 
	gcc -Wall -c wavetable.c -o wavetable.o 

mathutils.o : mathutils.c lib/aubio_priv.h lib/fvec.h lib/mathutils.h lib/musicutils.h
	gcc -Wall -c mathutils.c -o mathutils.o 

audio_unit.o : audio_unit.c lib/aubio_priv.h lib/fvec.h lib/fmat.h lib/audio_unit.h
	gcc -Wall -c audio_unit.c -o audio_unit.o 

aubiopitch.o : aubiopitch.c lib/utils.h lib/parse_args.h lib/pitch.h
	gcc -Wall -c aubiopitch.c -o aubiopitch.o

utils.o : utils.c lib/utils.h lib/jackio.h
	gcc -Wall -c utils.c -o utils.o

