#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100.0 //read from file samples per second
#define DISPLAY_RATE 10.0
#define DISPLAY_MOD 50.0//recommended 50.0
#define DISPLAY_STEPS 4.0//set to 4.0 for led grid, 50.0 for computer

void importFreq(double refine[], int songLength);
void playDisplay(double refine[], int songLength);
double minFreq(double array[]);
double maxFreq(double array[]);
double avgFreq(double array[]);

void refineArray(double array[], int length);

int main(void)
{
    int songLength;//10*seconds

    //songLength = 20 * SAMPLE_RATE;//test
    scanf("%d\n", &songLength);//real

    songLength = songLength / SAMPLE_RATE * DISPLAY_RATE;

    double refineFreq[songLength];

    importFreq(refineFreq, songLength);

    refineArray(refineFreq, songLength);

    playDisplay(refineFreq, songLength);

    return 0;
}

void importFreq(double refine[], int songLength){//FINISH_ME

    srand(time(NULL));

    int i, j;
    double rawAvg=0.0;
    double rawImport;

    double max, min, average;

    for(i=0;i< songLength;i++){
        for(j=0;j<SAMPLE_RATE/DISPLAY_RATE;j++){//importing sound
            //rawImport += (double)(rand()%5-rand()%5);//test (double)rand()
            scanf("%lf\n", &rawImport);//real import

            rawAvg += fabs(rawImport);
        }
        refine[i] = (rawAvg / (SAMPLE_RATE/DISPLAY_RATE));
        rawAvg =0.0;
    }
    printf("DEBUG: Frequency imported\n");
}

void playDisplay(double refine[], int songLength){
    int i = 0, j = 0;
    double t = clock()/((double)CLOCKS_PER_SEC);
    printf("DEBUG: %lf / %lf\n", minFreq(refine), maxFreq(refine));

    while(i<songLength){
        if(t <= clock()/((double)CLOCKS_PER_SEC) - 1/DISPLAY_RATE){
            for(j=0;j<((int)refine[i])*DISPLAY_MOD/DISPLAY_STEPS;j++){
                printf("*");
            }
            printf("\n");
            i++;

            t = clock()/((double)CLOCKS_PER_SEC);
        }
    }
    printf("DEBUG: end");//test
}

double minFreq(double array[]){
    double min;
    int i;
    for(i=0;array[i]!= '\0';i++){
        if(min > array[i]) min = array[i];
    }
    return min;
}

double maxFreq(double array[]){
    double max;
    int i;
    for(i=0;array[i]!= '\0';i++){
        if(max < array[i]) max = array[i];
    }
    return max;
}

double avgFreq(double array[]){
    double avg;
    int i;
    for(i=0;array[i]!= '\0';i++){
        avg+= array[i];
    }
    avg = avg/i;
    return avg;
}

void refineArray(double array[], int length){
    double min = minFreq(array);
    double max = maxFreq(array);
    double difference = max - min;
    double mod = difference/DISPLAY_STEPS;
    int i;
    for(i=0;i<length;i++){
        array[i]-=min;
    }
    for(i=0;i<length;i++){
        array[i]/=mod;
    }
    printf("DEBUG: avgFreq %lf\n", avgFreq(array));
}
