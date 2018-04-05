#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* file = fopen ("data_a5.txt", "r");
    int size = 0;
    char ch;
    /**
     * Get size of file , to set array size
     * Count number of lines as we save each Integer in Each line
    */
    do
    {
        ch = fgetc(file);
        if(ch == '\n')
            size++;
    } while (ch != EOF);
    //Seek file back to first position
    fseek(file, 0L, SEEK_SET);
    //Crate array with calculated size
    int data[size] ;
    //Create arrray for 2-Way sorting, 2*n+1
    int sort_data[2*size+1];


    //Read data from File
    fscanf (file, "%d", &data[0]);
    int i = 1;
    while (!feof (file))
    {

          fscanf (file, "%d", &data[i]);
          i++;
    }
    fclose (file);

    //set all data in 2Way Sort Array to 0
    for(i=0 ; i< 2*size ; i++){
        sort_data[i] = 0;
    }

    /*Start of 2-Way Quick sort*/

    //Place first element at middle position
    sort_data[size] = data[0];

    for(i = 1 ; i < size ; i++){
        //find right position to insert
        int idx = size;
        //given element less than middle element so insert left side
        if(data[i] <= sort_data[size]){

            while(!(data[i] <= sort_data[idx]) &&
                  sort_data[idx] != 0 && idx >=0)
            {
                 idx--;
            }
        }

        //given element greater than middle element so insert right side
        if(data[i] > sort_data[size]){
            //find right position to insert

            while(!(data[i] <= sort_data[idx]) &&
                  sort_data[idx] != 0 && idx < 2*size)
            {
                 idx++;
            }
        }
        //IF found position is free , value at position is 0, insert there
        if(sort_data[idx] == 0){
           sort_data[idx] = data[i];
        }
         //IF found position is not free
        else{

           int next_r_pos,next_l_pos = idx;
            //found next free position right side
           while(sort_data[next_r_pos] != 0 && next_r_pos <= 2*size ){
               next_r_pos++;
           }
           //found next free position right side
          while(sort_data[next_l_pos] != 0 && next_l_pos >=0 ){
              next_l_pos--;
          }
          int rshift = next_r_pos - idx;
          int lshift = idx- next_l_pos;
          //right side shifting is more, so shift left side
          if(rshift > lshift){
              while(lshift <= idx){
                  sort_data[lshift] = sort_data[lshift+1];
                  lshift++;
              }
              sort_data[idx] = data[i];
          }
          //left side shifting is more, so shift right side
          else{
              while(rshift >= idx){
                  sort_data[rshift] = sort_data[rshift-1];
                  rshift--;
              }
              sort_data[idx] = data[i];
          }
        }
    }
    printf("Completed");
    return 0;
}


