#include <iostream>

std::string colors[] = {
    "\033[31m", // Red
    "\033[32m", // Green
    "\033[33m", // Yellow
    "\033[34m", // Blue
    "\033[35m", // Magenta
    "\033[36m", // Cyan
    "\033[37m", // White
    "\033[90m", // Bright Black (Gray)
    "\033[91m", // Bright Red
    "\033[92m", // Bright Green
    "\033[93m", // Bright Yellow
    "\033[94m", // Bright Blue
    "\033[95m", // Bright Magenta
    "\033[96m", // Bright Cyan
    "\033[97m", // Bright White
    "\033[0m"   // Reset
};

void printSplash(){
        std::cout << R"(  
        __  __                  _    __                              
       / / / /___ _____  ____  (_)  / /_____ _      _____  __________
      / /_/ / __ `/ __ \/ __ \/ /  / __/ __ \ | /| / / _ \/ ___/ ___/
     / __  / /_/ / / / / /_/ / /  / /_/ /_/ / |/ |/ /  __/ /  (__  ) 
    /_/ /_/\__,_/_/ /_/\____/_/   \__/\____/|__/|__/\___/_/  /____/ 
    )" << std::endl;
}

class c_ring{
    public: 
        int size;
        std::string color;

    void printRing(){
        std::cout << color; 
        for(int i = 0; i < size; i++){
            std::cout << "x";
        }
        std::cout << colors[15];
    }
};

class c_pilar{
    public:
        int heigth;
        int width;
        c_ring* ringsOn[8] = {nullptr};
    
    void printPilar(){
        for (int i = 0; i < 8; ++i) {
            if (ringsOn[i]) {
                ringsOn[i]->printRing();
            } else {
                std::cout << "null";
            }
            std::cout << " ";
        }
    }
    int getTopRingIndex(){
        int ring = 0;
        for (int i = 7; i >= 0; i--) {
            if (ringsOn[i] != nullptr) {
                ring = i;
                break;
            }  
        }
        return ring;
    }
};

bool ringsCreate(int amount, c_ring rings[]){
    if(amount < 3 || amount > 7){
        std::cout << "Invalid size for the amount of rings; Try between 3 and 7 inclusive";
        return false;
    }
    for(int i = 0; i < amount; i++){
        c_ring ring;
        ring.size = 3 + 2 * i;
        ring.color = colors[i];
        rings[i] = ring;
    }
    return true;
}

bool pilarsCreate(int p_amount, int r_amount, int widestRing, c_pilar pilars[]){
    if(p_amount < 3 || p_amount > 5){
        std::cout << "Invalid size for the amount of pilars; Try between 3 and 5 inclusive";
        return false;
    }
    for(int i = 0; i < p_amount; i++){
        c_pilar pilar;
        pilar.heigth = r_amount + 1;
        pilar.width = widestRing + 1;
        pilars[i] = pilar;
    }
    return true;
}

// void pilarsPrint2(int amount, c_pilar pilars[]){
//     for(int i = 0; i < amount; i++){
//         std::cout << i << ". Pillar has these rings: ";
//         pilars[i].printPilar();
//         std::cout << "\n";
//     }
//     std::cout << "\n";
// }
void spacerPrint(int length){
    for(int i = 0; i < length; i++){
        std::cout << " ";
    }
}
void pilarsPrint(int amount, c_pilar pilars[], int widestRing) {
    std::cout << "\n";
    for (int ring = 7; ring >= 0; ring--) {
        for (int pillar = 0; pillar < amount; pillar++) {
            if (pilars[pillar].ringsOn[ring] != nullptr) {
                int ringSize = pilars[pillar].ringsOn[ring]->size/2;
                int spacerSize = widestRing/2 - ringSize;
                spacerPrint(spacerSize);
                pilars[pillar].ringsOn[ring]->printRing();
                spacerPrint(spacerSize+1);
            } else {
                spacerPrint(widestRing/2);
                std::cout << "|\t"; // empty space for visual alignment
                spacerPrint(widestRing/2);
            }
            std::cout << "\t"; // space between pillars
        }
        std::cout << "\n"; // move to next row (ring level)
    }
    std::cout << "\n";
}
void printNumbers(int amount, int widestRing){
    for(int i = 1; i <= amount; i++){
        spacerPrint(widestRing/2);
        std::cout << i << "\t\t";
    }
    std::cout << "\n";
}

void printArrows(int amount, int widestRing){
    for(int i = 0; i < amount; i++){
        spacerPrint(widestRing/2);
        std::cout << "↓\t\t";
    }
}

void ringsPrint(int amount, c_ring rings[]){
    for(int i = 0; i < amount; i++){
        for(int j = amount - i - 1; j > 0; j--){
            std::cout << " ";
        }
        rings[i].printRing();
        std::cout << "\n";
    }
    std::cout << "\n";
}

void initRings(c_ring rings[], int amountRings, c_pilar& firstpillar){ //this function assigns the created rings to the first pilar
    for(int i = 0; i < amountRings; i++){
        firstpillar.ringsOn[i] = &rings[amountRings - i - 1];
    }
}

void moveRing(c_pilar pilars[], int i_pilarFrom, int i_pilarTo) {
    if(i_pilarFrom==i_pilarTo){
        return;
    }
    c_pilar& from = pilars[i_pilarFrom];
    c_pilar& to = pilars[i_pilarTo];
    
    int fromTop = from.getTopRingIndex();
    if (from.ringsOn[fromTop] == nullptr) {
        std::cout << "No ring to move.\n";
        return;
    }
    c_ring* ringToMove = from.ringsOn[fromTop];

    int toTop = -1;
    toTop = to.getTopRingIndex();
    if(to.ringsOn[toTop] != nullptr){
        toTop++;
    }
    to.ringsOn[toTop] = ringToMove;
    from.ringsOn[fromTop] = nullptr;
}

int main(){
    std::cout << "\033[2J\033[H";
    printSplash();
    int amountRings;
    int amountPilars;
    std::cout << "Input the amount of rings (3-7): ";
    std::cin >> amountRings;

    c_ring rings[amountRings];
    if(!ringsCreate(amountRings, rings)){
        return 0;
    }
    int widestRing = rings[amountRings-1].size;
    // Test
    // std::cout << "Biggest ring char amount: [" << widestRing << "] .\n"; // amount of chars to draw 
    // std::cout << "Available rings: \n";
    // ringsPrint(amountRings, rings);

    std::cout << "Input the amount of pilars (3-5): ";
    std::cin >> amountPilars;
    c_pilar pilars[amountPilars];
    pilarsCreate(amountPilars, amountRings, widestRing, pilars);
    initRings(rings, amountRings, pilars[0]);
    // pilarsPrint(amountPilars, pilars, widestRing);
    // moveRing(pilars, 0, 2);
    // pilarsPrint(amountPilars, pilars, widestRing);
    while(true){
        std::cout << "\033[2J\033[H";
        printSplash();
        printNumbers(amountPilars, widestRing);
        pilarsPrint(amountPilars, pilars, widestRing);
        int from;
        int to;
        std::cout << "Where do you want to take the ring from?";
        std::cin >> from;
        std::cout << "\033[2J\033[H";
        printSplash();
        printNumbers(amountPilars, widestRing);
        printArrows(amountPilars, widestRing);
        pilarsPrint(amountPilars, pilars, widestRing);
        std::cout << "Where do you put the ring to?";
        std::cin >> to;
        moveRing(pilars, from - 1, to - 1);
        pilarsPrint(amountPilars, pilars, widestRing);
    }
}
