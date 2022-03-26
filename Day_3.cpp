#include "msoftcon.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
const int CPF=5;
const int maxHorse=7;

class track;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class horse
{
    private:
        const track *ptrTrack;                // Track Pointer
        const int horse_number;               // Horse Numbers
        float finish_time;                    // this horse's finish time
        float distance_run;                    // distance run so far;
    
    public:
        horse(const int n, const track *ptrT):horse_number(n), ptrTrack(ptrT),distance_run(0.0)
        {

        }

        ~horse()
        {   }
        void display_horse(const float elapsed_time);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class track{
    private:
        horse *hArray[maxHorse];
        int total_horse;
        int horse_count;
        const float track_length;
        float elapsed_time;

    public:
        track(float lenT, int nH);
        ~track();
        void display_track();
        void run();
        float get_track_len() const;
};


void horse::display_horse(float elapsed_time)
{
    set_cursor_pos(1+ int(distance_run * CPF), 2+horse_number*2);
    set_color(static_cast<color>(cBLUE+horse_number));

    char horse_char= '0'+static_cast<char>(horse_number);
    putch(' ');putch('\xDB');putch(horse_char);putch('\xDB');
    if(distance_run < ptrTrack->get_track_len()+1.0 / CPF)
    {
        if(rand() % 3)
            distance_run+=0.2F;
        finish_time=elapsed_time;
    }
else
    {
        int mins = int(finish_time)/60;
        int sec=int(finish_time)-mins*60;
        cout<<" Time= *"<<mins<<":"<<sec;
    }
}
//..........................................................................................................
track::track(float lenT, int nH):track_length(lenT),total_horse(nH), horse_count(0), elapsed_time(0.0)
{
    init_graphics();
    total_horse = (total_horse > maxHorse)? maxHorse:total_horse;
    for(int j=0; j<total_horse; j++)
        hArray[j] = new horse(horse_count++, this);

    time_t aTime;
    srand( static_cast<unsigned>(time(&aTime)));
    display_track();

}
//...........................................................................................................
track::~track()
{
    for( int j=0; j<total_horse;j++)
        delete hArray[j];
}
//............................................................................................................
void track::display_track()
{
    clear_screen();

    for( int f=0; f<=track_length; f++)
        {
            for(int r=1; r<=total_horse*2 + 1;r++)
            {
                set_cursor_pos(f*CPF + 5,r);
                if(f==0 || f==track_length)
                    cout<<'\xDE';
                else
                    cout<<'\xB3';
            }
        }
}
//..............................................................................................................

void track::run()
{
    while( !kbhit())
    {
        elapsed_time+=1.75;

        for(int j=0; j<total_horse;j++)
            hArray[j]->display_horse(elapsed_time);
        wait(500);
    }
    getch();
    cout<<endl;
}

//................................................................................................................
float track::get_track_len() const
{ 
    return track_length ; 
}

int main(){
    float length;
    int total;

    cout<<"\n Enter track length (furlongs; 1 to 12): ";
    cin>>length;
    cout<<"\n Enter number of horses (1 to 7): ";
    cin>>total;
    track theTrack(length, total);
    theTrack.run();
    return 0;
}