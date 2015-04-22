#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100.0 //read from file samples per second
#define DISPLAY_RATE 10.0//updates per second
#define DISPLAY_MOD 50.0//recommended 50.0
#define DISPLAY_STEPS 4.0//set to 4.0 for led grid, 50.0 for computer

void importFreq(double refine[], int songLength);
void playDisplay(double refine[], int songLength);
void refineArray(double array[], int length);
double minFreq(double array[]);
double maxFreq(double array[]);

int main(void)
{
    int songLength;//(DISPLAY_RATE)*(length in seconds)

    //songLength = 20 * SAMPLE_RATE;//test
    scanf("%d\n", &songLength);//real

    songLength = songLength / SAMPLE_RATE * DISPLAY_RATE;

    double refineFreq[songLength];

    importFreq(refineFreq, songLength);

    refineArray(refineFreq, songLength);

    playDisplay(refineFreq, songLength);

    printf("End");

    return 0;
}

void importFreq(double refine[], int songLength){//takes the average of the song volume over a sections that are 1/DISPLAY_RATE seconds

    srand(time(NULL));

    int i, j;
    double rawAvg=0.0;
    double rawImport;

    for(i=0;i< songLength;i++){
        for(j=0;j<SAMPLE_RATE/DISPLAY_RATE;j++){
            //rawImport += (double)(rand()%5-rand()%5);//test (double)rand()
            scanf("%lf\n", &rawImport);//real
            rawAvg += fabs(rawImport);
        }

        refine[i] = (rawAvg / (SAMPLE_RATE/DISPLAY_RATE));
        rawAvg =0.0;
    }
}

void playDisplay(double refine[], int songLength){//prints stars based on the refined array and DISPLAY constants
    int i = 0, j = 0;
    double t = clock()/((double)CLOCKS_PER_SEC);

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
}

double minFreq(double array[]){//finds the min of the array
    int i;
    double min;

    for(i=0;array[i]!= '\0';i++){
        if(min > array[i]) min = array[i];
    }

    return min;
}

double maxFreq(double array[]){//finds the max of the array
    int i;
    double max;

    for(i=0;array[i]!= '\0';i++){
        if(max < array[i]) max = array[i];
    }

    return max;
}

void refineArray(double array[], int length){//converts array to have a range from 0 to DISPLAY_STEPS
    int i;
    double min = minFreq(array);
    double max = maxFreq(array);

    double difference = max - min;
    double mod = difference/DISPLAY_STEPS;

    for(i=0;i<length;i++){
        array[i]-=min;
        array[i]+=(difference/10);
        array[i]/=mod;
    }
}
