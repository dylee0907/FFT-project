Top : stftTest.m
1. chopen etude op.25 no11 파일을 8192Hz로 10초간 Resampling
2. Resampling 된 data를 1024point, 50% overlap으로 STFT
3. power spectogram 출력

/////////////////////////////////////////////////////
// 수정사항
// 2022-07-15

1. Spectogram의 Y축을 normal형태로 교체
2. Power Sectrum의 각 시간 smaple에 대한 Density를 Spectogram으로 출력
* Gaussian probability density function을 구하여 사용하였음

/////////////////////////////////////////////////////
// 수정사항
// 2022-07-16

1. drawnow 기능을 이용하여 time index마다 FFT결과를 출력

/////////////////////////////////////////////////////
// Error
// 2022-08-08
