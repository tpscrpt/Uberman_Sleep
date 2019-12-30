#include <math.h>

// 1. Load raw heart rate data into heart rate collection
// 2. Get valid interval (start -> end in single case)
// 3. Crop heart rate collection to valid interval
// 4. Write to file (cropped)
// 5. Interpolate and normalize cropped data
// Basically, linearly fill gaps of more than 1 second between each data point
// 6. Convolve interpolated heart rate with window size (10 * 30s - 15) -- 300s = 5 mins -  30 = 4 mins 30s on each side
// y = y - np.mean(y)
// box = arr(WINDOW_SIZE, 1).elems / WINDOW_SIZE
// mu1 = int(WINDOW_SIZE / 2)
// sigma1 = 120
// mu2 = int(WINDOW_SIZE / 2)
// sigma2 = 600
// scalar = 0.75
/*
  for ind in range(0, box_pts):
    box[ind] = np.exp(-1 / 2 * (((ind - mu1) / sigma1) ** 2)) - scalar * np.exp(
        -1 / 2 * (((ind - mu2) / sigma2) ** 2))

*/

void convolve_with_dog(float* interpolated_hr, int length, int box_pts) {
  float accum = 0;

  for (int i = 0; i < length; i ++)
    accum += interpolated_hr[i];

  float mean = accum / length;

  for (int i = 0; i < length; i ++) 
    interpolated_hr[i] = interpolated_hr[i] / mean;

  float box[box_pts];

  for (int i = 0; i < length; i ++)
    box[i] = 1 / box_pts;

  int mu1, mu2 = (int)(box_pts / 2);
  int sigma1 = 120;
  int sigma2 = 600;
  float scalar = 0.75;

  for (int i = 0; i < box_pts; i ++) {
    box[i] =    exp(-1/2 * pow((i - mu1) / sigma1, 2)) - 
      (scalar * exp(-1/2 * pow((i - mu2) / sigma2, 2)));
  
  }
}
// I have no clue how to manage memory in c. At all. Everything is so confusing to me. I don't even know all the required syntax. Darnit.
int main() {
  return 0;
}

struct HeartRateCollection {
  int     subject_id;
  float** values;
  int**   timestamps;
};