/*
  Copyright (C) 2003-2009 Paul Brossier <piem@aubio.org>

  This file is part of aubio.

  aubio is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  aubio is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with aubio.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "lib/aubio_priv.h"
#include "lib/types.h"
#include "lib/fvec.h"
#include "lib/lvec.h"
#include "lib/filter.h"
#include "lib/c_weighting.h"

uint_t
aubio_filter_set_c_weighting (aubio_filter_t * f, uint_t samplerate)
{
  uint_t order; lsmp_t *a, *b; lvec_t *as, *bs;

  if ((sint_t)samplerate <= 0) {
    AUBIO_ERROR("aubio_filter: failed setting C-weighting with samplerate %d\n", samplerate);
    return AUBIO_FAIL;
  }
  if (f == NULL) {
    AUBIO_ERROR("aubio_filter: failed setting C-weighting with filter NULL\n");
    return AUBIO_FAIL;
  }

  order = aubio_filter_get_order (f);
  if ( order != 5 ) {
    AUBIO_ERROR ("aubio_filter: order of C-weighting filter must be 5, not %d\n", order);
    return 1;
  }

  aubio_filter_set_samplerate (f, samplerate);
  bs = aubio_filter_get_feedforward (f);
  as = aubio_filter_get_feedback (f);
  b = bs->data, a = as->data;

  /* select coefficients according to sampling frequency */
  switch (samplerate) {

    case 8000:
      b[0] =  6.782173932405135552414776611840352416038513183593750000e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -1.356434786481027110482955322368070483207702636718750000e+00;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  6.782173932405135552414776611840352416038513183593750000e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -6.589092811505605773447769024642184376716613769531250000e-01;
      a[2] = -1.179445664897062595599663836765103042125701904296875000e+00;
      a[3] =  4.243329729632123736848825501510873436927795410156250000e-01;
      a[4] =  4.147270002091348328754349950031610205769538879394531250e-01;
      break;

    case 11025:
      b[0] =  6.002357155402652244546857218665536493062973022460937500e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -1.200471431080530448909371443733107298612594604492187500e+00;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  6.002357155402652244546857218665536493062973022460937500e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -8.705602141280316397242700077185872942209243774414062500e-01;
      a[2] = -9.037199507150940336330791069485712796449661254882812500e-01;
      a[3] =  4.758433040929530011275971901341108605265617370605468750e-01;
      a[4] =  2.987653956523212417373258631414500996470451354980468750e-01;
      break;

    case 16000:
      b[0] =  4.971057193673903418229542694461997598409652709960937500e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -9.942114387347806836459085388923995196819305419921875000e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  4.971057193673903418229542694461997598409652709960937500e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -1.162322939286873690889478893950581550598144531250000000e+00;
      a[2] = -4.771961355734982701548574368644040077924728393554687500e-01;
      a[3] =  4.736145114694704227886745684372726827859878540039062500e-01;
      a[4] =  1.660337524309875301131711466950946487486362457275390625e-01;
      break;

    case 22050:
      b[0] =  4.033381299002754549754001800465630367398262023925781250e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -8.066762598005509099508003600931260734796524047851562500e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  4.033381299002754549754001800465630367398262023925781250e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -1.449545371157945350404361306573264300823211669921875000e+00;
      a[2] = -1.030104190885922088583015465701464563608169555664062500e-02;
      a[3] =  3.881857047554073680828423675848171114921569824218750000e-01;
      a[4] =  7.171589940116777917022972133054281584918498992919921875e-02;
      break;

    case 24000:
      b[0] =  3.786678621924967069745093795063439756631851196289062500e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -7.573357243849934139490187590126879513263702392578125000e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  3.786678621924967069745093795063439756631851196289062500e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -1.529945307555420797029910318087786436080932617187500000e+00;
      a[2] =  1.283553182116208835061854642844991758465766906738281250e-01;
      a[3] =  3.494608072385725350272878131363540887832641601562500000e-01;
      a[4] =  5.217291949300089520802359288609295617789030075073242188e-02;
      break;

    case 32000:
      b[0] =  2.977986488230693340462096330156782642006874084472656250e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -5.955972976461386680924192660313565284013748168945312500e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  2.977986488230693340462096330156782642006874084472656250e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -1.812455387128179218336754274787381291389465332031250000e+00;
      a[2] =  6.425013281155662614452239722595550119876861572265625000e-01;
      a[3] =  1.619857574578579817448087396769551560282707214355468750e-01;
      a[4] =  7.987649713547682189807019881300220731645822525024414062e-03;
      break;

    case 44100:
      b[0] =  2.170085619492190254220531642204150557518005371093750000e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -4.340171238984380508441063284408301115036010742187500000e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  2.170085619492190254220531642204150557518005371093750000e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -2.134674963687040794013682898366823792457580566406250000e+00;
      a[2] =  1.279333533236062692139967111870646476745605468750000000e+00;
      a[3] = -1.495598460893957093453821016737492755055427551269531250e-01;
      a[4] =  4.908700174624683852664386307651511742733418941497802734e-03;
      break;

    case 48000:
      b[0] =  1.978871200263932761398422144338837824761867523193359375e-01;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -3.957742400527865522796844288677675649523735046386718750e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  1.978871200263932761398422144338837824761867523193359375e-01;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -2.219172914052801814932536217384040355682373046875000000e+00;
      a[2] =  1.455135878947171557129536267893854528665542602539062500e+00;
      a[3] = -2.484960738877830532800317087094299495220184326171875000e-01;
      a[4] =  1.253882314727246607977129144728678511455655097961425781e-02;
      break;

    case 88200:
      b[0] =  9.221909851156021020734954163344809785485267639160156250e-02;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -1.844381970231204204146990832668961957097053527832031250e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  9.221909851156021020734954163344809785485267639160156250e-02;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -2.785795902923448696952846148633398115634918212890625000e+00;
      a[2] =  2.727736758747444145711824603495188057422637939453125000e+00;
      a[3] = -1.097007502819661528548067508381791412830352783203125000e+00;
      a[4] =  1.550674356752141103132913713125162757933139801025390625e-01;
      break;

    case 96000:
      b[0] =  8.182864044979756834585771230194950476288795471191406250e-02;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -1.636572808995951366917154246038990095257759094238281250e-01;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  8.182864044979756834585771230194950476288795471191406250e-02;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -2.856378516857566829401093855267390608787536621093750000e+00;
      a[2] =  2.897640237559524045707348705036565661430358886718750000e+00;
      a[3] = -1.225265958339703198376469117647502571344375610351562500e+00;
      a[4] =  1.840048283551226071530493300087982788681983947753906250e-01;
      break;

    case 192000:
      b[0] =  2.784755468532278815940728122768632601946592330932617188e-02;
      b[1] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[2] = -5.569510937064557631881456245537265203893184661865234375e-02;
      b[3] =  0.000000000000000000000000000000000000000000000000000000e+00;
      b[4] =  2.784755468532278815940728122768632601946592330932617188e-02;
      a[0] =  1.000000000000000000000000000000000000000000000000000000e+00;
      a[1] = -3.333298856144166322224009491037577390670776367187500000e+00;
      a[2] =  4.111467536240339448738723149290308356285095214843750000e+00;
      a[3] = -2.222889041651291641699117462849244475364685058593750000e+00;
      a[4] =  4.447204118126878991112960193277103826403617858886718750e-01;
      break;

    default:
      AUBIO_ERROR ( "sampling rate of C-weighting filter is %d, should be one of\
 8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000, 88200, 96000, 192000.\n", 
 samplerate );
      return 1;

  }

  return 0;
}

aubio_filter_t * new_aubio_filter_c_weighting (uint_t samplerate) {
  aubio_filter_t * f = new_aubio_filter(5);
  if (aubio_filter_set_c_weighting(f,samplerate) != AUBIO_OK) {
    del_aubio_filter(f);
    return NULL;
  }
  return f;
}
