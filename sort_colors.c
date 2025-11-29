
void sortColors(int* nums, int numsSize) {
    int redCount = 0; int whiteCount = 0; 
    for (int i = 0; i < numsSize; i++){
        switch(nums[i]){
        case 0:
            redCount++;
            break;
        case 1:
            whiteCount++;
            break;
        default:
            break;
        } 
    }
    for (int i = 0; i < numsSize; i++){
        if (redCount == 0 && whiteCount == 0){
            nums[i] = 2;
        } else if (redCount == 0 && whiteCount != 0){
            nums[i] = 1;
            whiteCount--;
        }else {
            nums[i] = 0;
            redCount--;
        }
    }
}

int main(int argc, char *argv[]){

    
}

