#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100.0 //read from file samples per second
#define DISPLAY_RATE 10.0
#define DISPLAY_MOD 50.0

void importFreq(double refine[], int songLength);//FINISH_ME
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
            //rawImport++;//test (double)rand()
            scanf("%lf\n", &rawImport);//real import

            rawAvg += fabs(rawImport);
        }

        //refine[i] = ((rawAvg / (SAMPLE_RATE/DISPLAY_RATE)) * DISPLAY_MOD);//previous
        refine[i] = (rawAvg / (SAMPLE_RATE/DISPLAY_RATE));//new TEST_ME
        rawAvg =0.0;
    }
    printf("Frequency imported\n");//test
}

void playDisplay(double refine[], int songLength){
    int i = 0, j = 0;
    double t = clock()/((double)CLOCKS_PER_SEC);
    while(i<songLength){
        if(t <= clock()/((double)CLOCKS_PER_SEC) - 1/DISPLAY_RATE){
            for(j=0;j<refine[i];j++){
                printf("*");
            }
            printf("\n");
            i++;

            t = clock()/((double)CLOCKS_PER_SEC);
        }
    }
    printf("end");//test
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

void refineArray(double array[], int length){//TEST_ME
    double min = minFreq(array);
    double max = maxFreq(array);
    double difference = max - min;
    double mod = difference/50.0;
    int i;
    for(i=0;i<length;i++){
        array[i]-=min;
    }
    for(i=0;i<length;i++){
        array[i]/=mod;
    }
    printf("DEBUG: avgFreq %lf\n", avgFreq(array));//test
}
